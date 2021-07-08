#pragma once

#include "llvm/ADT/StringRef.h"
#include "llvm/ExecutionEngine/JITSymbol.h"
#include "llvm/ExecutionEngine/Orc/CompileUtils.h"
#include "llvm/ExecutionEngine/Orc/Core.h"
#include "llvm/ExecutionEngine/Orc/ExecutionUtils.h"
#include "llvm/ExecutionEngine/Orc/ExecutorProcessControl.h"
#include "llvm/ExecutionEngine/Orc/IRCompileLayer.h"
#include "llvm/ExecutionEngine/Orc/JITTargetMachineBuilder.h"
#include "llvm/ExecutionEngine/Orc/RTDyldObjectLinkingLayer.h"
#include "llvm/ExecutionEngine/SectionMemoryManager.h"
#include "llvm/IR/DataLayout.h"
#include "llvm/IR/LLVMContext.h"
#include <memory>

namespace Ñ
{
    class ConstructorJAT // Justo A Tiempo
    {
    private:
        llvm::orc::ExecutorProcessControl* gestorEjecución;
        llvm::orc::ExecutionSession* sesiónEjecución;

        llvm::DataLayout disposiciónDatos;
        llvm::orc::MangleAndInterner denomina;

        llvm::orc::RTDyldObjectLinkingLayer capaObjeto;
        llvm::orc::IRCompileLayer capaConstrucción;

        llvm::orc::JITDylib &tablaSímbolosBibliotecaDinámica;

    public:
        ConstructorJAT( llvm::orc::ExecutorProcessControl* gestorEjecución,
                llvm::orc::ExecutionSession* sesiónEjecución,
                llvm::orc::JITTargetMachineBuilder constructorJATMáquinaDestino,
                llvm::DataLayout disposiciónDatos
            ) :
                gestorEjecución(gestorEjecución),
                sesiónEjecución(sesiónEjecución),
                disposiciónDatos(disposiciónDatos),
                denomina(*this->sesiónEjecución, this->disposiciónDatos),
                capaObjeto(*this->sesiónEjecución, []() { return std::make_unique<llvm::SectionMemoryManager>(); }),
                capaConstrucción(*this->sesiónEjecución, capaObjeto, std::make_unique<llvm::orc::ConcurrentIRCompiler>(std::move(constructorJATMáquinaDestino)) ),
                tablaSímbolosBibliotecaDinámica(this->sesiónEjecución->createBareJITDylib("<main>"))
        {
            tablaSímbolosBibliotecaDinámica.addGenerator( cantFail( llvm::orc::DynamicLibrarySearchGenerator::GetForCurrentProcess( disposiciónDatos.getGlobalPrefix())));
        }

        ~ConstructorJAT()
        {
            if (auto error = sesiónEjecución->endSession())
            {
                sesiónEjecución->reportError(std::move(error));
            }
        }

        static llvm::Expected<Ñ::ConstructorJAT*> Crea()
        {
            auto conjuntoNombres = std::make_shared<llvm::orc::SymbolStringPool>();
            auto gestorEjecución = llvm::orc::SelfExecutorProcessControl::Create(conjuntoNombres);

            if (!gestorEjecución)
            {
                return gestorEjecución.takeError();
            }

            auto sesiónEjecución = new llvm::orc::ExecutionSession(std::move(conjuntoNombres));

            llvm::orc::JITTargetMachineBuilder constructorJATMáquinaDestino((*gestorEjecución)->getTargetTriple());

            auto disposiciónDatos = constructorJATMáquinaDestino.getDefaultDataLayoutForTarget();
            if (!disposiciónDatos)
            {
                return disposiciónDatos.takeError();
            }

            return new Ñ::ConstructorJAT((*gestorEjecución).get(), sesiónEjecución, std::move(constructorJATMáquinaDestino), std::move(*disposiciónDatos));
        }

        const llvm::DataLayout &leeDisposiciónDatos() const
        {
            return disposiciónDatos;
        }

        llvm::orc::JITDylib &leeTablaSímbolosBibliotecaDinámica()
        {
            return tablaSímbolosBibliotecaDinámica;
        }

        llvm::Error añadeMódulo(llvm::orc::ThreadSafeModule móduloMultihilo, llvm::orc::ResourceTrackerSP monitorRecursos = nullptr)
        {
            if (!monitorRecursos)
            {
                monitorRecursos = tablaSímbolosBibliotecaDinámica.getDefaultResourceTracker();
            }

            return capaConstrucción.add(monitorRecursos, std::move(móduloMultihilo));
        }

        llvm::Expected<llvm::JITEvaluatedSymbol> busca(llvm::StringRef nombre)
        {
            return sesiónEjecución->lookup({&tablaSímbolosBibliotecaDinámica}, denomina(nombre.str()));
        }
    };
}