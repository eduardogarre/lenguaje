#pragma once

#include <string>

namespace Ñ
{
    extern class Posición;

    class Resultado
    {
    private:
        bool _error;
        std::string _mensaje;
        Ñ::Nodo* _nodo;
        Ñ::Posición* _posición = nullptr;

    public:
        Resultado();

        Ñ::Posición* posición();
        void posición(Ñ::Posición* pos);

        bool error();
        void error(std::string mensaje);
        void éxito();
        std::string mensaje();

        void nodo(Ñ::Nodo* nodo);
        Ñ::Nodo* nodo();
    };
}