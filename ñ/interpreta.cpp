#include <iostream>
#include <string>
#include <vector>

#include "interpreta.hpp"
#include "nodo.hpp"
#include "tipo.hpp"
#include "valor.hpp"

namespace Ñ
{
    Ñ::Resultado interpretaLIA(Ñ::Nodo* nodos, Ñ::TablaSímbolos* tablaSímbolos);
    Ñ::Resultado interpretaLDA(Ñ::Nodo* nodos, Ñ::TablaSímbolos* tablaSímbolos);

    Ñ::Resultado ejecutaFunción(std::string identificador, Ñ::Nodo* argumentos, Ñ::TablaSímbolos* tablaSímbolos)
    {
        Ñ::Resultado resultado;
        Ñ::Nodo* función;
        
        Ñ::Resultado rSímbolo = tablaSímbolos->leeValor(identificador);
        if(rSímbolo.error())
        {
            return rSímbolo;
        }
        función = rSímbolo.nodo();

        if(función->categoría == Ñ::CategoríaNodo::NODO_FUNCIÓN_EJECUTABLE)
        {
            Ñ::FunciónEjecutable* efn = (Ñ::FunciónEjecutable*)función;
            efn->función(nullptr, argumentos);
            resultado.éxito();
            return resultado;
        }
        else if(función->categoría == Ñ::CategoríaNodo::NODO_FUNCIÓN)
        {
            Ñ::LlamaFunción* fn = (Ñ::LlamaFunción*)función;
            Ñ::TablaSímbolos* subTabla = new Ñ::TablaSímbolos(tablaSímbolos);
            if(argumentos != nullptr)
            {
                for(int i = 0; i < argumentos->ramas.size(); i++)
                {
                    Ñ::Nodo* arg = argumentos->ramas[i];
                    if(arg->categoría == Ñ::CategoríaNodo::NODO_LITERAL)
                    {
                        Ñ::Literal* valorArgumento = (Ñ::Literal*)arg;
                        Ñ::DeclaraVariable* declaraciónArgumento = (Ñ::DeclaraVariable*)(((Ñ::Nodo*)fn)->ramas[1]->ramas[i]);
                        subTabla->declara(declaraciónArgumento->variable, ((Ñ::Nodo*)declaraciónArgumento)->ramas[0]);
                        subTabla->ponValor(declaraciónArgumento->variable, (Ñ::Nodo*)valorArgumento);
                    }
                }
            }
            resultado = Ñ::interpretaNodos(función->ramas[2], subTabla);
            delete subTabla;
            resultado.éxito();
            return resultado;
        }

        resultado.error("Pendiente de implementar");
        return resultado;
    }

    Ñ::Resultado sumaLiteralesEnteros(Ñ::Nodo* n1, Ñ::Nodo* n2)
    {
        std::string d1 = ((Ñ::Literal*)n1)->dato;
        std::string d2 = ((Ñ::Literal*)n2)->dato;

        int32_t i1 = std::atoi(d1.c_str());
        int32_t i2 = std::atoi(d2.c_str());

        Ñ::Literal* l = new Ñ::Literal;
        l->dato = std::to_string(i1 + i2);
        Ñ::Resultado r;
        r.éxito();
        r.nodo((Ñ::Nodo*)l);
        return r;
    }
    
    Ñ::Resultado restaLiteralesEnteros(Ñ::Nodo* n1, Ñ::Nodo* n2)
    {
        std::string d1 = ((Ñ::Literal*)n1)->dato;
        std::string d2 = ((Ñ::Literal*)n2)->dato;

        int32_t i1 = std::atoi(d1.c_str());
        int32_t i2 = std::atoi(d2.c_str());

        Ñ::Literal* l = new Ñ::Literal;
        l->dato = std::to_string(i1 - i2);
        Ñ::Resultado r;
        r.éxito();
        r.nodo((Ñ::Nodo*)l);
        return r;
    }
    
