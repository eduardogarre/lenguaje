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
                    if(arg->categoría == Ñ::CategoríaNodo::NODO_VALOR)
                    {
                        Ñ::Literal* valorArgumento = (Ñ::Literal*)arg;
                        Ñ::Valor* valor = duplicaValor((Ñ::Valor*)arg);
                        Ñ::DeclaraVariable* declaraciónArgumento = (Ñ::DeclaraVariable*)(((Ñ::Nodo*)fn)->ramas[1]->ramas[i]);
                        subTabla->declara(declaraciónArgumento->variable, ((Ñ::Nodo*)declaraciónArgumento)->ramas[0]);
                        subTabla->ponValor(declaraciónArgumento->variable, (Ñ::Nodo*)valor);
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

    Ñ::Resultado sumaValores(Ñ::Nodo* n1, Ñ::Nodo* n2)
    {
        Ñ::Resultado resultado;
        if(n1 == nullptr || n2 == nullptr)
        {
            resultado.error("Uno de los valores es nulo");
            return resultado;
        }
        else if(n1->categoría != Ñ::CategoríaNodo::NODO_VALOR || n2->categoría != Ñ::CategoríaNodo::NODO_VALOR)
        {
            resultado.error("Uno de los nodos no es un valor");
            return resultado;
        }

        Ñ::Valor* v1 = (Ñ::Valor*)n1;
        Ñ::Valor* v2 = (Ñ::Valor*)n2;
        Ñ::Valor* r;

        Ñ::CategoríaTipo tmc = obténTipoMínimoComún(v1->obténTipo(), v2->obténTipo());
	
        switch (tmc)
        {
        case TIPO_NADA:
            resultado.error("Valor de tipo incorrecto");
            return resultado;
            break;
        
        case TIPO_PUNTERO:
            r = new Ñ::Valor;
            r->puntero(v1->puntero() + v2->puntero());
            resultado.éxito();
            resultado.nodo((Ñ::Nodo*)r);
            return resultado;
            break;
        
        case TIPO_BOOLEANO:
            r = new Ñ::Valor;
            r->booleano(v1->booleano() || v2->booleano());
            resultado.éxito();
            resultado.nodo((Ñ::Nodo*)r);
            return resultado;
            break;
        
        case TIPO_NATURAL_8:
            r = new Ñ::Valor;
            r->nat8(v1->nat8() + v2->nat8());
            resultado.éxito();
            resultado.nodo((Ñ::Nodo*)r);
            return resultado;
            break;
        
        case TIPO_NATURAL_16:
            r = new Ñ::Valor;
            r->nat16(v1->nat16() + v2->nat16());
            resultado.éxito();
            resultado.nodo((Ñ::Nodo*)r);
            return resultado;
            break;
        
        case TIPO_NATURAL_32:
            r = new Ñ::Valor;
            r->nat32(v1->nat32() + v2->nat32());
            resultado.éxito();
            resultado.nodo((Ñ::Nodo*)r);
            return resultado;
            break;
        
        case TIPO_NATURAL_64:
            r = new Ñ::Valor;
            r->nat64(v1->nat64() + v2->nat64());
            resultado.éxito();
            resultado.nodo((Ñ::Nodo*)r);
            return resultado;
            break;
        
        case TIPO_ENTERO_8:
            r = new Ñ::Valor;
            r->ent8(v1->ent8() + v2->ent8());
            resultado.éxito();
            resultado.nodo((Ñ::Nodo*)r);
            return resultado;
            break;
        
        case TIPO_ENTERO_16:
            r = new Ñ::Valor;
            r->ent16(v1->ent16() + v2->ent16());
            resultado.éxito();
            resultado.nodo((Ñ::Nodo*)r);
            return resultado;
            break;
        
        case TIPO_ENTERO_32:
            r = new Ñ::Valor;
            r->ent32(v1->ent32() + v2->ent32());
            resultado.éxito();
            resultado.nodo((Ñ::Nodo*)r);
            return resultado;
            break;
        
        case TIPO_ENTERO_64:
            r = new Ñ::Valor;
            r->ent64(v1->ent64() + v2->ent64());
            resultado.éxito();
            resultado.nodo((Ñ::Nodo*)r);
            return resultado;
            break;
        
        case TIPO_REAL_32:
            r = new Ñ::Valor;
            r->real32(v1->real32() + v2->real32());
            resultado.éxito();
            resultado.nodo((Ñ::Nodo*)r);
            return resultado;
            break;
        
        case TIPO_REAL_64:
            r = new Ñ::Valor;
            r->real64(v1->real64() + v2->real64());
            resultado.éxito();
            resultado.nodo((Ñ::Nodo*)r);
            return resultado;
            break;
        
        default:
            resultado.error("Tipo mínimo común incorrecto");
            return resultado;
            break;
        }
    }
    
    Ñ::Resultado restaValores(Ñ::Nodo* n1, Ñ::Nodo* n2)
    {
        Ñ::Resultado resultado;
        if(n1 == nullptr || n2 == nullptr)
        {
            resultado.error("Uno de los valores es nulo");
            return resultado;
        }
        else if(n1->categoría != Ñ::CategoríaNodo::NODO_VALOR || n2->categoría != Ñ::CategoríaNodo::NODO_VALOR)
        {
            resultado.error("Uno de los nodos no es un valor");
            return resultado;
        }

        Ñ::Valor* v1 = (Ñ::Valor*)n1;
        Ñ::Valor* v2 = (Ñ::Valor*)n2;
        Ñ::Valor* r;

        Ñ::CategoríaTipo tmc = obténTipoMínimoComún(v1->obténTipo(), v2->obténTipo());
	
        switch (tmc)
        {
        case TIPO_NADA:
        case TIPO_BOOLEANO:
            resultado.error("Valor de tipo incorrecto");
            return resultado;
            break;
        
        case TIPO_PUNTERO:
            r = new Ñ::Valor;
            r->puntero(v1->puntero() - v2->puntero());
            resultado.éxito();
            resultado.nodo((Ñ::Nodo*)r);
            return resultado;
            break;
        
        case TIPO_NATURAL_8:
            r = new Ñ::Valor;
            r->nat8(v1->nat8() - v2->nat8());
            resultado.éxito();
            resultado.nodo((Ñ::Nodo*)r);
            return resultado;
            break;
        
        case TIPO_NATURAL_16:
            r = new Ñ::Valor;
            r->nat16(v1->nat16() - v2->nat16());
            resultado.éxito();
            resultado.nodo((Ñ::Nodo*)r);
            return resultado;
            break;
        
        case TIPO_NATURAL_32:
            r = new Ñ::Valor;
            r->nat32(v1->nat32() - v2->nat32());
            resultado.éxito();
            resultado.nodo((Ñ::Nodo*)r);
            return resultado;
            break;
        
        case TIPO_NATURAL_64:
            r = new Ñ::Valor;
            r->nat64(v1->nat64() - v2->nat64());
            resultado.éxito();
            resultado.nodo((Ñ::Nodo*)r);
            return resultado;
            break;
        
        case TIPO_ENTERO_8:
            r = new Ñ::Valor;
            r->ent8(v1->ent8() - v2->ent8());
            resultado.éxito();
            resultado.nodo((Ñ::Nodo*)r);
            return resultado;
            break;
        
        case TIPO_ENTERO_16:
            r = new Ñ::Valor;
            r->ent16(v1->ent16() - v2->ent16());
            resultado.éxito();
            resultado.nodo((Ñ::Nodo*)r);
            return resultado;
            break;
        
        case TIPO_ENTERO_32:
            r = new Ñ::Valor;
            r->ent32(v1->ent32() - v2->ent32());
            resultado.éxito();
            resultado.nodo((Ñ::Nodo*)r);
            return resultado;
            break;
        
        case TIPO_ENTERO_64:
            r = new Ñ::Valor;
            r->ent64(v1->ent64() - v2->ent64());
            resultado.éxito();
            resultado.nodo((Ñ::Nodo*)r);
            return resultado;
            break;
        
        case TIPO_REAL_32:
            r = new Ñ::Valor;
            r->real32(v1->real32() - v2->real32());
            resultado.éxito();
            resultado.nodo((Ñ::Nodo*)r);
            return resultado;
            break;
        
        case TIPO_REAL_64:
            r = new Ñ::Valor;
            r->real64(v1->real64() - v2->real64());
            resultado.éxito();
            resultado.nodo((Ñ::Nodo*)r);
            return resultado;
            break;
        
        default:
            resultado.error("Tipo mínimo común incorrecto");
            return resultado;
            break;
        }
    }
    
    Ñ::Resultado multiplicaValores(Ñ::Nodo* n1, Ñ::Nodo* n2)
    {
        Ñ::Resultado resultado;
        if(n1 == nullptr || n2 == nullptr)
        {
            resultado.error("Uno de los valores es nulo");
            return resultado;
        }
        else if(n1->categoría != Ñ::CategoríaNodo::NODO_VALOR || n2->categoría != Ñ::CategoríaNodo::NODO_VALOR)
        {
            resultado.error("Uno de los nodos no es un valor");
            return resultado;
        }

        Ñ::Valor* v1 = (Ñ::Valor*)n1;
        Ñ::Valor* v2 = (Ñ::Valor*)n2;
        Ñ::Valor* r;

        Ñ::CategoríaTipo tmc = obténTipoMínimoComún(v1->obténTipo(), v2->obténTipo());
	
        switch (tmc)
        {
        case TIPO_NADA:
            resultado.error("Valor de tipo incorrecto");
            return resultado;
            break;
        
        case TIPO_PUNTERO:
            r = new Ñ::Valor;
            r->puntero(v1->puntero() * v2->puntero());
            resultado.éxito();
            resultado.nodo((Ñ::Nodo*)r);
            return resultado;
            break;
        
        case TIPO_BOOLEANO:
            r = new Ñ::Valor;
            r->booleano(v1->booleano() && v2->booleano());
            resultado.éxito();
            resultado.nodo((Ñ::Nodo*)r);
            return resultado;
            break;
        
        case TIPO_NATURAL_8:
            r = new Ñ::Valor;
            r->nat8(v1->nat8() * v2->nat8());
            resultado.éxito();
            resultado.nodo((Ñ::Nodo*)r);
            return resultado;
            break;
        
        case TIPO_NATURAL_16:
            r = new Ñ::Valor;
            r->nat16(v1->nat16() * v2->nat16());
            resultado.éxito();
            resultado.nodo((Ñ::Nodo*)r);
            return resultado;
            break;
        
        case TIPO_NATURAL_32:
            r = new Ñ::Valor;
            r->nat32(v1->nat32() * v2->nat32());
            resultado.éxito();
            resultado.nodo((Ñ::Nodo*)r);
            return resultado;
            break;
        
        case TIPO_NATURAL_64:
            r = new Ñ::Valor;
            r->nat64(v1->nat64() * v2->nat64());
            resultado.éxito();
            resultado.nodo((Ñ::Nodo*)r);
            return resultado;
            break;
        
        case TIPO_ENTERO_8:
            r = new Ñ::Valor;
            r->ent8(v1->ent8() * v2->ent8());
            resultado.éxito();
            resultado.nodo((Ñ::Nodo*)r);
            return resultado;
            break;
        
        case TIPO_ENTERO_16:
            r = new Ñ::Valor;
            r->ent16(v1->ent16() * v2->ent16());
            resultado.éxito();
            resultado.nodo((Ñ::Nodo*)r);
            return resultado;
            break;
        
        case TIPO_ENTERO_32:
            r = new Ñ::Valor;
            r->ent32(v1->ent32() * v2->ent32());
            resultado.éxito();
            resultado.nodo((Ñ::Nodo*)r);
            return resultado;
            break;
        
        case TIPO_ENTERO_64:
            r = new Ñ::Valor;
            r->ent64(v1->ent64() * v2->ent64());
            resultado.éxito();
            resultado.nodo((Ñ::Nodo*)r);
            return resultado;
            break;
        
        case TIPO_REAL_32:
            r = new Ñ::Valor;
            r->real32(v1->real32() * v2->real32());
            resultado.éxito();
            resultado.nodo((Ñ::Nodo*)r);
            return resultado;
            break;
        
        case TIPO_REAL_64:
            r = new Ñ::Valor;
            r->real64(v1->real64() * v2->real64());
            resultado.éxito();
            resultado.nodo((Ñ::Nodo*)r);
            return resultado;
            break;
        
        default:
            resultado.error("Tipo mínimo común incorrecto");
            return resultado;
            break;
        }
    }
    
    Ñ::Resultado divideValores(Ñ::Nodo* n1, Ñ::Nodo* n2)
    {
        Ñ::Resultado resultado;
        if(n1 == nullptr || n2 == nullptr)
        {
            resultado.error("Uno de los valores es nulo");
            return resultado;
        }
        else if(n1->categoría != Ñ::CategoríaNodo::NODO_VALOR || n2->categoría != Ñ::CategoríaNodo::NODO_VALOR)
        {
            resultado.error("Uno de los nodos no es un valor");
            return resultado;
        }

        Ñ::Valor* v1 = (Ñ::Valor*)n1;
        Ñ::Valor* v2 = (Ñ::Valor*)n2;
        Ñ::Valor* r;

        Ñ::CategoríaTipo tmc = obténTipoMínimoComún(v1->obténTipo(), v2->obténTipo());
	
        switch (tmc)
        {
        case TIPO_NADA:
        case TIPO_BOOLEANO:
            resultado.error("Valor de tipo incorrecto");
            return resultado;
            break;
        
        case TIPO_PUNTERO:
            r = new Ñ::Valor;
            r->puntero(v1->puntero() / v2->puntero());
            resultado.éxito();
            resultado.nodo((Ñ::Nodo*)r);
            return resultado;
            break;
        
        case TIPO_NATURAL_8:
            r = new Ñ::Valor;
            r->nat8(v1->nat8() / v2->nat8());
            resultado.éxito();
            resultado.nodo((Ñ::Nodo*)r);
            return resultado;
            break;
        
        case TIPO_NATURAL_16:
            r = new Ñ::Valor;
            r->nat16(v1->nat16() / v2->nat16());
            resultado.éxito();
            resultado.nodo((Ñ::Nodo*)r);
            return resultado;
            break;
        
        case TIPO_NATURAL_32:
            r = new Ñ::Valor;
            r->nat32(v1->nat32() / v2->nat32());
            resultado.éxito();
            resultado.nodo((Ñ::Nodo*)r);
            return resultado;
            break;
        
        case TIPO_NATURAL_64:
            r = new Ñ::Valor;
            r->nat64(v1->nat64() / v2->nat64());
            resultado.éxito();
            resultado.nodo((Ñ::Nodo*)r);
            return resultado;
            break;
        
        case TIPO_ENTERO_8:
            r = new Ñ::Valor;
            r->ent8(v1->ent8() / v2->ent8());
            resultado.éxito();
            resultado.nodo((Ñ::Nodo*)r);
            return resultado;
            break;
        
        case TIPO_ENTERO_16:
            r = new Ñ::Valor;
            r->ent16(v1->ent16() / v2->ent16());
            resultado.éxito();
            resultado.nodo((Ñ::Nodo*)r);
            return resultado;
            break;
        
        case TIPO_ENTERO_32:
            r = new Ñ::Valor;
            r->ent32(v1->ent32() / v2->ent32());
            resultado.éxito();
            resultado.nodo((Ñ::Nodo*)r);
            return resultado;
            break;
        
        case TIPO_ENTERO_64:
            r = new Ñ::Valor;
            r->ent64(v1->ent64() / v2->ent64());
            resultado.éxito();
            resultado.nodo((Ñ::Nodo*)r);
            return resultado;
            break;
        
        case TIPO_REAL_32:
            r = new Ñ::Valor;
            r->real32(v1->real32() / v2->real32());
            resultado.éxito();
            resultado.nodo((Ñ::Nodo*)r);
            return resultado;
            break;
        
        case TIPO_REAL_64:
            r = new Ñ::Valor;
            r->real64(v1->real64() / v2->real64());
            resultado.éxito();
            resultado.nodo((Ñ::Nodo*)r);
            return resultado;
            break;
        
        default:
            resultado.error("Tipo mínimo común incorrecto");
            return resultado;
            break;
        }
    }

    Ñ::Resultado obténValor(Ñ::Nodo* nodo, Ñ::TablaSímbolos* tablaSímbolos)
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
                n = (Ñ::Nodo*)duplicaValor((Ñ::Valor*)rid.nodo());
            }
        }
        else if(nodo->categoría == Ñ::CategoríaNodo::NODO_VALOR)
        {
            n = (Ñ::Nodo*)duplicaValor((Ñ::Valor*)nodo);
        }
        else if(nodo->categoría == Ñ::CategoríaNodo::NODO_LITERAL)
        {
            n = (Ñ::Nodo*)creaValor((Ñ::Literal*)nodo);
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
                    n = (Ñ::Nodo*)duplicaValor((Ñ::Valor*)rid.nodo());
                }
            }
            else if(nodo->categoría == Ñ::CategoríaNodo::NODO_VALOR)
            {
                n = (Ñ::Nodo*)nodo;
            }
            else if(nodo->categoría == Ñ::CategoríaNodo::NODO_LITERAL)
            {
                n = (Ñ::Nodo*)creaValor((Ñ::Literal*)nodo);
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

                    n = (Ñ::Nodo*)duplicaValor((Ñ::Valor*)r.nodo());
                    ((Ñ::Nodo*)argumentos)->ramas.push_back(n);
                }
            }
            else if(r.nodo()->categoría == Ñ::CategoríaNodo::NODO_LITERAL)
            {
                n = (Ñ::Nodo*)creaValor((Ñ::Literal*)r.nodo());
                ((Ñ::Nodo*)argumentos)->ramas.push_back(n);
            }
            else if(r.nodo()->categoría == Ñ::CategoríaNodo::NODO_VALOR)
            {
                ((Ñ::Nodo*)argumentos)->ramas.push_back(r.nodo());
            }
            else
            {
                delete argumentos;
                resultado.error("He recibido como argumento un árbol que no consigo interpretar");
                return resultado;
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
            resultado = obténValor(nodos, tablaSímbolos);
            return resultado;
        }
        else if(nodos->categoría == Ñ::CategoríaNodo::NODO_LITERAL)
        {
            Ñ::Valor* v = creaValor((Ñ::Literal*)nodos);

            resultado.éxito();
            resultado.nodo((Ñ::Nodo*)v);
            return resultado;
        }
        else if(nodos->categoría == Ñ::CategoríaNodo::NODO_VALOR)
        {
            resultado.éxito();
            resultado.nodo(nodos);
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
                
                Ñ::Resultado rn = obténValor(r.nodo(), tablaSímbolos);
                if(rn.error())
                {
                    return rn;
                }
                else
                {
                    n1 = rn.nodo();
                }
                delete r.nodo();

                Ñ::Valor* val = (Ñ::Valor*)n1;
                Ñ::OperaciónUnaria* op = (Ñ::OperaciónUnaria*)nodos;
                Ñ::Valor* valor;

                if(op->operación == "!")
                {
                    if(val->obténTipo() != Ñ::CategoríaTipo::TIPO_BOOLEANO)
                    {
                        resultado.error("Has intentado aplicar la operación lógica NO a un valor que no es booleano");
                        return resultado;
                    }
                    else if(val->booleano() == true)
                    {
                        valor = new Ñ::Valor;
                        valor->booleano(false);
                    }
                    else if(val->booleano() == false)
                    {
                        valor = new Ñ::Valor;
                        valor->booleano(true);
                    }
                    else
                    {
                        resultado.error("Has intentado aplicar la operación lógica NO a un valor que no es booleano");
                        return resultado;
                    }

                    resultado.éxito();
                    resultado.nodo((Ñ::Nodo*)valor);
                    return resultado;
                }
                else if(op->operación == "-")
                {
                    switch (val->obténTipo())
                    {
                    case Ñ::CategoríaTipo::TIPO_NADA:
                        resultado.error("Has intentado negativizar un valor vacío");
                        return resultado;
                        break;
                    
                    case Ñ::CategoríaTipo::TIPO_BOOLEANO:
                        valor = new Ñ::Valor;
                        if(val->booleano() == true)
                        {
                            valor->booleano(false);
                        }
                        else if(val->booleano() == false)
                        {
                            valor->booleano(true);
                        }
                    
                    case Ñ::CategoríaTipo::TIPO_ENTERO_8:
                        valor = new Ñ::Valor;
                        valor->ent8((-1) * val->ent8());
                        break;
                    
                    case Ñ::CategoríaTipo::TIPO_ENTERO_16:
                        valor = new Ñ::Valor;
                        valor->ent16((-1) * val->ent16());
                        break;
                    
                    case Ñ::CategoríaTipo::TIPO_ENTERO_32:
                        valor = new Ñ::Valor;
                        valor->ent32((-1) * val->ent32());
                        break;
                    
                    case Ñ::CategoríaTipo::TIPO_ENTERO_64:
                        valor = new Ñ::Valor;
                        valor->ent64((-1) * val->ent64());
                        break;
                    
                    case Ñ::CategoríaTipo::TIPO_REAL_32:
                        valor = new Ñ::Valor;
                        valor->real32((-1) * val->real32());
                        break;
                    
                    case Ñ::CategoríaTipo::TIPO_REAL_64:
                        valor = new Ñ::Valor;
                        valor->real64((-1) * val->real64());
                        break;
                    
                    case Ñ::CategoríaTipo::TIPO_TEXTO:
                        valor = new Ñ::Valor;
                        valor->texto(val->texto());
                        break;
                    
                    default:
                        break;
                    }

                    resultado.éxito();
                    resultado.nodo((Ñ::Nodo*)valor);
                    return resultado;
                }

                delete val;

                resultado.éxito();
                resultado.nodo((Ñ::Nodo*)valor);
                return resultado;
            }
            else
            {
                resultado.error("El nodo Ñ::OpUnaria tenía " + std::to_string(nodos->ramas.size()) + " ramas");
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
                resultado.error("El nodo Ñ::Igualdad tiene " + std::to_string(nodos->ramas.size()) + " ramas");
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
                Ñ::Resultado rn = obténValor(r.nodo(), tablaSímbolos);
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
                        rn2 = obténValor(rn2.nodo(), tablaSímbolos);
                        if(rn2.error())
                        {
                            return rn2;
                        }
                        n2 = rn2.nodo();
                    }

                    if(operación == "+")
                    {
                        Ñ::Resultado rop = sumaValores(n1, n2);
                        delete n2, n1;
                        if(rop.error())
                        {
                            return rop;
                        }
                        n1 = rop.nodo();
                    }
                    else if(operación == "-")
                    {
                        Ñ::Resultado rop = restaValores(n1, n2);
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
                Ñ::Resultado rn = obténValor(r.nodo(), tablaSímbolos);
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
                        rn2 = obténValor(rn2.nodo(), tablaSímbolos);
                        if(rn2.error())
                        {
                            return rn2;
                        }
                        n2 = rn2.nodo();
                    }

                    if(operación == "*")
                    {
                        Ñ::Resultado rop = multiplicaValores(n1, n2);
                        delete n2, n1;
                        if(rop.error())
                        {
                            return rop;
                        }
                        n1 = rop.nodo();
                    }
                    else if(operación == "/")
                    {
                        Ñ::Resultado rop = divideValores(n1, n2);
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
            Ñ::Resultado rBloque;
            if(n == nullptr)
            {
                rBloque.error("He recibido un nodo nulo");
                return rBloque;
            }

            if(n->categoría == Ñ::CategoríaNodo::NODO_BLOQUE)
            {
                Ñ::TablaSímbolos* subTabla = new Ñ::TablaSímbolos(tablaSímbolos);
                rBloque = interpretaNodos(n, subTabla);
                delete subTabla;
            }
            else
            {
                rBloque = interpretaNodos(n, tablaSímbolos);
            }

            if(rBloque.error())
            {
                return rBloque;
            }
            if(n->ramas[0]->categoría == Ñ::CategoríaNodo::NODO_DEVUELVE)
            {
                return rBloque;
            }
        }
        
        resultado.éxito();
        return resultado;
    }
    else if(nodos->categoría == Ñ::CategoríaNodo::NODO_EXPRESIÓN)
    {
        for(Ñ::Nodo* n : nodos->ramas)
        {
            Ñ::Resultado rExpresión = interpretaNodos(n, tablaSímbolos);
            if(rExpresión.error())
            {
                return rExpresión;
            }
            if(n->categoría == Ñ::CategoríaNodo::NODO_DEVUELVE)
            {
                return rExpresión;
            }
        }
        
        resultado.éxito();
        return resultado;
    }
    else if(nodos->categoría == Ñ::CategoríaNodo::NODO_DEVUELVE)
    {
        if(nodos->ramas.size() == 0)
        {
            Ñ::Valor* retorno = new Ñ::Valor;
            resultado.éxito();
            resultado.nodo((Ñ::Nodo*)retorno);
            return resultado;
        }
        else if(nodos->ramas.size() == 1)
        {
            Ñ::Resultado rLda = interpretaLDA(nodos->ramas[0], tablaSímbolos);
            if(rLda.error())
            {
                return rLda;
            }

            // Obtengo el valor del 'devuelve X' y lo devuelvo
            resultado.éxito();
            resultado.nodo(rLda.nodo());
            return resultado;
        }
    }
    else if(nodos->categoría == Ñ::CategoríaNodo::NODO_LITERAL)
    {
        Ñ::Nodo* v = (Ñ::Nodo*) creaValor((Ñ::Literal*)nodos);
        resultado.éxito();
        resultado.nodo(v);
        return resultado;
    }
    else if(nodos->categoría == Ñ::CategoríaNodo::NODO_VALOR)
    {
        resultado.éxito();
        resultado.nodo(duplicaÁrbol(nodos));
        return resultado;
    }
    else if(nodos->categoría == Ñ::CategoríaNodo::NODO_DECLARA_VARIABLE)
    {
        return interpretaLIA(nodos, tablaSímbolos);
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
        
        if(rLda.nodo()->categoría == Ñ::CategoríaNodo::NODO_VALOR)
        {
            std::string id = ((Ñ::Identificador*)(rLia.nodo()))->id;
            tablaSímbolos->ponValor(id, rLda.nodo());
        }
        else if(rLda.nodo()->categoría == Ñ::CategoríaNodo::NODO_IDENTIFICADOR)
        {
            Ñ::Identificador* idLia = ((Ñ::Identificador*)rLia.nodo());
            Ñ::Identificador* idLda = ((Ñ::Identificador*)rLda.nodo());

            Ñ::Resultado rId = obténValor(rLda.nodo(), tablaSímbolos);
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