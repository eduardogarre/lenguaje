/*
SPDX-License-Identifier: MPL-2.0-no-copyleft-exception

This Source Code Form is subject to the terms of the Mozilla Public License, v.
2.0. If a copy of the MPL was not distributed with this file, You can obtain one
at http://mozilla.org/MPL/2.0/.

This Source Code Form is "Incompatible With Secondary Licenses", as defined by
the Mozilla Public License, v. 2.0.

Copyright © 2021 Eduardo Garre Muñoz
*/

#include <string>

#include "nodo.hpp"
#include "posicion.hpp"
#include "resultado.hpp"

Ñ::Resultado::Resultado() : _error(true), _nodo(nullptr)
{
    _posición = new Ñ::Posición;
}

Ñ::Posición* Ñ::Resultado::posición()
{
    return _posición;
}

void Ñ::Resultado::posición(Ñ::Posición* pos)
{
    if(pos != nullptr)
    {
        *_posición = *pos;
    }
}

bool Ñ::Resultado::error()
{
    return _error;
}

void Ñ::Resultado::error(std::string mensaje)
{
    _error = true;
    _mensaje = mensaje;
}

void Ñ::Resultado::éxito() { _error = false; }

std::string Ñ::Resultado::mensaje()
{
    return (_error ? _mensaje : "");
}

void Ñ::Resultado::nodo(Ñ::Nodo* nodo)
{
    _nodo = nodo;
}

Ñ::Nodo* Ñ::Resultado::nodo()
{
    return (_error ? nullptr : _nodo);
}