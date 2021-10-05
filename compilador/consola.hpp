#pragma once

#include <string>

namespace Ñ
{
    extern class Posición;
}

namespace Compilador
{
    void escribe(std::string texto);
    void escribeAviso(std::string texto, std::string archivo, Ñ::Posición* posición);
    void escribeError(std::string texto, std::string archivo, Ñ::Posición* posición);
}