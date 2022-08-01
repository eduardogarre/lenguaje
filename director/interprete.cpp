/*
SPDX-License-Identifier: MPL-2.0-no-copyleft-exception

This Source Code Form is subject to the terms of the Mozilla Public License, v.
2.0. If a copy of the MPL was not distributed with this file, You can obtain one
at http://mozilla.org/MPL/2.0/.

This Source Code Form is "Incompatible With Secondary Licenses", as defined by
the Mozilla Public License, v. 2.0.

Copyright © 2021 Eduardo Garre Muñoz
*/

#include <fstream>
#include <iostream>
#include <string>

#if defined(WIN32) || defined(WIN64)
#include <Windows.h>
#endif

#include "director.hpp"
#include "herramientas.hpp"
#include "interprete.hpp"

namespace Director
{
#if defined(WIN32) || defined(WIN64)
	// Función basada en el código encontrado en https://github.com/skeeto/scratch/blob/master/misc/read-password-w32.c
	// Código distribuido bajo el dominio público en el momento de la lectura.
	static int terminal_windows(char *esp8, int len, char *term)
	{
		// Recursos que después limpiaremos
		int nBytesLeídos = 0;
		DWORD orig = 0;
		WCHAR *esp16 = 0;
		SIZE_T esp16_long = 0;
		HANDLE pe, ps = INVALID_HANDLE_VALUE; // Punteros de E/S

		// Preparo el puntero a la entrada de la consola
		DWORD acceso = GENERIC_READ | GENERIC_WRITE;
		pe = CreateFileA("CONIN$", acceso, 0, 0, OPEN_EXISTING, 0, 0);
		if (!GetConsoleMode(pe, &orig))
		{
			goto hecho;
		}
		DWORD modo = orig;
		modo |= ENABLE_PROCESSED_INPUT;
		modo |= ENABLE_LINE_INPUT;
		modo |= ENABLE_ECHO_INPUT;
		if (!SetConsoleMode(pe, modo))
		{
			goto hecho;
		}

		// Preparo el puntero a la salida de la consola
		ps = CreateFileA("CONOUT$", GENERIC_WRITE, 0, 0, OPEN_EXISTING, 0, 0);
		if (!WriteConsoleA(ps, term, strlen(term), 0, 0))
		{
			goto hecho;
		}

		// Reservo espacio para tantos caracteres anchos como mide la salida
		esp16_long = (len - 1 + 2) * sizeof(WCHAR);
		esp16 = (WCHAR *)HeapAlloc(GetProcessHeap(), 0, esp16_long);
		if (!esp16)
		{
			goto hecho;
		}

		// Leo y convierto a UTF-8
		DWORD nleídos;
		if (!ReadConsoleW(pe, esp16, len - 1 + 2, &nleídos, 0))
		{
			goto hecho;
		}
		if (nleídos < 2)
		{
			goto hecho;
		}
		if (esp16[nleídos - 2] != '\r' || esp16[nleídos - 1] != '\n')
		{
			goto hecho;
		}

		esp16[nleídos - 2] = 0; // trunco "\r\n"
		nBytesLeídos = WideCharToMultiByte(CP_UTF8, 0, esp16, -1, esp8, len, 0, 0);

	hecho:
		if (esp16)
		{
			SecureZeroMemory(esp16, esp16_long);
			HeapFree(GetProcessHeap(), 0, esp16);
		}

		// Aprovecho que las operaciones sobre los INVALID_HANDLE_VALUE son no-op's
		SetConsoleMode(pe, orig);
		CloseHandle(ps);
		CloseHandle(pe);
		return nBytesLeídos;
	}
#endif

	std::string esperaComando()
	{
		std::string comando;
		std::string term = "> ";

#if defined(WIN32) || defined(WIN64)
		char espacio[1024];
		int len = terminal_windows(espacio, sizeof(espacio), (char *)term.c_str());
		if (len > 0)
		{
			comando = espacio;
		}
#elif defined(UNIX)
		std::cout << term;
		std::getline(std::cin, comando);
#endif

		return comando;
	}

