#include "simbolo.hpp"

Ñ::Símbolo::Símbolo()
{

}

Ñ::Símbolo::~Símbolo()
{

}

bool Ñ::Símbolo::esEjecutable()
{
    return _ejecutable;
}

void Ñ::Símbolo::ejecuta()
{
    if(_ejecutable && _ejecuta)
    {
        _ejecuta();
    }
}

void Ñ::Símbolo::añadeEjecución(void (*fn)())
{
    _ejecutable = true;
    _ejecuta = fn;
}

void Ñ::Símbolo::borraEjecución()
{
    _ejecutable = false;
    _ejecuta = nullptr;
}