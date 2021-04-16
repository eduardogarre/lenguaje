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

        NODO_LADO_DERECHO_ASIGNACIÓN,
        NODO_OP_SUMA_RESTA,
        NODO_OP_MULTIPLICACIÓN_DIVISIÓN,
        NODO_FACTOR,

        NODO_DECLARA_VARIABLE,
        NODO_ASIGNA,
        NODO_DECLARA_Y_ASIGNA_VARIABLE,
        NODO_DECLARA_FUNCIÓN,
        NODO_DEFINE_FUNCIÓN,
        NODO_LLAMA_FUNCIÓN,

        NODO_EXPRESIÓN
    };

    class Nodo
    {
    public:
        CategoríaNodo categoría;
        std::vector<Ñ::Nodo*> ramas;

        Nodo();
        Nodo(const Ñ::Nodo& nodo);
        ~Nodo();

        void muestra();
    };

    class Literal : Nodo
    {
    public:
        std::string dato;

        Literal();
        Literal(const Ñ::Literal& nodo);
        ~Literal();

        void muestra();
    };

    class Identificador : Nodo
    {
    public:
        std::string id;

        Identificador();
        Identificador(const Ñ::Identificador& nodo);
        ~Identificador();

        void muestra();
    };

    class Tipo : Nodo
    {
    public:
        std::string tipo;
        bool vector;

        Tipo();
        Tipo(const Ñ::Tipo& nodo);
        ~Tipo();

        void muestra();
    };

    class LadoDerechoAsignación : Nodo
    {
    public:
        LadoDerechoAsignación();
        LadoDerechoAsignación(const Ñ::LadoDerechoAsignación& nodo);
        ~LadoDerechoAsignación();

        void muestra();
    };

    class OpSumaResta : Nodo
    {
    public:
        std::string operación;

        OpSumaResta();
        OpSumaResta(const Ñ::OpSumaResta& nodo);
        ~OpSumaResta();

        void muestra();
    };

    class OpMultiplicaciónDivisión : Nodo
    {
    public:
        std::string operación;

        OpMultiplicaciónDivisión();
        OpMultiplicaciónDivisión(const Ñ::OpMultiplicaciónDivisión& nodo);
        ~OpMultiplicaciónDivisión();

        void muestra();
    };

    class Factor : Nodo
    {
    public:
        std::string factor;

        Factor();
        Factor(const Ñ::Factor& nodo);
        ~Factor();

        void muestra();
    };

    class DeclaraVariable : Nodo
    {
    public:
        std::string variable;

        DeclaraVariable();
        DeclaraVariable(const Ñ::DeclaraVariable& nodo);
        ~DeclaraVariable();

        void muestra();
    };

    class Asigna : Nodo
    {
    public:
        Asigna();
        Asigna(const Ñ::Asigna& nodo);
        ~Asigna();

        void muestra();
    };

    class LlamaFunción : Nodo
    {
    public:
        std::string función;

        LlamaFunción();
        LlamaFunción(const Ñ::LlamaFunción& nodo);
        ~LlamaFunción();

        void muestra();
    };

    class Expresión : Nodo
    {
    public:

        Expresión();
        Expresión(const Ñ::Expresión& nodo);
        ~Expresión();

        void muestra();
    };

    void borraNodos(Ñ::Nodo* nodos);
    void muestraNodos(Nodo* nodo);
}