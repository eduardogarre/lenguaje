#pragma once

#include <string>
#include <vector>

#include "lexema.hpp"

namespace Ñ
{
    // Análisis léxico
    std::vector<Ñ::Lexema*> analizaLéxico(std::string comando);
}