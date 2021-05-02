#pragma once

#include <vector>

#include "lexema.hpp"
#include "nodo.hpp"

namespace Ñ
{
    class Sintaxis
    {
// Compilación condicional: si estamos en pruebas, expongo las funciones privadas del módulo
#ifdef EVALUANDO_PRUEBAS
    public:
#else
    private:
#endif
        uint32_t cursor;
        std::vector<Ñ::Lexema*> lexemas;

        bool notación(std::string carácter);
        Ñ::Nodo* literal();
        Ñ::Nodo* tipo();
        Ñ::Nodo* identificador();
        Ñ::Nodo* primario();
        Ñ::Nodo* opMultiplicaciónDivisión();
        Ñ::Nodo* opSumaResta();
        Ñ::Nodo* ladoIzquierdoAsignación();
        Ñ::Nodo* ladoDerechoAsignación();
        Ñ::Nodo* declaraVariable();
        Ñ::Nodo* asigna();
        Ñ::Nodo* argumento();
        Ñ::Nodo* argumentos();
        Ñ::Nodo* llamaFunción();
        Ñ::Nodo* expresión();

    public:
        Ñ::Nodo* analiza(std::vector<Ñ::Lexema*> _lexemas);
    };
}