    Ñ::Resultado multiplicaLiteralesEnteros(Ñ::Nodo* n1, Ñ::Nodo* n2)
    {
        std::string d1 = ((Ñ::Literal*)n1)->dato;
        std::string d2 = ((Ñ::Literal*)n2)->dato;

        int32_t i1 = std::atoi(d1.c_str());
        int32_t i2 = std::atoi(d2.c_str());

        Ñ::Literal* l = new Ñ::Literal;
        l->dato = std::to_string(i1 * i2);
        Ñ::Resultado r;
        r.éxito();
        r.nodo((Ñ::Nodo*)l);
        return r;
    }
    
    Ñ::Resultado divideLiteralesEnteros(Ñ::Nodo* n1, Ñ::Nodo* n2)
    {
        std::string d1 = ((Ñ::Literal*)n1)->dato;
        std::string d2 = ((Ñ::Literal*)n2)->dato;

        int32_t i1 = std::atoi(d1.c_str());
        int32_t i2 = std::atoi(d2.c_str());

        Ñ::Literal* l = new Ñ::Literal;
        l->dato = std::to_string(i1 / i2);
        Ñ::Resultado r;
        r.éxito();
        r.nodo((Ñ::Nodo*)l);
        return r;
    }

    Ñ::Resultado obténLiteral(Ñ::Nodo* nodo, Ñ::TablaSímbolos* tablaSímbolos)
    {
        Ñ::Resultado resultado;
        Ñ::Nodo* n;

        if(nodo->categoría == Ñ::CategoríaNodo::NODO_IDENTIFICADOR)
        {
            std::string id = ((Ñ::Identificador*)(nodo))->id;
            Ñ::Resultado rid = tablaSímbolos->leeValor(id);
            if(rid.error())
            {
                return rid;
            }
            else
            {
                n = duplicaÁrbol(rid.nodo());
            }
        }
        else if(nodo->categoría == Ñ::CategoríaNodo::NODO_LITERAL)
        {
            n = duplicaÁrbol(nodo);
        }
        else
        {
            Ñ::Resultado r = interpretaNodos(nodo, tablaSímbolos);
            if(r.error())
            {
                return r;
            }
            if(r.nodo()->categoría == Ñ::CategoríaNodo::NODO_IDENTIFICADOR)
            {
                std::string id = ((Ñ::Identificador*)(r.nodo()))->id;
                Ñ::Resultado rid = tablaSímbolos->leeValor(id);
                if(rid.error())
                {
                    return rid;
                }
                else
                {
                    n = duplicaÁrbol(rid.nodo());
                }
            }
            else if(nodo->categoría == Ñ::CategoríaNodo::NODO_LITERAL)
            {
                n = duplicaÁrbol(nodo);
            }
            else
            {
                resultado.error("He recibido un nodo de categoría " + std::to_string(nodo->categoría));
                return resultado;
            }
        }
        
        resultado.éxito();
        resultado.nodo(n);
        return resultado;
    }

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
                if(!tablaSímbolos->nombreReservadoEnCualquierÁmbito(id->id))
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
            else if(a->categoría == Ñ::CategoríaNodo::NODO_LITERAL)
            {
                n = duplicaÁrbol(a);
                ((Ñ::Nodo*)argumentos)->ramas.push_back(n);
            }
            else
            {
                Ñ::Resultado r = interpretaLDA(a, tablaSímbolos);
                if(r.error())
                {
                    delete argumentos;
                    return r;
                }

                if(r.nodo()->categoría == Ñ::CategoríaNodo::NODO_IDENTIFICADOR)
                {
                    Ñ::Identificador* id = (Ñ::Identificador*)(r.nodo());
                    if(!tablaSímbolos->nombreReservadoEnCualquierÁmbito(id->id))
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
                else if(r.nodo()->categoría == Ñ::CategoríaNodo::NODO_LITERAL)
                {
                    n = duplicaÁrbol(r.nodo());
                    ((Ñ::Nodo*)argumentos)->ramas.push_back(n);
                }
                else
                {
                    delete argumentos;
                    resultado.error("He recibido como argumento un árbol que no consigo interpretar");
                    muestraNodos(r.nodo());
                    return resultado;
                }
            }
        }

