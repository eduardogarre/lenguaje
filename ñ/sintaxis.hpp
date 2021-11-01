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

#include <vector>

#include "lexema.hpp"
#include "nodo.hpp"
#include "posicion.hpp"
#include "resultado.hpp"

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
        Ñ::Posición* últimaPosición = nullptr;
        std::string mensajeError;
        bool éxito = false;

        uint32_t cursor;
        std::vector<Ñ::Lexema*> lexemas;

        void apuntaError(Ñ::Posición* p, std::string error);

        bool notación(std::string carácter);
        bool reservada(std::string palabra);
        Ñ::Nodo* literal();
        Ñ::Nodo* tipo();
        Ñ::Nodo* identificador();
        Ñ::Nodo* puntero();
        Ñ::Nodo* primario();
        Ñ::Nodo* operaciónUnaria();
        Ñ::Nodo* elementoVector();
        Ñ::Nodo* factor();
        Ñ::Nodo* término();
        Ñ::Nodo* comparación();
        Ñ::Nodo* ladoIzquierdoAsignación();
        Ñ::Nodo* ladoDerechoAsignación();
        Ñ::Nodo* declaraVariable();
        Ñ::Nodo* asigna();
        Ñ::Nodo* declaraArgumento();
        Ñ::Nodo* declaraArgumentos();
        Ñ::Nodo* ponArgumento();
        Ñ::Nodo* ponArgumentos();
        Ñ::Nodo* llamaFunción();
        Ñ::Nodo* vuelve();
        Ñ::Nodo* devuelve();
        Ñ::Nodo* para();
        Ñ::Nodo* siCondicional();
        Ñ::Nodo* bucleMientras();
        Ñ::Nodo* expresión();
        Ñ::Nodo* bloque();
        Ñ::Nodo* defineFunción();
        Ñ::Nodo* declaraFunción();
        Ñ::Nodo* módulo(std::string nombre);

    public:
        Ñ::Resultado analiza(std::vector<Ñ::Lexema*> _lexemas, std::string nombreArchivo);
        Ñ::Resultado analizaComando(std::vector<Ñ::Lexema*> _lexemas);
    };
}