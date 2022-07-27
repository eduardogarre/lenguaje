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
#include "herramientas.hpp"
#include "ñ/ñ.hpp"
#include "promotor.hpp"


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

	Ñ::Léxico léxico;
	Ñ::Sintaxis sintaxis;

	if (cfg.HABLADOR)
	{
		std::cout << "ANALIZANDO LEXICO" << std::endl;
	}

	lexemas = léxico.analiza(código, entorno);

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
	Ñ::EntornoConstrucción *entorno = Ñ::preparaEntornoConstrucción(cfg);

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

	std::string archivoDestino = cfg.nombreArchivoDestino + cfg.extensión;

	std::string carpeta = obténCarpetaInstalación() + "/";
	std::string bibliotecaEstándar = "bibñ.lib";
	std::string lugar_de_inicio = "__lugar_de_inicio";

	Ñ::ConfiguraciónEnlazador cfgEnlazador;

	cfgEnlazador.ponArchivoDestino(archivoDestino);
	cfgEnlazador.ponCarpetaBibliotecaEstándar(carpeta);

	std::vector<const char *> argumentos;
	std::string opción_llvm = "";
	char *texto = nullptr;

	opción_llvm = "enlazador";
	texto = (char *)malloc(opción_llvm.size() + 1);
	strcpy(texto, opción_llvm.c_str());
	argumentos.push_back(texto);

	opción_llvm = carpeta + bibliotecaEstándar;
	texto = (char *)malloc(opción_llvm.size() + 1);
	strcpy(texto, opción_llvm.c_str());
	argumentos.push_back(texto);

	for (std::string archivo : cfg.archivos)
	{
		std::string nombreMódulo = Ñ::creaNombreMódulo(archivo) + ".o ";
		cfgEnlazador.ponArchivoObjeto(nombreMódulo);
		opción_llvm = Ñ::creaNombreMódulo(archivo) + ".o ";
		texto = (char *)malloc(opción_llvm.size() + 1);
		strcpy(texto, opción_llvm.c_str());
		argumentos.push_back(texto);
	}

	cfgEnlazador.ponLugarInicio(lugar_de_inicio);

	opción_llvm = "/entry:" + lugar_de_inicio;
	texto = (char *)malloc(opción_llvm.size() + 1);
	strcpy(texto, opción_llvm.c_str());
	argumentos.push_back(texto);

	opción_llvm = "/nodefaultlib";
	texto = (char *)malloc(opción_llvm.size() + 1);
	strcpy(texto, opción_llvm.c_str());
	argumentos.push_back(texto);

	cfgEnlazador.ponSubsistema("console");

	opción_llvm = "/subsystem:console";
	texto = (char *)malloc(opción_llvm.size() + 1);
	strcpy(texto, opción_llvm.c_str());
	argumentos.push_back(texto);

	opción_llvm = "/out:" + archivoDestino;
	texto = (char *)malloc(opción_llvm.size() + 1);
	strcpy(texto, opción_llvm.c_str());
	argumentos.push_back(texto);

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

	std::vector<const char *> argumentos2;

	argumentos2 = cfgEnlazador.generaArgumentos();

	if (cfg.HABLADOR)
	{
		std::cout << std::endl << std::to_string(argumentos2.size()) << " argumentos2 para LLD" << std::endl;

		for (int i = 0; i < argumentos2.size(); i++)
		{
			std::cout << "arg " << std::to_string(i) << ": ";
			printf(argumentos2[i]);
			printf("\n");
		}
	}

	int resultado = Ñ::enlaza(argumentos2);

	for (int i = 0; i < argumentos.size(); i++)
	{
		free((void *)(argumentos[i]));
	}

	return resultado;
}