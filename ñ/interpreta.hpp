#pragma once

#include <map>

#include "nodo.hpp"
#include "resultado.hpp"
#include "simbolo.hpp"

namespace Ñ
{
    Ñ::Resultado interpretaNodos(Ñ::Nodo* nodos, std::map<std::string, Ñ::Símbolo> tablaSímbolos);
}