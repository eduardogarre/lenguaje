#pragma once

#include <map>
#include <string>

#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"

namespace Ñ
{
    class EntornoConstrucción
    {
    public:
        bool                                HABLADOR = false;
        uint8_t                             optimización = 0;
        std::string                         archivoActual = "";
        llvm::LLVMContext                   contextoLlvm;
        llvm::legacy::FunctionPassManager*  gestorPasesOptimización = nullptr;
        llvm::IRBuilder<>                   constructorLlvm;
        std::map<std::string, llvm::Type*>  globales;

        EntornoConstrucción() : constructorLlvm(contextoLlvm) {}
        ~EntornoConstrucción() {}
    };
}