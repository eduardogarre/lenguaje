#include <iostream>

#include "simbolo.hpp"

Ñ::Símbolo::Símbolo()
{
    _categoría = CategoríaSímbolo::VACÍO;
    _ejecutable = false;
    _implementada = false;

    _implementación = nullptr;
}

Ñ::Símbolo::~Símbolo()
{

}

bool Ñ::Símbolo::esFunción()
{
    return _categoría == Ñ::CategoríaSímbolo::FUNCIÓN;
}

bool Ñ::Símbolo::esFunciónEjecutable()
{
    return _ejecutable;
}

bool Ñ::Símbolo::esFunciónImplementada()
{
    return _implementada;
}

bool Ñ::Símbolo::esVariable()
{
    return _categoría == Ñ::CategoríaSímbolo::VARIABLE;
}

void Ñ::Símbolo::declaraVariable(Ñ::Nodo* tipo)
{
    if(_categoría != CategoríaSímbolo::VACÍO)
    {
        std::cout << "ERROR en la creación del símbolo, intentas sobreescribir un símbolo que no está vacío" << std::endl;
        
        return;
    }

    _categoría = CategoríaSímbolo::VARIABLE;
    Ñ::Tipo* t = new Ñ::Tipo();
    t->tipo = ((Ñ::Tipo*)tipo)->tipo;
    t->vector = ((Ñ::Tipo*)tipo)->vector;
    _tipo = (Ñ::Nodo*)(t);
}

void Ñ::Símbolo::ejecutaFunción()
{
    if(_categoría == CategoríaSímbolo::FUNCIÓN && _ejecutable && _ejecuta)
    {
        _ejecuta(_arg);
    }
}

void Ñ::Símbolo::añadeEjecución(void (*fn)(void* arg), void* arg)
{
    _categoría = CategoríaSímbolo::FUNCIÓN;
    _ejecutable = true;
    _ejecuta = fn;
    _arg = arg;
}

void Ñ::Símbolo::borraEjecución()
{
    _ejecutable = false;
    _ejecuta = nullptr;
}

Ñ::Nodo* Ñ::Símbolo::implementación()
{
    if(_implementada)
    {
        return _implementación;
    }
    else
    {
        return nullptr;
    }
}

void Ñ::Símbolo::implementación(Ñ::Nodo* impl)
{
    _implementada = true;
    _implementación = impl;
}

void Ñ::Símbolo::borraImplementación()
{
    _implementada = false;
    _implementación = nullptr;
}

void Ñ::Símbolo::muestra()
{
    if(_categoría == Ñ::CategoríaSímbolo::VACÍO)
    {
        std::cout << "[]";
    }
    else if(_categoría == Ñ::CategoríaSímbolo::VARIABLE)
    {
        std::cout << "[VARIABLE] ";
        muestraNodos(_tipo);
    }
    else if(_categoría == Ñ::CategoríaSímbolo::FUNCIÓN)
    {
        std::cout << "[FUNCIÓN]";
        if(_ejecutable)
        {
            std::cout << " [ejecutable]";
        }
        else
        {
            std::cout << " [----------]";
        }

        if(_implementada)
        {
            std::cout << " [implementada]" << std::endl << " ";
            muestraNodos(_implementación);
        }
        else
        {
            std::cout << std::endl;
        }
    }

}

void Ñ::muestraTablaSímbolos(std::map<std::string, Ñ::Símbolo> tablaSímbolos)
{
    for (auto [clave, valor] : tablaSímbolos)
    {
        std::cout << clave << " ";
        valor.muestra();
    }
}