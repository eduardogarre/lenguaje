#pragma once

#include <string>
#include <vector>

namespace Ñ
{
    // Análisis sintáctico
    enum CategoríaNodo {
        NODO_VACÍO,

        NODO_EXPANDIDO,

        NODO_LITERAL,
        NODO_TIPO,
        NODO_IDENTIFICADOR,

        NODO_LADO_IZQUIERDO_ASIGNACIÓN,
        NODO_LADO_DERECHO_ASIGNACIÓN,
        NODO_IGUALDAD,
        NODO_COMPARACIÓN,
        NODO_TÉRMINO,
        NODO_FACTOR,
        NODO_OP_BINARIA,
        NODO_OP_UNARIA,
        NODO_PRIMARIO,

        NODO_DECLARA_VARIABLE,
        NODO_ASIGNA,
        NODO_DECLARA_Y_ASIGNA_VARIABLE,
        NODO_ARGUMENTO,
        NODO_ARGUMENTOS,
        NODO_DECLARA_FUNCIÓN,
        NODO_DEFINE_FUNCIÓN,
        NODO_LLAMA_FUNCIÓN,

        NODO_EXPRESIÓN,

        NODO_BLOQUE,

        NODO_MÓDULO
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

    class LadoIzquierdoAsignación : Nodo
    {
    public:
        LadoIzquierdoAsignación();
        LadoIzquierdoAsignación(const Ñ::LadoIzquierdoAsignación& nodo);
        ~LadoIzquierdoAsignación();

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

    class Igualdad : Nodo
    {
    public:
        Igualdad();
        Igualdad(const Ñ::Igualdad& nodo);
        ~Igualdad();

        void muestra();
    };

    class Comparación : Nodo
    {
    public:
        Comparación();
        Comparación(const Ñ::Comparación& nodo);
        ~Comparación();

        void muestra();
    };

    class Término : Nodo
    {
    public:
        Término();
        Término(const Ñ::Término& nodo);
        ~Término();

        void muestra();
    };

    class Factor : Nodo
    {
    public:
        Factor();
        Factor(const Ñ::Factor& nodo);
        ~Factor();

        void muestra();
    };

    class OperaciónBinaria : Nodo
    {
    public:
        std::string operación;

        OperaciónBinaria();
        OperaciónBinaria(const Ñ::OperaciónBinaria& nodo);
        ~OperaciónBinaria();

        void muestra();
    };

    class OperaciónUnaria : Nodo
    {
    public:
        std::string operación;

        OperaciónUnaria();
        OperaciónUnaria(const Ñ::OperaciónUnaria& nodo);
        ~OperaciónUnaria();

        void muestra();
    };

    class Primario : Nodo
    {
    public:
        std::string primario;

        Primario();
        Primario(const Ñ::Primario& nodo);
        ~Primario();

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

    class Argumento : Nodo
    {
    public:
        Argumento();
        Argumento(const Ñ::Argumento& nodo);
        ~Argumento();

        void muestra();
    };

    class Argumentos : Nodo
    {
    public:
        Argumentos();
        Argumentos(const Ñ::Argumentos& nodo);
        ~Argumentos();

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

    class Bloque : Nodo
    {
    public:
        Bloque();
        Bloque(const Ñ::Bloque& nodo);
        ~Bloque();

        void muestra();
    };

    class DefineFunción : Nodo
    {
    public:
        std::string función;

        DefineFunción();
        DefineFunción(const Ñ::DefineFunción& nodo);
        ~DefineFunción();

        void muestra();
    };

    class Módulo : Nodo
    {
    public:
        std::string módulo;

        Módulo();
        Módulo(const Ñ::Módulo& nodo);
        ~Módulo();

        void muestra();
    };

    void borraNodos(Ñ::Nodo* nodos);
    void muestraNodos(Nodo* nodo);
    bool sonÁrbolesDuplicados(Nodo* nodo1, Nodo* nodo2);
    Nodo* duplicaÁrbol(Nodo* nodo);
}