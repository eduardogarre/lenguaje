#include <iostream>
#include <string>

#include "ñ/ñ.hpp"

#include "consola.hpp"
#include "herramientas.hpp"

namespace Compilador
{
    struct {
        std::string predefinido = "\033[0m";
        std::string blanco = "\x1B[97m";
        std::string grisclaro = "\x1B[37m";
        std::string gris = "\x1B[90m";
        std::string negro = "\x1B[30m";
        std::string rojo = "\x1B[31m";
        std::string verde = "\x1B[32m";
        std::string amarillo = "\x1B[33m";
        std::string azul = "\x1B[34m";
        std::string magenta = "\x1B[35m";
        std::string cian = "\x1B[36m";
        std::string rojoclaro = "\x1B[91m";
        std::string verdeclaro = "\x1B[92m";
        std::string amarilloclaro = "\x1B[93m";
        std::string azulclaro = "\x1B[94m";
        std::string magentaclaro = "\x1B[95m";
        std::string cianclaro = "\x1B[96m";
    } ColorConsola;

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
        std::string código;
        bool errorLeerArchivo = false;

        try
        {
            código = leeArchivo(archivo);
        }
        catch(...)
        {
            std::cout << texto << std::endl;
        }

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

        while(código[i] == '\r' || código[i] == '\n')
        {
            i++;
        }
        inicio = i;

        for(i = cursor; i > 0 && i < código.size() && código[i] != '\r' && código[i] != '\n'; i++)
        {

        }

        fin = i;

        std::string prefijo = código.substr(inicio, cursor - inicio);
        std::string color   = código.substr(cursor, posición->longitud());
        std::string posfijo = código.substr(cursor + posición->longitud(), fin - cursor - posición->longitud());

        std::cout << ColorConsola.rojoclaro;
        std::cout << "Error: [";
        std::cout << ColorConsola.cianclaro;
        std::cout << archivo;
        std::cout << ":" << posición->línea();
        std::cout << ":" << posición->columna();
        std::cout << ColorConsola.rojoclaro;
        std::cout << "]: ";
        std::cout << ColorConsola.predefinido;
        std::cout << texto;
        std::cout << std::endl;
        std::cout << ColorConsola.cianclaro;
        std::cout << "Línea " << posición->línea() << ": ";
        std::cout << ColorConsola.predefinido;
        std::cout << prefijo;
        std::cout << ColorConsola.rojoclaro;
        std::cout << color;
        std::cout << ColorConsola.predefinido;
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

        while(código[i] == '\r' || código[i] == '\n')
        {
            i++;
        }
        inicio = i;

        for(i = cursor; i > 0 && i < código.size() && código[i] != '\r' && código[i] != '\n'; i++)
        {

        }

        fin = i;

        std::string prefijo = código.substr(inicio, cursor - inicio);
        std::string color   = código.substr(cursor, posición->longitud());
        std::string posfijo = código.substr(cursor + posición->longitud(), fin - cursor - posición->longitud());

        std::cout << ColorConsola.amarilloclaro;
        std::cout << "Error: [";
        std::cout << ColorConsola.cianclaro;
        std::cout << archivo;
        std::cout << ":" << posición->línea();
        std::cout << ":" << posición->columna();
        std::cout << ColorConsola.amarilloclaro;
        std::cout << "]: ";
        std::cout << ColorConsola.predefinido;
        std::cout << texto;
        std::cout << std::endl;
        std::cout << ColorConsola.cianclaro;
        std::cout << "Línea " << posición->línea() << ": ";
        std::cout << ColorConsola.predefinido;
        std::cout << prefijo;
        std::cout << ColorConsola.amarilloclaro;
        std::cout << color;
        std::cout << ColorConsola.predefinido;
        std::cout << posfijo;
        std::cout << std::endl << std::endl;

        //std::cout << "\x1B[93mERROR\033[0m [" << archivo << "  " << pos << "] \"" << texto << "\"" << std::endl;
    }

}