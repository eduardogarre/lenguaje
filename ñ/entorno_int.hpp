/*
SPDX-License-Identifier: MPL-2.0-no-copyleft-exception

This Source Code Form is subject to the terms of the Mozilla Public License, v.
2.0. If a copy of the MPL was not distributed with this file, You can obtain one
at http://mozilla.org/MPL/2.0/.

This Source Code Form is "Incompatible With Secondary Licenses", as defined by
the Mozilla Public License, v. 2.0.

Copyright © 2021 Eduardo Garre Muñoz
*/

#pragma once

#include <string>

#include <map>

#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/Target/TargetMachine.h"

#include "entorno.hpp"
namespace Ñ
{
    class EntornoConstrucción
    {
    public:
        bool HABLADOR = false;
        uint8_t optimización = 0;
        std::string archivoActual = "";
        llvm::LLVMContext contextoLlvm;
        llvm::legacy::FunctionPassManager *gestorPasesOptimización = nullptr;
        llvm::IRBuilder<> constructorLlvm;
        std::map<std::string, llvm::Type *> globales;
        std::string tripleteDestino;
        const llvm::Target *destino;
        llvm::TargetMachine *máquinaDestino;

        EntornoConstrucción() : constructorLlvm(contextoLlvm) {}
        ~EntornoConstrucción() {}
    };

    namespace Entorno
    {
        extern struct Configuración;

        Ñ::EntornoConstrucción *preparaEntornoConstrucción(Entorno::Configuración cfg);
        void ponArchivoActual(Ñ::EntornoConstrucción *entorno, std::string archivo);
        std::string leeArchivoActual(Ñ::EntornoConstrucción *entorno, std::string archivo);
    }
}