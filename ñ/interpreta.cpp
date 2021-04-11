#include <iostream>

#include "interpreta.hpp"

void Ñ::interpretaNodos(Ñ::Nodo* nodos, std::map<std::string, Ñ::Símbolo> tablaSímbolos)
{
    Ñ::LlamaFunción* fn = (Ñ::LlamaFunción*)(nodos->ramas[0]);
    //std::cout << "SEMÁNTICO :: Compruebo si la función " << fn->función << "() es ejecutable" << std::endl;

    if ( tablaSímbolos.count(fn->función) == 0 )
    {
        std::cout << fn->función << "() no está en la tabla de símbolos" << std::endl;
    }
    else
    {
        Ñ::Símbolo s = tablaSímbolos.at(fn->función);
        if(s.esEjecutable())
        {
            //std::cout << fn->función << "() está en la tabla de símbolos y es ejecutable" << std::endl;
            //std::cout << "ejecuto " << fn->función << "()" << std::endl;
            s.ejecuta();
        }
        else
        {
            std::cout << fn->función << "() está en la tabla de símbolos pero debe implementarse" << std::endl;
        }
    }
}