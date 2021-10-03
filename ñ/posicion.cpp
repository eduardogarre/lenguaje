#include "posicion.hpp"

void Ñ::Posición::inicia()
{
    _cursor = 0;
    _línea = 1;
    _columna = 1;
    _lexema = 0;
    _archivo = "";
}

uint64_t Ñ::Posición::cursor()
{
    return _cursor;
}

uint64_t Ñ::Posición::línea()
{
    return _línea;
}

uint64_t Ñ::Posición::columna()
{
    return _columna;
}

uint64_t Ñ::Posición::lexema()
{
    return _lexema;
}

std::string Ñ::Posición::archivo()
{
    return _archivo;
}

void Ñ::Posición::incCursor()
{
    _cursor++;
    _columna++;
}

void Ñ::Posición::incLínea()
{
    _línea++;
    _columna = 0;
}

void Ñ::Posición::empiezaColumna()
{
    _columna = 0;
}

void Ñ::Posición::incColumna()
{
    _columna++;
}

void Ñ::Posición::lexema(uint64_t lexema)
{
    _lexema = lexema;
}

void Ñ::Posición::archivo(std::string archivo)
{
    _archivo = archivo;
}
