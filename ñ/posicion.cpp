#include "posicion.hpp"

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

void Ñ::Posición::cursor(uint64_t cursor)
{
    _cursor = cursor;
}

void Ñ::Posición::línea(uint64_t línea)
{
    _línea = línea;
}

void Ñ::Posición::columna(uint64_t columna)
{
    _columna = columna;
}

void Ñ::Posición::lexema(uint64_t lexema)
{
    _lexema = lexema;
}

void Ñ::Posición::archivo(std::string archivo)
{
    _archivo = archivo;
}
