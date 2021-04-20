#include <iostream>

#include "simbolo.hpp"

Ñ::Símbolo::Símbolo()
{
    _categoría = CategoríaSímbolo::VACÍO;
    _ejecutable = false;
    _definida = false;

    _definición = nullptr;
    _tipo = nullptr;
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
    return _definida;
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

void Ñ::Símbolo::asignaValor(Ñ::Nodo* valor)
{
    _categoría = CategoríaSímbolo::VARIABLE;

    if(valor->categoría == Ñ::CategoríaNodo::NODO_LITERAL)
    {
        Ñ::Literal* v = new Ñ::Literal();
        v->dato = ((Ñ::Literal*)valor)->dato;
        _definición = (Ñ::Nodo*)v;
    }
}

Ñ::Nodo* Ñ::Símbolo::obténValor()
{
    return _definición;
}

void Ñ::Símbolo::ejecutaFunción(Ñ::Argumentos* args)
{
    if(_categoría == CategoríaSímbolo::FUNCIÓN && _ejecutable && _ejecuta)
    {
        if(args == nullptr)
        {
            _ejecuta(_args);
        }
        else
        {
            _ejecuta(args);
        }
    }
}

void Ñ::Símbolo::añadeEjecución(void (*fn)(Ñ::Argumentos* args), Ñ::Nodo* args)
{
    _categoría = CategoríaSímbolo::FUNCIÓN;
    _ejecutable = true;
    _ejecuta = fn;
    
    if(args == nullptr)
    {
        _args = nullptr;
    }
    else if(args->categoría == Ñ::CategoríaNodo::NODO_ARGUMENTOS)
    {
        _args = (Ñ::Argumentos*)args;
    }
}

void Ñ::Símbolo::borraEjecución()
{
    _ejecutable = false;
    _ejecuta = nullptr;
}

Ñ::Nodo* Ñ::Símbolo::obténImplementación()
{
    if(_definida)
    {
        return _definición;
    }
    else
    {
        return nullptr;
    }
}

void Ñ::Símbolo::añadeImplementación(Ñ::Nodo* impl)
{
    _definida = true;
    _definición = impl;
}

void Ñ::Símbolo::borraImplementación()
{
    _definida = false;
    _definición = nullptr;
}

void Ñ::Símbolo::muestra()
{
    if(_categoría == Ñ::CategoríaSímbolo::VACÍO)
    {
        std::cout << "[]";
    }
    else if(_categoría == Ñ::CategoríaSímbolo::VARIABLE)
    {
        if((Ñ::Literal*)_definición != nullptr)
        {
            std::cout << "[VARIABLE :: \"" + ((Ñ::Literal*)_definición)->dato + "\"] ";
        }
        else
        {
            std::cout << "[VARIABLE] ";
        }

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

        if(_definida)
        {
            std::cout << " [implementada]" << std::endl << " ";
            muestraNodos(_definición);
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