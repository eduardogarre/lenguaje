#pragma once

#include <map>

#include "nodo.hpp"
#include "simbolo.hpp"

namespace Ñ
{
    void interpretaNodos(Ñ::Nodo* nodos, std::map<std::string, Ñ::Símbolo> tablaSímbolos);
}