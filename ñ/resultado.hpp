#pragma once

#include <string>

namespace Ñ
{

    class Resultado
    {
    private:
        bool _error;
        std::string _mensaje;
        Ñ::Nodo* _resultado;

    public:
        Resultado() : _error(true), _resultado(nullptr) {}

        bool error() { return _error; }
        void error(std::string mensaje) { _error = true; _mensaje = mensaje; }
        void éxito() { _error = false; }
        std::string mensaje() { return (_error ? _mensaje : ""); }

        void resultado(Ñ::Nodo* resultado) { _resultado = resultado; }
        Ñ::Nodo* resultado() { return (_error ? nullptr : _resultado); }
    };
}