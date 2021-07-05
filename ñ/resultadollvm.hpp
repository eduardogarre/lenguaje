#pragma once

#include <string>

#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Value.h"

namespace Ñ
{
    enum CategoríaLlvm {
        FUNCIÓN_LLVM,
        BLOQUE_LLVM,
        VALOR_LLVM
    };

    class ResultadoLlvm
    {
    private:
        bool _error;
        std::string _mensaje;

        CategoríaLlvm categoría;

        union {
            llvm::Function *    _función;
            llvm::BasicBlock *  _bloque;
            llvm::Value *  _valor;
        } entidad;

    public:
        ResultadoLlvm() : _error(true) {}

        bool error() { return _error; }
        void error(std::string mensaje) { _error = true; _mensaje = mensaje; }
        void éxito() { _error = false; }
        std::string mensaje() { return (_error ? _mensaje : ""); }

        void función(llvm::Function* fn) { categoría = Ñ::CategoríaLlvm::FUNCIÓN_LLVM; entidad._función = fn; }
        llvm::Function* función() { return (_error ? nullptr : entidad._función); }

        void bloque(llvm::BasicBlock* blq) { categoría = Ñ::CategoríaLlvm::BLOQUE_LLVM; entidad._bloque = blq; }
        llvm::BasicBlock* bloque() { return (_error ? nullptr : entidad._bloque); }

        void valor(llvm::Value* val) { categoría = Ñ::CategoríaLlvm::VALOR_LLVM; entidad._valor = val; }
        llvm::Value* valor() { return (_error ? nullptr : entidad._valor); }
    };
}