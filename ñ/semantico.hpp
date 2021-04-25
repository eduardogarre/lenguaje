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