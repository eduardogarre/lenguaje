#include <iostream>

#include "tablasimbolos.hpp"

namespace Ñ
{
    enum CategoríaSímbolo {
        VACÍO,
        VARIABLE,
        FUNCIÓN,
        TIPO
    };

    class Símbolo
    {
    public:

        Símbolo();
        ~Símbolo();

        bool esFunción();
        bool esFunciónEjecutable();
        bool esFunciónImplementada();
        bool esVariable();

        void declaraFunción() { _categoría = CategoríaSímbolo::FUNCIÓN; }

        void declaraVariable(Ñ::Nodo* tipo);
        void asignaValor(Ñ::Nodo* valor);
        Ñ::Nodo* obténValor();

        void ejecutaFunción(Ñ::Argumentos* args);
        void añadeEjecución(void (*fn)(Ñ::Argumentos* args), Ñ::Nodo* args = nullptr);
        void borraEjecución();

        Ñ::Nodo* obténImplementación();
        void añadeImplementación(Ñ::Nodo* impl);
        void borraImplementación();

        void muestra();
        
    private:
        CategoríaSímbolo _categoría;
        bool _ejecutable = false;
        bool _definida = false;
        
        Ñ::Nodo* _tipo;
        Ñ::Nodo* _definición;

        void (*_ejecuta)(Ñ::Argumentos* args);
        Ñ::Argumentos * _args;
    };
}

Ñ::Símbolo::Símbolo()
{
    _categoría = CategoríaSímbolo::VACÍO;
    _ejecutable = false;
    _definida = false;

    _definición = nullptr;
    _tipo = nullptr;
}

Ñ::Símbolo::~Símbolo()
{

}

bool Ñ::Símbolo::esFunción()
{
    return _categoría == Ñ::CategoríaSímbolo::FUNCIÓN;
}

bool Ñ::Símbolo::esFunciónEjecutable()
{
    return _ejecutable;
}

bool Ñ::Símbolo::esFunciónImplementada()
{
    return _definida;
}

bool Ñ::Símbolo::esVariable()
{
    return _categoría == Ñ::CategoríaSímbolo::VARIABLE;
}

void Ñ::Símbolo::declaraVariable(Ñ::Nodo* tipo)
{
    if(_categoría != CategoríaSímbolo::VACÍO)
    {
        std::cout << "ERROR en la creación del símbolo, intentas sobreescribir un símbolo que no está vacío" << std::endl;
        
        return;
    }

    _categoría = CategoríaSímbolo::VARIABLE;
    Ñ::Tipo* t = new Ñ::Tipo();
    t->tipo = ((Ñ::Tipo*)tipo)->tipo;
    t->vector = ((Ñ::Tipo*)tipo)->vector;
    _tipo = (Ñ::Nodo*)(t);
}

void Ñ::Símbolo::asignaValor(Ñ::Nodo* valor)
{
    _categoría = CategoríaSímbolo::VARIABLE;

    if(valor->categoría == Ñ::CategoríaNodo::NODO_LITERAL)
    {
        _definición = duplicaÁrbol(valor);
    }
}

Ñ::Nodo* Ñ::Símbolo::obténValor()
{
    return _definición;
}

void Ñ::Símbolo::ejecutaFunción(Ñ::Argumentos* args)
{
    if(_categoría == CategoríaSímbolo::FUNCIÓN && _ejecutable && _ejecuta)
    {
        if(args == nullptr)
        {
            _ejecuta(_args);
        }
        else
        {
            _ejecuta(args);
        }
    }
}

void Ñ::Símbolo::añadeEjecución(void (*fn)(Ñ::Argumentos* args), Ñ::Nodo* args)
{
    _categoría = CategoríaSímbolo::FUNCIÓN;
    _ejecutable = true;
    _ejecuta = fn;
    
    if(args == nullptr)
    {
        _args = nullptr;
    }
    else if(args->categoría == Ñ::CategoríaNodo::NODO_ARGUMENTOS)
    {
        _args = (Ñ::Argumentos*)args;
    }
}

void Ñ::Símbolo::borraEjecución()
{
    _ejecutable = false;
    _ejecuta = nullptr;
}

Ñ::Nodo* Ñ::Símbolo::obténImplementación()
{
    if(_definida)
    {
        return _definición;
    }
    else
    {
        return nullptr;
    }
}

void Ñ::Símbolo::añadeImplementación(Ñ::Nodo* impl)
{
    _definida = true;
    _definición = impl;
}

void Ñ::Símbolo::borraImplementación()
{
    _definida = false;
    _definición = nullptr;
}

