#include <iostream>

#include "nodo.hpp"
#include "resultado.hpp"
#include "semantico.hpp"
#include "tablasimbolos.hpp"
#include "tipo.hpp"
#include "valor.hpp"

Ñ::Resultado resuelveSímbolos(Ñ::Nodo* nodo, Ñ::TablaSímbolos* tablaSímbolos)
{
    Ñ::Resultado resultado;

    if(nodo->categoría == Ñ::CategoríaNodo::NODO_MÓDULO)
    {
        for(Ñ::Nodo* n : nodo->ramas)
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
    else if(nodo->categoría == Ñ::CategoríaNodo::NODO_DEFINE_FUNCIÓN)
    {
        tablaSímbolos->declara(((Ñ::DefineFunción*)nodo)->nombre, nullptr);

        for(Ñ::Nodo* n : nodo->ramas)
        {
            Ñ::Resultado rResuelveSímbolos;
            if(n == nullptr)
            {
                rResuelveSímbolos.error("He recibido un nodo nulo entre los hijos de NODO_DEFINE_FUNCIÓN [" + ((Ñ::DefineFunción*)nodo)->nombre + "]");
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
    else if(nodo->categoría == Ñ::CategoríaNodo::NODO_ARGUMENTOS)
    {
        for(Ñ::Nodo* n : nodo->ramas)
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
    else if(nodo->categoría == Ñ::CategoríaNodo::NODO_BLOQUE)
    {
        for(Ñ::Nodo* n : nodo->ramas)
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
    else if(nodo->categoría == Ñ::CategoríaNodo::NODO_EXPRESIÓN)
    {
        for(Ñ::Nodo* n : nodo->ramas)
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
    else if(nodo->categoría == Ñ::CategoríaNodo::NODO_DECLARA_VARIABLE)
    {
        std::string nombre = ((Ñ::DeclaraVariable*)nodo)->variable;
        if(tablaSímbolos->nombreReservadoEnEsteÁmbito(nombre))
        {
            resultado.error("RESOLUCIÓN DE SÍMBOLOS :: El identificador \"" + nombre + "\" ya se había declarado previamente");
            return resultado;
        }

        if( nodo->ramas.size() != 1)
        {
            resultado.error("RESOLUCIÓN DE SÍMBOLOS :: Árbol de la declaración de variable mal construido");
            return resultado;
        }

        Ñ::Resultado r = tablaSímbolos->declara(nombre, nodo->ramas[0]);
        if(r.error())
        {
            return r;
        }

        resultado.éxito();
        return resultado;
    }
    else if(nodo->categoría == Ñ::CategoríaNodo::NODO_ASIGNA)
    {
        for(Ñ::Nodo* n : nodo->ramas)
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
    else if(nodo->categoría == Ñ::CategoríaNodo::NODO_IGUALDAD)
    {
        for(Ñ::Nodo* n : nodo->ramas)
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
    else if(nodo->categoría == Ñ::CategoríaNodo::NODO_COMPARACIÓN)
    {
        for(Ñ::Nodo* n : nodo->ramas)
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
    else if(nodo->categoría == Ñ::CategoríaNodo::NODO_TÉRMINO)
    {
        for(Ñ::Nodo* n : nodo->ramas)
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
    else if(nodo->categoría == Ñ::CategoríaNodo::NODO_FACTOR)
    {
        for(Ñ::Nodo* n : nodo->ramas)
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
    else if(nodo->categoría == Ñ::CategoríaNodo::NODO_IDENTIFICADOR)
    {
        std::string nombre = ((Ñ::Identificador*)nodo)->id;
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
    else if(nodo->categoría == Ñ::CategoríaNodo::NODO_OP_BINARIA)
    {
        for(Ñ::Nodo* n : nodo->ramas)
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
    else if(nodo->categoría == Ñ::CategoríaNodo::NODO_OP_UNARIA)
    {
        for(Ñ::Nodo* n : nodo->ramas)
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
    else if(nodo->categoría == Ñ::CategoríaNodo::NODO_LITERAL)
    {
        resultado.éxito();
        return resultado;
    }
    else if(nodo->categoría == Ñ::CategoríaNodo::NODO_TIPO)
    {
        resultado.éxito();
        return resultado;
    }
    else if(nodo->categoría == Ñ::CategoríaNodo::NODO_LLAMA_FUNCIÓN)
    {
        Ñ::LlamaFunción* fn = (Ñ::LlamaFunción*)(nodo);
        
        if(!tablaSímbolos->nombreReservadoEnCualquierÁmbito(fn->nombre))
        {
            resultado.error("RESOLUCIÓN DE SÍMBOLOS :: " + fn->nombre + "() no está en la tabla de símbolos");
            return resultado;
        }

        resultado.éxito();
        return resultado;
    }
    else if(nodo->categoría == Ñ::CategoríaNodo::NODO_VACÍO)
    {
        resultado.éxito();
        return resultado;
    }

    resultado.error("RESOLUCIÓN DE SÍMBOLOS :: No esperaba este nodo.");
    return resultado;
}

Ñ::Resultado compruebaTiposLIA(Ñ::Nodo* nodo, Ñ::TablaSímbolos* tablaSímbolos)
{
    Ñ::Resultado resultado;

    if(nodo == nullptr)
    {
        resultado.error("ANÁLISIS DE TIPOS :: El nodo es nulo");
        return resultado;
    }
    
    if(nodo->categoría == Ñ::CategoríaNodo::NODO_DECLARA_VARIABLE)
    {
        if( nodo->ramas.size() != 1)
        {
            resultado.error("ANÁLISIS DE TIPOS :: Árbol de la declaración de variable mal construido");
            return resultado;
        }

        resultado.éxito();
        resultado.nodo(nodo->ramas[0]);
        return resultado;
    }
    else if(nodo->categoría == Ñ::CategoríaNodo::NODO_IDENTIFICADOR)
    {
        std::string nombre = ((Ñ::Identificador*)nodo)->id;
        if(tablaSímbolos->nombreReservadoEnCualquierÁmbito(nombre))
        {
            return tablaSímbolos->leeTipo(nombre);
        }
        else
        {
            resultado.error("RESOLUCIÓN DE SÍMBOLOS :: El identificador \"" + nombre + "\" no se había declarado previamente");
            return resultado;
        }
    }
    else
    {
        resultado.error("ANÁLISIS DE TIPOS :: El nodo tiene una categoría desconocida");
        return resultado;
    }
}

Ñ::Resultado compruebaTiposLDA(Ñ::Nodo* nodo, Ñ::TablaSímbolos* tablaSímbolos)
{
    Ñ::Resultado resultado;

    if(nodo->categoría == Ñ::CategoríaNodo::NODO_IDENTIFICADOR)
    {
        resultado = tablaSímbolos->leeTipo(((Ñ::Identificador*)nodo)->id);
        return resultado;
    }
    else if(nodo->categoría == Ñ::CategoríaNodo::NODO_VALOR)
    {

    }
    else if(nodo->categoría == Ñ::CategoríaNodo::NODO_LITERAL)
    {
        
    }

    resultado.error("El árbol de nodos es incorrecto, esperaba Lado Derecho de Asignación. Categoría del nódulo actual: " + std::to_string(nodo->categoría));
    return resultado;
}


Ñ::Resultado compruebaTipos(Ñ::Nodo* nodo, Ñ::TablaSímbolos* tablaSímbolos)
{
    Ñ::Resultado resultado;

    if(nodo == nullptr)
    {
        resultado.error("ANÁLISIS DE TIPOS :: El nodo es nulo");
        return resultado;
    }

    if(nodo->categoría == Ñ::CategoríaNodo::NODO_MÓDULO)
    {
        for(Ñ::Nodo* n : nodo->ramas)
        {
            Ñ::Resultado rCompruebaTipos = compruebaTipos(n, tablaSímbolos);
            
            if(rCompruebaTipos.error())
            {
                return rCompruebaTipos;
            }
        }
        
        resultado.éxito();
        return resultado;
    }
    else if(nodo->categoría == Ñ::CategoríaNodo::NODO_EXPRESIÓN)
    {
        for(Ñ::Nodo* n : nodo->ramas)
        {
            Ñ::Resultado rCompruebaTipos = compruebaTipos(n, tablaSímbolos);
            
            if(rCompruebaTipos.error())
            {
                return rCompruebaTipos;
            }
        }
        
        resultado.éxito();
        return resultado;
    }
    else if(nodo->categoría == Ñ::CategoríaNodo::NODO_ASIGNA)
    {
        // Analizo LIA, puede haber una declaración o una variable
        Ñ::CategoríaNodo catLIA = nodo->ramas[0]->categoría;
        Ñ::Resultado rTipoLIA = compruebaTiposLIA(nodo->ramas[0], tablaSímbolos);
        if(rTipoLIA.error())
        {
            return rTipoLIA;
        }
        
        resultado.éxito();
        return resultado;
    }
    else if(nodo->categoría == Ñ::CategoríaNodo::NODO_DECLARA_VARIABLE)
    {
        return compruebaTiposLIA(nodo, tablaSímbolos);
    }
    else
    {
        resultado.error("ANÁLISIS DE TIPOS :: El nodo tiene una categoría desconocida");
        return resultado;
    }
}

Ñ::Resultado Ñ::analizaSemántica(Ñ::Nodo* nodo, Ñ::TablaSímbolos* tablaSímbolos)
{
    Ñ::Resultado resultado;

    if(nodo == nullptr)
    {
        resultado.error("SEMÁNTICO :: El nodo raíz es nulo");
        return resultado;
    }

    if(nodo->ramas.size() < 1)
    {
        resultado.error("SEMÁNTICO :: El nodo raíz está vacío");
        return resultado;
    }

    Ñ::Resultado rResuelveSímbolos = resuelveSímbolos(nodo, tablaSímbolos);
    if(rResuelveSímbolos.error())
    {
        resultado.error("SEMÁNTICO :: " + rResuelveSímbolos.mensaje());
        return resultado;
    }
    Ñ::Resultado rCompruebaTipos = compruebaTipos(nodo, tablaSímbolos);
    if(rCompruebaTipos.error())
    {
        resultado.error("SEMÁNTICO :: " + rCompruebaTipos.mensaje());
        return resultado;
    }

    resultado.éxito();
    return resultado;
}