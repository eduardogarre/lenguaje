#pragma once

#include <map>

#include "nodo.hpp"
#include "simbolo.hpp"

namespace Ñ
{
    enum CategoríaResultadoInterpretación {
        ERROR,
        ÉXITO
    };

    class ResultadoInterpretación
    {
    public:
        CategoríaResultadoInterpretación resultado;
        std::string mensaje;

        ResultadoInterpretación() : resultado(Ñ::CategoríaResultadoInterpretación::ERROR) {}
    };

    Ñ::ResultadoInterpretación interpretaNodos(Ñ::Nodo* nodos, std::map<std::string, Ñ::Símbolo> tablaSímbolos);
}