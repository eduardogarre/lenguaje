#include <iostream>

#include "interpreta.hpp"

Ñ::Resultado Ñ::interpretaNodos(Ñ::Nodo* nodos, std::map<std::string, Ñ::Símbolo>& tablaSímbolos)
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
        auto declvar = nodos->ramas[0];
        std::string nombre = ((Ñ::DeclaraVariable*)declvar)->variable;

        auto tipo = (declvar->ramas[0]);
        std::string cadenaTipo = ((Ñ::Tipo*)tipo)->tipo;

        // Añado la variable a la tabla de símbolos
        Ñ::Símbolo s;
        s.declaraVariable(tipo);
        tablaSímbolos[nombre] = s;
        
        resultado.éxito();
        return resultado;
    }

    resultado.error("INTÉRPRETE :: No consigo interpretar el árbol de nodos");
    return resultado;
}