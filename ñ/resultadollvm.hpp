#pragma once

#include <string>

#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Value.h"

namespace Ñ
{
    extern class Posición;

    enum CategoríaLlvm {
        BLOQUE_LLVM,
        FUNCIÓN_LLVM,
        MÓDULO_LLVM,
        VALOR_LLVM
    };

    class ResultadoLlvm
    {
    private:
        bool _error;
        std::string _mensaje;
        CategoríaLlvm categoría;
        Posición* _posición = nullptr;

        union {
            llvm::BasicBlock *  _bloque;
            llvm::Function *    _función;
            llvm::Module *      _módulo;
            llvm::Value *       _valor;
        } entidad;

    public:
        ResultadoLlvm();

        Posición* posición();
        void posición(Ñ::Posición* pos);

        bool error();
        void error(std::string mensaje);
        void éxito();
        std::string mensaje();

        void bloque(llvm::BasicBlock* blq);
        llvm::BasicBlock* bloque();

        void función(llvm::Function* fn);
        llvm::Function* función();

        void módulo(llvm::Module* mod);
        llvm::Module* módulo();

        void valor(llvm::Value* val);
        llvm::Value* valor();
    };
}