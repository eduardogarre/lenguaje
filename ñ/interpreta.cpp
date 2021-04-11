#include <iostream>

#include "interpreta.hpp"

Ñ::Resultado Ñ::interpretaNodos(Ñ::Nodo* nodos, std::map<std::string, Ñ::Símbolo> tablaSímbolos)
{
    Ñ::Resultado resultado;

    if(nodos->ramas[0]->categoría == Ñ::CategoríaNodo::NODO_LLAMA_FUNCIÓN)
    {
        Ñ::LlamaFunción* fn = (Ñ::LlamaFunción*)(nodos->ramas[0]);
        //std::cout << "SEMÁNTICO :: Compruebo si la función " << fn->función << "() es ejecutable" << std::endl;

        if ( tablaSímbolos.count(fn->función) == 0 )
        {
            resultado.error(fn->función + "() no está en la tabla de símbolos");
            return resultado;
        }
        else
        {
            Ñ::Símbolo s = tablaSímbolos.at(fn->función);
            if(s.esFunciónEjecutable())
            {
                //std::cout << fn->función << "() está en la tabla de símbolos y es ejecutable" << std::endl;
                //std::cout << "ejecuto " << fn->función << "()" << std::endl;
                s.ejecutaFunción();

                resultado.éxito();
                return resultado;
            }
            else
            {
                resultado.error(fn->función + "() está en la tabla de símbolos pero debe implementarse");
                return resultado;
            }
        }
    }
    else if(nodos->ramas[0]->categoría == Ñ::CategoríaNodo::NODO_DECLARA_VARIABLE)
    {
        muestraNodos(nodos);
        return resultado;
    }

    resultado.error("No se consigue interpretar el árbol de nodos");
    return resultado;
}