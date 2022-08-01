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
#include <map>

#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/Support/Host.h"
#include "llvm/Support/FileSystem.h"
#include "llvm/Support/TargetRegistry.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Target/TargetMachine.h"

#include "entorno.hpp"
#include "entorno_int.hpp"
#include "justoatiempo.hpp"

namespace Ñ
{
	extern class ConstructorJAT;

	void Entorno::ponArchivoActual(Ñ::EntornoConstrucción *entorno, std::string archivo)
	{
		entorno->archivoActual = archivo;
	}

	std::string Entorno::leeArchivoActual(Ñ::EntornoConstrucción *entorno, std::string archivo)
	{
		return entorno->archivoActual;
	}

	Ñ::EntornoConstrucción *Entorno::preparaEntornoConstrucción(Entorno::Configuración cfg)
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

		return entorno;
	}

	void Entorno::preparaJAT(Ñ::EntornoConstrucción *entorno)
	{
		if (!entorno->jat)
		{
			// Si es la primera ejecución, todavía no hemos creado el JAT
			entorno->jat = Ñ::ConstructorJAT::Crea();
		}
	}
}