#include <iostream>

#include "interpreta.hpp"
#include "nodo.hpp"

Ñ::Resultado Ñ::interpretaNodos(Ñ::Nodo* nodos, std::map<std::string, Ñ::Símbolo>* tablaSímbolos)
{
    Ñ::Resultado resultado;

    if(nodos->categoría == Ñ::CategoríaNodo::NODO_EXPRESIÓN)
    {
        for(Ñ::Nodo* n : nodos->ramas)
        {
            Ñ::Resultado rResuelveSímbolos = interpretaNodos(n, tablaSímbolos);
            if(rResuelveSímbolos.error())
            {
                return rResuelveSímbolos;
            }
        }
        
        resultado.éxito();
        return resultado;
    }
    else if(nodos->categoría == Ñ::CategoríaNodo::NODO_LLAMA_FUNCIÓN)
    {
        Ñ::LlamaFunción* fn = (Ñ::LlamaFunción*)nodos;
        Ñ::Símbolo s = tablaSímbolos->at(fn->función);
        
        Ñ::Argumentos* args;
        if(nodos->ramas.size() < 1)
        {
            args = nullptr;
        }
        else
        {
            args = (Ñ::Argumentos*)(nodos->ramas[0]);
        }
        s.ejecutaFunción(args);
        
        resultado.éxito();
        return resultado;
    }
    else if(nodos->categoría == Ñ::CategoríaNodo::NODO_DECLARA_VARIABLE)
    {
        std::string nombre = ((Ñ::DeclaraVariable*)nodos)->variable;

        auto tipo = (nodos->ramas[0]);
        std::string cadenaTipo = ((Ñ::Tipo*)tipo)->tipo;

        // Añado la variable a la tabla de símbolos
        Ñ::Símbolo s;
        s.declaraVariable(tipo);
        (*tablaSímbolos)[nombre] = s;
        
        resultado.éxito();
        return resultado;
    }

    resultado.error("INTÉRPRETE :: No consigo interpretar el árbol de nodos");
    return resultado;
}