/*
This Source Code Form is subject to the terms of the Mozilla Public License, v.
2.0. If a copy of the MPL was not distributed with this file, You can obtain one
at http://mozilla.org/MPL/2.0/.

This Source Code Form is "Incompatible With Secondary Licenses", as defined by
the Mozilla Public License, v. 2.0.
*/

#pragma once

#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "llvm/IR/Value.h"

namespace Ñ
{
    enum Ámbito {
        ÁMBITO_GLOBAL,
        ÁMBITO_BLOQUE_FUNCIÓN,
        ÁMBITO_SUBBLOQUE_FUNCIÓN
    };

    class Tabla
    {
    private:
        Ñ::Ámbito ámbito;

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

        Ñ::Ámbito leeÁmbito()
        {
            return ámbito;
        }

        void ponÁmbito(Ñ::Ámbito _ámbito)
        {
            ámbito = _ámbito;
        }

        void ponBloqueDestino(llvm::BasicBlock* bloqueDestino)
        {
            pila.push_back(bloqueDestino);
        }

        llvm::BasicBlock* leeBloqueDestino()
        {
            if(pila.empty())
            {
                return nullptr;
            }
            else
            {
                return pila.back();
            }
        }

        void borraBloqueDestino()
        {
            if(!(pila.empty()))
            {
                pila.pop_back();
            }
        }
    };


    class Símbolos
    {
    private:
        std::vector<Ñ::Tabla*> tablas;

    public:
        Símbolos() {}

        ~Símbolos() {}

        void creaÁmbito(Ñ::Ámbito ámbito)
        {
            Ñ::Tabla* tabla = new Ñ::Tabla;
            tabla->ponÁmbito(ámbito);
            tablas.push_back(tabla);
        }

        void borraÁmbito()
        {
            if(!(tablas.empty()))
            {
                delete tablas.back();
                tablas.pop_back();
            }
        }

        void ponBloqueDestino(llvm::BasicBlock* bloqueDestino)
        {
            if(tablas.size() < 1)
            {
                std::cout << "Error, no puedo guardar el bloque de destino, la tabla de símbolos tiene " << std::to_string(tablas.size()) << " niveles" << std::endl;
                return;
            }

            tablas.back()->ponBloqueDestino(bloqueDestino);
        }

        llvm::BasicBlock* leeBloqueDestino()
        {
            if(tablas.size() < 1)
            {
                std::cout << "Error, no puedo leer el bloque de destino, la tabla de símbolos tiene " << std::to_string(tablas.size()) << " niveles" << std::endl;
                return nullptr;
            }
            else
            {
                for(int i = tablas.size() - 1; i >= 0; i--)
                {
                    llvm::BasicBlock* blq = tablas[i]->leeBloqueDestino();

                    if(blq != nullptr)
                    {
                        return blq;
                    }

                    if(tablas[i]->leeÁmbito() == Ñ::Ámbito::ÁMBITO_BLOQUE_FUNCIÓN)
                    {
                        // Ya he llegado al bloque raíz de la función
                        break;
                    }
                }

                return nullptr;
            }
        }

        void borraBloqueDestino()
        {
            if(tablas.size() < 1)
            {
                std::cout << "Error, no puedo leer el bloque de destino, la tabla de símbolos tiene " << std::to_string(tablas.size()) << " niveles" << std::endl;
                return;
            }

            return tablas.back()->borraBloqueDestino();
        }

        void ponId(std::string id, llvm::Value* valor)
        {
            if(tablas.size() < 1)
            {
                std::cout << "Error, no puedo guardar el identificador '" << id << "', la tabla de símbolos tiene " << std::to_string(tablas.size()) << " niveles" << std::endl;
                return;
            }

            tablas[tablas.size() - 1]->ponId(id, valor);
        }

        llvm::Value* leeId(std::string id)
        {
            llvm::Value* valor = nullptr;

            for(int i = tablas.size() - 1; i >= 0; i--)
            {
                valor = tablas.at(i)->leeId(id);
                if(valor != nullptr)
                {
                    return valor;
                }
            }
            
            return nullptr;
        }
    };
}