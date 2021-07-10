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
                llvm::DataLayout disposiciónDatos
            ) :
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

        static llvm::Expected<Ñ::ConstructorJAT*> Crea()
        {
            auto destinoConstrucciónJAT = llvm::orc::JITTargetMachineBuilder::detectHost();

            if(!destinoConstrucciónJAT)
            {
                return destinoConstrucciónJAT.takeError();
            }

            auto disposiciónDatos = destinoConstrucciónJAT->getDefaultDataLayoutForTarget();

            if(!disposiciónDatos)
            {
                return disposiciónDatos.takeError();
            }

            Ñ::ConstructorJAT* jat = new Ñ::ConstructorJAT(std::move(*destinoConstrucciónJAT), std::move(*disposiciónDatos));
        
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
            //sesiónEjecución.getJITDylibByName("<main>")->dump(llvm::errs());
            //std::cout << std::endl;
            return sesiónEjecución.lookup({sesiónEjecución.getJITDylibByName("<main>")}, traduceSímbolos(nombre.str()), llvm::orc::SymbolState::Resolved);
        }
    };
}