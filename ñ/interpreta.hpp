#pragma once

#include <map>

#include "nodo.hpp"
#include "resultado.hpp"
#include "tablasimbolos.hpp"

namespace Ñ
{
    Ñ::Resultado interpretaNodos(Ñ::Nodo* nodos, Ñ::TablaSímbolos* tablaSímbolos);
}