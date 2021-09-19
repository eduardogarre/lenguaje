#pragma once

#include "entorno.hpp"
#include "nodo.hpp"
#include "resultadollvm.hpp"

namespace Ñ
{
    Ñ::ResultadoLlvm construye(Ñ::Nodo* árbol, Ñ::EntornoConstrucción* entorno, Ñ::CategoríaNodo categoríaNodo = Ñ::CategoríaNodo::NODO_MÓDULO);
}