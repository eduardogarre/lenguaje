#pragma once

#include <map>
#include <string>

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
        void asignaValor(Ñ::Nodo* valor);
        Ñ::Nodo* obténValor();

        void ejecutaFunción(Ñ::Argumentos* args);
        void añadeEjecución(void (*fn)(Ñ::Argumentos* args), Ñ::Nodo* args = nullptr);
        void borraEjecución();

        Ñ::Nodo* obténImplementación();
        void añadeImplementación(Ñ::Nodo* impl);
        void borraImplementación();

        void muestra();
        
    private:
        CategoríaSímbolo _categoría;
        bool _ejecutable = false;
        bool _definida = false;
        
        Ñ::Nodo* _tipo;
        Ñ::Nodo* _definición;

        void (*_ejecuta)(Ñ::Argumentos* args);
        Ñ::Argumentos * _args;
    };

    void muestraTablaSímbolos(std::map<std::string, Ñ::Símbolo> tablaSímbolos);
}