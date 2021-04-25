#pragma once

#include <vector>

#include "lexema.hpp"
#include "nodo.hpp"

namespace Ñ
{
    Nodo* analizaSintaxis(std::vector<Ñ::Lexema*> lexemas);
// Compilación condicional: si estamos en pruebas, expongo las funciones privadas del módulo
#ifdef EVALUANDO_PRUEBAS
    bool notación(std::string carácter);
    Ñ::Nodo* literal();
    Ñ::Nodo* tipo();
    Ñ::Nodo* identificador();
    Ñ::Nodo* factor();
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
    Ñ::Nodo* Ñ::analizaSintaxis(std::vector<Ñ::Lexema*> _lexemas);
#endif
}