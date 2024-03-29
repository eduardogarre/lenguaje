/*
SPDX-License-Identifier: MPL-2.0-no-copyleft-exception

This Source Code Form is subject to the terms of the Mozilla Public License, v.
2.0. If a copy of the MPL was not distributed with this file, You can obtain one
at http://mozilla.org/MPL/2.0/.

This Source Code Form is "Incompatible With Secondary Licenses", as defined by
the Mozilla Public License, v. 2.0.

Copyright © 2021 Eduardo Garre Muñoz
*/

#include <iostream>
#include <string>
#include <vector>

#include "consola.hpp"
#include "director.hpp"
#include "herramientas.hpp"
#include "ñ/ñ.hpp"
#include "constructor.hpp"

Ñ::ResultadoLlvm construyeArchivo(std::string archivo, Ñ::EntornoConstrucción *entorno, Ñ::Entorno::Configuración cfg)
{
	Ñ::ResultadoLlvm resultadoLlvm;

	std::string código = "";

	std::string nombreMódulo = Ñ::creaNombreMódulo(archivo);

	if (cfg.HABLADOR)
	{
		std::cout << "LEYENDO EL CODIGO DEL ARCHIVO" << std::endl;
	}

	try
	{
		código = leeArchivo(archivo);
	}
	catch (std::exception &e)
	{
		resultadoLlvm.error("No puedo abrir el archivo.");
		return resultadoLlvm;
	}

	std::vector<Ñ::Lexema *> lexemas;
	Ñ::Nodo *nodos;
	Ñ::Resultado resultado;

	Ñ::Sintaxis sintaxis;

	if (cfg.HABLADOR)
	{
		std::cout << "ANALIZANDO LEXICO" << std::endl;
	}

	lexemas = Ñ::analizaLéxico(código, entorno);

	if (cfg.HABLADOR)
	{
		Ñ::muestraLexemas(lexemas);
	}

	if (cfg.HABLADOR)
	{
		std::cout << "ANALIZANDO SINTAXIS" << std::endl;
	}

	resultado = sintaxis.analiza(lexemas, nombreMódulo);

	if (resultado.error())
	{
		for (auto l : lexemas)
		{
			delete l;
		}
		lexemas.clear();

		resultadoLlvm.error(resultado.mensaje());
		resultadoLlvm.posición(resultado.posición());
		return resultadoLlvm;
	}

	nodos = resultado.nodo();

	if (cfg.HABLADOR)
	{
		muestraNodos(nodos);
	}

	if (cfg.HABLADOR)
	{
		std::cout << "ANALIZANDO SEMANTICA" << std::endl;
	}

	Ñ::TablaSímbolos *tablaSímbolos = new Ñ::TablaSímbolos;
	Ñ::Resultado rSemántico = Ñ::analizaSemántica(nodos, tablaSímbolos);

	if (cfg.HABLADOR)
	{
		muestraNodos(nodos, tablaSímbolos);
	}

	delete tablaSímbolos;

	if (rSemántico.error())
	{
		for (auto l : lexemas)
		{
			delete l;
		}
		lexemas.clear();
		delete nodos;

		resultadoLlvm.error(rSemántico.mensaje());
		resultadoLlvm.posición(rSemántico.posición());
		return resultadoLlvm;
	}

	if (cfg.HABLADOR)
	{
		std::cout << "CREANDO MODULO" << std::endl;
	}

	resultadoLlvm = Ñ::creaRepresentaciónIntermedia(nodos, entorno);

	if (resultadoLlvm.error())
	{
		return resultadoLlvm;
	}

	resultado = emiteArchivoObjeto(resultadoLlvm.módulo(), entorno);

	if (resultado.error())
	{
		resultadoLlvm.error("[" + archivo + "] " + resultado.mensaje());
		return resultadoLlvm;
	}
	else
	{
		resultadoLlvm.éxito();
	}

	for (auto l : lexemas)
	{
		delete l;
	}
	lexemas.clear();
	delete nodos;

	return resultadoLlvm;
}

int Director::compila(Ñ::Entorno::Configuración cfg)
{
	Ñ::EntornoConstrucción *entorno = Ñ::Entorno::preparaEntornoConstrucción(cfg);

	if (!entorno)
	{
		return -1;
	}

	for (std::string archivo : cfg.archivos)
	{
		if (cfg.HABLADOR)
		{
			std::cout << "Construyendo '" << archivo << "'" << std::endl;
		}

		Ñ::Entorno::ponArchivoActual(entorno, archivo);
		Ñ::ResultadoLlvm resultado = construyeArchivo(archivo, entorno, cfg);
		if (resultado.error())
		{
			Director::escribeError(resultado.mensaje(), archivo, resultado.posición());

			return -1;
		}
	}

	Ñ::ConfiguraciónEnlazador cfgEnlazador;

	cfgEnlazador.ponArchivoDestino(cfg.nombreArchivoDestino + cfg.extensión);
	cfgEnlazador.ponNombreBibliotecaEstándar(biblioteca_estándar);
	cfgEnlazador.ponCarpetaBibliotecaEstándar(obténCarpetaInstalación() + "/");
	cfgEnlazador.ponLugarInicio(lugar_de_inicio);
	cfgEnlazador.ponSubsistema("console");

	for (std::string archivo : cfg.archivos)
	{
		std::string nombreMódulo = Ñ::creaNombreMódulo(archivo) + ".o";
		cfgEnlazador.ponArchivoObjeto(nombreMódulo);
	}

	std::vector<const char *> argumentos;
	argumentos = cfgEnlazador.generaArgumentos();

	if (cfg.HABLADOR)
	{
		std::cout << std::to_string(argumentos.size()) << " argumentos para LLD" << std::endl;

		for (int i = 0; i < argumentos.size(); i++)
		{
			std::cout << "arg " << std::to_string(i) << ": ";
			printf(argumentos[i]);
			printf("\n");
		}
	}

	int resultado = Ñ::enlaza(argumentos);

	for (int i = 0; i < argumentos.size(); i++)
	{
		free((void *)(argumentos[i]));
	}

	return resultado;
}