/*
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
#include "valor.hpp"

namespace Ñ
{

    extern class TablaSímbolos;
    extern class Posición;
    
    enum CategoríaTipo
    {
        TIPO_NADA = 0,
        TIPO_PUNTERO,
        TIPO_BOOLEANO,
        TIPO_NATURAL_8,
        TIPO_NATURAL_16,
        TIPO_NATURAL_32,
        TIPO_NATURAL_64,
        TIPO_ENTERO_8,
        TIPO_ENTERO_16,
        TIPO_ENTERO_32,
        TIPO_ENTERO_64,
        TIPO_REAL_32,
        TIPO_REAL_64,
        TIPO_TEXTO,

        TIPO_FUNCIÓN,

        TIPO_VECTOR
    };
    
    class Tipo : public Nodo
    {
    private:
        uint64_t _tamaño = 0;
        uint64_t _ramas();

    public:
        CategoríaTipo tipo;

        Tipo(Ñ::Posición* posición = nullptr);
        ~Tipo();

        void muestra(TablaSímbolos* tablaSímbolos = nullptr);
        uint64_t tamaño();
        void tamaño(uint64_t nuevotamaño);
        Ñ::Tipo* subtipo();
    };

    Ñ::Tipo* obténTipoMínimoComún(Ñ::Tipo* t1, Ñ::Tipo* t2);
    Ñ::Tipo* creaTipoBásico(Ñ::CategoríaTipo tipo);
    Ñ::Resultado creaFirmaFunción(Ñ::Nodo* fn);
    std::string obténNombreDeTipo(Ñ::Tipo* t);
    Ñ::Tipo* obténTipoDeLiteral(Ñ::Literal* literal);
    Ñ::Tipo* obténTipoDeValor(Ñ::Valor* valor);
    Ñ::CategoríaTipo obténTipoDeNombre(std::string nombre);
    Ñ::CategoríaTipo obténMínimoNaturalVálido(uint64_t n);
    Ñ::CategoríaTipo obténMínimoEnteroVálido(int64_t e);
    bool tiposAsignables(Ñ::Tipo* lia, Ñ::Tipo* lda);
    bool esBooleano(Ñ::Tipo* tipo);
    bool esEntero(Ñ::Tipo* tipo);
    bool esNatural(Ñ::Tipo* tipo);
    bool esPuntero(Ñ::Tipo* tipo);
    bool esReal(Ñ::Tipo* tipo);
    bool esVector(Ñ::Tipo* tipo);
}