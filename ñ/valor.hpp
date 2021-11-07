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
#include <vector>

#include "nodo.hpp"
#include "resultado.hpp"
#include "tipo.hpp"

namespace Ñ
{
    extern class Posición;
    extern class TablaSímbolos;
    
    class Valor : public Nodo
    {
    private:
        union {
            bool        booleano;
            uint8_t     nat8;
            uint16_t    nat16;
            uint32_t    nat32;
            uint64_t    nat64;
            int8_t      ent8;
            int16_t     ent16;
            int32_t     ent32;
            int64_t     ent64;
            float       real32;
            double      real64;
            int64_t     puntero;
            uint64_t    serie;
        } dato;

        std::string _texto;

    public:
        CategoríaTipo tipo;
        
        Valor(Ñ::Posición* posición = nullptr);
        ~Valor();

        Ñ::CategoríaTipo obténTipo();

        uint8_t     nat8();
        void        nat8(uint8_t nat8);
        bool        esNat8();
        uint16_t    nat16();
        void        nat16(uint16_t nat16);
        bool        esNat16();
        uint32_t    nat32();
        void        nat32(uint32_t nat32);
        bool        esNat32();
        uint64_t    nat64();
        void        nat64(uint64_t nat64);
        bool        esNat64();

        int8_t      ent8();
        void        ent8(int8_t ent8);
        bool        esEnt8();
        int16_t     ent16();
        void        ent16(int16_t ent16);
        bool        esEnt16();
        int32_t     ent32();
        void        ent32(int32_t ent32);
        bool        esEnt32();
        int64_t     ent64();
        void        ent64(int64_t ent64);
        bool        esEnt64();

        float       real32();
        void        real32(float real32);
        bool        esReal32();

        double      real64();
        void        real64(double real64);
        bool        esReal64();
        
        void        serie(uint64_t tamaño);
        bool        esSerie();

        bool booleano();
        void booleano(bool booleano);
        bool esBooleano();

        int64_t puntero();
        void puntero(int64_t puntero);
        bool esPuntero();

        std::string texto();
        void texto(std::string texto);
        bool esTexto();

        void muestra(TablaSímbolos* tablaSímbolos = nullptr);
    };

    Ñ::Valor* creaValor(Ñ::Literal* literal);

    bool comparaValores(Ñ::Valor* valor1, Ñ::Valor* valor2);
    Ñ::Valor* duplicaValor(Ñ::Valor* valor);
    
    Ñ::Resultado convierteValor(Ñ::Valor* valor, Ñ::Tipo* tipoDestino);
    
    Ñ::Resultado aBooleano(Ñ::Valor* valor);
    Ñ::Resultado aNat8(Ñ::Valor* valor);
    Ñ::Resultado aNat16(Ñ::Valor* valor);
    Ñ::Resultado aNat32(Ñ::Valor* valor);
    Ñ::Resultado aNat64(Ñ::Valor* valor);
    Ñ::Resultado aEnt8(Ñ::Valor* valor);
    Ñ::Resultado aEnt16(Ñ::Valor* valor);
    Ñ::Resultado aEnt32(Ñ::Valor* valor);
    Ñ::Resultado aEnt64(Ñ::Valor* valor);
    Ñ::Resultado aPuntero(Ñ::Valor* valor);
    Ñ::Resultado aReal32(Ñ::Valor* valor);
    Ñ::Resultado aReal64(Ñ::Valor* valor);
    Ñ::Resultado aTexto(Ñ::Valor* valor);
}