        resultado.éxito();
        resultado.nodo((Ñ::Nodo*)argumentos);
        return resultado;
    }

    Ñ::Resultado interpretaLIA(Ñ::Nodo* nodos, Ñ::TablaSímbolos* tablaSímbolos)
    {
        Ñ::Resultado resultado;

        if(nodos->categoría == Ñ::CategoríaNodo::NODO_IDENTIFICADOR)
        {
            resultado.éxito();
            resultado.nodo(duplicaÁrbol(nodos));
            return resultado;
        }
        else if(nodos->categoría == Ñ::CategoríaNodo::NODO_DECLARA_VARIABLE)
        {
            std::string nombre = ((Ñ::DeclaraVariable*)nodos)->variable;

            auto tipo = (nodos->ramas[0]);
            std::string cadenaTipo = ((Ñ::Tipo*)tipo)->tipo;

            // Añado la variable a la tabla de símbolos
            tablaSímbolos->declara(nombre, tipo);

            Ñ::Identificador* id = new Ñ::Identificador();
            id->id = nombre;
            
            resultado.éxito();
            resultado.nodo((Ñ::Nodo*)id);
            return resultado;
        }

        resultado.error("INTÉRPRETE :: El árbol de nodos es incorrecto, esperaba Lado Izquierdo de Asignación. Categoría del nódulo actual: " + std::to_string(nodos->categoría));
        return resultado;
    }

    Ñ::Resultado interpretaLDA(Ñ::Nodo* nodos, Ñ::TablaSímbolos* tablaSímbolos)
    {
        Ñ::Resultado resultado;

        if(nodos->categoría == Ñ::CategoríaNodo::NODO_IDENTIFICADOR)
        {
            resultado = obténLiteral(nodos, tablaSímbolos);
            return resultado;
        }
        else if(nodos->categoría == Ñ::CategoríaNodo::NODO_LITERAL)
        {
            resultado.éxito();
            resultado.nodo(duplicaÁrbol(nodos));
            return resultado;
        }
        else if(nodos->categoría == Ñ::CategoríaNodo::NODO_OP_UNARIA)
        {
            if(nodos->ramas.size() == 1)
            {
                Ñ::Nodo* n1;
                Ñ::Resultado r = interpretaLDA(nodos->ramas[0], tablaSímbolos);
                if(r.error())
                {
                    return r;
                }
                Ñ::Resultado rn = obténLiteral(r.nodo(), tablaSímbolos);
                if(rn.error())
                {
                    return rn;
                }
                else
                {
                    n1 = rn.nodo();
                }
                delete r.nodo();
                Ñ::Literal* lit = (Ñ::Literal*)n1;
                Ñ::OperaciónUnaria* op = (Ñ::OperaciónUnaria*)nodos;
                if(op->operación == "!")
                {
                    if(lit->dato == "cierto")
                    {
                        lit->dato = "falso";
                    }
                    else if(lit->dato == "falso")
                    {
                        lit->dato = "cierto";
                    }
                    else
                    {
                        resultado.error("Has intentado aplicar la operación lógica NO a un valor que no es booleano");
                        return resultado;
                    }

                    resultado.éxito();
                    resultado.nodo(n1);
                    return resultado;
                }
                else if(op->operación == "-")
                {
                    int32_t núm = std::strtol(lit->dato.c_str(), nullptr, 10);
                    núm *= -1;
                    lit->dato = std::to_string(núm);

                    resultado.éxito();
                    resultado.nodo(n1);
                    return resultado;
                }

                resultado.éxito();
                resultado.nodo(n1);
                return resultado;
            }
            else
            {
                resultado.error("El nodo Ñ::Igualdad tenía " + std::to_string(nodos->ramas.size()) + " ramas");
                return resultado;
            }
        }
        else if(nodos->categoría == Ñ::CategoríaNodo::NODO_IGUALDAD)
        {
            if(nodos->ramas.size() == 1)
            {
                Ñ::Resultado r = interpretaLDA(nodos->ramas[0], tablaSímbolos);
                if(r.error())
                {
                    return r;
                }
                Ñ::Nodo* n = duplicaÁrbol(r.nodo());
                delete r.nodo();
                resultado.éxito();
                resultado.nodo(n);
                return resultado;
            }
            else if(nodos->ramas.size() > 1)
            {
                resultado.error("Pendiente de implementar operaciones de igualdad");
                return resultado;
            }
            else
            {
                resultado.error("El nodo Ñ::Igualdad tenía " + std::to_string(nodos->ramas.size()) + " ramas");
                return resultado;
            }
        }
        else if(nodos->categoría == Ñ::CategoríaNodo::NODO_COMPARACIÓN)
        {
            if(nodos->ramas.size() == 1)
            {
                Ñ::Resultado r = interpretaLDA(nodos->ramas[0], tablaSímbolos);
                if(r.error())
                {
                    return r;
                }
                Ñ::Nodo* n = duplicaÁrbol(r.nodo());
                delete r.nodo();
                resultado.éxito();
                resultado.nodo(n);
                return resultado;
            }
            else if(nodos->ramas.size() > 1)
            {
                resultado.error("Pendiente de implementar operaciones de comparación");
                return resultado;
            }
            else
            {
                resultado.error("El nodo Ñ::Comparación tenía " + std::to_string(nodos->ramas.size()) + " ramas");
                return resultado;
            }
        }
        else if(nodos->categoría == Ñ::CategoríaNodo::NODO_TÉRMINO)
        {
            if(nodos->ramas.size() == 1)
            {
                Ñ::Resultado r = interpretaLDA(nodos->ramas[0], tablaSímbolos);
                if(r.error())
                {
                    return r;
                }
                Ñ::Nodo* n = duplicaÁrbol(r.nodo());
                delete r.nodo();
                resultado.éxito();
                resultado.nodo(n);
                return resultado;
            }
            else if(nodos->ramas.size() > 1)
            {
                Ñ::Nodo* n1;
                Ñ::Resultado r = interpretaLDA(nodos->ramas[0], tablaSímbolos);
                if(r.error())
                {
                    return r;
                }
                Ñ::Resultado rn = obténLiteral(r.nodo(), tablaSímbolos);
                if(rn.error())
                {
                    return rn;
                }
                else
                {
                    n1 = rn.nodo();
                }
                delete r.nodo();

                for(int i = 1; i < nodos->ramas.size(); i++)
                {
                    if(nodos->ramas[i]->categoría != Ñ::CategoríaNodo::NODO_OP_BINARIA)
                    {
                        resultado.error("Término no ha recibido una operación válida");
                        return resultado;
                    }
                    Ñ::Nodo* op = nodos->ramas[i];
                    if(op->ramas.size() != 1)
                    {
                        resultado.error("El árbol del 2º argumento de la operación binaria es incorrecto");
                        return resultado;
                    }
                    std::string operación = ((Ñ::OperaciónBinaria*)op)->operación;
                    Ñ::Nodo* n2;
                    Ñ::Resultado rn2 = interpretaLDA(op->ramas[0], tablaSímbolos);
                    
                    if(rn2.error())
                    {
                        return rn2;
                    }
                    else
                    {
                        rn2 = obténLiteral(rn2.nodo(), tablaSímbolos);
                        if(rn2.error())
                        {
                            return rn2;
                        }
                        n2 = rn2.nodo();
                    }

                    if(operación == "+")
                    {
                        Ñ::Resultado rop = sumaLiteralesEnteros(n1, n2);
                        delete n2, n1;
                        if(rop.error())
                        {
                            return rop;
                        }
                        n1 = rop.nodo();
                    }
                    else if(operación == "-")
                    {
                        Ñ::Resultado rop = restaLiteralesEnteros(n1, n2);
                        delete n2, n1;
                        if(rop.error())
                        {
                            return rop;
                        }
                        n1 = rop.nodo();
                    }
                }

                resultado.éxito();
                resultado.nodo(n1);
                return resultado;
            }
            else
            {
                resultado.error("El nodo Ñ::Término tenía " + std::to_string(nodos->ramas.size()) + " ramas");
                return resultado;
            }
        }
        else if(nodos->categoría == Ñ::CategoríaNodo::NODO_FACTOR)
        {
            if(nodos->ramas.size() == 1)
            {
                Ñ::Resultado r = interpretaLDA(nodos->ramas[0], tablaSímbolos);
                if(r.error())
                {
                    return r;
                }
                Ñ::Nodo* n = duplicaÁrbol(r.nodo());
                delete r.nodo();
                resultado.éxito();
                resultado.nodo(n);
                return resultado;
            }
            else if(nodos->ramas.size() > 1)
            {
                Ñ::Nodo* n1;
                Ñ::Resultado r = interpretaLDA(nodos->ramas[0], tablaSímbolos);
                if(r.error())
                {
                    return r;
                }
                Ñ::Resultado rn = obténLiteral(r.nodo(), tablaSímbolos);
                if(rn.error())
                {
                    return rn;
                }
                else
                {
                    n1 = rn.nodo();
                }
                delete r.nodo();

                for(int i = 1; i < nodos->ramas.size(); i++)
                {
                    if(nodos->ramas[i]->categoría != Ñ::CategoríaNodo::NODO_OP_BINARIA)
                    {
                        resultado.error("Factor no ha recibido una operación válida");
                        return resultado;
                    }
                    Ñ::Nodo* op = nodos->ramas[i];
                    if(op->ramas.size() != 1)
                    {
                        resultado.error("El árbol del 2º argumento de la operación binaria es incorrecto");
                        return resultado;
                    }
                    std::string operación = ((Ñ::OperaciónBinaria*)op)->operación;
                    Ñ::Nodo* n2;
                    Ñ::Resultado rn2 = interpretaLDA(op->ramas[0], tablaSímbolos);

                    if(rn2.error())
                    {
                        return rn2;
                    }
                    else
                    {
                        rn2 = obténLiteral(rn2.nodo(), tablaSímbolos);
                        if(rn2.error())
                        {
                            return rn2;
                        }
                        n2 = rn2.nodo();
                    }

                    if(operación == "*")
                    {
                        Ñ::Resultado rop = multiplicaLiteralesEnteros(n1, n2);
                        delete n2, n1;
                        if(rop.error())
                        {
                            return rop;
                        }
                        n1 = rop.nodo();
                    }
                    else if(operación == "/")
                    {
                        Ñ::Resultado rop = divideLiteralesEnteros(n1, n2);
                        delete n2, n1;
                        if(rop.error())
                        {
                            return rop;
                        }
                        n1 = rop.nodo();
                    }
                }

                resultado.éxito();
                resultado.nodo(n1);
                return resultado;
            }
            else
            {
                resultado.error("El nodo Ñ::Factor tenía " + std::to_string(nodos->ramas.size()) + " ramas");
                return resultado;
            }
        }
        else if(nodos->categoría == Ñ::CategoríaNodo::NODO_LLAMA_FUNCIÓN)
        {
            Ñ::Nodo* args;
            if(nodos->ramas.size() == 0)
            {
                args = (Ñ::Nodo*)(new Ñ::Argumentos);
            }
            else if(nodos->ramas.size() == 1)
            {
                Ñ::Resultado rArgs = resuelveArgumentos((Ñ::Argumentos*)(nodos->ramas[0]), tablaSímbolos);
                if(rArgs.error())
                {
                    return rArgs;
                }
                args = rArgs.nodo();
            }
            return ejecutaFunción(((Ñ::LlamaFunción*)nodos)->nombre, args, tablaSímbolos);
        }

        resultado.error("INTÉRPRETE :: El árbol de nodos es incorrecto, esperaba Lado Derecho de Asignación. Categoría del nódulo actual: " + std::to_string(nodos->categoría));
        return resultado;
    }
}

