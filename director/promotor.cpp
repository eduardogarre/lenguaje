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

#include "lld/Common/Driver.h"
#include "llvm/Support/Host.h"
#include "llvm/Support/FileSystem.h"
#include "llvm/Support/TargetRegistry.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Target/TargetMachine.h"

#include "configuracion.hpp"
#include "consola.hpp"
#include "herramientas.hpp"
#include "ñ/ñ.hpp"
#include "promotor.hpp"

std::string creaNombreMódulo(std::string archivo)
{
	std::filesystem::path p = archivo;
	std::string antes = p.string();
	std::string después = p.stem().string();
	// std::cout << "Antes: " << antes << std::endl;
	// std::cout << "Después: " << después << std::endl;

	return después;
}

Ñ::ResultadoLlvm construyeArchivo(std::string archivo, Ñ::EntornoConstrucción *entorno)
{
	Ñ::ResultadoLlvm resultadoLlvm;

	std::string código = "";

	std::string nombreMódulo = creaNombreMódulo(archivo);

	if (entorno->HABLADOR)
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

	if (entorno->HABLADOR)
	{
		std::cout << "ANALIZANDO LEXICO" << std::endl;
	}

	lexemas = léxico.analiza(código, entorno);

	if (entorno->HABLADOR)
	{
		Ñ::muestraLexemas(lexemas);
	}

	/*
	if(lexemas.size() <= 1)
	{
		Ñ::errorConsola(u8"El análisis léxico no encontró código.");

		for(auto l : lexemas)
		{
			delete l;
		}
		lexemas.clear();

		resultado.éxito();
		return resultado;
	}
	*/

	if (entorno->HABLADOR)
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

	if (entorno->HABLADOR)
	{
		muestraNodos(nodos);
	}

	if (entorno->HABLADOR)
	{
		std::cout << "ANALIZANDO SEMANTICA" << std::endl;
	}

	Ñ::TablaSímbolos *tablaSímbolos = new Ñ::TablaSímbolos;
	Ñ::Resultado rSemántico = Ñ::analizaSemántica(nodos, tablaSímbolos);

	if (entorno->HABLADOR)
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

	if (entorno->HABLADOR)
	{
		std::cout << "CREANDO MODULO" << std::endl;
	}

	resultadoLlvm = Ñ::creaRepresentaciónIntermedia(nodos, entorno);

	for (auto l : lexemas)
	{
		delete l;
	}
	lexemas.clear();
	delete nodos;

	if (resultadoLlvm.error())
	{
		return resultadoLlvm;
	}

	resultadoLlvm.éxito();
	return resultadoLlvm;
}

Ñ::EntornoConstrucción *preparaEntornoConstrucción(Director::Configuración cfg)
{
	Ñ::EntornoConstrucción *entorno = new Ñ::EntornoConstrucción;
	entorno->optimización = cfg.optimización;

	llvm::InitializeNativeTarget();
	llvm::InitializeNativeTargetAsmParser();
	llvm::InitializeNativeTargetAsmPrinter();

	entorno->tripleteDestino = llvm::sys::getDefaultTargetTriple();

	std::string error;
	entorno->destino = llvm::TargetRegistry::lookupTarget(entorno->tripleteDestino, error);

	if (!entorno->destino)
	{
		return nullptr;
	}

	if (cfg.HABLADOR)
	{
		entorno->HABLADOR = true;

		std::cout << "Construiré ";
		std::cout << "'" << cfg.nombreArchivoDestino << cfg.extensión << "'";

		std::cout << ", empleando";

		for (std::string archivo : cfg.archivos)
		{
			std::cout << " " << archivo;
		}

		std::cout << std::endl
				  << std::endl;

		std::cout << "Tripleta de Destino: " << entorno->tripleteDestino << std::endl
				  << std::endl;
	}

	std::string procesador = "x86-64";
	std::string características = "";

	llvm::TargetOptions opciones;
	auto modeloReordenamiento = llvm::Optional<llvm::Reloc::Model>();
	entorno->máquinaDestino = entorno->destino->createTargetMachine(entorno->tripleteDestino, procesador, características, opciones, modeloReordenamiento);

	// std::cout << "Preparando construcción con LLVM" << std::endl << std::endl;

	return entorno;
}

int Director::compila(Director::Configuración cfg)
{

	for (std::string archivo : cfg.archivos)
	{
		Ñ::EntornoConstrucción *entorno = preparaEntornoConstrucción(cfg);

		if (!entorno)
		{
			return -1;
		}

		if (cfg.HABLADOR)
		{
			std::cout << "Construyendo '" << archivo << "'" << std::endl;
		}

		entorno->archivoActual = archivo;
		Ñ::ResultadoLlvm resultado = construyeArchivo(archivo, entorno);
		if (resultado.error())
		{
			Director::escribeError(resultado.mensaje(), archivo, resultado.posición());

			return -1;
		}

		llvm::Module *móduloLlvm = resultado.módulo();

		móduloLlvm->setDataLayout(entorno->máquinaDestino->createDataLayout());
		móduloLlvm->setTargetTriple(entorno->tripleteDestino);

		if (cfg.HABLADOR)
		{
			std::cout << std::endl
					  << "Archivo de representación intermedia:" << std::endl
					  << std::endl;
			móduloLlvm->print(llvm::outs(), nullptr);
		}

		std::string nombreMódulo = creaNombreMódulo(archivo);

		std::string nombreArchivoDestino = nombreMódulo + ".o";
		std::error_code códigoError;
		llvm::raw_fd_ostream archivoDestino(nombreArchivoDestino, códigoError, llvm::sys::fs::OF_None);

		if (códigoError)
		{
			std::cout << ("No he podido abrir el archivo: " + códigoError.message()) << std::endl;
			return -1;
		}

		llvm::legacy::PassManager paseDeCódigoObjeto;
		auto tipoArchivo = llvm::CGFT_ObjectFile;

		if (entorno->máquinaDestino->addPassesToEmitFile(paseDeCódigoObjeto, archivoDestino, nullptr, tipoArchivo))
		{
			std::cout << ("No he podido emitir un archivo de este tipo") << std::endl;
			return -1;
		}

		paseDeCódigoObjeto.run(*(móduloLlvm));
		archivoDestino.flush();

		if (cfg.HABLADOR)
		{
			std::cout << "He construido el archivo '" + nombreArchivoDestino + "'." << std::endl;
		}
	}

	std::string archivoDestino = cfg.nombreArchivoDestino + cfg.extensión;

	std::string carpeta = obténCarpetaInstalación() + "/";
	std::string bibliotecaEstándar = "bibñ.lib";
	std::string lugar_de_inicio = "__lugar_de_inicio";

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
		opción_llvm = creaNombreMódulo(archivo) + ".o ";
		texto = (char *)malloc(opción_llvm.size() + 1);
		strcpy(texto, opción_llvm.c_str());
		argumentos.push_back(texto);
	}

	opción_llvm = "/entry:" + lugar_de_inicio;
	texto = (char *)malloc(opción_llvm.size() + 1);
	strcpy(texto, opción_llvm.c_str());
	argumentos.push_back(texto);

	opción_llvm = "/nodefaultlib";
	texto = (char *)malloc(opción_llvm.size() + 1);
	strcpy(texto, opción_llvm.c_str());
	argumentos.push_back(texto);

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

	int resultado = lld::coff::link(argumentos, true, llvm::outs(), llvm::errs());

	for (int i = 0; i < argumentos.size(); i++)
	{
		free((void *)(argumentos[i]));
	}

	return resultado;
}