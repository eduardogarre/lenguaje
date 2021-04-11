#pragma once

#include <string>
#include <vector>

namespace Ñ
{
    // Análisis sintáctico
    enum CategoríaNodo {
        NODO_VACÍO,

        NODO_LITERAL,
        NODO_TIPO,
        NODO_IDENTIFICADOR,

        NODO_EXPRESIÓN,
        NODO_TÉRMINO,
        NODO_FACTOR,

        NODO_DECLARA_VARIABLE,
        NODO_ASIGNA,
        NODO_DECLARA_Y_ASIGNA_VARIABLE,
        NODO_DECLARA_FUNCIÓN,
        NODO_DEFINE_FUNCIÓN,
        NODO_LLAMA_FUNCIÓN,

        NODO_AFIRMA
    };

    class Nodo
    {
    public:
        CategoríaNodo categoría;
        std::vector<Ñ::Nodo*> ramas;

        Nodo();
        ~Nodo();

        void muestra();
    };

    class Literal : Nodo
    {
    public:
        std::string dato;

        Literal();
        ~Literal();

        void muestra();
    };

    class Identificador : Nodo
    {
    public:
        std::string id;

        Identificador();
        ~Identificador();

        void muestra();
    };

    class Tipo : Nodo
    {
    public:
        std::string tipo;
        bool vector;

        Tipo();
        ~Tipo();

        void muestra();
    };

    class Expresión : Nodo
    {
    public:
        std::string operación;

        Expresión();
        ~Expresión();

        void muestra();
    };

    class Término : Nodo
    {
    public:
        std::string operación;

        Término();
        ~Término();

        void muestra();
    };

    class Factor : Nodo
    {
    public:
        std::string factor;

        Factor();
        ~Factor();

        void muestra();
    };

    class DeclaraVariable : Nodo
    {
    public:
        std::string variable;

        DeclaraVariable();
        ~DeclaraVariable();

        void muestra();
    };

    class Asigna : Nodo
    {
    public:
        Asigna();
        ~Asigna();

        void muestra();
    };

    class LlamaFunción : Nodo
    {
    public:
        std::string función;

        LlamaFunción();
        ~LlamaFunción();

        void muestra();
    };

    class Afirma : Nodo
    {
    public:

        Afirma();
        ~Afirma();

        void muestra();
    };
    
    void muestraNodos(Nodo* nodo);
}