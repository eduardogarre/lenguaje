#pragma once

#include <string>

#include "posicion.hpp"

namespace Ñ
{

    class Resultado
    {
    private:
        bool _error;
        std::string _mensaje;
        Ñ::Nodo* _nodo;
        Posición _posición;

    public:
        Resultado(Posición posición = {}) : _error(true), _nodo(nullptr) {}

        Posición posición();

        bool error() { return _error; }
        void error(std::string mensaje) { _error = true; _mensaje = mensaje; }
        void éxito() { _error = false; }
        std::string mensaje() { return (_error ? _mensaje : ""); }

        void nodo(Ñ::Nodo* nodo) { _nodo = nodo; }
        Ñ::Nodo* nodo() { return (_error ? nullptr : _nodo); }
    };
}