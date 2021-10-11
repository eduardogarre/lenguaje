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
        Tabla(Ñ::Ámbito ámbito)
        {
            ámbito = ámbito;
        }

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
        std::vector<Ñ::Tabla> tablas;

    public:
        Símbolos() {}

        ~Símbolos() {}

        void creaÁmbito(Ñ::Ámbito ámbito)
        {
            Ñ::Tabla tabla(ámbito);
            tablas.push_back(tabla);
        }

        void borraÁmbito()
        {
            if(!(tablas.empty()))
            {
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

            tablas.back().ponBloqueDestino(bloqueDestino);
        }

        llvm::BasicBlock* leeBloqueDestino()
        {
            if(tablas.size() < 1)
            {
                std::cout << "Error, no puedo leer el bloque de destino, la tabla de símbolos tiene " << std::to_string(tablas.size()) << " niveles" << std::endl;
                return nullptr;
            }

            return tablas.back().leeBloqueDestino();
        }

        void borraBloqueDestino()
        {
            if(tablas.size() < 1)
            {
                std::cout << "Error, no puedo leer el bloque de destino, la tabla de símbolos tiene " << std::to_string(tablas.size()) << " niveles" << std::endl;
                return;
            }

            return tablas.back().borraBloqueDestino();
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