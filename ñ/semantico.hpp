/*
This Source Code Form is subject to the terms of the Mozilla Public License, v.
2.0. If a copy of the MPL was not distributed with this file, You can obtain one
at http://mozilla.org/MPL/2.0/.

This Source Code Form is "Incompatible With Secondary Licenses", as defined by
the Mozilla Public License, v. 2.0.
*/

#pragma once

#include <map>
#include <vector>

#include "nodo.hpp"
#include "resultado.hpp"
#include "tablasimbolos.hpp"

namespace Ñ
{
    Ñ::Resultado analizaSemántica(Ñ::Nodo* nodos, Ñ::TablaSímbolos* tablaSímbolos);
}