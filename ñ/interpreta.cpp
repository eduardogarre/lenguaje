#include <iostream>
#include <vector>

#include "interpreta.hpp"
#include "nodo.hpp"

namespace Ñ
{
    Ñ::Resultado resuelveArgumentos(Ñ::Argumentos* args, Ñ::TablaSímbolos* tablaSímbolos)
    {
        Ñ::Resultado resultado;
        if(args == nullptr)
        {
            resultado.éxito();
            resultado.nodo(nullptr);
            return resultado;
        }

        Ñ::Argumentos* argumentos = new Ñ::Argumentos();

        for(auto a : ((Ñ::Nodo*)args)->ramas)
        {
            Ñ::Nodo* n;

            if(a->categoría == Ñ::CategoríaNodo::NODO_IDENTIFICADOR)
            {
                Ñ::Identificador* id = (Ñ::Identificador*)a;
                if(tablaSímbolos->identificadorDisponible(id->id))
                {
                    delete argumentos;
                    resultado.error("He recibido como argumento un identificador inexistente");
                    return resultado;
                }
                else
                {
                    Ñ::Resultado r = tablaSímbolos->leeValor(id->id);
                    if(r.error())
                    {
                        delete argumentos;
                        return r;
                    }

                    n = Ñ::duplicaÁrbol(r.nodo());
                    ((Ñ::Nodo*)argumentos)->ramas.push_back(n);
                }
            }
            else
            {
                n = Ñ::duplicaÁrbol(a);
                ((Ñ::Nodo*)argumentos)->ramas.push_back(n);
            }
        }

        resultado.éxito();
        resultado.nodo((Ñ::Nodo*)argumentos);
        return resultado;
    }

    Ñ::Resultado resuelveIdentificador(Ñ::Nodo* n, Ñ::TablaSímbolos* tablaSímbolos)
    {
        Ñ::Resultado resultado;

        if(n->categoría == Ñ::CategoríaNodo::NODO_IDENTIFICADOR)
        {
            Ñ::Identificador* id = (Ñ::Identificador*)n;
            if(tablaSímbolos->identificadorDisponible(id->id))
            {
                resultado.error("He recibido como argumento un identificador inexistente");
                return resultado;
            }
            else
            {
                Ñ::Resultado r = tablaSímbolos->leeValor(id->id);
                if(r.error())
                {
                    return r;
                }

                n = Ñ::duplicaÁrbol(r.nodo());
                resultado.éxito();
                resultado.nodo(n);
                return resultado;
            }
        }

        resultado.error("El nodo no es un identificador");
        return resultado;
    }
}