	void interpretaComando(std::string comando, Ñ::TablaSímbolos *tablaSímbolos, Ñ::EntornoConstrucción *entorno)
	{
		Ñ::Resultado resultado;

		std::vector<Ñ::Lexema *> lexemas;
		Ñ::Nodo *nodos;

		Ñ::Léxico léxico;
		Ñ::Sintaxis sintaxis;

		lexemas = léxico.analiza(comando, entorno);

		if (lexemas.empty())
		{
			Ñ::errorConsola(u8"Error durante el análisis léxico, comando incorrecto.");
			return;
		}

		resultado = sintaxis.analiza(lexemas, "");
		if (resultado.error())
		{
			Ñ::errorConsola(resultado.mensaje());
			muestraLexemas(lexemas);
			return;
		}

		nodos = resultado.nodo();

		Ñ::Resultado rSemántico = Ñ::analizaSemántica(nodos, tablaSímbolos);

		if (rSemántico.error())
		{
			std::cout << rSemántico.mensaje() << std::endl;
			muestraNodos(nodos, tablaSímbolos);
			return;
		}

		Ñ::ResultadoLlvm rConstrucción = Ñ::creaRepresentaciónIntermedia(nodos, entorno, Ñ::CategoríaNodo::NODO_EXPRESIÓN);
		if (rConstrucción.error())
		{
			std::cout << rConstrucción.mensaje() << std::endl;
			return;
		}

		resultado = Ñ::ejecutaMóduloJAT(rConstrucción.módulo(), entorno);

		if (resultado.error())
		{
			Ñ::errorConsola(resultado.mensaje());
			return;
		}

		for (auto l : lexemas)
		{
			delete l;
		}
		lexemas.clear();
		delete nodos;
	}

	int interpreta(Ñ::Entorno::Configuración cfg)
	{
		Ñ::ResultadoLlvm resultadoLlvm;

		Ñ::TablaSímbolos *tablaSímbolos = new Ñ::TablaSímbolos;

		Ñ::EntornoConstrucción *entorno = Ñ::Entorno::preparaEntornoConstrucción(cfg);

		Ñ::Entorno::preparaJAT(entorno);

		std::string ruta_biblioteca_estándar = obténCarpetaInstalación() + "/" + biblioteca_estándar;

		if (cfg.archivos.size() != 1)
		{
			std::cout << "Ruta a la biblioteca estándar: '" << ruta_biblioteca_estándar << "'" << std::endl;
			std::cout << "Error, debería haber recibido 1 archivo para interpretar." << std::endl;
		}

		std::string archivo = cfg.archivos[0];
		if (cfg.HABLADOR)
		{
			std::cout << "Interpretando '" << archivo << "'" << std::endl;
		}

		Ñ::Entorno::ponArchivoActual(entorno, archivo);

		std::string código = "";

		std::string nombreMódulo = Ñ::creaNombreMódulo(archivo);

		std::ifstream parchivo(archivo);

		if (cfg.HABLADOR)
		{
			std::cout << "LEYENDO EL CODIGO DEL ARCHIVO" << std::endl;
		}

		std::string comando;
		while (std::getline(parchivo, comando))
		{
			if (cfg.HABLADOR)
			{
				std::cout << "comando: '" << comando << "'" << std::endl;
				std::cout << "Tabla de Símbolos:" << std::endl;
				tablaSímbolos->muestra();
			}

			if (comando.size() == 0)
			{
				continue;
			}
			else if (comando == "sal")
			{
				break;
			}
			interpretaComando(comando, tablaSímbolos, entorno);
		}

		delete tablaSímbolos;

		return 0;
	}

	int interpretaEnLínea(Ñ::Entorno::Configuración cfg)
	{
		Ñ::TablaSímbolos *tablaSímbolos = new Ñ::TablaSímbolos;

		Ñ::EntornoConstrucción *entorno = Ñ::Entorno::preparaEntornoConstrucción(cfg);

		Ñ::Entorno::preparaJAT(entorno);

		std::string ruta_biblioteca_estándar = obténCarpetaInstalación() + "/" + biblioteca_estándar;

		if (cfg.HABLADOR)
		{
			std::cout << "Ruta a la biblioteca estándar: '" << ruta_biblioteca_estándar << "'" << std::endl;
		}

		EJECUTA_INTÉRPRETE = true;

		while (EJECUTA_INTÉRPRETE)
		{
			std::string comando = esperaComando();

			if (cfg.HABLADOR)
			{
				std::cout << "comando: '" << comando << "'" << std::endl;
				std::cout << "Tabla de Símbolos:" << std::endl;
				tablaSímbolos->muestra();
			}

			if (comando.size() == 0)
			{
				continue;
			}
			else if (comando == "sal")
			{
				break;
			}
			interpretaComando(comando, tablaSímbolos, entorno);
		}

		delete tablaSímbolos;

		return 0;
	}
}