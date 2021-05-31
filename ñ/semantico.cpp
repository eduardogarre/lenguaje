#include <iostream>

#include "nodo.hpp"
#include "resultado.hpp"
#include "semantico.hpp"
#include "tablasimbolos.hpp"
#include "tipo.hpp"
#include "valor.hpp"

Ñ::Resultado resuelveSímbolos(Ñ::Nodo* nodos, Ñ::TablaSímbolos* tablaSímbolos)
{
    Ñ::Resultado resultado;

    if(nodos->categoría == Ñ::CategoríaNodo::NODO_MÓDULO)
    {
        for(Ñ::Nodo* n : nodos->ramas)
        {
            Ñ::Resultado rResuelveSímbolos;
            if(n == nullptr)
            {
                rResuelveSímbolos.error("He recibido un nodo nulo entre los hijos de NODO_MÓDULO");
                return rResuelveSímbolos;
            }

            rResuelveSímbolos = resuelveSímbolos(n, tablaSímbolos);
            
            if(rResuelveSímbolos.error())
            {
                return rResuelveSímbolos;
            }
        }
        
        resultado.éxito();
        return resultado;
    }
    else if(nodos->categoría == Ñ::CategoríaNodo::NODO_DEFINE_FUNCIÓN)
    {
        //Ñ::Nodo* fn = Ñ::duplicaÁrbol(nodos);
        //fn->categoría = Ñ::CategoríaNodo::NODO_FUNCIÓN;
        tablaSímbolos->declara(((Ñ::DefineFunción*)nodos)->nombre, nullptr);
        //tablaSímbolos->ponValor(((Ñ::DefineFunción*)nodos)->nombre, fn);

        for(Ñ::Nodo* n : nodos->ramas)
        {
            Ñ::Resultado rResuelveSímbolos;
            if(n == nullptr)
            {
                rResuelveSímbolos.error("He recibido un nodo nulo entre los hijos de NODO_DEFINE_FUNCIÓN [" + ((Ñ::DefineFunción*)nodos)->nombre + "]");
                return rResuelveSímbolos;
            }

            if(n->categoría == Ñ::CategoríaNodo::NODO_BLOQUE)
            {
                Ñ::TablaSímbolos* subTabla = new Ñ::TablaSímbolos(tablaSímbolos);
                rResuelveSímbolos = resuelveSímbolos(n, subTabla);
                delete subTabla;
            }
            else
            {
                rResuelveSímbolos = resuelveSímbolos(n, tablaSímbolos);
            }

            if(rResuelveSímbolos.error())
            {
                return rResuelveSímbolos;
            }
        }
        
        resultado.éxito();
        return resultado;
    }
    else if(nodos->categoría == Ñ::CategoríaNodo::NODO_ARGUMENTOS)
    {
        for(Ñ::Nodo* n : nodos->ramas)
        {
            Ñ::Resultado rResuelveSímbolos;
            rResuelveSímbolos = resuelveSímbolos(n, tablaSímbolos);
            if(rResuelveSímbolos.error())
            {
                return rResuelveSímbolos;
            }
        }

        resultado.éxito();
        return resultado;
    }
    else if(nodos->categoría == Ñ::CategoríaNodo::NODO_BLOQUE)
    {
        for(Ñ::Nodo* n : nodos->ramas)
        {
            Ñ::Resultado rResuelveSímbolos;
            if(n == nullptr)
            {
                rResuelveSímbolos.error("He recibido un nodo nulo entre los hijos de NODO_BLOQUE");
                return rResuelveSímbolos;
            }

            if(n->categoría == Ñ::CategoríaNodo::NODO_BLOQUE)
            {
                Ñ::TablaSímbolos* subTabla = new Ñ::TablaSímbolos(tablaSímbolos);
                rResuelveSímbolos = resuelveSímbolos(n, subTabla);
                delete subTabla;
            }
            else
            {
                rResuelveSímbolos = resuelveSímbolos(n, tablaSímbolos);
            }

            if(rResuelveSímbolos.error())
            {
                return rResuelveSímbolos;
            }
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
    else if(nodos->categoría == Ñ::CategoríaNodo::NODO_DECLARA_VARIABLE)
    {
        std::string nombre = ((Ñ::DeclaraVariable*)nodos)->variable;
        if(tablaSímbolos->nombreReservadoEnEsteÁmbito(nombre))
        {
            resultado.error("RESOLUCIÓN DE SÍMBOLOS :: El identificador \"" + nombre + "\" ya se había declarado previamente");
            return resultado;
        }

        if( nodos->ramas.size() != 1)
        {
            resultado.error("RESOLUCIÓN DE SÍMBOLOS :: Árbol de la declaración de variable mal construido");
            return resultado;
        }

        Ñ::Resultado r = tablaSímbolos->declara(nombre, nodos->ramas[0]);
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
        if(tablaSímbolos->nombreReservadoEnCualquierÁmbito(nombre))
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
    else if(nodos->categoría == Ñ::CategoríaNodo::NODO_TIPO)
    {
        resultado.éxito();
        return resultado;
    }
    else if(nodos->categoría == Ñ::CategoríaNodo::NODO_LLAMA_FUNCIÓN)
    {
        Ñ::LlamaFunción* fn = (Ñ::LlamaFunción*)(nodos);
        
        if(!tablaSímbolos->nombreReservadoEnCualquierÁmbito(fn->nombre))
        {
            resultado.error("RESOLUCIÓN DE SÍMBOLOS :: " + fn->nombre + "() no está en la tabla de símbolos");
            return resultado;
        }

        resultado.éxito();
        return resultado;
    }
    else if(nodos->categoría == Ñ::CategoríaNodo::NODO_VACÍO)
    {
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

    //if(nodos->categoría != Ñ::CategoríaNodo::NODO_EXPRESIÓN)
    //{
    //    resultado.error("SEMÁNTICO :: El nodo raíz no es una expresión");
    //    return resultado;
    //}

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