void Ñ::Símbolo::muestra()
{
    if(_categoría == Ñ::CategoríaSímbolo::VACÍO)
    {
        std::cout << "[]";
    }
    else if(_categoría == Ñ::CategoríaSímbolo::VARIABLE)
    {
        if((Ñ::Literal*)_definición != nullptr)
        {
            std::cout << "[VARIABLE :: \"" + ((Ñ::Literal*)_definición)->dato + "\"] ";
        }
        else
        {
            std::cout << "[VARIABLE] ";
        }

        muestraNodos(_tipo);
    }
    else if(_categoría == Ñ::CategoríaSímbolo::FUNCIÓN)
    {
        std::cout << "[FUNCIÓN]";
        if(_ejecutable)
        {
            std::cout << " [ejecutable]";
        }
        else
        {
            std::cout << " [----------]";
        }

        if(_definida)
        {
            std::cout << " [implementada]" << std::endl << " ";
            muestraNodos(_definición);
        }
        else
        {
            std::cout << std::endl;
        }
    }

}

bool Ñ::TablaSímbolos::identificadorDisponible(std::string id)
{
    if(_tabla.count(id) == 0 )
    {
        return true;
    }
    else
    {
        return false;
    }
}

Ñ::Resultado Ñ::TablaSímbolos::declaraFunción(std::string id)
{
    Ñ::Resultado resultado;

    if(!identificadorDisponible(id))
    {
        resultado.error("El identificador \"" + id + "\" ya está en uso");
        return resultado;
    }

    Ñ::Símbolo* s = new Ñ::Símbolo();
    s->declaraFunción();
    _tabla[id] = s;

    resultado.éxito();
    return resultado;
}

Ñ::Resultado Ñ::TablaSímbolos::defineFunciónEjecutable(std::string id, void (*fn)(Ñ::Argumentos* args), Ñ::Nodo* args)
{
    Ñ::Resultado resultado;

    if(identificadorDisponible(id))
    {
        resultado.error("El identificador no se ha declarado todavía");
        return resultado;
    }

    Ñ::Símbolo* s = _tabla[id];
    if(!s->esFunción())
    {
        resultado.error("El identificador no se había declarado como una función");
        return resultado;
    }

    if(s->esFunciónEjecutable())
    {
        resultado.error("Ya se ha asignado una ejecución a esta función");
        return resultado;
    }
    else if(s->esFunciónImplementada())
    {
        resultado.error("Ya se ha definido una implementación para esta función");
        return resultado;
    }

    s->añadeEjecución(fn, args);
    _tabla[id] = s;

    resultado.éxito();
    return resultado;
}

Ñ::Resultado Ñ::TablaSímbolos::ejecutaFunción(std::string id, Ñ::Nodo* args)
{
    Ñ::Resultado resultado;

    if(identificadorDisponible(id))
    {
        resultado.error("El identificador no se ha declarado todavía");
        return resultado;
    }

    Ñ::Símbolo* s = _tabla[id];
    if(!s->esFunción())
    {
        resultado.error("El identificador no se había declarado como una función");
        return resultado;
    }

    if(!s->esFunciónEjecutable() && !s->esFunciónImplementada())
    {
        resultado.error("No se ha definido una implementación para esta función");
        return resultado;
    }

    s->ejecutaFunción((Ñ::Argumentos*)args);

    resultado.éxito();
    return resultado;
}

Ñ::Resultado Ñ::TablaSímbolos::declaraVariable(std::string id, Ñ::Nodo* tipo)
{
    Ñ::Resultado resultado;

    if(!identificadorDisponible(id))
    {
        resultado.error("El identificador ya está en uso");
        return resultado;
    }

    Ñ::Símbolo* s = new Ñ::Símbolo();
    s->declaraVariable(tipo);
    _tabla[id] = s;

    resultado.éxito();
    return resultado;
}

Ñ::Resultado Ñ::TablaSímbolos::ponValor(std::string id, Ñ::Nodo* valor)
{
    Ñ::Resultado resultado;

    if(identificadorDisponible(id))
    {
        resultado.error("El identificador no se ha declarado");
        return resultado;
    }

    Ñ::Símbolo* s = _tabla[id];
    if(!s->esVariable())
    {
        resultado.error("El identificador no es una variable");
        return resultado;
    }

    s->asignaValor(valor);
    _tabla[id] = s;

    resultado.éxito();
    return resultado;
}

Ñ::Resultado Ñ::TablaSímbolos::leeValor(std::string id)
{
    Ñ::Resultado resultado;

    if(identificadorDisponible(id))
    {
        resultado.error("El identificador no se ha declarado");
        return resultado;
    }

    Ñ::Símbolo* s = _tabla[id];
    if(!s->esVariable())
    {
        resultado.error("El identificador no es una variable");
        return resultado;
    }
    
    resultado.nodo(s->obténValor());
    resultado.éxito();
    return resultado;
}

void Ñ::TablaSímbolos::muestra()
{
    for (auto [clave, valor] : _tabla)
    {
        std::cout << clave << " ";
        valor->muestra();
    }
}

Ñ::TablaSímbolos::~TablaSímbolos()
{
    for (auto [clave, valor] : _tabla)
    {
        delete valor;
    }
    
    _tabla.clear();
}