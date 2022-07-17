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