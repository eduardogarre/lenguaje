#pragma once

#include <string>
#include <vector>

namespace Ñ
{
    extern enum CategoríaTipo;

    // Análisis sintáctico
    enum CategoríaNodo {
        NODO_VACÍO,

        NODO_EXPANDIDO,
        
        NODO_TIPO,
        NODO_VALOR,

        NODO_LITERAL,
        NODO_IDENTIFICADOR,

        NODO_CONVIERTE_TIPOS,

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
        
        NODO_DEVUELVE,

        NODO_EXPRESIÓN,
        
        NODO_BLOQUE,
        NODO_SI_CONDICIONAL,
        
        NODO_FUNCIÓN,
        NODO_FUNCIÓN_EJECUTABLE,

        NODO_MÓDULO
    };

    class Nodo
    {
    public:
        CategoríaNodo categoría;
        std::vector<Ñ::Nodo*> ramas;

        Nodo();
        ~Nodo();

        void imprimeAjuste();

        void muestra();
    };

    class Literal : Nodo
    {
    public:
        Ñ::CategoríaTipo tipo;
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

    class ConvierteTipos : Nodo
    {
    public:
        Ñ::CategoríaTipo origen;
        Ñ::CategoríaTipo destino;

        ConvierteTipos();
        ~ConvierteTipos();

        void muestra();
    };

    class LadoIzquierdoAsignación : Nodo
    {
    public:
        LadoIzquierdoAsignación();
        ~LadoIzquierdoAsignación();

        void muestra();
    };

    class LadoDerechoAsignación : Nodo
    {
    public:
        LadoDerechoAsignación();
        ~LadoDerechoAsignación();

        void muestra();
    };

    class Igualdad : Nodo
    {
    public:
        Igualdad();
        ~Igualdad();

        void muestra();
    };

    class Comparación : Nodo
    {
    public:
        Comparación();
        ~Comparación();

        void muestra();
    };

    class Término : Nodo
    {
    public:
        Término();
        ~Término();

        void muestra();
    };

    class Factor : Nodo
    {
    public:
        Factor();
        ~Factor();

        void muestra();
    };

    class OperaciónBinaria : Nodo
    {
    public:
        std::string operación;
        Ñ::CategoríaTipo tipo;        

        OperaciónBinaria();
        ~OperaciónBinaria();

        void muestra();
    };

    class OperaciónUnaria : Nodo
    {
    public:
        std::string operación;

        OperaciónUnaria();
        ~OperaciónUnaria();

        void muestra();
    };

    class Primario : Nodo
    {
    public:
        std::string primario;

        Primario();
        ~Primario();

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

    class Argumento : Nodo
    {
    public:
        Argumento();
        ~Argumento();

        void muestra();
    };

    class Argumentos : Nodo
    {
    public:
        Argumentos();
        ~Argumentos();

        void muestra();
    };

    class LlamaFunción : Nodo
    {
    public:
        std::string nombre;

        LlamaFunción();
        ~LlamaFunción();

        void muestra();
    };

    class Devuelve : Nodo
    {
    public:
        Devuelve();
        ~Devuelve();

        void muestra();
    };

    class Expresión : Nodo
    {
    public:
        Expresión();
        ~Expresión();

        void muestra();
    };

    class Bloque : Nodo
    {
    public:
        Bloque();
        ~Bloque();

        void muestra();
    };

    class SiCondicional : Nodo
    {
    public:
        SiCondicional();
        ~SiCondicional();

        void muestra();
    };

    class DefineFunción : Nodo
    {
    public:
        std::string nombre;
        bool público;

        DefineFunción();
        ~DefineFunción();

        void muestra();
    };

    class DeclaraFunción : Nodo
    {
    public:
        std::string nombre;
        bool externo;

        DeclaraFunción();
        ~DeclaraFunción();

        void muestra();
    };

    class Función : Nodo
    {
    public:
        std::string nombre;

        Función();
        ~Función();

        void muestra();
    };

    class FunciónEjecutable : Nodo
    {
    public:
        std::string nombre;
        Ñ::Nodo* (*función)(Ñ::Nodo* yo, Ñ::Nodo* argumentos);

        FunciónEjecutable();
        ~FunciónEjecutable();

        void muestra();
    };

    class Módulo : Nodo
    {
    public:
        std::string módulo;

        Módulo();
        ~Módulo();

        void muestra();
    };


    std::string obténNombreDeNodo(Ñ::CategoríaNodo n);
    void borraNodos(Ñ::Nodo* nodos);
    void muestraNodos(Nodo* nodo);
    bool sonÁrbolesDuplicados(Nodo* nodo1, Nodo* nodo2);
    Nodo* duplicaÁrbol(Nodo* nodo);
}