/*
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
        ConstructorJAT( llvm::orc::JITTargetMachineBuilder constructorJATMáquinaDestino,
                llvm::DataLayout disposiciónDatos,
                std::unique_ptr<llvm::orc::SelfExecutorProcessControl> controlEjecutorDelProceso
            ) :
                sesiónEjecución(std::move(controlEjecutorDelProceso)),
                capaObjeto(sesiónEjecución, []() { return std::make_unique<llvm::SectionMemoryManager>(); }),
                capaConstrucción(sesiónEjecución, capaObjeto, std::make_unique<llvm::orc::ConcurrentIRCompiler>(std::move(constructorJATMáquinaDestino))),
                disposiciónDatos(std::move(disposiciónDatos)),
                traduceSímbolos(sesiónEjecución, this->disposiciónDatos),
                contexto(std::make_unique<llvm::LLVMContext>()),
                tablaSímbolosPrincipal(this->sesiónEjecución.createBareJITDylib("<main>"))
        {
            // Por el momento, en Windows el gestor de COFF, RuntimeDyldCOFF, no informa correctamente del estado de los símbolos
            capaObjeto.setOverrideObjectFlagsWithResponsibilityFlags(true);
            llvm::orc::JITDylib* jitdylib = sesiónEjecución.getJITDylibByName("<main>");

            if(jitdylib)
            {
                jitdylib->addGenerator(llvm::cantFail(llvm::orc::DynamicLibrarySearchGenerator::GetForCurrentProcess(disposiciónDatos.getGlobalPrefix())));
            }
        }

        static Ñ::ConstructorJAT* Crea()
        {
            auto controlEjecutorDelProceso = llvm::orc::SelfExecutorProcessControl::Create();
            if(!controlEjecutorDelProceso)
            {
                controlEjecutorDelProceso.takeError();
                return nullptr;
            }

            auto destinoConstrucciónJAT = llvm::orc::JITTargetMachineBuilder::detectHost();
            if(!destinoConstrucciónJAT)
            {
                destinoConstrucciónJAT.takeError();
                return nullptr;
            }

            auto disposiciónDatos = destinoConstrucciónJAT->getDefaultDataLayoutForTarget();

            if(!disposiciónDatos)
            {
                disposiciónDatos.takeError();
                return nullptr;
            }

            Ñ::ConstructorJAT* jat = new Ñ::ConstructorJAT(std::move(*destinoConstrucciónJAT), std::move(*disposiciónDatos), std::move(*controlEjecutorDelProceso));
        
            return jat;
        }

        const llvm::DataLayout &leeDisposiciónDatos() const
        {
            return disposiciónDatos;
        }

        llvm::LLVMContext &leeContexto()
        {
            return *contexto.getContext();
        }

        void añadeMódulo(std::unique_ptr<llvm::Module> módulo)
        {
            llvm::orc::JITDylib* jitdylib = sesiónEjecución.getJITDylibByName("<main>");
            llvm::cantFail(capaConstrucción.add(*jitdylib, llvm::orc::ThreadSafeModule(std::move(módulo), contexto)));
        }

        llvm::Expected<llvm::JITEvaluatedSymbol> busca(llvm::StringRef nombre)
        {
            return sesiónEjecución.lookup({sesiónEjecución.getJITDylibByName("<main>")}, traduceSímbolos(nombre.str()), llvm::orc::SymbolState::Resolved);
        }

        void muestraSímbolos()
        {
            sesiónEjecución.getJITDylibByName("<main>")->dump(llvm::errs());
        }

        llvm::Error eliminaSímbolo(std::string nombre)
        {
            auto conjuntoSímbolos = new llvm::orc::SymbolStringPool();
            auto símbolo = sesiónEjecución.intern(nombre);

            auto res = tablaSímbolosPrincipal.remove({símbolo});

            return res;
        }
    };
}