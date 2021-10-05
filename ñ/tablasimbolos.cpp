#include <iostream>

#include "tablasimbolos.hpp"
#include "tipo.hpp"
#include "valor.hpp"


Ñ::Símbolo::Símbolo(std::string nombre, Ñ::Nodo* tipo)
{
    _nombre = nombre;
    _tipo = Ñ::duplicaÁrbol(tipo);
    _valor = nullptr;
}

Ñ::Símbolo::~Símbolo()
{
    if(_tipo != nullptr)
    {
        delete _tipo;
        _tipo = nullptr;
    }
    
    if(_valor != nullptr)
    {
        delete _valor;
        _valor = nullptr;
    }
}

std::string Ñ::Símbolo::nombre()
{
    return _nombre;
}

Ñ::Nodo* Ñ::Símbolo::tipo()
{
    return _tipo;
}

void Ñ::Símbolo::valor(Ñ::Nodo* valor)
{
    _valor = Ñ::duplicaÁrbol(valor);
}

Ñ::Nodo* Ñ::Símbolo::valor()
{
    return _valor;
}

Ñ::TablaSímbolos::TablaSímbolos()
{
    _superior = nullptr;
    funciónPropietaria = "";
}

Ñ::TablaSímbolos::TablaSímbolos(Ñ::TablaSímbolos* tablaSuperior)
{
    _superior = tablaSuperior;
    funciónPropietaria = "";
}

Ñ::TablaSímbolos::~TablaSímbolos()
{
    for (auto [clave, símbolo] : _tabla)
    {
        if(símbolo != nullptr)
        {
            delete símbolo;
        }
    }

    _tabla.clear();
}

bool Ñ::TablaSímbolos::nombreReservadoEnEsteÁmbito(std::string nombre)
{
    if(_tabla.count(nombre) == 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool Ñ::TablaSímbolos::nombreReservadoEnCualquierÁmbito(std::string nombre)
{
    if(_tabla.count(nombre) == 1)
    {
        return true;
    }
    else
    {
        if(_superior != nullptr)
        {
            return _superior->nombreReservadoEnCualquierÁmbito(nombre);
        }
        else
        {
            return false;
        }
    }
}

Ñ::Resultado Ñ::TablaSímbolos::declara(std::string nombre, Ñ::Nodo* tipo)
{
    Ñ::Resultado resultado;

    if(nombreReservadoEnEsteÁmbito(nombre))
    {
        resultado.error("El identificador \"" + nombre + "\" ya existe en este ámbito.");
        return resultado;
    }
    
    Ñ::Símbolo* s = new Ñ::Símbolo(nombre, tipo);
    _tabla[nombre] = s;
    
    resultado.éxito();
    return resultado;
}

Ñ::Resultado Ñ::TablaSímbolos::leeValor(std::string nombre)
{
    Ñ::Resultado resultado;

    if(!nombreReservadoEnCualquierÁmbito(nombre))
    {
        resultado.error("Todavía no has declarado el identificador '" + nombre + "'.");
        return resultado;
    }

    if(!nombreReservadoEnEsteÁmbito(nombre))
    {
        return _superior->leeValor(nombre);
    }
    
    Ñ::Nodo* valor = _tabla[nombre]->valor();
    
    if(valor == nullptr)
    {
        resultado.error("Todavía no has definido el identificador '" + nombre + "'.");
        return resultado;
    }

    resultado.éxito();
    resultado.nodo(Ñ::duplicaÁrbol(valor));
    return resultado;
}

Ñ::Resultado Ñ::TablaSímbolos::leeTipo(std::string nombre)
{
    Ñ::Resultado resultado;

    if(!nombreReservadoEnCualquierÁmbito(nombre))
    {
        resultado.error("Todavía no has declarado el identificador '" + nombre + "'.");
        return resultado;
    }

    if(!nombreReservadoEnEsteÁmbito(nombre))
    {
        return _superior->leeTipo(nombre);
    }
    
    Ñ::Nodo* tipo = _tabla[nombre]->tipo();
    
    if(tipo == nullptr)
    {
        resultado.error("No has declarado correctamente el identificador '" + nombre + "', no sé su tipo.");
        return resultado;
    }

    resultado.éxito();
    resultado.nodo(Ñ::duplicaÁrbol(tipo));
    return resultado;
}

Ñ::Resultado Ñ::TablaSímbolos::ponValor(std::string nombre, Ñ::Nodo* valor)
{
    Ñ::Resultado resultado;
    
    if(valor == nullptr)
    {
        resultado.error("Definición errónea");
        return resultado;
    }

    if(!nombreReservadoEnCualquierÁmbito(nombre))
    {
        resultado.error("Todavía no has declarado el identificador '" + nombre + "'.");
        resultado.posición(valor->posición());
        return resultado;
    }

    if(!nombreReservadoEnEsteÁmbito(nombre))
    {
        return _superior->ponValor(nombre, valor);
    }
    
    Ñ::Símbolo* s = _tabla[nombre];
    s->valor(valor);
    _tabla[nombre] = s;

    resultado.éxito();
    return resultado;
}

void Ñ::TablaSímbolos::ponFunciónPropietaria(std::string fn)
{
    funciónPropietaria = fn;
}

std::string Ñ::TablaSímbolos::leeFunciónPropietaria()
{
    return funciónPropietaria;
}


Ñ::Resultado Ñ::TablaSímbolos::defineFunciónEjecutable(std::string nombre, Ñ::Nodo* (fne)(Ñ::Nodo*, Ñ::Nodo*), Ñ::Nodo* firma)
{
    Ñ::Resultado r;

    Ñ::FunciónEjecutable* función = new Ñ::FunciónEjecutable;
    función->función = fne;
    función->nombre = nombre;
    r = declara(nombre, firma);
    if(r.error())
    {
        return r;
    }
    r = ponValor(nombre, (Ñ::Nodo*)función);
    if(r.error())
    {
        return r;
    }

    r.éxito();
    return r;
}

void Ñ::TablaSímbolos::muestra()
{
    std::cout << "Propietario: " << funciónPropietaria << "()" << std::endl;

    for (auto [clave, valor] : _tabla)
    {
        std::cout << "[" << valor->nombre() << "]" << std::endl;
        std::cout << "\tTipo:\n";
        muestraNodos(valor->tipo());
        std::cout << "\tValor:\n";
        muestraNodos(valor->valor());
    }
}