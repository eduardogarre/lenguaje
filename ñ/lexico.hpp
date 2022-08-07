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

#include "json.hpp"

#include "lexema.hpp"

using json = nlohmann::json;

namespace Ñ
{
    extern class EntornoConstrucción;
    extern class Posición;

    std::vector<Lexema *> analizaLéxico(std::string código, Ñ::EntornoConstrucción *entorno);

    class Léxico // Análisis léxico
    {
    public:
        std::vector<Lexema *> analiza(std::string código, Ñ::EntornoConstrucción *entorno);
        std::string analiza(std::string petición);

        static json aJson(std::vector<Lexema *> lexemas);
        static std::vector<Lexema *> desdeJson(json json_lexemas);

// Compilación condicional: si estamos en pruebas, expongo las funciones privadas de la clase Léxico
#ifdef EVALUANDO_PRUEBAS
    public:
#else
    private:
#endif
        uint32_t longitudarchivo = 0;
        Posición *posición;

        std::vector<Ñ::Lexema *> lexemas;

        bool esfindelarchivo(Posición *p);
        void incrementaCursor(std::string txt);
        std::string siguienteCarácter(std::string txt);
        bool comentario(std::string txt);
        bool _comentario1L(std::string txt);
        bool _comentarioXL(std::string txt);
        bool nuevaLínea(std::string txt);
        bool espacio(std::string txt);
        bool notación(std::string txt);
        bool _nombre(std::string txt);
        bool reservada(std::string txt);
        bool _notacióncientífica(std::string txt);
        bool _númerodecimales(std::string txt);
        bool _número(std::string txt);
        bool número(std::string txt);
        bool texto(std::string txt);
        bool identificador(std::string txt);
    };

// Compilación condicional: si estamos en pruebas, expongo las funciones privadas de la clase Léxico
#ifdef EVALUANDO_PRUEBAS
    bool esdígito(std::string c);
    bool espuntuación(std::string c);
    bool esnuevalínea(std::string c);
    bool esespacio(std::string c);
    bool esalfa(std::string c);
    bool esalfanum(std::string c);
#endif
}