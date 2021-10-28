/*
This Source Code Form is subject to the terms of the Mozilla Public License, v.
2.0. If a copy of the MPL was not distributed with this file, You can obtain one
at http://mozilla.org/MPL/2.0/.

This Source Code Form is "Incompatible With Secondary Licenses", as defined by
the Mozilla Public License, v. 2.0.

Copyright © 2021 Eduardo Garre Muñoz
*/

#pragma once

#include <string>

namespace Ñ
{
    extern class Posición;
}

namespace Compilador
{
    void escribe(std::string texto);
    void escribeAviso(std::string texto, std::string archivo, Ñ::Posición* posición);
    void escribeError(std::string texto, std::string archivo, Ñ::Posición* posición);
}