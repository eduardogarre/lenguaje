#include <string>

#include "nodo.hpp"
#include "posicion.hpp"
#include "resultado.hpp"

Ñ::Resultado::Resultado() : _error(true), _nodo(nullptr)
{
    _posición = new Ñ::Posición;
}

Ñ::Posición* Ñ::Resultado::posición()
{
    return _posición;
}

void Ñ::Resultado::posición(Ñ::Posición* pos)
{
    if(pos != nullptr)
    {
        *_posición = *pos;
    }
}

bool Ñ::Resultado::error()
{
    return _error;
}

void Ñ::Resultado::error(std::string mensaje)
{
    _error = true;
    _mensaje = mensaje;
}

void Ñ::Resultado::éxito() { _error = false; }

std::string Ñ::Resultado::mensaje()
{
    return (_error ? _mensaje : "");
}

void Ñ::Resultado::nodo(Ñ::Nodo* nodo)
{
    _nodo = nodo;
}

Ñ::Nodo* Ñ::Resultado::nodo()
{
    return (_error ? nullptr : _nodo);
}