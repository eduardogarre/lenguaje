#include <iostream>
#include <vector>

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
    else if(nodos->categoría == Ñ::CategoríaNodo::NODO_DECLARA_VARIABLE)
    {
        std::string nombre = ((Ñ::DeclaraVariable*)nodos)->variable;

        auto tipo = (nodos->ramas[0]);
        std::string cadenaTipo = ((Ñ::Tipo*)tipo)->tipo;

        // Añado la variable a la tabla de símbolos
        Ñ::Símbolo s;
        s.declaraVariable(tipo);
        (*tablaSímbolos)[nombre] = s;

        Ñ::Identificador* id = new Ñ::Identificador();
        id->id = nombre;
        
        resultado.éxito();
        resultado.resultado((Ñ::Nodo*)id);
        return resultado;
    }
    else if(nodos->categoría == Ñ::CategoríaNodo::NODO_IDENTIFICADOR)
    {
        resultado.éxito();
        resultado.resultado(nodos);
        return resultado;
    }
    else if(nodos->categoría == Ñ::CategoríaNodo::NODO_LITERAL)
    {
        resultado.éxito();
        resultado.resultado(nodos);
        return resultado;
    }
    else if(nodos->categoría == Ñ::CategoríaNodo::NODO_ASIGNA)
    {
        Ñ::Resultado rLia = interpretaNodos(nodos->ramas[0], tablaSímbolos);
        Ñ::Resultado rLda = interpretaNodos(nodos->ramas[1], tablaSímbolos);
        
        if(rLda.resultado()->categoría == Ñ::CategoríaNodo::NODO_LITERAL)
        {
            std::string id = ((Ñ::Identificador*)(rLia.resultado()))->id;
            (*tablaSímbolos)[id].defineVariable(rLda.resultado());
        }
        else if(rLda.resultado()->categoría == Ñ::CategoríaNodo::NODO_IDENTIFICADOR)
        {
            std::string idLda = ((Ñ::Identificador*)rLda.resultado())->id;
            Ñ::Símbolo s = tablaSímbolos->at(idLda);
            std::string idLia = ((Ñ::Identificador*)(rLia.resultado()))->id;
            (*tablaSímbolos)[idLia].defineVariable(s.valor());
        }

        resultado.éxito();
        resultado.resultado(rLia.resultado());
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

    resultado.error("INTÉRPRETE :: No consigo interpretar el árbol de nodos");
    return resultado;
}