#pragma once

#include "nodo.hpp"

namespace Ñ
{
    enum CategoríaSímbolo {
        VACÍO,
        VARIABLE,
        FUNCIÓN,
        TIPO
    };

    class Símbolo
    {
    public:

        Símbolo();
        ~Símbolo();

        bool esFunción();
        bool esFunciónEjecutable();
        bool esVariable();

        void declaraVariable(Ñ::Nodo* tipo);

        void ejecutaFunción();
        void añadeEjecución(void (*fn)());
        void borraEjecución();
        
    private:
        CategoríaSímbolo _categoría;
        bool _ejecutable = false;
        
        Ñ::Nodo* _tipo;
        Ñ::Nodo* _implementación;

        void (*_ejecuta)();
    };
}