/*
This Source Code Form is subject to the terms of the Mozilla Public License, v.
2.0. If a copy of the MPL was not distributed with this file, You can obtain one
at http://mozilla.org/MPL/2.0/.

This Source Code Form is "Incompatible With Secondary Licenses", as defined by
the Mozilla Public License, v. 2.0.

Copyright © 2021 Eduardo Garre Muñoz
*/

#pragma once

#include "entorno.hpp"
#include "nodo.hpp"
#include "resultadollvm.hpp"

namespace Ñ
{
    Ñ::ResultadoLlvm construye(Ñ::Nodo* árbol, Ñ::EntornoConstrucción* entorno, Ñ::CategoríaNodo categoríaNodo = Ñ::CategoríaNodo::NODO_MÓDULO);
}