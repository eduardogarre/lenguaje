#pragma once

#include <map>
#include <vector>

#include "nodo.hpp"
#include "simbolo.hpp"

namespace Ñ
{
    Ñ::Nodo* analizaSemántica(Ñ::Nodo* nodos, std::map<std::string, Ñ::Símbolo>& tablaSímbolos);
}