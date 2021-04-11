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
        bool esFunciónImplementada();
        bool esVariable();

        void declaraVariable(Ñ::Nodo* tipo);

        void ejecutaFunción();
        void añadeEjecución(void (*fn)());
        void borraEjecución();

        Ñ::Nodo* implementación();
        void implementación(Ñ::Nodo* impl);
        void borraImplementación();
        
    private:
        CategoríaSímbolo _categoría;
        bool _ejecutable = false;
        bool _implementada = false;
        
        Ñ::Nodo* _tipo;
        Ñ::Nodo* _implementación;

        void (*_ejecuta)();
    };
}