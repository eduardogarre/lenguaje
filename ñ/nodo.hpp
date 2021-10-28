/*
This Source Code Form is subject to the terms of the Mozilla Public License, v.
2.0. If a copy of the MPL was not distributed with this file, You can obtain one
at http://mozilla.org/MPL/2.0/.

This Source Code Form is "Incompatible With Secondary Licenses", as defined by
the Mozilla Public License, v. 2.0.
*/

#pragma once

#include <string>
#include <vector>

namespace Ñ
{
    extern enum CategoríaTipo;
    extern class Posición;
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
        NODO_PUNTERO,

        NODO_CONVIERTE_TIPOS,

        NODO_LADO_IZQUIERDO_ASIGNACIÓN,
        NODO_LADO_DERECHO_ASIGNACIÓN,
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
        NODO_PARA_BUCLE,

        NODO_EXPRESIÓN,
        
        NODO_BLOQUE,
        NODO_SI_CONDICIONAL,
        NODO_BUCLE_MIENTRAS,
        
        NODO_FUNCIÓN,
        NODO_FUNCIÓN_EJECUTABLE,

        NODO_MÓDULO
    };

    class Nodo
    {
    private:
        Posición* _posición;

    public:
        CategoríaNodo categoría;
        std::vector<Ñ::Nodo*> ramas;

        Nodo(Posición* posición = nullptr);
        ~Nodo();

        void imprimeAjuste();
        Posición* posición();
        virtual void muestra(TablaSímbolos* tablaSímbolos = nullptr);
    };

    class Literal : public Nodo
    {
    public:
        Ñ::CategoríaTipo tipo;
        std::string dato;

        Literal(Posición* posición = nullptr);
        ~Literal();

        void muestra(TablaSímbolos* tablaSímbolos = nullptr) override;
    };

    class Identificador : public Nodo
    {
    public:
        std::string id;

        Identificador(Posición* posición = nullptr);
        ~Identificador();

        void muestra(TablaSímbolos* tablaSímbolos = nullptr) override;
    };

    class Puntero : public Nodo
    {
    public:
        std::string id;

        Puntero(Posición* posición = nullptr);
        ~Puntero();

        void muestra(TablaSímbolos* tablaSímbolos = nullptr) override;
    };

    class ConvierteTipos : public Nodo
    {
    public:
        Ñ::Tipo* origen;
        Ñ::Tipo* destino;

        ConvierteTipos(Posición* posición = nullptr);
        ~ConvierteTipos();

        void muestra(TablaSímbolos* tablaSímbolos = nullptr) override;
    };

    class LadoIzquierdoAsignación : public Nodo
    {
    public:
        LadoIzquierdoAsignación(Posición* posición = nullptr);
        ~LadoIzquierdoAsignación();

        void muestra(TablaSímbolos* tablaSímbolos = nullptr) override;
    };

    class LadoDerechoAsignación : public Nodo
    {
    public:
        LadoDerechoAsignación(Posición* posición = nullptr);
        ~LadoDerechoAsignación();

        void muestra(TablaSímbolos* tablaSímbolos = nullptr) override;
    };

    class Comparación : public Nodo
    {
    public:
        Comparación(Posición* posición = nullptr);
        ~Comparación();

        void muestra(TablaSímbolos* tablaSímbolos = nullptr) override;
    };

    class Término : public Nodo
    {
    public:
        Término(Posición* posición = nullptr);
        ~Término();

        void muestra(TablaSímbolos* tablaSímbolos = nullptr) override;
    };

    class Factor : public Nodo
    {
    public:
        Factor(Posición* posición = nullptr);
        ~Factor();

        void muestra(TablaSímbolos* tablaSímbolos = nullptr) override;
    };

    class OperaciónBinaria : public Nodo
    {
    public:
        std::string operación;
        Ñ::Tipo* tipo = nullptr;        

        OperaciónBinaria(Posición* posición = nullptr);
        ~OperaciónBinaria();

        void muestra(TablaSímbolos* tablaSímbolos = nullptr) override;
    };

    class OperaciónUnaria : public Nodo
    {
    public:
        std::string operación;

        OperaciónUnaria(Posición* posición = nullptr);
        ~OperaciónUnaria();

        void muestra(TablaSímbolos* tablaSímbolos = nullptr) override;
    };

    class ElementoVector : public Nodo
    {
    public:
        ElementoVector(Posición* posición = nullptr);
        ~ElementoVector();

        void muestra(TablaSímbolos* tablaSímbolos = nullptr) override;
    };

    class Primario : public Nodo
    {
    public:
        std::string primario;

        Primario(Posición* posición = nullptr);
        ~Primario();

        void muestra(TablaSímbolos* tablaSímbolos = nullptr) override;
    };

    class DeclaraVariable : public Nodo
    {
    public:
        std::string variable;

        DeclaraVariable(Posición* posición = nullptr);
        ~DeclaraVariable();

        void muestra(TablaSímbolos* tablaSímbolos = nullptr) override;
    };

    class Asigna : public Nodo
    {
    public:
        Asigna(Posición* posición = nullptr);
        ~Asigna();

        void muestra(TablaSímbolos* tablaSímbolos = nullptr) override;
    };

    class Argumento : public Nodo
    {
    public:
        Argumento(Posición* posición = nullptr);
        ~Argumento();

        void muestra(TablaSímbolos* tablaSímbolos = nullptr) override;
    };

    class Argumentos : public Nodo
    {
    public:
        Argumentos(Posición* posición = nullptr);
        ~Argumentos();

        void muestra(TablaSímbolos* tablaSímbolos = nullptr) override;
    };

    class LlamaFunción : public Nodo
    {
    public:
        std::string nombre;

        LlamaFunción(Posición* posición = nullptr);
        ~LlamaFunción();

        void muestra(TablaSímbolos* tablaSímbolos = nullptr) override;
    };

    class Devuelve : public Nodo
    {
    public:
        Devuelve(Posición* posición = nullptr);
        ~Devuelve();

        void muestra(TablaSímbolos* tablaSímbolos = nullptr) override;
    };

    class ParaBucle : public Nodo
    {
    public:
        ParaBucle(Posición* posición = nullptr);
        ~ParaBucle();

        void muestra(TablaSímbolos* tablaSímbolos = nullptr) override;
    };

    class Expresión : public Nodo
    {
    public:
        Expresión(Posición* posición = nullptr);
        ~Expresión();

        void muestra(TablaSímbolos* tablaSímbolos = nullptr) override;
    };

    class Bloque : public Nodo
    {
    public:
        Bloque(Posición* posición = nullptr);
        ~Bloque();

        void muestra(TablaSímbolos* tablaSímbolos = nullptr) override;
    };

    class SiCondicional : public Nodo
    {
    public:
        SiCondicional(Posición* posición = nullptr);
        ~SiCondicional();

        void muestra(TablaSímbolos* tablaSímbolos = nullptr) override;
    };

    class BucleMientras : public Nodo
    {
    public:
        BucleMientras(Posición* posición = nullptr);
        ~BucleMientras();

        void muestra(TablaSímbolos* tablaSímbolos = nullptr) override;
    };

    class DefineFunción : public Nodo
    {
    public:
        std::string nombre;
        bool público;

        DefineFunción(Posición* posición = nullptr);
        ~DefineFunción();

        void muestra(TablaSímbolos* tablaSímbolos = nullptr) override;
    };

    class DeclaraFunción : public Nodo
    {
    public:
        std::string nombre;
        bool externo;

        DeclaraFunción(Posición* posición = nullptr);
        ~DeclaraFunción();

        void muestra(TablaSímbolos* tablaSímbolos = nullptr) override;
    };

    class Función : public Nodo
    {
    public:
        std::string nombre;

        Función(Posición* posición = nullptr);
        ~Función();

        void muestra(TablaSímbolos* tablaSímbolos = nullptr) override;
    };

    class FunciónEjecutable : public Nodo
    {
    public:
        std::string nombre;
        Ñ::Nodo* (*función)(Ñ::Nodo* yo, Ñ::Nodo* argumentos);

        FunciónEjecutable(Posición* posición = nullptr);
        ~FunciónEjecutable();

        void muestra(TablaSímbolos* tablaSímbolos = nullptr) override;
    };

    class Módulo : public Nodo
    {
    public:
        std::string módulo;

        Módulo(Posición* posición = nullptr);
        ~Módulo();

        void muestra(TablaSímbolos* tablaSímbolos = nullptr) override;
    };


    std::string obténNombreDeNodo(Ñ::CategoríaNodo n);
    void borraNodos(Ñ::Nodo* nodos);
    void muestraNodos(Nodo* nodo, TablaSímbolos* tablaSímbolos = nullptr);
    bool sonÁrbolesDuplicados(Nodo* nodo1, Nodo* nodo2);
    Nodo* duplicaÁrbol(Nodo* nodo);
}