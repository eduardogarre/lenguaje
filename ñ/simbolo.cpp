#include <iostream>

#include "simbolo.hpp"

Ñ::Símbolo::Símbolo()
{
    _categoría = CategoríaSímbolo::VACÍO;
    _ejecutable = false;
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
    _tipo = tipo;
}

void Ñ::Símbolo::ejecutaFunción()
{
    if(_categoría == CategoríaSímbolo::FUNCIÓN && _ejecutable && _ejecuta)
    {
        _ejecuta();
    }
}

void Ñ::Símbolo::añadeEjecución(void (*fn)())
{
    _categoría = CategoríaSímbolo::FUNCIÓN;
    _ejecutable = true;
    _ejecuta = fn;
}

void Ñ::Símbolo::borraEjecución()
{
    _ejecutable = false;
    _ejecuta = nullptr;
}