Ñ::Resultado Ñ::interpretaNodos(Ñ::Nodo* nodos, Ñ::TablaSímbolos* tablaSímbolos)
{
    Ñ::Resultado resultado;

    if(nodos->categoría == Ñ::CategoríaNodo::NODO_MÓDULO)
    {
        for(Ñ::Nodo* n : nodos->ramas)
        {
            Ñ::Resultado rResuelveSímbolos;
            if(n == nullptr)
            {
                rResuelveSímbolos.error("He recibido un nodo nulo");
                return rResuelveSímbolos;
            }

            rResuelveSímbolos = interpretaNodos(n, tablaSímbolos);

            if(rResuelveSímbolos.error())
            {
                return rResuelveSímbolos;
            }
        }
        
        resultado.éxito();
        return resultado;
    }
    else if(nodos->categoría == Ñ::CategoríaNodo::NODO_LLAMA_FUNCIÓN)
    {
        Ñ::Nodo* args;
        if(nodos->ramas.size() == 0)
        {
            args = (Ñ::Nodo*)(new Ñ::Argumentos);
        }
        else if(nodos->ramas.size() == 1)
        {
            Ñ::Resultado rArgs = resuelveArgumentos((Ñ::Argumentos*)(nodos->ramas[0]), tablaSímbolos);
            if(rArgs.error())
            {
                return rArgs;
            }
            args = rArgs.nodo();
        }
        return ejecutaFunción(((Ñ::LlamaFunción*)nodos)->nombre, args, tablaSímbolos);
    }
    else if(nodos->categoría == Ñ::CategoríaNodo::NODO_DEFINE_FUNCIÓN)
    {
        Ñ::Resultado rDeclara;
        rDeclara = tablaSímbolos->declara(((Ñ::DefineFunción*)nodos)->nombre, nullptr);
        if(rDeclara.error())
        {
            return rDeclara;
        }

        Ñ::Resultado rDefine;
        Ñ::Función* fn = new Ñ::Función;
        fn->nombre = ((Ñ::DefineFunción*)nodos)->nombre;
        for(auto n : nodos->ramas)
        {
            ((Ñ::Nodo*)fn)->ramas.push_back(n);
        }
        
        rDefine = tablaSímbolos->ponValor(((Ñ::DefineFunción*)nodos)->nombre, (Ñ::Nodo*)fn);
        if(rDefine.error())
        {
            return rDefine;
        }

        resultado.éxito();
        return resultado;
    }
    else if(nodos->categoría == Ñ::CategoríaNodo::NODO_BLOQUE)
    {
        for(Ñ::Nodo* n : nodos->ramas)
        {
            Ñ::Resultado rResuelveSímbolos;
            if(n == nullptr)
            {
                rResuelveSímbolos.error("He recibido un nodo nulo");
                return rResuelveSímbolos;
            }

            if(n->categoría == Ñ::CategoríaNodo::NODO_BLOQUE)
            {
                Ñ::TablaSímbolos* subTabla = new Ñ::TablaSímbolos(tablaSímbolos);
                rResuelveSímbolos = interpretaNodos(n, subTabla);
                delete subTabla;
            }
            else
            {
                rResuelveSímbolos = interpretaNodos(n, tablaSímbolos);
            }

            if(rResuelveSímbolos.error())
            {
                return rResuelveSímbolos;
            }
        }
        
        resultado.éxito();
        return resultado;
    }
    else if(nodos->categoría == Ñ::CategoríaNodo::NODO_EXPRESIÓN)
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
    else if(nodos->categoría == Ñ::CategoríaNodo::NODO_LITERAL)
    {
        resultado.éxito();
        resultado.nodo(duplicaÁrbol(nodos));
        return resultado;
    }
    else if(nodos->categoría == Ñ::CategoríaNodo::NODO_ASIGNA)
    {
        Ñ::Resultado rLia = interpretaLIA(nodos->ramas[0], tablaSímbolos);
        Ñ::Resultado rLda = interpretaLDA(nodos->ramas[1], tablaSímbolos);

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

            Ñ::Resultado rId = obténLiteral(rLda.nodo(), tablaSímbolos);
            if(rId.error())
            {
                return rId;
            }

            Ñ::Nodo* valor = rId.nodo();
            Ñ::Nodo* valorTmp = duplicaÁrbol(valor);
            tablaSímbolos->ponValor(idLia->id, valorTmp);
            delete valorTmp;
        }

        resultado.éxito();
        resultado.nodo(rLia.nodo());
        return resultado;
    }

    resultado.error("INTÉRPRETE :: No consigo interpretar el árbol de nodos. Categoría del nódulo actual: " + std::to_string(nodos->categoría));
    return resultado;
}