Ñ::Resultado Ñ::interpretaNodos(Ñ::Nodo* nodos, Ñ::TablaSímbolos* tablaSímbolos)
{
    Ñ::Resultado resultado;

    if(nodos->categoría == Ñ::CategoríaNodo::NODO_EXPRESIÓN)
    {
        for(Ñ::Nodo* n : nodos->ramas)
        {
            Ñ::Resultado rResuelveSímbolos = interpretaNodos(n, tablaSímbolos);
            if(rResuelveSímbolos.error())
            {
                return rResuelveSímbolos;
            }
        }
        
        resultado.éxito();
        return resultado;
    }
    else if(nodos->categoría == Ñ::CategoríaNodo::NODO_DECLARA_VARIABLE)
    {
        std::string nombre = ((Ñ::DeclaraVariable*)nodos)->variable;

        auto tipo = (nodos->ramas[0]);
        std::string cadenaTipo = ((Ñ::Tipo*)tipo)->tipo;

        // Añado la variable a la tabla de símbolos
        tablaSímbolos->declaraVariable(nombre, tipo);

        Ñ::Identificador* id = new Ñ::Identificador();
        id->id = nombre;
        
        resultado.éxito();
        resultado.nodo((Ñ::Nodo*)id);
        return resultado;
    }
    else if(nodos->categoría == Ñ::CategoríaNodo::NODO_IDENTIFICADOR)
    {
        resultado.éxito();
        resultado.nodo(nodos);
        return resultado;
    }
    else if(nodos->categoría == Ñ::CategoríaNodo::NODO_LITERAL)
    {
        resultado.éxito();
        resultado.nodo(nodos);
        return resultado;
    }
    else if(nodos->categoría == Ñ::CategoríaNodo::NODO_ASIGNA)
    {
        Ñ::Resultado rLia = interpretaNodos(nodos->ramas[0], tablaSímbolos);
        Ñ::Resultado rLda = interpretaNodos(nodos->ramas[1], tablaSímbolos);

        if(rLia.error())
        {
            return rLia;
        }
        if(rLda.error())
        {
            return rLda;
        }
        
        if(rLda.nodo()->categoría == Ñ::CategoríaNodo::NODO_LITERAL)
        {
            std::string id = ((Ñ::Identificador*)(rLia.nodo()))->id;
            tablaSímbolos->ponValor(id, rLda.nodo());
        }
        else if(rLda.nodo()->categoría == Ñ::CategoríaNodo::NODO_IDENTIFICADOR)
        {
            Ñ::Identificador* idLia = ((Ñ::Identificador*)rLia.nodo());
            Ñ::Identificador* idLda = ((Ñ::Identificador*)rLda.nodo());

            Ñ::Resultado rLda = tablaSímbolos->leeValor(idLda->id);
            if(rLda.error())
            {
                return rLda;
            }

            Ñ::Nodo* valor = rLda.nodo();
            Ñ::Nodo* valorTmp = duplicaÁrbol(valor);
            tablaSímbolos->ponValor(idLia->id, valorTmp);
            delete valorTmp;
        }

        resultado.éxito();
        resultado.nodo(rLia.nodo());
        return resultado;
    }
    else if(nodos->categoría == Ñ::CategoríaNodo::NODO_OP_SUMA_RESTA)
    {
        Ñ::Nodo* op0 = nullptr;
        Ñ::Nodo* op1 = nullptr;
        bool op0tmp = false;
        bool op1tmp = false;

        Ñ::Resultado r0 = interpretaNodos(nodos->ramas[0], tablaSímbolos);
        if(r0.error())
        {
            return r0;
        }
        else if(r0.nodo()->categoría == Ñ::CategoríaNodo::NODO_LITERAL)
        {
            op0 = r0.nodo();
        }
        else if(r0.nodo()->categoría == Ñ::CategoríaNodo::NODO_IDENTIFICADOR)
        {
            Ñ::Resultado rOp = resuelveIdentificador(r0.nodo(), tablaSímbolos);
            if(rOp.error())
            {
                return rOp;
            }

            op0 = rOp.nodo();
            op0tmp = true;
        }

        Ñ::Resultado r1 = interpretaNodos(nodos->ramas[1], tablaSímbolos);
        if(r1.error())
        {
            if(op0tmp)
            {
                delete op0;
            }
            return r1;
        }
        else if(r1.nodo()->categoría == Ñ::CategoríaNodo::NODO_LITERAL)
        {
            op1 = r1.nodo();
        }
        else if(r1.nodo()->categoría == Ñ::CategoríaNodo::NODO_IDENTIFICADOR)
        {
            Ñ::Resultado rOp = resuelveIdentificador(r1.nodo(), tablaSímbolos);
            if(rOp.error())
            {
                if(op0tmp)
                {
                    delete op0;
                }
                return rOp;
            }

            op1 = rOp.nodo();
            op1tmp = true;
        }

        // PENDIENTE DE IMPLEMENTAR TIPOS
        // POR EL MOMENTO FIJO LITERALES NATURALES
        int64_t l0 = std::atoi(((Ñ::Literal*)op0)->dato.c_str());
        int64_t l1 = std::atoi(((Ñ::Literal*)op1)->dato.c_str());
        int64_t res = 0;

        if(((Ñ::OpSumaResta*)nodos)->operación == "+")
        {
            res = l0 + l1;
            Ñ::Literal* literal = new Ñ::Literal();
            literal->dato = std::to_string(res);
            resultado.éxito();
            resultado.nodo((Ñ::Nodo*)literal);
        }
        else if(((Ñ::OpSumaResta*)nodos)->operación == "-")
        {
            res = -(l0 - l1); // Los hijos están invertidos en el árbol
            Ñ::Literal* literal = new Ñ::Literal();
            literal->dato = std::to_string(res);
            resultado.éxito();
            resultado.nodo((Ñ::Nodo*)literal);
        }
        else
        {
            resultado.error("Operación desconocida");
        }
        
        if(op0tmp)
        {
            delete op0;
        }
        if(op1tmp)
        {
            delete op1;
        }
        return resultado;
    }
    else if(nodos->categoría == Ñ::CategoríaNodo::NODO_OP_MULTIPLICACIÓN_DIVISIÓN)
    {
        resultado.error("Pendiente de implementar");
        return resultado;
    }
    else if(nodos->categoría == Ñ::CategoríaNodo::NODO_LLAMA_FUNCIÓN)
    {
        Ñ::LlamaFunción* fn = (Ñ::LlamaFunción*)nodos;
        
        Ñ::Argumentos* args;
        if(nodos->ramas.size() < 1)
        {
            args = nullptr;
        }
        else
        {
            args = (Ñ::Argumentos*)(nodos->ramas[0]);
        }

        Ñ::Resultado rArgs = resuelveArgumentos(args, tablaSímbolos);
        if(rArgs.error())
        {
            return rArgs;
        }
        Ñ::Nodo* argsResueltos = rArgs.nodo();

        tablaSímbolos->ejecutaFunción(fn->función, argsResueltos);
        
        resultado.éxito();
        return resultado;
    }

    resultado.error("INTÉRPRETE :: No consigo interpretar el árbol de nodos");
    return resultado;
}