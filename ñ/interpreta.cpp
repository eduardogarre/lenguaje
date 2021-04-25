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
        resultado.nodo((Ñ::Nodo*)id);
        return resultado;
    }
    else if(nodos->categoría == Ñ::CategoríaNodo::NODO_IDENTIFICADOR)
    {
        resultado.éxito();
        resultado.nodo(nodos);
        return resultado;
    }
    else if(nodos->categoría == Ñ::CategoríaNodo::NODO_LITERAL)
    {
        resultado.éxito();
        resultado.nodo(nodos);
        return resultado;
    }
    else if(nodos->categoría == Ñ::CategoríaNodo::NODO_ASIGNA)
    {
        Ñ::Resultado rLia = interpretaNodos(nodos->ramas[0], tablaSímbolos);
        Ñ::Resultado rLda = interpretaNodos(nodos->ramas[1], tablaSímbolos);

        if(rLia.error())
        {
            return rLia;
        }
        if(rLda.error())
        {
            return rLda;
        }
        
        if(rLda.nodo()->categoría == Ñ::CategoríaNodo::NODO_LITERAL)
        {
            std::string id = ((Ñ::Identificador*)(rLia.nodo()))->id;
            (*tablaSímbolos)[id].asignaValor(rLda.nodo());
        }
        else if(rLda.nodo()->categoría == Ñ::CategoríaNodo::NODO_IDENTIFICADOR)
        {
            Ñ::Identificador* idLia = ((Ñ::Identificador*)rLia.nodo());
            Ñ::Identificador* idLda = ((Ñ::Identificador*)rLda.nodo());

            Ñ::Símbolo s = tablaSímbolos->at(idLda->id);
            Ñ::Nodo* valor = s.obténValor();
            Ñ::Nodo* valorTmp = duplicaÁrbol(valor);
            (*tablaSímbolos)[idLia->id].asignaValor(valorTmp);
            delete valorTmp;
        }

        resultado.éxito();
        resultado.nodo(rLia.nodo());
        return resultado;
    }
    else if(nodos->categoría == Ñ::CategoríaNodo::NODO_OP_SUMA_RESTA)
    {
        resultado.error("Pendiente de implementar");
        return resultado;
    }
    else if(nodos->categoría == Ñ::CategoríaNodo::NODO_OP_MULTIPLICACIÓN_DIVISIÓN)
    {
        resultado.error("Pendiente de implementar");
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