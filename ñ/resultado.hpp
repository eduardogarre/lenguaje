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

#include "nodo.hpp"

namespace Ñ
{
    extern class Posición;

    class Resultado
    {
    private:
        bool _error;
        std::string _mensaje;
        Ñ::Nodo *_nodo;
        Ñ::Posición *_posición = nullptr;

    public:
        Resultado();

        Ñ::Posición *posición();
        void posición(Ñ::Posición *pos);

        bool error();
        void error(std::string mensaje);
        void éxito();
        std::string mensaje();

        void nodo(Ñ::Nodo *nodo);
        Ñ::Nodo *nodo();
    };
}