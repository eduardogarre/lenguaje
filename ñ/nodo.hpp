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

        virtual void muestra(TablaSímbolos* tablaSímbolos = nullptr);
    };

    class Literal : public Nodo
    {
    public:
        Ñ::CategoríaTipo tipo;
        std::string dato;

        Literal();
        ~Literal();

        void muestra(TablaSímbolos* tablaSímbolos = nullptr) override;
    };

    class Identificador : public Nodo
    {
    public:
        std::string id;

        Identificador();
        ~Identificador();

        void muestra(TablaSímbolos* tablaSímbolos = nullptr) override;
    };

    class ConvierteTipos : public Nodo
    {
    public:
        Ñ::Tipo* origen;
        Ñ::Tipo* destino;

        ConvierteTipos();
        ~ConvierteTipos();

        void muestra(TablaSímbolos* tablaSímbolos = nullptr) override;
    };

    class LadoIzquierdoAsignación : public Nodo
    {
    public:
        LadoIzquierdoAsignación();
        ~LadoIzquierdoAsignación();

        void muestra(TablaSímbolos* tablaSímbolos = nullptr) override;
    };

    class LadoDerechoAsignación : public Nodo
    {
    public:
        LadoDerechoAsignación();
        ~LadoDerechoAsignación();

        void muestra(TablaSímbolos* tablaSímbolos = nullptr) override;
    };

    class Igualdad : public Nodo
    {
    public:
        Igualdad();
        ~Igualdad();

        void muestra(TablaSímbolos* tablaSímbolos = nullptr) override;
    };

    class Comparación : public Nodo
    {
    public:
        Comparación();
        ~Comparación();

        void muestra(TablaSímbolos* tablaSímbolos = nullptr) override;
    };

    class Término : public Nodo
    {
    public:
        Término();
        ~Término();

        void muestra(TablaSímbolos* tablaSímbolos = nullptr) override;
    };

    class Factor : public Nodo
    {
    public:
        Factor();
        ~Factor();

        void muestra(TablaSímbolos* tablaSímbolos = nullptr) override;
    };

    class OperaciónBinaria : public Nodo
    {
    public:
        std::string operación;
        Ñ::Tipo* tipo = nullptr;        

        OperaciónBinaria();
        ~OperaciónBinaria();

        void muestra(TablaSímbolos* tablaSímbolos = nullptr) override;
    };

    class OperaciónUnaria : public Nodo
    {
    public:
        std::string operación;

        OperaciónUnaria();
        ~OperaciónUnaria();

        void muestra(TablaSímbolos* tablaSímbolos = nullptr) override;
    };

    class ElementoVector : public Nodo
    {
    public:
        uint64_t posición = 0;

        ElementoVector();
        ~ElementoVector();

        void muestra(TablaSímbolos* tablaSímbolos = nullptr) override;
    };

    class Primario : public Nodo
    {
    public:
        std::string primario;

        Primario();
        ~Primario();

        void muestra(TablaSímbolos* tablaSímbolos = nullptr) override;
    };

    class DeclaraVariable : public Nodo
    {
    public:
        std::string variable;

        DeclaraVariable();
        ~DeclaraVariable();

        void muestra(TablaSímbolos* tablaSímbolos = nullptr) override;
    };

    class Asigna : public Nodo
    {
    public:
        Asigna();
        ~Asigna();

        void muestra(TablaSímbolos* tablaSímbolos = nullptr) override;
    };

    class Argumento : public Nodo
    {
    public:
        Argumento();
        ~Argumento();

        void muestra(TablaSímbolos* tablaSímbolos = nullptr) override;
    };

    class Argumentos : public Nodo
    {
    public:
        Argumentos();
        ~Argumentos();

        void muestra(TablaSímbolos* tablaSímbolos = nullptr) override;
    };

    class LlamaFunción : public Nodo
    {
    public:
        std::string nombre;

        LlamaFunción();
        ~LlamaFunción();

        void muestra(TablaSímbolos* tablaSímbolos = nullptr) override;
    };

    class Devuelve : public Nodo
    {
    public:
        Devuelve();
        ~Devuelve();

        void muestra(TablaSímbolos* tablaSímbolos = nullptr) override;
    };

    class Expresión : public Nodo
    {
    public:
        Expresión();
        ~Expresión();

        void muestra(TablaSímbolos* tablaSímbolos = nullptr) override;
    };

    class Bloque : public Nodo
    {
    public:
        Bloque();
        ~Bloque();

        void muestra(TablaSímbolos* tablaSímbolos = nullptr) override;
    };

    class SiCondicional : public Nodo
    {
    public:
        SiCondicional();
        ~SiCondicional();

        void muestra(TablaSímbolos* tablaSímbolos = nullptr) override;
    };

    class DefineFunción : public Nodo
    {
    public:
        std::string nombre;
        bool público;

        DefineFunción();
        ~DefineFunción();

        void muestra(TablaSímbolos* tablaSímbolos = nullptr) override;
    };

    class DeclaraFunción : public Nodo
    {
    public:
        std::string nombre;
        bool externo;

        DeclaraFunción();
        ~DeclaraFunción();

        void muestra(TablaSímbolos* tablaSímbolos = nullptr) override;
    };

    class Función : public Nodo
    {
    public:
        std::string nombre;

        Función();
        ~Función();

        void muestra(TablaSímbolos* tablaSímbolos = nullptr) override;
    };

    class FunciónEjecutable : public Nodo
    {
    public:
        std::string nombre;
        Ñ::Nodo* (*función)(Ñ::Nodo* yo, Ñ::Nodo* argumentos);

        FunciónEjecutable();
        ~FunciónEjecutable();

        void muestra(TablaSímbolos* tablaSímbolos = nullptr) override;
    };

    class Módulo : public Nodo
    {
    public:
        std::string módulo;

        Módulo();
        ~Módulo();

        void muestra(TablaSímbolos* tablaSímbolos = nullptr) override;
    };


    std::string obténNombreDeNodo(Ñ::CategoríaNodo n);
    void borraNodos(Ñ::Nodo* nodos);
    void muestraNodos(Nodo* nodo, TablaSímbolos* tablaSímbolos = nullptr);
    bool sonÁrbolesDuplicados(Nodo* nodo1, Nodo* nodo2);
    Nodo* duplicaÁrbol(Nodo* nodo);
}