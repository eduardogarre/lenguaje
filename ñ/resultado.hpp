#pragma once

#include <string>

namespace Ñ
{

    class Resultado
    {
    public:
        bool _error;
        std::string _mensaje;

        Resultado() : _error(true) {}

        bool error() { return _error; }
        void error(std::string msj) { _error = true; _mensaje = msj; }
        void éxito() { _error = false; }
        std::string mensaje() { return (_error ? _mensaje : ""); }
    };
}