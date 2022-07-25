/*
SPDX-License-Identifier: MPL-2.0-no-copyleft-exception

This Source Code Form is subject to the terms of the Mozilla Public License, v.
2.0. If a copy of the MPL was not distributed with this file, You can obtain one
at http://mozilla.org/MPL/2.0/.

This Source Code Form is "Incompatible With Secondary Licenses", as defined by
the Mozilla Public License, v. 2.0.

Copyright © 2021 Eduardo Garre Muñoz
*/

#include <filesystem>
#include <iostream>

#include "lld/Common/Driver.h"
#include "llvm/Support/Host.h"
#include "llvm/Support/FileSystem.h"
#include "llvm/Support/TargetRegistry.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Target/TargetMachine.h"

#include "constructor_int.hpp"
#include "entorno_int.hpp"
#include "resultado.hpp"

std::string Ñ::creaNombreMódulo(std::string archivo)
{
	std::filesystem::path p = archivo;
	std::string antes = p.string();
	std::string después = p.stem().string();

	return después;
}

Ñ::Resultado Ñ::emiteArchivoObjeto(llvm::Module *móduloLlvm, Ñ::EntornoConstrucción *entorno)
{
	Ñ::Resultado resultado;

	móduloLlvm->setDataLayout(entorno->máquinaDestino->createDataLayout());
	móduloLlvm->setTargetTriple(entorno->tripleteDestino);

	if (entorno->HABLADOR)
	{
		std::cout << std::endl
				  << "Archivo de representación intermedia:" << std::endl
				  << std::endl;
		móduloLlvm->print(llvm::outs(), nullptr);
	}

	std::string nombreMódulo = creaNombreMódulo(entorno->archivoActual);

	std::string nombreArchivoDestino = nombreMódulo + ".o";
	std::error_code códigoError;
	llvm::raw_fd_ostream archivoDestino(nombreArchivoDestino, códigoError, llvm::sys::fs::OF_None);

	if (códigoError)
	{
		resultado.error("No he podido abrir el archivo: " + códigoError.message());
		return resultado;
	}

	llvm::legacy::PassManager paseDeCódigoObjeto;
	auto tipoArchivo = llvm::CGFT_ObjectFile;

	if (entorno->máquinaDestino->addPassesToEmitFile(paseDeCódigoObjeto, archivoDestino, nullptr, tipoArchivo))
	{
		resultado.error("No he podido emitir un archivo de este tipo");
		return resultado;
	}

	paseDeCódigoObjeto.run(*móduloLlvm);
	archivoDestino.flush();

	if (entorno->HABLADOR)
	{
		std::cout << "He construido el archivo '" + nombreArchivoDestino + "'." << std::endl;
	}

	resultado.éxito();
	return resultado;
}