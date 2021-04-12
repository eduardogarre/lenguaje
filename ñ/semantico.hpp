#pragma once

#include <map>
#include <vector>

#include "nodo.hpp"
#include "resultado.hpp"
#include "simbolo.hpp"

namespace Ñ
{
    Ñ::Resultado analizaSemántica(Ñ::Nodo* nodos, std::map<std::string, Ñ::Símbolo>* tablaSímbolos);
}