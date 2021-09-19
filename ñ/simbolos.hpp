#pragma once

#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "llvm/IR/Value.h"

namespace Ñ
{
    class Símbolos
    {
    private:
        std::vector<std::map<std::string, llvm::Value*>> tabla;

    public:
        Símbolos() {}

        ~Símbolos() {}

        void abreBloque()
        {
            std::map<std::string, llvm::Value*> ámbito;
            tabla.push_back(ámbito);
        }

        void cierraBloque()
        {
            tabla.pop_back();
        }

        void ponId(std::string id, llvm::Value* valor)
        {
            if(tabla.size() < 1)
            {
                std::cout << "Error, no es posible guardar el identificador '" << id << "', la tabla de símbolos tiene " << std::to_string(tabla.size()) << " niveles" << std::endl;
                return;
            }

            tabla[tabla.size() - 1][id] = valor;
        }

        llvm::Value* leeId(std::string id)
        {
            llvm::Value* valor = nullptr;

            for(int i = tabla.size() - 1; i >= 0; i--)
            {
                valor = tabla.at(i).at(id);
                if(valor != nullptr)
                {
                    return valor;
                }
            }
            
            return nullptr;
        }
    };
}