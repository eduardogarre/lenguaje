#pragma once

#include <string>
#include <vector>

namespace Ñ
{
    extern enum CategoríaTipo;
    extern class TablaSímbolos;
    extern class Tipo;

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
        NODO_ELEMENTO_VECTOR,
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

        void muestra(TablaSímbolos* tablaSímbolos = nullptr);
    };

    class Literal : Nodo
    {
    public:
        Ñ::CategoríaTipo tipo;
        std::string dato;

        Literal();
        ~Literal();

        void muestra(TablaSímbolos* tablaSímbolos = nullptr);
    };

    class Identificador : Nodo
    {
    public:
        std::string id;

        Identificador();
        ~Identificador();

        void muestra(TablaSímbolos* tablaSímbolos = nullptr);
    };

    class ConvierteTipos : Nodo
    {
    public:
        Ñ::Tipo* origen;
        Ñ::Tipo* destino;

        ConvierteTipos();
        ~ConvierteTipos();

        void muestra(TablaSímbolos* tablaSímbolos = nullptr);
    };

    class LadoIzquierdoAsignación : Nodo
    {
    public:
        LadoIzquierdoAsignación();
        ~LadoIzquierdoAsignación();

        void muestra(TablaSímbolos* tablaSímbolos = nullptr);
    };

    class LadoDerechoAsignación : Nodo
    {
    public:
        LadoDerechoAsignación();
        ~LadoDerechoAsignación();

        void muestra(TablaSímbolos* tablaSímbolos = nullptr);
    };

    class Igualdad : Nodo
    {
    public:
        Igualdad();
        ~Igualdad();

        void muestra(TablaSímbolos* tablaSímbolos = nullptr);
    };

    class Comparación : Nodo
    {
    public:
        Comparación();
        ~Comparación();

        void muestra(TablaSímbolos* tablaSímbolos = nullptr);
    };

    class Término : Nodo
    {
    public:
        Término();
        ~Término();

        void muestra(TablaSímbolos* tablaSímbolos = nullptr);
    };

    class Factor : Nodo
    {
    public:
        Factor();
        ~Factor();

        void muestra(TablaSímbolos* tablaSímbolos = nullptr);
    };

    class OperaciónBinaria : Nodo
    {
    public:
        std::string operación;
        Ñ::Tipo* tipo = nullptr;        

        OperaciónBinaria();
        ~OperaciónBinaria();

        void muestra(TablaSímbolos* tablaSímbolos = nullptr);
    };

    class OperaciónUnaria : Nodo
    {
    public:
        std::string operación;

        OperaciónUnaria();
        ~OperaciónUnaria();

        void muestra(TablaSímbolos* tablaSímbolos = nullptr);
    };

    class ElementoVector : Nodo
    {
    public:
        uint64_t posición = 0;

        ElementoVector();
        ~ElementoVector();

        void muestra(TablaSímbolos* tablaSímbolos = nullptr);
    };

    class Primario : Nodo
    {
    public:
        std::string primario;

        Primario();
        ~Primario();

        void muestra(TablaSímbolos* tablaSímbolos = nullptr);
    };

    class DeclaraVariable : Nodo
    {
    public:
        std::string variable;

        DeclaraVariable();
        ~DeclaraVariable();

        void muestra(TablaSímbolos* tablaSímbolos = nullptr);
    };

    class Asigna : Nodo
    {
    public:
        Asigna();
        ~Asigna();

        void muestra(TablaSímbolos* tablaSímbolos = nullptr);
    };

    class Argumento : Nodo
    {
    public:
        Argumento();
        ~Argumento();

        void muestra(TablaSímbolos* tablaSímbolos = nullptr);
    };

    class Argumentos : Nodo
    {
    public:
        Argumentos();
        ~Argumentos();

        void muestra(TablaSímbolos* tablaSímbolos = nullptr);
    };

    class LlamaFunción : Nodo
    {
    public:
        std::string nombre;

        LlamaFunción();
        ~LlamaFunción();

        void muestra(TablaSímbolos* tablaSímbolos = nullptr);
    };

    class Devuelve : Nodo
    {
    public:
        Devuelve();
        ~Devuelve();

        void muestra(TablaSímbolos* tablaSímbolos = nullptr);
    };

    class Expresión : Nodo
    {
    public:
        Expresión();
        ~Expresión();

        void muestra(TablaSímbolos* tablaSímbolos = nullptr);
    };

    class Bloque : Nodo
    {
    public:
        Bloque();
        ~Bloque();

        void muestra(TablaSímbolos* tablaSímbolos = nullptr);
    };

    class SiCondicional : Nodo
    {
    public:
        SiCondicional();
        ~SiCondicional();

        void muestra(TablaSímbolos* tablaSímbolos = nullptr);
    };

    class DefineFunción : Nodo
    {
    public:
        std::string nombre;
        bool público;

        DefineFunción();
        ~DefineFunción();

        void muestra(TablaSímbolos* tablaSímbolos = nullptr);
    };

    class DeclaraFunción : Nodo
    {
    public:
        std::string nombre;
        bool externo;

        DeclaraFunción();
        ~DeclaraFunción();

        void muestra(TablaSímbolos* tablaSímbolos = nullptr);
    };

    class Función : Nodo
    {
    public:
        std::string nombre;

        Función();
        ~Función();

        void muestra(TablaSímbolos* tablaSímbolos = nullptr);
    };

    class FunciónEjecutable : Nodo
    {
    public:
        std::string nombre;
        Ñ::Nodo* (*función)(Ñ::Nodo* yo, Ñ::Nodo* argumentos);

        FunciónEjecutable();
        ~FunciónEjecutable();

        void muestra(TablaSímbolos* tablaSímbolos = nullptr);
    };

    class Módulo : Nodo
    {
    public:
        std::string módulo;

        Módulo();
        ~Módulo();

        void muestra(TablaSímbolos* tablaSímbolos = nullptr);
    };


    std::string obténNombreDeNodo(Ñ::CategoríaNodo n);
    void borraNodos(Ñ::Nodo* nodos);
    void muestraNodos(Nodo* nodo, TablaSímbolos* tablaSímbolos = nullptr);
    bool sonÁrbolesDuplicados(Nodo* nodo1, Nodo* nodo2);
    Nodo* duplicaÁrbol(Nodo* nodo);
}