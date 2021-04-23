#pragma once

#include <vector>

#include "lexema.hpp"
#include "nodo.hpp"

namespace Ñ
{
    Nodo* analizaSintaxis(std::vector<Ñ::Lexema*> lexemas);
}