#pragma once

#include "entorno.hpp"
#include "nodo.hpp"
#include "resultado.hpp"

namespace Ñ
{
    Ñ::Resultado construye(Ñ::Nodo* árbol, Ñ::EntornoConstrucción* entorno, Ñ::CategoríaNodo categoríaNodo = Ñ::CategoríaNodo::NODO_MÓDULO);
}