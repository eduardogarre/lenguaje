#include <iostream>
#include <map>

#include "nodo.hpp"
#include "resultado.hpp"
#include "semantico.hpp"
#include "simbolo.hpp"

Ñ::Resultado resuelveSímbolos(Ñ::Nodo* nodos, std::map<std::string, Ñ::Símbolo>* tablaSímbolos)
{
    Ñ::Resultado resultado;

    if(nodos->categoría == Ñ::CategoríaNodo::NODO_EXPRESIÓN)
    {
        for(Ñ::Nodo* n : nodos->ramas)
        {
            Ñ::Resultado rResuelveSímbolos = resuelveSímbolos(n, tablaSímbolos);
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
        if(tablaSímbolos->count(nombre) > 0 )
        {
            resultado.error("RESOLUCIÓN DE SÍMBOLOS :: El identificador \"" + nombre + "\" ya se había declarado previamente");
            return resultado;
        }

        if( nodos->ramas.size() != 1)
        {
            resultado.error("RESOLUCIÓN DE SÍMBOLOS :: Árbol de la declaración de variable mal construido");
            return resultado;
        }

        resultado.éxito();
        return resultado;
    }
    else if(nodos->categoría == Ñ::CategoríaNodo::NODO_ASIGNA)
    {
        for(Ñ::Nodo* n : nodos->ramas)
        {
            Ñ::Resultado rResuelveSímbolos = resuelveSímbolos(n, tablaSímbolos);
            if(rResuelveSímbolos.error())
            {
                return rResuelveSímbolos;
            }
        }
        
        resultado.éxito();
        return resultado;
    }
    else if(nodos->categoría == Ñ::CategoríaNodo::NODO_OP_SUMA_RESTA)
    {
        for(Ñ::Nodo* n : nodos->ramas)
        {
            Ñ::Resultado rResuelveSímbolos = resuelveSímbolos(n, tablaSímbolos);
            if(rResuelveSímbolos.error())
            {
                return rResuelveSímbolos;
            }
        }
        
        resultado.éxito();
        return resultado;
    }
    else if(nodos->categoría == Ñ::CategoríaNodo::NODO_OP_MULTIPLICACIÓN_DIVISIÓN)
    {
        for(Ñ::Nodo* n : nodos->ramas)
        {
            Ñ::Resultado rResuelveSímbolos = resuelveSímbolos(n, tablaSímbolos);
            if(rResuelveSímbolos.error())
            {
                return rResuelveSímbolos;
            }
        }
        
        resultado.éxito();
        return resultado;
    }
    else if(nodos->categoría == Ñ::CategoríaNodo::NODO_IDENTIFICADOR)
    {
        std::string nombre = ((Ñ::Identificador*)nodos)->id;
        if(tablaSímbolos->count(nombre) > 0 )
        {
            resultado.éxito();
            return resultado;
        }
        else
        {
            resultado.error("RESOLUCIÓN DE SÍMBOLOS :: El identificador \"" + nombre + "\" no se había declarado previamente");
            return resultado;
        }
    }
    else if(nodos->categoría == Ñ::CategoríaNodo::NODO_LITERAL)
    {
        resultado.éxito();
        return resultado;
    }
    else if(nodos->categoría == Ñ::CategoríaNodo::NODO_LLAMA_FUNCIÓN)
    {
        Ñ::LlamaFunción* fn = (Ñ::LlamaFunción*)(nodos);
        
        if( tablaSímbolos->count(fn->función) == 0 )
        {
            resultado.error("RESOLUCIÓN DE SÍMBOLOS :: " + fn->función + "() no está en la tabla de símbolos");
            return resultado;
        }
        else
        {
            Ñ::Símbolo s = tablaSímbolos->at(fn->función);
            if(!s.esFunciónEjecutable() && !s.esFunciónImplementada())
            {
                resultado.error("RESOLUCIÓN DE SÍMBOLOS :: " + fn->función + "() está en la tabla de símbolos pero sin implementación");
                return resultado;
            }
        }

        resultado.éxito();
        return resultado;
    }

    resultado.error("RESOLUCIÓN DE SÍMBOLOS :: No reconozco el árbol de nodos");
    return resultado;
}

Ñ::Resultado compruebaTipos(Ñ::Nodo* nodos, std::map<std::string, Ñ::Símbolo>* tablaSímbolos)
{
    Ñ::Resultado resultado;
    
    if(nodos->categoría == Ñ::CategoríaNodo::NODO_LLAMA_FUNCIÓN)
    {
        resultado.éxito();
        return resultado;
    }
    else if(nodos->categoría == Ñ::CategoríaNodo::NODO_DECLARA_VARIABLE)
    {
        std::string nombre = ((Ñ::DeclaraVariable*)nodos)->variable;
        if(nodos->categoría == Ñ::CategoríaNodo::NODO_TIPO)
        {
            if(nodos->ramas.size() != 1)
            {
                resultado.error("COMPROBACIÓN DE TIPOS :: Esperaba un tipo para la declaración");
                return resultado;
            }

            auto tipo = (nodos->ramas[0]);
            std::string cadenaTipo = ((Ñ::Tipo*)tipo)->tipo;

            if( cadenaTipo == "bool" ||
                cadenaTipo == "ent" ||
                cadenaTipo == "nat" ||
                cadenaTipo == "real" ||
                cadenaTipo == "txt" )
            {
                resultado.éxito();
                return resultado;
            }
            else
            {
                resultado.error("COMPROBACIÓN DE TIPOS :: Tipo desconocido");
                return resultado;
            }
        }
        else
        {
            resultado.error("COMPROBACIÓN DE TIPOS :: La declaración de variable no contiene tipo");
            return resultado;
        }

        resultado.éxito();
        return resultado;
    }
    else if(nodos->categoría == Ñ::CategoríaNodo::NODO_EXPRESIÓN)
    {
        for(Ñ::Nodo* n : nodos->ramas)
        {
            Ñ::Resultado rResuelveSímbolos = resuelveSímbolos(n, tablaSímbolos);
            if(rResuelveSímbolos.error())
            {
                return rResuelveSímbolos;
            }
        }
        

        resultado.éxito();
        return resultado;
    }

    resultado.error("COMPROBACIÓN DE TIPOS :: No reconozco el árbol de nodos");
    return resultado;
}

Ñ::Resultado Ñ::analizaSemántica(Ñ::Nodo* nodos, std::map<std::string, Ñ::Símbolo>* tablaSímbolos)
{
    Ñ::Resultado resultado;

    if(nodos->categoría != Ñ::CategoríaNodo::NODO_EXPRESIÓN)
    {
        resultado.error("SEMÁNTICO :: El nodo raíz no es una asignación");
        return resultado;
    }

    if(nodos->ramas.size() < 1)
    {
        resultado.error("SEMÁNTICO :: El nodo raíz está vacío");
        return resultado;
    }

    Ñ::Resultado rResuelveSímbolos = resuelveSímbolos(nodos, tablaSímbolos);
    if(rResuelveSímbolos.error())
    {
        resultado.error("SEMÁNTICO :: " + rResuelveSímbolos.mensaje());
        return resultado;
    }
    Ñ::Resultado rCompruebaTipos = compruebaTipos(nodos, tablaSímbolos);
    if(rCompruebaTipos.error())
    {
        resultado.error("SEMÁNTICO :: " + rCompruebaTipos.mensaje());
        return resultado;
    }

    resultado.éxito();
    return resultado;
}