#pragma once

#include <string>
#include <vector>

#include "nodo.hpp"
#include "resultado.hpp"

namespace Ñ
{
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
    
    class Tipo : Nodo
    {
    public:
        CategoríaTipo tipo;

        Tipo();
        ~Tipo();

        void muestra();
    };

    Ñ::CategoríaTipo obténTipoMínimoComún(Ñ::CategoríaTipo t1, Ñ::CategoríaTipo t2);
    Ñ::Tipo* creaTipoBásico(Ñ::CategoríaTipo tipo);
    Ñ::Resultado creaFirmaFunción(Ñ::Nodo* fn);
    std::string obténNombreDeTipo(Ñ::CategoríaTipo t);
    Ñ::CategoríaTipo obténTipoDeNombre(std::string nombre);
    Ñ::CategoríaTipo obténMínimoNaturalVálido(uint64_t n);
    Ñ::CategoríaTipo obténMínimoEnteroVálido(int64_t e);
    bool tiposAsignables(Ñ::CategoríaTipo lia, Ñ::CategoríaTipo lda);
}