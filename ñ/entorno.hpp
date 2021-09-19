#pragma once

#include <map>
#include <string>

#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"

#include "simbolos.hpp"

namespace Ñ
{
    class EntornoConstrucción
    {
    public:
        llvm::LLVMContext                   contextoLlvm;
        llvm::legacy::FunctionPassManager*  gestorPasesOptimización = nullptr;
        llvm::IRBuilder<>                   constructorLlvm;
        std::map<std::string, llvm::Type*>  globales;
        Ñ::Símbolos*                        tablaSímbolos = nullptr;

        EntornoConstrucción() : constructorLlvm(contextoLlvm) {}
        ~EntornoConstrucción() {}
    };
}