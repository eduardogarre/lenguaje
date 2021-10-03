#pragma once

#include <string>
#include <vector>

#include "posicion.hpp"

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
    private:
        Posición _posición;

    public:
        CategoríaNodo categoría;
        std::vector<Ñ::Nodo*> ramas;

        Nodo(Posición posición = {});
        ~Nodo();

        void imprimeAjuste();
        Posición posición();
        virtual void muestra(TablaSímbolos* tablaSímbolos = nullptr);
    };

    class Literal : public Nodo
    {
    public:
        Ñ::CategoríaTipo tipo;
        std::string dato;

        Literal(Posición posición = {});
        ~Literal();

        void muestra(TablaSímbolos* tablaSímbolos = nullptr) override;
    };

    class Identificador : public Nodo
    {
    public:
        std::string id;

        Identificador(Posición posición = {});
        ~Identificador();

        void muestra(TablaSímbolos* tablaSímbolos = nullptr) override;
    };

    class ConvierteTipos : public Nodo
    {
    public:
        Ñ::Tipo* origen;
        Ñ::Tipo* destino;

        ConvierteTipos(Posición posición = {});
        ~ConvierteTipos();

        void muestra(TablaSímbolos* tablaSímbolos = nullptr) override;
    };

    class LadoIzquierdoAsignación : public Nodo
    {
    public:
        LadoIzquierdoAsignación(Posición posición = {});
        ~LadoIzquierdoAsignación();

        void muestra(TablaSímbolos* tablaSímbolos = nullptr) override;
    };

    class LadoDerechoAsignación : public Nodo
    {
    public:
        LadoDerechoAsignación(Posición posición = {});
        ~LadoDerechoAsignación();

        void muestra(TablaSímbolos* tablaSímbolos = nullptr) override;
    };

    class Igualdad : public Nodo
    {
    public:
        Igualdad(Posición posición = {});
        ~Igualdad();

        void muestra(TablaSímbolos* tablaSímbolos = nullptr) override;
    };

    class Comparación : public Nodo
    {
    public:
        Comparación(Posición posición = {});
        ~Comparación();

        void muestra(TablaSímbolos* tablaSímbolos = nullptr) override;
    };

    class Término : public Nodo
    {
    public:
        Término(Posición posición = {});
        ~Término();

        void muestra(TablaSímbolos* tablaSímbolos = nullptr) override;
    };

    class Factor : public Nodo
    {
    public:
        Factor(Posición posición = {});
        ~Factor();

        void muestra(TablaSímbolos* tablaSímbolos = nullptr) override;
    };

    class OperaciónBinaria : public Nodo
    {
    public:
        std::string operación;
        Ñ::Tipo* tipo = nullptr;        

        OperaciónBinaria(Posición posición = {});
        ~OperaciónBinaria();

        void muestra(TablaSímbolos* tablaSímbolos = nullptr) override;
    };

    class OperaciónUnaria : public Nodo
    {
    public:
        std::string operación;

        OperaciónUnaria(Posición posición = {});
        ~OperaciónUnaria();

        void muestra(TablaSímbolos* tablaSímbolos = nullptr) override;
    };

    class ElementoVector : public Nodo
    {
    public:
        uint64_t posición = 0;

        ElementoVector(Posición posición = {});
        ~ElementoVector();

        void muestra(TablaSímbolos* tablaSímbolos = nullptr) override;
    };

    class Primario : public Nodo
    {
    public:
        std::string primario;

        Primario(Posición posición = {});
        ~Primario();

        void muestra(TablaSímbolos* tablaSímbolos = nullptr) override;
    };

    class DeclaraVariable : public Nodo
    {
    public:
        std::string variable;

        DeclaraVariable(Posición posición = {});
        ~DeclaraVariable();

        void muestra(TablaSímbolos* tablaSímbolos = nullptr) override;
    };

    class Asigna : public Nodo
    {
    public:
        Asigna(Posición posición = {});
        ~Asigna();

        void muestra(TablaSímbolos* tablaSímbolos = nullptr) override;
    };

    class Argumento : public Nodo
    {
    public:
        Argumento(Posición posición = {});
        ~Argumento();

        void muestra(TablaSímbolos* tablaSímbolos = nullptr) override;
    };

    class Argumentos : public Nodo
    {
    public:
        Argumentos(Posición posición = {});
        ~Argumentos();

        void muestra(TablaSímbolos* tablaSímbolos = nullptr) override;
    };

    class LlamaFunción : public Nodo
    {
    public:
        std::string nombre;

        LlamaFunción(Posición posición = {});
        ~LlamaFunción();

        void muestra(TablaSímbolos* tablaSímbolos = nullptr) override;
    };

    class Devuelve : public Nodo
    {
    public:
        Devuelve(Posición posición = {});
        ~Devuelve();

        void muestra(TablaSímbolos* tablaSímbolos = nullptr) override;
    };

    class Expresión : public Nodo
    {
    public:
        Expresión(Posición posición = {});
        ~Expresión();

        void muestra(TablaSímbolos* tablaSímbolos = nullptr) override;
    };

    class Bloque : public Nodo
    {
    public:
        Bloque(Posición posición = {});
        ~Bloque();

        void muestra(TablaSímbolos* tablaSímbolos = nullptr) override;
    };

    class SiCondicional : public Nodo
    {
    public:
        SiCondicional(Posición posición = {});
        ~SiCondicional();

        void muestra(TablaSímbolos* tablaSímbolos = nullptr) override;
    };

    class DefineFunción : public Nodo
    {
    public:
        std::string nombre;
        bool público;

        DefineFunción(Posición posición = {});
        ~DefineFunción();

        void muestra(TablaSímbolos* tablaSímbolos = nullptr) override;
    };

    class DeclaraFunción : public Nodo
    {
    public:
        std::string nombre;
        bool externo;

        DeclaraFunción(Posición posición = {});
        ~DeclaraFunción();

        void muestra(TablaSímbolos* tablaSímbolos = nullptr) override;
    };

    class Función : public Nodo
    {
    public:
        std::string nombre;

        Función(Posición posición = {});
        ~Función();

        void muestra(TablaSímbolos* tablaSímbolos = nullptr) override;
    };

    class FunciónEjecutable : public Nodo
    {
    public:
        std::string nombre;
        Ñ::Nodo* (*función)(Ñ::Nodo* yo, Ñ::Nodo* argumentos);

        FunciónEjecutable(Posición posición = {});
        ~FunciónEjecutable();

        void muestra(TablaSímbolos* tablaSímbolos = nullptr) override;
    };

    class Módulo : public Nodo
    {
    public:
        std::string módulo;

        Módulo(Posición posición = {});
        ~Módulo();

        void muestra(TablaSímbolos* tablaSímbolos = nullptr) override;
    };


    std::string obténNombreDeNodo(Ñ::CategoríaNodo n);
    void borraNodos(Ñ::Nodo* nodos);
    void muestraNodos(Nodo* nodo, TablaSímbolos* tablaSímbolos = nullptr);
    bool sonÁrbolesDuplicados(Nodo* nodo1, Nodo* nodo2);
    Nodo* duplicaÁrbol(Nodo* nodo);
}