#pragma once

#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "llvm/IR/Value.h"

namespace Ñ
{
    class Tabla
    {
        std::map<std::string, llvm::Value*> tabla;
        std::vector<llvm::BasicBlock*>      pila;

    public:
        Tabla() {}
        ~Tabla() {}

        void ponId(std::string id, llvm::Value* valor)
        {
            tabla[id] = valor;
        }

        llvm::Value* leeId(std::string id)
        {
            llvm::Value* valor = nullptr;

            valor = tabla[id];
            return valor;
        }
    };


    class Símbolos
    {
    private:
        std::vector<Ñ::Tabla> tablas;

    public:
        Símbolos() {}

        ~Símbolos() {}

        void abreBloque()
        {
            Ñ::Tabla ámbito;
            tablas.push_back(ámbito);
        }

        void cierraBloque()
        {
            tablas.pop_back();
        }

        void ponId(std::string id, llvm::Value* valor)
        {
            if(tablas.size() < 1)
            {
                std::cout << "Error, no puedo guardar el identificador '" << id << "', la tabla de símbolos tiene " << std::to_string(tablas.size()) << " niveles" << std::endl;
                return;
            }

            tablas[tablas.size() - 1].ponId(id, valor);
        }

        llvm::Value* leeId(std::string id)
        {
            llvm::Value* valor = nullptr;

            for(int i = tablas.size() - 1; i >= 0; i--)
            {
                valor = tablas.at(i).leeId(id);
                if(valor != nullptr)
                {
                    return valor;
                }
            }
            
            return nullptr;
        }
    };
}