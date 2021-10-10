#pragma once

#include <vector>

#include "lexema.hpp"
#include "nodo.hpp"

namespace Ñ
{
    class Sintaxis
    {
// Compilación condicional: si estamos en pruebas, expongo las funciones privadas del módulo
#ifdef EVALUANDO_PRUEBAS
    public:
#else
    private:
#endif
        uint32_t cursor;
        std::vector<Ñ::Lexema*> lexemas;

        bool notación(std::string carácter);
        bool reservada(std::string palabra);
        Ñ::Nodo* literal();
        Ñ::Nodo* tipo();
        Ñ::Nodo* identificador();
        Ñ::Nodo* puntero();
        Ñ::Nodo* primario();
        Ñ::Nodo* operaciónUnaria();
        Ñ::Nodo* elementoVector();
        Ñ::Nodo* factor();
        Ñ::Nodo* término();
        Ñ::Nodo* comparación();
        Ñ::Nodo* ladoIzquierdoAsignación();
        Ñ::Nodo* ladoDerechoAsignación();
        Ñ::Nodo* declaraVariable();
        Ñ::Nodo* asigna();
        Ñ::Nodo* declaraArgumento();
        Ñ::Nodo* declaraArgumentos();
        Ñ::Nodo* ponArgumento();
        Ñ::Nodo* ponArgumentos();
        Ñ::Nodo* llamaFunción();
        Ñ::Nodo* vuelve();
        Ñ::Nodo* devuelve();
        Ñ::Nodo* siCondicional();
        Ñ::Nodo* bucleMientras();
        Ñ::Nodo* expresión();
        Ñ::Nodo* bloque();
        Ñ::Nodo* defineFunción();
        Ñ::Nodo* declaraFunción();
        Ñ::Nodo* módulo(std::string nombre);

    public:
        Ñ::Nodo* analiza(std::vector<Ñ::Lexema*> _lexemas, std::string nombreArchivo);
        Ñ::Nodo* analizaComando(std::vector<Ñ::Lexema*> _lexemas);
    };
}