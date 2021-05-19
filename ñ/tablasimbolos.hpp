#pragma once

#include <map>
#include <string>

#include "nodo.hpp"
#include "resultado.hpp"

namespace Ñ
{
    class Símbolo;

    class TablaSímbolos
    {
    private:
        std::map<std::string, Símbolo*> _tabla;
        TablaSímbolos* _superior;

    public:
        TablaSímbolos();
        TablaSímbolos(TablaSímbolos* tablaSuperior);
        ~TablaSímbolos();
        
        bool nombreAsignadoEnEsteÁmbito(std::string id);
        bool nombreAsignadoEnCualquierÁmbito(std::string id);
        Resultado declaraFunción(std::string id);
        Resultado defineFunciónEjecutable(std::string id, void (*fn)(Ñ::Argumentos* args), Ñ::Nodo* args = nullptr);
        Resultado ejecutaFunción(std::string id, Ñ::Nodo* args);

        Resultado declaraVariable(std::string id, Ñ::Nodo* tipo);
        Resultado ponValor(std::string id, Ñ::Nodo* valor);
        Resultado leeValor(std::string id);

        void muestra();
    };
}