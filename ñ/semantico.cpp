#include <iostream>
#include <map>

#include "nodo.hpp"
#include "resultado.hpp"
#include "semantico.hpp"
#include "simbolo.hpp"

std::map<std::string, Ñ::Símbolo> tablaSímbolos;

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

    if( nodos->ramas.size() == 1)
    {
        if(nodos->ramas[0]->categoría == Ñ::CategoríaNodo::NODO_LLAMA_FUNCIÓN)
        {
            Ñ::LlamaFunción* fn = (Ñ::LlamaFunción*)(nodos->ramas[0]);
            
            if( tablaSímbolos->count(fn->función) == 0 )
            {
                resultado.error("SEMÁNTICO :: " + fn->función + "() no está en la tabla de símbolos");
                return resultado;
            }
            else
            {
                Ñ::Símbolo s = tablaSímbolos->at(fn->función);
                if(!s.esFunciónEjecutable() && !s.esFunciónImplementada())
                {
                    resultado.error("SEMÁNTICO :: " + fn->función + "() está en la tabla de símbolos pero sin implementación");
                    return resultado;
                }
            }

            resultado.éxito();
            return resultado;
        }
        else if(nodos->ramas[0]->categoría == Ñ::CategoríaNodo::NODO_DECLARA_VARIABLE)
        {
            auto declvar = nodos->ramas[0];
            std::string nombre = ((Ñ::DeclaraVariable*)declvar)->variable;
            if(tablaSímbolos->count(nombre) > 0 )
            {
                resultado.error("SEMÁNTICO :: El identificador \"" + nombre + "\" ya se había declarado previamente");
            }

            if( declvar->ramas.size() != 1)
            {
                resultado.error("SEMÁNTICO :: Árbol de la declaración de variable mal construido");
                return resultado;
            }
            else if(declvar->ramas[0]->categoría == Ñ::CategoríaNodo::NODO_TIPO)
            {
                auto tipo = (declvar->ramas[0]);
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
                    resultado.error("SEMÁNTICO :: Tipo desconocido");
                    return resultado;
                }
            }
            else
            {
                resultado.error("SEMÁNTICO :: La declaración de variable no contiene tipo");
                return resultado;
            }

            resultado.éxito();
            return resultado;
        }
    }

    resultado.error("SEMÁNTICO :: No reconozco el árbol de nodos");
    return resultado;
}