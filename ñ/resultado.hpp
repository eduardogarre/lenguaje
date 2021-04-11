#pragma once

#include <string>

namespace Ñ
{
    enum CategoríaResultado {
        ERROR,
        ÉXITO
    };

    class Resultado
    {
    public:
        CategoríaResultado resultado;
        std::string mensaje;

        Resultado() : resultado(Ñ::CategoríaResultado::ERROR) {}
    };
}