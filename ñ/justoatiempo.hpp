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

#include "llvm/ADT/StringRef.h"
#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include "llvm/ExecutionEngine/JITSymbol.h"
#include "llvm/ExecutionEngine/Orc/CompileUtils.h"
#include "llvm/ExecutionEngine/Orc/Core.h"
#include "llvm/ExecutionEngine/Orc/ExecutionUtils.h"
#include "llvm/ExecutionEngine/Orc/ExecutorProcessControl.h"
#include "llvm/ExecutionEngine/Orc/IRCompileLayer.h"
#include "llvm/ExecutionEngine/Orc/JITTargetMachineBuilder.h"
#include "llvm/ExecutionEngine/Orc/LLJIT.h"
#include "llvm/ExecutionEngine/Orc/RTDyldObjectLinkingLayer.h"
#include "llvm/ExecutionEngine/Orc/ThreadSafeModule.h"
#include "llvm/ExecutionEngine/SectionMemoryManager.h"
#include "llvm/IR/DataLayout.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/Support/Error.h"
#include "llvm/Target/TargetMachine.h"

#include <iostream>
#include <memory>

namespace Ñ
{
    class ConstructorJAT // Justo A Tiempo
    {
    private:
        llvm::orc::ExecutionSession sesiónEjecución;
        llvm::orc::RTDyldObjectLinkingLayer capaObjeto;
        llvm::orc::IRCompileLayer capaConstrucción;
        llvm::DataLayout disposiciónDatos;
        llvm::orc::MangleAndInterner traduceSímbolos;
        llvm::orc::ThreadSafeContext contexto;
        llvm::orc::ThreadSafeModule móduloMultihilo;
        llvm::orc::JITDylib &tablaSímbolosPrincipal;

    public:
        ConstructorJAT(llvm::orc::JITTargetMachineBuilder constructorJATMáquinaDestino,
                       llvm::DataLayout disposiciónDatos,
                       std::unique_ptr<llvm::orc::SelfExecutorProcessControl> controlEjecutorDelProceso);

        static Ñ::ConstructorJAT *Crea();

        const llvm::DataLayout &leeDisposiciónDatos() const;

        llvm::LLVMContext &leeContexto();

        void añadeMódulo(std::unique_ptr<llvm::Module> módulo);

        llvm::Expected<llvm::JITEvaluatedSymbol> busca(llvm::StringRef nombre);

        void muestraSímbolos();

        llvm::Error eliminaSímbolo(std::string nombre);
    };
}