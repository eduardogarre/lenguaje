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

#include "posicion.hpp"

Ñ::Posición::Posición()
{
    _cursor = 0;
    _línea = 1;
    _columna = 1;
    _longitud = 0;
    _archivo = "";
}

Ñ::Posición::Posición(json jPosición)
{
    _cursor = jPosición.at("cursor");
    _línea = jPosición.at("línea");
    _columna = jPosición.at("columna");
    _longitud = jPosición.at("longitud");
    _archivo = jPosición.at("archivo");
}

std::string Ñ::Posición::muestra()
{
    std::string texto = "";
    texto += " [LIN:" + std::to_string(línea()) + ", ";
    texto += "COL:" + std::to_string(columna()) + ", ";
    texto += "ARC:" + archivo() + ", ";
    texto += "LON:" + std::to_string(longitud()) + "]";
    return texto;
}

uint64_t Ñ::Posición::cursor()
{
    return _cursor;
}

uint64_t Ñ::Posición::línea()
{
    return _línea;
}

uint64_t Ñ::Posición::columna()
{
    return _columna;
}

uint64_t Ñ::Posición::longitud()
{
    return _longitud;
}

std::string Ñ::Posición::archivo()
{
    return _archivo;
}

void Ñ::Posición::incCursor()
{
    _cursor++;
    _columna++;
}

void Ñ::Posición::incLínea()
{
    _línea++;
    _columna = 0;
}

void Ñ::Posición::empiezaColumna()
{
    _columna = 0;
}

void Ñ::Posición::incColumna()
{
    _columna++;
}

void Ñ::Posición::longitud(uint64_t longitud)
{
    _longitud = longitud;
}

void Ñ::Posición::archivo(std::string archivo)
{
    _archivo = archivo;
}

json Ñ::Posición::aJson()
{
    json posición = {
        {"cursor", _cursor},
        {"línea", _línea},
        {"columna", _columna},
        {"longitud", _longitud},
        {"archivo", _archivo}
    };

    return posición;
}