#include <iostream>
#include <map>

#include "nodo.hpp"
#include "resultado.hpp"
#include "semantico.hpp"
#include "simbolo.hpp"

std::map<std::string, Ñ::Símbolo> tablaSímbolos;

Ñ::Resultado Ñ::analizaSemántica(Ñ::Nodo* nodos, std::map<std::string, Ñ::Símbolo>& tablaSímbolos)
{
    Ñ::Resultado resultado;

    if(nodos->categoría != Ñ::CategoríaNodo::NODO_AFIRMA)
    {
        resultado.resultado = Ñ::CategoríaResultado::ERROR;
        resultado.mensaje = "SEMÁNTICO :: El nodo raíz no es una asignación";
        return resultado;
    }

    if(nodos->ramas.size() < 1)
    {
        resultado.resultado = Ñ::CategoríaResultado::ERROR;
        resultado.mensaje = "SEMÁNTICO :: El nodo raíz está vacío";
        return resultado;
    }

    if( nodos->ramas.size() == 1)
    {
        if(nodos->ramas[0]->categoría == Ñ::CategoríaNodo::NODO_LLAMA_FUNCIÓN)
        {
            resultado.resultado = Ñ::CategoríaResultado::ÉXITO;
            return resultado;
        }
        else if(nodos->ramas[0]->categoría == Ñ::CategoríaNodo::NODO_DECLARA_VARIABLE)
        {
            resultado.resultado = Ñ::CategoríaResultado::ÉXITO;
            return resultado;
        }
    }

    resultado.resultado = Ñ::CategoríaResultado::ERROR;
    resultado.mensaje = "SEMÁNTICO :: No reconozco el árbol de nodos";
    return resultado;
}