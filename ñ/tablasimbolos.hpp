#pragma once

#include <map>
#include <string>

#include "nodo.hpp"
#include "resultado.hpp"

namespace Ñ
{
    class Símbolo
    {
    public:
        Símbolo(std::string nombre, Ñ::Nodo* tipo);
        ~Símbolo();

        std::string nombre();
        Ñ::Nodo* tipo();
        void valor(Ñ::Nodo* valor);
        Ñ::Nodo* valor();
        //void muestra();
        
    private:
        std::string _nombre;
        Ñ::Nodo* _tipo;
        Ñ::Nodo* _valor;
    };

    class TablaSímbolos
    {
    private:
        std::map<std::string, Símbolo*> _tabla;
        TablaSímbolos* _superior;

        std::string funciónPropietaria;

    public:
        TablaSímbolos();
        TablaSímbolos(TablaSímbolos* tablaSuperior);
        ~TablaSímbolos();
        
        bool nombreReservadoEnEsteÁmbito(std::string id);
        bool nombreReservadoEnCualquierÁmbito(std::string id);
        Ñ::Resultado declara(std::string nombre, Ñ::Nodo* tipo);
        Ñ::Resultado ponValor(std::string nombre, Ñ::Nodo* valor);
        Ñ::Resultado leeValor(std::string nombre);
        Ñ::Resultado leeTipo(std::string nombre);
        
        void ponFunciónPropietaria(std::string fn);
        std::string leeFunciónPropietaria();

        Ñ::Resultado defineFunciónEjecutable(std::string nombre, Ñ::Nodo* (fne)(Ñ::Nodo*, Ñ::Nodo*), Ñ::Nodo* firma = nullptr);

        void muestra();
    };
}