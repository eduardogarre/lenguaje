#include <iostream>
#include <map>

#include "nodo.hpp"
#include "semantico.hpp"
#include "simbolo.hpp"

std::map<std::string, Ñ::Símbolo> tablaSímbolos;

Ñ::Nodo* Ñ::analizaSemántica(Ñ::Nodo* nodos, std::map<std::string, Ñ::Símbolo>& tablaSímbolos)
{
    //muestraNodos(nodos);

    if(nodos->categoría != Ñ::CategoríaNodo::NODO_AFIRMA)
    {
        std::cout << "SEMÁNTICO :: El nodo raíz no es una asignación" << std::endl;
        return nullptr;
    }

    if(nodos->ramas.size() < 1)
    {
        std::cout << "SEMÁNTICO :: El nodo raíz está vacío" << std::endl;
        return nullptr;
    }

    if( nodos->ramas.size() == 1)
    {
        if(nodos->ramas[0]->categoría == Ñ::CategoríaNodo::NODO_LLAMA_FUNCIÓN)
        {
            return nodos;
        }
        else if(nodos->ramas[0]->categoría == Ñ::CategoríaNodo::NODO_DECLARA_VARIABLE)
        {
            return nodos;
        }
    }

    return nullptr;
}