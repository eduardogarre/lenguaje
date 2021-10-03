#include "posicion.hpp"

void Ñ::Posición::inicia()
{
    _cursor = 0;
    _línea = 1;
    _columna = 1;
    _longitud = 0;
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

uint64_t Ñ::Posición::longitud()
{
    return _longitud;
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

void Ñ::Posición::longitud(uint64_t longitud)
{
    _longitud = longitud;
}

void Ñ::Posición::archivo(std::string archivo)
{
    _archivo = archivo;
}
