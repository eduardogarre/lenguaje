#include <iostream>

#include "nodo.hpp"
#include "resultado.hpp"
#include "semantico.hpp"
#include "tablasimbolos.hpp"

Ñ::Resultado resuelveSímbolos(Ñ::Nodo* nodos, Ñ::TablaSímbolos* tablaSímbolos)
{
    Ñ::Resultado resultado;

    if(nodos->categoría == Ñ::CategoríaNodo::NODO_BLOQUE)
    {
        Ñ::TablaSímbolos* subTabla = new Ñ::TablaSímbolos(tablaSímbolos);

        for(Ñ::Nodo* n : nodos->ramas)
        {
            Ñ::Resultado rResuelveSímbolos = resuelveSímbolos(n, subTabla);
            if(rResuelveSímbolos.error())
            {
                return rResuelveSímbolos;
            }
        }

        delete subTabla;
        
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
    else if(nodos->categoría == Ñ::CategoríaNodo::NODO_DECLARA_VARIABLE)
    {
        std::string nombre = ((Ñ::DeclaraVariable*)nodos)->variable;
        if(!tablaSímbolos->identificadorDisponible(nombre))
        {
            resultado.error("RESOLUCIÓN DE SÍMBOLOS :: El identificador \"" + nombre + "\" ya se había declarado previamente");
            return resultado;
        }

        if( nodos->ramas.size() != 1)
        {
            resultado.error("RESOLUCIÓN DE SÍMBOLOS :: Árbol de la declaración de variable mal construido");
            return resultado;
        }

        Ñ::Resultado r = tablaSímbolos->declaraVariable(nombre, nodos->ramas[0]);
        if(r.error())
        {
            return r;
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
    else if(nodos->categoría == Ñ::CategoríaNodo::NODO_IGUALDAD)
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
    else if(nodos->categoría == Ñ::CategoríaNodo::NODO_COMPARACIÓN)
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
    else if(nodos->categoría == Ñ::CategoríaNodo::NODO_TÉRMINO)
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
    else if(nodos->categoría == Ñ::CategoríaNodo::NODO_FACTOR)
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
        if(!tablaSímbolos->identificadorDisponible(nombre))
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
    else if(nodos->categoría == Ñ::CategoríaNodo::NODO_OP_BINARIA)
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
    else if(nodos->categoría == Ñ::CategoríaNodo::NODO_OP_UNARIA)
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
    else if(nodos->categoría == Ñ::CategoríaNodo::NODO_LITERAL)
    {
        resultado.éxito();
        return resultado;
    }
    else if(nodos->categoría == Ñ::CategoríaNodo::NODO_LLAMA_FUNCIÓN)
    {
        Ñ::LlamaFunción* fn = (Ñ::LlamaFunción*)(nodos);
        
        if(tablaSímbolos->identificadorDisponible(fn->función))
        {
            resultado.error("RESOLUCIÓN DE SÍMBOLOS :: " + fn->función + "() no está en la tabla de símbolos");
            return resultado;
        }

        resultado.éxito();
        return resultado;
    }

    resultado.error("RESOLUCIÓN DE SÍMBOLOS :: No reconozco el árbol de nodos");
    return resultado;
}

Ñ::Resultado compruebaTipos(Ñ::Nodo* nodos, Ñ::TablaSímbolos* tablaSímbolos)
{
    Ñ::Resultado resultado;
    
    resultado.éxito();
    return resultado;
}

Ñ::Resultado Ñ::analizaSemántica(Ñ::Nodo* nodos, Ñ::TablaSímbolos* tablaSímbolos)
{
    Ñ::Resultado resultado;

    if(nodos->categoría != Ñ::CategoríaNodo::NODO_EXPRESIÓN)
    {
        resultado.error("SEMÁNTICO :: El nodo raíz no es una expresión");
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