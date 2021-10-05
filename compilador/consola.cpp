#include <iostream>
#include <string>

#include "ñ/ñ.hpp"

#include "consola.hpp"
#include "herramientas.hpp"

namespace Compilador
{
    void escribe(std::string texto)
    {
        std::cout << texto;
    }

    void escribeln(std::string texto)
    {
        escribe(texto);
        escribe("\n");
    }

    void escribeError(std::string texto, std::string archivo, Ñ::Posición* posición)
    {
        uint64_t cursor = posición->cursor();

        std::string código = leeArchivo(archivo);

        if(cursor >= código.size())
        {
            return;
        }

        uint64_t inicio;
        uint64_t fin;
        uint64_t i;

        for(i = cursor; i > 0 && i < código.size() && código[i] != '\r' && código[i] != '\n'; i--)
        {

        }

        inicio = i + 1;

        for(i = cursor; i > 0 && i < código.size() && código[i] != '\r' && código[i] != '\n'; i++)
        {

        }

        fin = i;

        std::string prefijo = código.substr(inicio, cursor - inicio);
        std::string color   = código.substr(cursor, posición->longitud());
        std::string posfijo = código.substr(cursor + posición->longitud(), fin - cursor - posición->longitud());

        std::cout << "\x1B[91m";
        std::cout << "Error: ";
        std::cout << "\033[0m";
        std::cout << "[" << archivo << ":";
        std::cout << posición->línea() << "] ";
        std::cout << texto;
        std::cout << std::endl;
        std::cout << "L" << posición->línea() << ": ";
        std::cout << prefijo;
        std::cout << "\x1B[91m";
        std::cout << color;
        std::cout << "\033[0m";
        std::cout << posfijo;
        std::cout << std::endl << std::endl;

        //std::cout << "\x1B[91mERROR\033[0m [" << archivo << "  " << pos << "] \"" << texto << "\"" << std::endl;
    }

    void escribeAviso(std::string texto, std::string archivo, Ñ::Posición* posición)
    {
        uint64_t cursor = posición->cursor();

        std::string código = leeArchivo(archivo);

        if(cursor >= código.size())
        {
            return;
        }

        uint64_t inicio;
        uint64_t fin;
        uint64_t i;

        for(i = cursor; i > 0 && i < código.size() && código[i] != '\r' && código[i] != '\n'; i--)
        {

        }

        inicio = i + 1;

        for(i = cursor; i > 0 && i < código.size() && código[i] != '\r' && código[i] != '\n'; i++)
        {

        }

        fin = i;

        std::string prefijo = código.substr(inicio, cursor - inicio);
        std::string color   = código.substr(cursor, posición->longitud());
        std::string posfijo = código.substr(cursor + posición->longitud(), fin - cursor - posición->longitud());

        std::cout << "\x1B[93m";
        std::cout << "Aviso: ";
        std::cout << "\033[0m";
        std::cout << "[" << archivo << ":";
        std::cout << posición->línea() << "] ";
        std::cout << texto;
        std::cout << std::endl;
        std::cout << "L" << posición->línea() << ": ";
        std::cout << prefijo;
        std::cout << "\x1B[93m";
        std::cout << color;
        std::cout << "\033[0m";
        std::cout << posfijo;
        std::cout << std::endl << std::endl;

        //std::cout << "\x1B[93mERROR\033[0m [" << archivo << "  " << pos << "] \"" << texto << "\"" << std::endl;
    }

}