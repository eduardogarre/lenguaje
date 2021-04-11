#include <iostream>

#include "interpreta.hpp"

Ñ::Resultado Ñ::interpretaNodos(Ñ::Nodo* nodos, std::map<std::string, Ñ::Símbolo> tablaSímbolos)
{
    Ñ::Resultado resultado;

    if(nodos->ramas[0]->categoría == Ñ::CategoríaNodo::NODO_LLAMA_FUNCIÓN)
    {
        Ñ::LlamaFunción* fn = (Ñ::LlamaFunción*)(nodos->ramas[0]);
        Ñ::Símbolo s = tablaSímbolos.at(fn->función);
        
        s.ejecutaFunción();
        
        resultado.éxito();
        return resultado;
    }
    else if(nodos->ramas[0]->categoría == Ñ::CategoríaNodo::NODO_DECLARA_VARIABLE)
    {
        muestraNodos(nodos);
        return resultado;
    }

    resultado.error("INTÉRPRETE :: No consigo interpretar el árbol de nodos");
    return resultado;
}