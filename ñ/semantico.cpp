/*
SPDX-License-Identifier: MPL-2.0-no-copyleft-exception

This Source Code Form is subject to the terms of the Mozilla Public License, v.
2.0. If a copy of the MPL was not distributed with this file, You can obtain one
at http://mozilla.org/MPL/2.0/.

This Source Code Form is "Incompatible With Secondary Licenses", as defined by
the Mozilla Public License, v. 2.0.

Copyright © 2021 Eduardo Garre Muñoz
*/

#include <iostream>

#include "nodo.hpp"
#include "posicion.hpp"
#include "resultado.hpp"
#include "semantico.hpp"
#include "tablasimbolos.hpp"
#include "tipo.hpp"
#include "valor.hpp"


Ñ::Resultado _analiza(Ñ::Nodo* nodo, Ñ::TablaSímbolos* tablaSímbolos);
Ñ::Resultado _analizaLIA(Ñ::Nodo* nodo, Ñ::TablaSímbolos* tablaSímbolos);
Ñ::Resultado _analizaLDA(Ñ::Nodo* nodo, Ñ::TablaSímbolos* tablaSímbolos);
Ñ::Resultado _insertaConversión(Ñ::Nodo* nodo, Ñ::Tipo* tipoOrigen, Ñ::Tipo* tipoDestino);

Ñ::Resultado _insertaConversión(Ñ::Nodo* padre, uint64_t índiceHijo, Ñ::Tipo* tipoOrigen, Ñ::Tipo* tipoDestino)
{
    Ñ::Resultado resultado;
    
    if(padre == nullptr)
    {
        resultado.error("Has pasados un nodo nulo.");
        return resultado;
    }

    Ñ::ConvierteTipos* conv = new Ñ::ConvierteTipos(tipoOrigen->posición());
    conv->origen = tipoOrigen;
    conv->destino = tipoDestino;
    conv->ramas.push_back(padre->ramas[índiceHijo]);

    padre->ramas[índiceHijo] = (Ñ::Nodo*)conv;

    resultado.éxito();
    return resultado;
}

Ñ::Resultado _analizaSiCondicional(Ñ::Nodo* nodo, Ñ::TablaSímbolos* tablaSímbolos)
{
    Ñ::Resultado resultado;

    if(nodo == nullptr)
    {
        resultado.error("El árbol de nodos es un puntero nulo, esperaba un si-condicional.");
        return resultado;
    }

    if(nodo->categoría != Ñ::CategoríaNodo::NODO_SI_CONDICIONAL)
    {
        resultado.error("El árbol de nodos es incorrecto, esperaba un si-condicional.");
        resultado.posición(nodo->posición());
        return resultado;
    }

    if(nodo->ramas.size() < 2)
    {
        resultado.error("El árbol de nodos es incorrecto, esperaba al menos una condición y un bloque.");
        resultado.posición(nodo->posición());
        return resultado;
    }

    int i = 0;
    for(i = 0; i < nodo->ramas.size() - 1; i += 2)
    {
        Ñ::Resultado rCondición = _analizaLDA(nodo->ramas[i], tablaSímbolos);
        if(rCondición.error())
        {
            return rCondición;
        }
        Ñ::Resultado rBloque = _analiza(nodo->ramas[i+1], tablaSímbolos);
        if(rBloque.error())
        {
            return rBloque;
        }
    }
    
    if(i == nodo->ramas.size()-1)
    {
        Ñ::Resultado rBloque = _analiza(nodo->ramas[i], tablaSímbolos);
        if(rBloque.error())
        {
            return rBloque;
        }
    }

    resultado.éxito();
    return resultado;
}

Ñ::Resultado _analizaBucleMientras(Ñ::Nodo* nodo, Ñ::TablaSímbolos* tablaSímbolos)
{
    Ñ::Resultado resultado;

    if(nodo == nullptr)
    {
        resultado.error("El árbol de nodos es un puntero nulo, esperaba un bucle-mientras.");
        return resultado;
    }

    if(nodo->categoría != Ñ::CategoríaNodo::NODO_BUCLE_MIENTRAS)
    {
        resultado.error("El árbol de nodos es incorrecto, esperaba un bucle-mientras.");
        resultado.posición(nodo->posición());
        return resultado;
    }

    if(nodo->ramas.size() != 2)
    {
        resultado.error("El árbol de nodos es incorrecto, esperaba una condición y un bloque.");
        resultado.posición(nodo->posición());
        return resultado;
    }

    Ñ::Resultado rCondición = _analizaLDA(nodo->ramas[0], tablaSímbolos);
    if(rCondición.error())
    {
        return rCondición;
    }
    Ñ::Resultado rBloque = _analiza(nodo->ramas[1], tablaSímbolos);
    if(rBloque.error())
    {
        return rBloque;
    }

    resultado.éxito();
    return resultado;
}

Ñ::Resultado _analizaLlamadaFunción(Ñ::Nodo* nodo, Ñ::TablaSímbolos* tablaSímbolos)
{
    Ñ::Resultado resultado;

    if(nodo == nullptr)
    {
        resultado.error("El árbol de nodos es un puntero nulo, esperaba una llamada a una función.");
        return resultado;
    }

    if(nodo->categoría != Ñ::CategoríaNodo::NODO_LLAMA_FUNCIÓN)
    {
        resultado.error("El árbol de nodos es incorrecto, esperaba una llamada a una función.");
        resultado.posición(nodo->posición());
        return resultado;
    }

    if(nodo->ramas.size() != 1)
    {
        resultado.error("El árbol de nodos es incorrecto, esperaba que se aportaran argumentos.");
        resultado.posición(nodo->posición());
        return resultado;
    }

    Ñ::LlamaFunción* fn = (Ñ::LlamaFunción*)nodo;
    
    if(!tablaSímbolos->nombreReservadoEnCualquierÁmbito(fn->nombre))
    {
        resultado.error("Todavía no has declarado la función " + fn->nombre + "().");
        resultado.posición(fn->posición());
        return resultado;
    }

    Ñ::Resultado rFirma = tablaSímbolos->leeTipo(fn->nombre);
    if(rFirma.error())
    {
        return rFirma;
    }

    Ñ::Nodo* tipoDevuelto = rFirma.nodo()->ramas[0];
    Ñ::Nodo* argsDeclarados = rFirma.nodo()->ramas[1];
    Ñ::Nodo* argsDefinidos = nodo->ramas[0];

    if(argsDeclarados->ramas.size() != argsDefinidos->ramas.size())
    {
        resultado.error("Has pasado " + std::to_string(argsDefinidos->ramas.size()) + " argumentos a " + fn->nombre + "(), que espera " + std::to_string(argsDeclarados->ramas.size()) + " argumentos.");
        resultado.posición(nodo->posición());
        return resultado;
    }

    Ñ::TablaSímbolos* subTabla = new Ñ::TablaSímbolos(tablaSímbolos);
    subTabla->ponFunciónPropietaria(fn->nombre);

    for(uint8_t i = 0; i < argsDeclarados->ramas.size(); i++)
    {
        Ñ::Resultado rTipoLIA = _analizaLIA(argsDeclarados->ramas[i], subTabla);
        Ñ::Resultado rTipoLDA = _analizaLDA(argsDefinidos->ramas[i], subTabla);

        if(rTipoLIA.error())
        {
            return rTipoLIA;
        }
        else if(rTipoLDA.error())
        {
            return rTipoLDA;
        }

        Ñ::Tipo* tipoLIA = (Ñ::Tipo*)(rTipoLIA.nodo());
        Ñ::Tipo* tipoLDA = (Ñ::Tipo*)(rTipoLDA.nodo());

        if(sonÁrbolesDuplicados((Ñ::Nodo*)tipoLIA, (Ñ::Nodo*)tipoLDA))
        {
            // No hace falta convertir tipos
        }
        else if(Ñ::tiposAsignables(tipoLIA, tipoLDA))
        {
            // Son tipos distintos pero compatibles, hay que convertir
            //std::cout << "Añadiendo conversión de '" << Ñ::obténNombreDeTipo(tipoLDA->tipo) << "' a '" << Ñ::obténNombreDeTipo(tipoLIA->tipo) << "' para la pase de argumentos" << std::endl;

            _insertaConversión(nodo->ramas[0], i, tipoLDA, tipoLIA);            
        }
        else
        {
            delete subTabla;
            resultado.error("Esperaba un argumento de tipo '" + Ñ::obténNombreDeTipo(tipoLIA) + "', pero he recibido un '" + Ñ::obténNombreDeTipo(tipoLDA) + "'.");
            resultado.posición(tipoLDA->posición());
            return resultado;
        }     
    }
    delete subTabla;

    resultado.éxito();
    resultado.nodo(tipoDevuelto);
    return resultado;
}

Ñ::Resultado _analizaDefiniciónFunción(Ñ::Nodo* nodo, Ñ::TablaSímbolos* tablaSímbolos)
{
    Ñ::Resultado resultado;

    if(nodo == nullptr)
    {
        resultado.error("El árbol de nodos es un puntero nulo, esperaba una definición de función.");
        return resultado;
    }

    if(nodo->categoría != Ñ::CategoríaNodo::NODO_DEFINE_FUNCIÓN)
    {
        resultado.error("El árbol de nodos es incorrecto, esperaba una definición de función.");
        resultado.posición(nodo->posición());
        return resultado;
    }

    if(nodo->ramas.size() != 3)
    {
        resultado.error("El árbol de nodos es incorrecto, la definición de una función debe tener 3 ramas: 'tipo', 'argumentos' y 'bloque'.");
        resultado.posición(nodo->posición());
        return resultado;
    }

    Ñ::DefineFunción* fn = (Ñ::DefineFunción*)nodo;
    
    if(tablaSímbolos->nombreReservadoEnEsteÁmbito(fn->nombre))
    {
        resultado.error("El identificador '" + fn->nombre + "' ya está en uso, no puedo definir una nueva función '" + fn->nombre + "()'.");
        resultado.posición(nodo->posición());
        return resultado;
    }
    else
    {
        Ñ::Resultado rFirma = creaFirmaFunción(nodo);
        if(rFirma.error())
        {
            return rFirma;
        }

        tablaSímbolos->declara(fn->nombre, rFirma.nodo());
    }

    Ñ::TablaSímbolos* nuevaTabla = new Ñ::TablaSímbolos(tablaSímbolos);
    nuevaTabla->ponFunciónPropietaria(fn->nombre);

    for(auto arg : nodo->ramas[1]->ramas)
    {
        Ñ::Resultado rArg = _analizaLIA(arg, nuevaTabla);
        if(rArg.error())
        {
            return rArg;
        }
    }

    resultado = _analiza(nodo->ramas[2], nuevaTabla);
    delete nuevaTabla;
    return resultado;
}

Ñ::Resultado _analizaDeclaraciónFunción(Ñ::Nodo* nodo, Ñ::TablaSímbolos* tablaSímbolos)
{
    Ñ::Resultado resultado;

    if(nodo == nullptr)
    {
        resultado.error("El árbol de nodos es un puntero nulo, esperaba una declaración de función.");
        return resultado;
    }

    if(nodo->categoría != Ñ::CategoríaNodo::NODO_DECLARA_FUNCIÓN)
    {
        resultado.error("El árbol de nodos es incorrecto, esperaba una declaración de función.");
        resultado.posición(nodo->posición());
        return resultado;
    }

    if(nodo->ramas.size() != 2)
    {
        resultado.error("El árbol de nodos es incorrecto, la declaración de una función debe tener 2 ramas: 'tipo' y 'argumentos'.");
        resultado.posición(nodo->posición());
        return resultado;
    }

    Ñ::DeclaraFunción* fn = (Ñ::DeclaraFunción*)nodo;
    
    if(!tablaSímbolos->nombreReservadoEnEsteÁmbito(fn->nombre))
    {
        Ñ::Resultado rFirma = creaFirmaFunción(nodo);
        if(rFirma.error())
        {
            return rFirma;
        }

        tablaSímbolos->declara(fn->nombre, rFirma.nodo());
    }
    else
    {
        resultado.error("El identificador " + fn->nombre + " ya está en uso, no puedo declarar una nueva función '" + fn->nombre + "()'.");
        resultado.posición(nodo->posición());
        return resultado;
    }
    
    resultado.éxito();
    return resultado;
}

Ñ::Resultado _analizaLIA(Ñ::Nodo* nodo, Ñ::TablaSímbolos* tablaSímbolos)
{
    Ñ::Resultado resultado;

    if(nodo == nullptr)
    {
        resultado.error("ANÁLISIS DE TIPOS :: El nodo es nulo.");
        resultado.posición(nodo->posición());
        return resultado;
    }
    
    if(nodo->categoría == Ñ::CategoríaNodo::NODO_DECLARA_VARIABLE)
    {
        // RESOLUCIÓN DE SÍMBOLOS

        // Obtengo nombre del nuevo identificador
        std::string nombre = ((Ñ::DeclaraVariable*)nodo)->variable;
        
        // Compruebo que el identificador no esté en uso en este ámbito
        if(tablaSímbolos->nombreReservadoEnEsteÁmbito(nombre))
        {
            resultado.error("Ya habías declarado el identificador '" + nombre + "'.");
            resultado.posición(nodo->posición());
            return resultado;
        }

        // Compruebo que el árbol de nodos tenga una rama con el tipo
        if( nodo->ramas.size() != 1)
        {
            resultado.error("Árbol de la declaración de variable mal construido.");
            resultado.posición(nodo->posición());
            return resultado;
        }

        // Si todo lo anterior se cumple, declaro el nuevo identificador y su tipo
        Ñ::Resultado r = tablaSímbolos->declara(nombre, nodo->ramas[0]);
        if(r.error())
        {
            return r;
        }

        // ANÁLISIS, RESOLUCIÓN Y PROPAGACIÓN DE TIPOS
        // Obtengo el tipo del identificador que hemos declarado
        Ñ::Resultado rTipo = tablaSímbolos->leeTipo(nombre);
        if(rTipo.error())
        {
            return rTipo;
        }
        
        resultado.éxito();
        // Propago el tipo del identificador declarado
        resultado.nodo(rTipo.nodo());
        return resultado;
    }
    else if(nodo->categoría == Ñ::CategoríaNodo::NODO_IDENTIFICADOR)
    {
        std::string nombre = ((Ñ::Identificador*)nodo)->id;
        if(tablaSímbolos->nombreReservadoEnCualquierÁmbito(nombre))
        {
            return tablaSímbolos->leeTipo(nombre);
        }
        else
        {
            resultado.error("Todavía no habías declarado el identificador '" + nombre + "'.");
            resultado.posición(nodo->posición());
            return resultado;
        }
    }
    else if(nodo->categoría == Ñ::CategoríaNodo::NODO_PUNTERO)
    {
        if(nodo->ramas.size() != 1)
        {
            resultado.error("No encuentro una referencia para acceder al puntero.");
            resultado.posición(nodo->posición());
            return resultado;
        }

        std::string nombre = ((Ñ::Identificador*)nodo->ramas[0])->id;
        if(tablaSímbolos->nombreReservadoEnCualquierÁmbito(nombre))
        {
            Ñ::Resultado rTipoPuntero = tablaSímbolos->leeTipo(nombre);
            if(rTipoPuntero.error())
            {
                rTipoPuntero.posición(nodo->ramas[0]->posición());
                return rTipoPuntero;
            }
            Ñ::Tipo* tipoPuntero = (Ñ::Tipo*)rTipoPuntero.nodo();

            resultado.éxito();
            resultado.nodo(tipoPuntero->subtipo());
            return resultado;
        }
        else
        {
            resultado.error("Todavía no habías declarado el identificador '" + nombre + "'.");
            resultado.posición(nodo->posición());
            return resultado;
        }
    }
    else
    {
        resultado.error("El LIA tiene una categoría inesperada: " + Ñ::obténNombreDeNodo(nodo->categoría) + ".");
        resultado.posición(nodo->posición());
        return resultado;
    }
}

Ñ::Resultado _analizaLDA(Ñ::Nodo* nodo, Ñ::TablaSímbolos* tablaSímbolos)
{
    Ñ::Resultado resultado;

    if(nodo->categoría == Ñ::CategoríaNodo::NODO_IDENTIFICADOR)
    {
        std::string nombre = ((Ñ::Identificador*)nodo)->id;
        if(tablaSímbolos->nombreReservadoEnCualquierÁmbito(nombre))
        {
            Ñ::Resultado rTipo = tablaSímbolos->leeTipo(((Ñ::Identificador*)nodo)->id);
            if(!rTipo.error())
            {
                Ñ::Tipo* tipo = (Ñ::Tipo*) (rTipo.nodo());
                //std::cout << "IDENTIFICADOR: " << nombre << " TIPO: " << obténNombreDeTipo(tipo) << std::endl;
            }
            return rTipo;
        }
        else
        {
            resultado.error("Todavía no habías declarado el identificador '" + nombre + "'.");
            resultado.posición(nodo->posición());
            return resultado;
        }
    }
    else if(nodo->categoría == Ñ::CategoríaNodo::NODO_VALOR)
    {
        resultado.éxito();
        Ñ::Tipo* tipo = obténTipoDeValor((Ñ::Valor*)nodo);
        resultado.nodo((Ñ::Nodo*)tipo);
        return resultado;
    }
    else if(nodo->categoría == Ñ::CategoríaNodo::NODO_OP_UNARIA)
    {
        if(nodo->ramas.size() == 1)
        {
            Ñ::Nodo* n1;
            Ñ::Resultado r = _analizaLDA(nodo->ramas[0], tablaSímbolos);
            if(r.error())
            {
                return r;
            }

            n1 = r.nodo();
            Ñ::Tipo* tipo = (Ñ::Tipo*)n1;
            Ñ::OperaciónUnaria* op = (Ñ::OperaciónUnaria*)nodo;

            if(op->operación == "!")
            {
                if(tipo->tipo != Ñ::CategoríaTipo::TIPO_BOOLEANO)
                {
                    resultado.error("Has intentado negar un tipo '" + obténNombreDeTipo(tipo) + "'. Sólo puedes negar un tipo booleano.");
                    resultado.posición(tipo->posición());
                    return resultado;
                }

                resultado.éxito();
                resultado.nodo((Ñ::Nodo*)tipo);
                return resultado;
            }
            else if(op->operación == "-")
            {
                Ñ::Tipo* tipoDestino;

                switch (tipo->tipo)
                {
                case Ñ::CategoríaTipo::TIPO_NATURAL_8:
                    tipoDestino = creaTipoBásico(Ñ::CategoríaTipo::TIPO_ENTERO_16);
                    _insertaConversión(nodo, 0, tipo, tipoDestino);
                    resultado.éxito();
                    resultado.nodo((Ñ::Nodo*)tipoDestino);
                    return resultado;
                    break;

                case Ñ::CategoríaTipo::TIPO_NATURAL_16:
                    tipoDestino = creaTipoBásico(Ñ::CategoríaTipo::TIPO_ENTERO_32);
                    _insertaConversión(nodo, 0, tipo, tipoDestino);
                    resultado.éxito();
                    resultado.nodo((Ñ::Nodo*)tipoDestino);
                    return resultado;
                    break;

                case Ñ::CategoríaTipo::TIPO_NATURAL_32:
                    tipoDestino = creaTipoBásico(Ñ::CategoríaTipo::TIPO_ENTERO_64);
                    _insertaConversión(nodo, 0, tipo, tipoDestino);
                    resultado.éxito();
                    resultado.nodo((Ñ::Nodo*)tipoDestino);
                    return resultado;
                    break;

                case Ñ::CategoríaTipo::TIPO_NATURAL_64:
                    resultado.error("Has intentado negativizar un 'nat64', que es demasiado grande.");
                    resultado.posición(tipo->posición());
                    return resultado;
                    break;
                
                case Ñ::CategoríaTipo::TIPO_ENTERO_8:
                case Ñ::CategoríaTipo::TIPO_ENTERO_16:
                case Ñ::CategoríaTipo::TIPO_ENTERO_32:
                case Ñ::CategoríaTipo::TIPO_ENTERO_64:
                    resultado.éxito();
                    resultado.nodo((Ñ::Nodo*)tipo);
                    return resultado;
                    break;
                
                case Ñ::CategoríaTipo::TIPO_REAL_32:
                case Ñ::CategoríaTipo::TIPO_REAL_64:
                    resultado.éxito();
                    resultado.nodo((Ñ::Nodo*)tipo);
                    return resultado;
                    break;
                
                default:
                    resultado.error("Has intentado negativizar un tipo '" + obténNombreDeTipo(tipo) + "'.");
                    resultado.posición(tipo->posición());
                    return resultado;
                    break;
                }
            }
            else if(op->operación == "@")
            {
                Ñ::Tipo* puntero = new Ñ::Tipo(tipo->posición());
                puntero->tipo = Ñ::CategoríaTipo::TIPO_PUNTERO;
                puntero->ramas.push_back(tipo);
                resultado.éxito();
                resultado.nodo(puntero);
                return resultado;
            }
            else if(op->operación == "*")
            {
                if(tipo->tipo == Ñ::CategoríaTipo::TIPO_PUNTERO)
                {
                    resultado.éxito();
                    resultado.nodo(tipo->subtipo());
                    return resultado;
                }
                else if(tipo->tipo == Ñ::CategoríaTipo::TIPO_SERIE)
                {
                    resultado.éxito();
                    resultado.nodo(tipo->subtipo());
                    return resultado;
                }
                else
                {
                    resultado.error("No sé leer el contenido en esta dirección.");
                    resultado.posición(tipo->posición());
                    return resultado;
                }
            }

            resultado.error("No reconozco la operación unaria '" + op->operación + "'.");
            resultado.posición(op->posición());
            return resultado;
        }
        else
        {
            resultado.error("El nodo Ñ::OpUnaria tenía " + std::to_string(nodo->ramas.size()) + " ramas.");
            resultado.posición(nodo->posición());
            return resultado;
        }
    }
    else if(nodo->categoría == Ñ::CategoríaNodo::NODO_LITERAL)
    {
        // Convierto a Ñ::Valor*
        Ñ::Valor* v = Ñ::creaValor((Ñ::Literal*)nodo);
        // Compruebo el tipo del valor y devuelvo el resultado
        Ñ::Resultado rTipoLiteral = _analizaLDA((Ñ::Nodo*)v, tablaSímbolos);
        if(!rTipoLiteral.error())
        {
            // Si resultado correcto, asignaré al literal el tipo adecuado más 
            ((Ñ::Literal*)nodo)->tipo = ((Ñ::Valor*)v)->obténTipo();
        }
        return rTipoLiteral;
    }
    else if(nodo->categoría == Ñ::CategoríaNodo::NODO_COMPARACIÓN)
    {
        if(nodo->ramas.size() == 1)
        {
            Ñ::Resultado r = _analizaLDA(nodo->ramas[0], tablaSímbolos);
            if(r.error())
            {
                return r;
            }
            //Ñ::Nodo* t = duplicaÁrbol(r.nodo());
            Ñ::Tipo* tipoBooleano = new Ñ::Tipo(r.nodo()->posición());
            tipoBooleano->tipo = Ñ::CategoríaTipo::TIPO_BOOLEANO;
            delete r.nodo();
            resultado.éxito();
            resultado.nodo(tipoBooleano);
            return resultado;
        }
        else if(nodo->ramas.size() > 1)
        {
            //std::cout << std::endl << "Realizando operación de comparación" << std::endl << std::endl;
            Ñ::Tipo* tipoResultado;
            Ñ::Nodo* t1;
            Ñ::Resultado r = _analizaLDA(nodo->ramas[0], tablaSímbolos);
            if(r.error())
            {
                return r;
            }
            t1 = r.nodo();
            tipoResultado = (Ñ::Tipo*)t1;
            Ñ::Tipo* tipoBooleano = new Ñ::Tipo(r.nodo()->posición());
            tipoBooleano->tipo = Ñ::CategoríaTipo::TIPO_BOOLEANO;
            
            for(int i = 1; i < nodo->ramas.size(); i++)
            {
                if(nodo->ramas[i]->categoría != Ñ::CategoríaNodo::NODO_OP_BINARIA)
                {
                    resultado.error("Comparación no ha recibido una operación válida.");
                    resultado.posición(nodo->ramas[i]->posición());
                    return resultado;
                }
                Ñ::Nodo* op = nodo->ramas[i];
                if(op->ramas.size() != 1)
                {
                    resultado.error("El árbol del 2º argumento de la operación binaria es incorrecto.");
                    resultado.posición(op->posición());
                    return resultado;
                }

                Ñ::Nodo* t2;
                Ñ::Resultado r2 = _analizaLDA(op->ramas[0], tablaSímbolos);
                if(r2.error())
                {
                    return r2;
                }

                t2 = r2.nodo();

                Ñ::Tipo* tmc = Ñ::obténTipoMínimoComún(tipoResultado, (Ñ::Tipo*)t2);
            
                if(sonÁrbolesDuplicados((Ñ::Nodo*)tmc, (Ñ::Nodo*)tipoResultado))
                {
                    // Tipos idénticos, no hace falta comprobar compatibilidad
                }
                else if(tiposAsignables(tmc, tipoResultado))
                {
                    // Son tipos distintos pero compatibles, hay que convertir
                    //std::cout << "Añadiendo conversión de '" << Ñ::obténNombreDeTipo(tipoResultado) << "' a '" << Ñ::obténNombreDeTipo(tmp) << "' para la suma/resta 1" << std::endl;
                    
                    _insertaConversión(nodo, 0, tipoResultado, tmc);
                    tipoResultado = tmc;
                }
                else
                {
                    resultado.error("Comparación 1: No puedes guardar un valor de tipo '" + Ñ::obténNombreDeTipo(tipoResultado) + "' en un destino de tipo '" + Ñ::obténNombreDeTipo(tmc) + "'.");
                    resultado.posición(tipoResultado->posición());
                    return resultado;
                }
            
                if(sonÁrbolesDuplicados(t2, (Ñ::Nodo*)tipoResultado))
                {
                    // Tipos idénticos, no hace falta comprobar compatibilidad
                    ((Ñ::OperaciónBinaria*)op)->tipo = tipoResultado;
                }
                else if(tiposAsignables(tipoResultado, (Ñ::Tipo*)t2))
                {
                    // Son tipos distintos pero compatibles, hay que convertir
                    //std::cout << "Añadiendo conversión de '" << Ñ::obténNombreDeTipo(((Ñ::Tipo*)t2)->tipo) << "' a '" << Ñ::obténNombreDeTipo(tipoResultado) << "' para la suma/resta 2" << std::endl;
                    _insertaConversión(nodo->ramas[i], 0, (Ñ::Tipo*)t2, tipoResultado);
                    ((Ñ::OperaciónBinaria*)op)->tipo = tipoResultado;
                }
                else
                {
                    resultado.error("Comparación 2: No puedes guardar un valor de tipo '" + Ñ::obténNombreDeTipo((Ñ::Tipo*)t2) + "' en un destino de tipo '" + Ñ::obténNombreDeTipo(tipoResultado) + "'.");
                    resultado.posición(t2->posición());
                    return resultado;
                }

                ((Ñ::OperaciónBinaria*)nodo)->tipo = tipoResultado;
            }

            resultado.éxito();
            resultado.nodo((Ñ::Nodo*)tipoBooleano);
            return resultado;
        }
        else
        {
            resultado.error("El nodo Ñ::Comparación tiene " + std::to_string(nodo->ramas.size()) + " ramas.");
            resultado.posición(nodo->posición());
            return resultado;
        }
    }
    else if(nodo->categoría == Ñ::CategoríaNodo::NODO_TÉRMINO)
    {
        if(nodo->ramas.size() == 1)
        {
            Ñ::Resultado r = _analizaLDA(nodo->ramas[0], tablaSímbolos);
            if(r.error())
            {
                return r;
            }
            Ñ::Nodo* t = duplicaÁrbol(r.nodo());
            delete r.nodo();
            resultado.éxito();
            resultado.nodo(t);
            return resultado;
        }
        else if(nodo->ramas.size() > 1)
        {
            Ñ::Tipo* tipoResultado;
            Ñ::Nodo* t1;
            Ñ::Resultado r = _analizaLDA(nodo->ramas[0], tablaSímbolos);
            if(r.error())
            {
                return r;
            }
            t1 = r.nodo();
            tipoResultado = (Ñ::Tipo*)t1;
            
            for(int i = 1; i < nodo->ramas.size(); i++)
            {
                if(nodo->ramas[i]->categoría != Ñ::CategoríaNodo::NODO_OP_BINARIA)
                {
                    resultado.error("Término no ha recibido una operación válida.");
                    resultado.posición(nodo->ramas[i]->posición());
                    return resultado;
                }
                Ñ::Nodo* op = nodo->ramas[i];
                if(op->ramas.size() != 1)
                {
                    resultado.error("El árbol del 2º argumento de la operación binaria es incorrecto.");
                    resultado.posición(op->posición());
                    return resultado;
                }

                Ñ::Nodo* t2;
                Ñ::Resultado r2 = _analizaLDA(op->ramas[0], tablaSímbolos);
                if(r2.error())
                {
                    return r2;
                }

                t2 = r2.nodo();

                Ñ::Tipo* tmc = Ñ::obténTipoMínimoComún(tipoResultado, (Ñ::Tipo*)t2);
            
                if(sonÁrbolesDuplicados((Ñ::Nodo*)tmc, (Ñ::Nodo*)tipoResultado))
                {
                    // Tipos idénticos, no hace falta comprobar compatibilidad
                }
                else if(tiposAsignables(tmc, tipoResultado))
                {
                    // Son tipos distintos pero compatibles, hay que convertir
                    //std::cout << "Añadiendo conversión de '" << Ñ::obténNombreDeTipo(tipoResultado) << "' a '" << Ñ::obténNombreDeTipo(tmp) << "' para la suma/resta 1" << std::endl;
                    
                    _insertaConversión(nodo, 0, tipoResultado, tmc);
                    tipoResultado = tmc;
                }
                else
                {
                    resultado.error("Suma/Resta 1: No puedes guardar un valor de tipo '" + Ñ::obténNombreDeTipo(tipoResultado) + "' en un destino de tipo '" + Ñ::obténNombreDeTipo(tmc) + "'.");
                    resultado.posición(nodo->posición());
                    return resultado;
                }
            
                if(sonÁrbolesDuplicados(t2, (Ñ::Nodo*)tipoResultado))
                {
                    // Tipos idénticos, no hace falta comprobar compatibilidad
                    ((Ñ::OperaciónBinaria*)op)->tipo = tipoResultado;
                }
                else if(tiposAsignables(tipoResultado, (Ñ::Tipo*)t2))
                {
                    // Son tipos distintos pero compatibles, hay que convertir
                    //std::cout << "Añadiendo conversión de '" << Ñ::obténNombreDeTipo(((Ñ::Tipo*)t2)->tipo) << "' a '" << Ñ::obténNombreDeTipo(tipoResultado) << "' para la suma/resta 2" << std::endl;
                   _insertaConversión(nodo->ramas[i], 0, (Ñ::Tipo*)t2, tipoResultado);
                    ((Ñ::OperaciónBinaria*)op)->tipo = tipoResultado;
                }
                else
                {
                    resultado.error("Suma/Resta 2: No puedes guardar un valor de tipo '" + Ñ::obténNombreDeTipo((Ñ::Tipo*)t2) + "' en un destino de tipo '" + Ñ::obténNombreDeTipo(tipoResultado) + "'.");
                    resultado.posición(t2->posición());
                    return resultado;
                }

                ((Ñ::OperaciónBinaria*)nodo)->tipo = tipoResultado;
            }

            resultado.éxito();
            resultado.nodo((Ñ::Nodo*)tipoResultado);
            return resultado;
        }
        else
        {
            resultado.error("El nodo Ñ::Término tiene " + std::to_string(nodo->ramas.size()) + " ramas.");
            resultado.posición(nodo->posición());
            return resultado;
        }
    }
    else if(nodo->categoría == Ñ::CategoríaNodo::NODO_FACTOR)
    {
        if(nodo->ramas.size() == 1)
        {
            Ñ::Resultado r = _analizaLDA(nodo->ramas[0], tablaSímbolos);
            if(r.error())
            {
                return r;
            }
            Ñ::Nodo* t = duplicaÁrbol(r.nodo());
            delete r.nodo();
            resultado.éxito();
            resultado.nodo(t);
            return resultado;
        }
        else if(nodo->ramas.size() > 1)
        {
            Ñ::Tipo* tipoResultado;
            Ñ::Nodo* t1;
            Ñ::Resultado r = _analizaLDA(nodo->ramas[0], tablaSímbolos);
            if(r.error())
            {
                return r;
            }
            t1 = r.nodo();
            tipoResultado = (Ñ::Tipo*)t1;
            
            for(int i = 1; i < nodo->ramas.size(); i++)
            {
                if(nodo->ramas[i]->categoría != Ñ::CategoríaNodo::NODO_OP_BINARIA)
                {
                    resultado.error("Término no ha recibido una operación válida.");
                    resultado.posición(nodo->ramas[i]->posición());
                    return resultado;
                }
                Ñ::Nodo* op = nodo->ramas[i];
                if(op->ramas.size() != 1)
                {
                    resultado.error("El árbol del 2º argumento de la operación binaria es incorrecto.");
                    resultado.posición(op->posición());
                    return resultado;
                }

                Ñ::Nodo* t2;
                Ñ::Resultado r2 = _analizaLDA(op->ramas[0], tablaSímbolos);
                if(r2.error())
                {
                    return r2;
                }

                t2 = r2.nodo();

                Ñ::Tipo* tmc = Ñ::obténTipoMínimoComún(tipoResultado, (Ñ::Tipo*)t2);

                if(sonÁrbolesDuplicados((Ñ::Nodo*)tmc, (Ñ::Nodo*)tipoResultado))
                {
                    // Tipos idénticos, no hace falta comprobar compatibilidad
                }
                else if(tiposAsignables(tmc, tipoResultado))
                {
                    // Son tipos distintos pero compatibles, hay que convertir
                    //std::cout << "Añadiendo conversión de '" << Ñ::obténNombreDeTipo(tipoResultado) << "' a '" << Ñ::obténNombreDeTipo(tmp) << "' para la multiplicación/división 1" << std::endl;
                    
                    _insertaConversión(nodo, 0, tipoResultado, tmc);
                    tipoResultado = tmc;
                }
                else
                {
                    resultado.error("Multiplicación/División/Resto 1: No puedes guardar un valor de tipo '" + Ñ::obténNombreDeTipo(tipoResultado) + "' en un destino de tipo '" + Ñ::obténNombreDeTipo(tmc) + "'.");
                    resultado.posición(tipoResultado->posición());
                    return resultado;
                }
            
                if(sonÁrbolesDuplicados(t2, (Ñ::Nodo*)tipoResultado))
                {
                    // Tipos idénticos, no hace falta comprobar compatibilidad
                    ((Ñ::OperaciónBinaria*)op)->tipo = tipoResultado;
                }
                else if(tiposAsignables(tipoResultado, (Ñ::Tipo*)t2))
                {
                    // Son tipos distintos pero compatibles, hay que convertir
                    //std::cout << "Añadiendo conversión de '" << Ñ::obténNombreDeTipo(((Ñ::Tipo*)t2)->tipo) << "' a '" << Ñ::obténNombreDeTipo(tipoResultado) << "' para la multiplicación/división 2" << std::endl;
                    
                    _insertaConversión(op, 0, (Ñ::Tipo*)t2, tipoResultado);
                    ((Ñ::OperaciónBinaria*)op)->tipo = tipoResultado;
                }
                else
                {
                    resultado.error("Multiplicación/División/Resto 2: No puedes guardar un valor de tipo '" + Ñ::obténNombreDeTipo((Ñ::Tipo*)t2) + "' en un destino de tipo '" + Ñ::obténNombreDeTipo(tipoResultado) + "'.");
                    resultado.posición(t2->posición());
                    return resultado;
                }

                ((Ñ::OperaciónBinaria*)nodo)->tipo = tipoResultado;
            }

            resultado.éxito();
            resultado.nodo((Ñ::Nodo*)tipoResultado);
            return resultado;
        }
        else
        {
            resultado.error("El nodo Ñ::Factor tiene " + std::to_string(nodo->ramas.size()) + " ramas.");
            resultado.posición(nodo->posición());
            return resultado;
        }
    }
    else if(nodo->categoría == Ñ::CategoríaNodo::NODO_ELEMENTO_SERIE)
    {
        if(nodo->ramas.size() != 2)
        {
            resultado.error("El nodo de acceso al elemento de una serie debe tener 2 hijos.");
            resultado.posición(nodo->posición());
            return resultado;
        }
        
        Ñ::Resultado rSerie = _analizaLDA(nodo->ramas[0], tablaSímbolos);
        if(rSerie.error())
        {
            return rSerie;
        }

        Ñ::Resultado rPosición = _analizaLDA(nodo->ramas[1], tablaSímbolos);
        if(rPosición.error())
        {
            return rPosición;
        }
        
        //Comprobar que el tipo leído es una serie
        Ñ::Nodo* serie = rSerie.nodo();
        if(serie == nullptr)
        {
            resultado.error("Esperaba recibir un nodo.");
            return resultado;
        }

        if(serie->categoría != Ñ::CategoríaNodo::NODO_TIPO)
        {
            resultado.error("Esperaba recibir un tipo.");
            resultado.posición(serie->posición());
            return resultado;
        }

        if(((Ñ::Tipo*)serie)->tipo != Ñ::CategoríaTipo::TIPO_SERIE)
        {
            resultado.error("Esperaba que el tipo fuera una serie.");
            resultado.posición(serie->posición());
            return resultado;
        }
        
        //Comprobar que la posición no excede el límite de la serie
        // PENDIENTE

        //Devolver el tipo del componente al que accedemos
        if(serie->ramas.size() < 1)
        {
            resultado.error("La serie no contiene subtipo.");
            resultado.posición(serie->posición());
            return resultado;
        }

        resultado.éxito();
        resultado.nodo(serie->ramas[0]);
        return resultado;
    }
    else if(nodo->categoría == Ñ::CategoríaNodo::NODO_LLAMA_FUNCIÓN)
    {
        return _analizaLlamadaFunción(nodo, tablaSímbolos);
    }

    resultado.error("El árbol de nodos es incorrecto, esperaba Lado Derecho de Asignación. Categoría del nódulo actual: " + Ñ::obténNombreDeNodo(nodo->categoría) + ".");
    resultado.posición(nodo->posición());
    return resultado;
}


Ñ::Resultado _analiza(Ñ::Nodo* nodo, Ñ::TablaSímbolos* tablaSímbolos)
{
    Ñ::Resultado resultado;

    if(nodo == nullptr)
    {
        resultado.error("El nodo es nulo.");
        return resultado;
    }

    if(nodo->categoría == Ñ::CategoríaNodo::NODO_MÓDULO)
    {
        for(Ñ::Nodo* n : nodo->ramas)
        {
            Ñ::Resultado rAnálisis;

            if(n == nullptr)
            {
                rAnálisis.error("He recibido un nodo nulo entre los hijos de NODO_MÓDULO.");
                return rAnálisis;
            }

            rAnálisis = _analiza(n, tablaSímbolos);
            
            if(rAnálisis.error())
            {
                return rAnálisis;
            }
        }
        
        resultado.éxito();
        return resultado;
    }
    else if(nodo->categoría == Ñ::CategoríaNodo::NODO_EXPRESIÓN)
    {
        for(Ñ::Nodo* n : nodo->ramas)
        {
            Ñ::Resultado rCompruebaTipos = _analiza(n, tablaSímbolos);
            
            if(rCompruebaTipos.error())
            {
                return rCompruebaTipos;
            }
        }
        
        resultado.éxito();
        return resultado;
    }
    else if(nodo->categoría == Ñ::CategoríaNodo::NODO_ASIGNA)
    {
        Ñ::Resultado rTipoLDA = _analizaLDA(nodo->ramas[1], tablaSímbolos);
        if(rTipoLDA.error())
        {
            return rTipoLDA;
        }
        Ñ::Tipo* lda = (Ñ::Tipo*)(rTipoLDA.nodo());

        if(    nodo->ramas[0]->categoría == Ñ::CategoríaNodo::NODO_DECLARA_VARIABLE
                &&  esSerie((Ñ::Tipo*)(nodo->ramas[0]->ramas[0]))
                &&  ((Ñ::Tipo*)(nodo->ramas[0]->ramas[0]))->tamaño() == 0
                //&&  sonÁrbolesDuplicados(nodo->ramas[0]->ramas[0]->ramas[0], lda->ramas[0])
                &&  tiposAsignables((Ñ::Tipo*)(nodo->ramas[0]->ramas[0]->ramas[0]), (Ñ::Tipo*)(lda->ramas[0]))
                )
        {
            //std::cout << "Defino tamaño aprovechando la definición" << std::endl;
            // nat[] mi_serie = [1, 2, 3];
            ((Ñ::Tipo*)(nodo->ramas[0]->ramas[0]))->tamaño(lda->tamaño());
        }

        Ñ::Resultado rTipoLIA = _analizaLIA(nodo->ramas[0], tablaSímbolos);
        if(rTipoLIA.error())
        {
            return rTipoLIA;
        }
        Ñ::Tipo* lia = (Ñ::Tipo*)(rTipoLIA.nodo());

        if(sonÁrbolesDuplicados((Ñ::Nodo*)lia, (Ñ::Nodo*)lda))
        {
            // Tipos idénticos, no hace falta comprobar compatibilidad
            resultado.éxito();
            return resultado;
        }
        else if(tiposAsignables(lia, lda))
        {
            // Son tipos distintos pero compatibles, hay que convertir
            //std::cout << "Añadiendo conversión de '" << Ñ::obténNombreDeTipo(lda) << "' a '" << Ñ::obténNombreDeTipo(lia) << "' para la asignación" << std::endl;
            _insertaConversión(nodo, 1, lda, lia);
            resultado.éxito();
            return resultado;
        }
        else
        {
            //std::cout << "LDA" << std::endl;
            //muestraNodos((Ñ::Nodo*)lda, tablaSímbolos);
            //std::cout << "LIA" << std::endl;
            //muestraNodos((Ñ::Nodo*)lia, tablaSímbolos);
            resultado.error("No puedes guardar un valor de tipo '" + Ñ::obténNombreDeTipo(lda) + "' en un destino de tipo '" + Ñ::obténNombreDeTipo(lia) + "'.");
            resultado.posición(nodo->posición());
            return resultado;
        }
    }
    else if(nodo->categoría == Ñ::CategoríaNodo::NODO_DECLARA_VARIABLE)
    {
        return _analizaLIA(nodo, tablaSímbolos);
    }
    else if(nodo->categoría == Ñ::CategoríaNodo::NODO_DEVUELVE)
    {
        if(nodo->ramas.size() == 0)
        {
            resultado.éxito();
            return resultado;
        }
        else if(nodo->ramas.size() == 1)
        {
            Ñ::Resultado rTipoLda = _analizaLDA(nodo->ramas[0], tablaSímbolos);
            if(rTipoLda.error())
            {
                return rTipoLda;
            }

            // Primero obtengo la firma de la función
            std::string fn = tablaSímbolos->leeFunciónPropietaria();
            Ñ::Resultado rTipoLia = tablaSímbolos->leeTipo(fn);
            if(rTipoLia.error())
            {
                return rTipoLia;
            }
            Ñ::Nodo* firma = rTipoLia.nodo();
            
            // Obtengo el tipo de retorno de la función
            Ñ::Tipo* tLia = (Ñ::Tipo*)(firma->ramas[0]);

            // Obtengo el tipo del 'devuelve X'
            Ñ::Tipo* tLda = (Ñ::Tipo*)(rTipoLda.nodo());

            // Comparo si los tipos son compatibles
            if(tLia->tipo == tLda->tipo)
            {
                // No hace falta convertir tipos
                resultado.éxito();
                return resultado;
            }
            else if(Ñ::tiposAsignables(tLia, tLda))
            {
                // Son tipos distintos pero compatibles, hay que convertir
                //std::cout << "Añadiendo conversión de '" << Ñ::obténNombreDeTipo(tLda->tipo) << "' a '" << Ñ::obténNombreDeTipo(tLia->tipo) << "' para la devolución" << std::endl;

                _insertaConversión(nodo, 0, tLda, tLia);
                resultado.éxito();
                return resultado;
            }
            else
            {
                std::string mensaje = "La función debe devolver un valor de tipo '" + Ñ::obténNombreDeTipo(tLia) + "', pero estás devolviendo un '" + Ñ::obténNombreDeTipo(tLda) + "'.";
                resultado.error(mensaje);
                return resultado;
            }
        }
        else // más de 1 rama
        {
            resultado.error("El nodo 'NODO_DEVUELVE' tiene " + std::to_string(nodo->ramas.size()) + " ramas.");
            resultado.posición(nodo->posición());
            return resultado;
        }
    }
    else if(nodo->categoría == Ñ::CategoríaNodo::NODO_PARA_BUCLE)
    {
        resultado.éxito();
        return resultado;
    }
    else if(nodo->categoría == Ñ::CategoríaNodo::NODO_SI_CONDICIONAL)
    {
        return _analizaSiCondicional(nodo, tablaSímbolos);
    }
    else if(nodo->categoría == Ñ::CategoríaNodo::NODO_BUCLE_MIENTRAS)
    {
        return _analizaBucleMientras(nodo, tablaSímbolos);
    }
    else if(nodo->categoría == Ñ::CategoríaNodo::NODO_LLAMA_FUNCIÓN)
    {
        return _analizaLlamadaFunción(nodo, tablaSímbolos);
    }
    else if(nodo->categoría == Ñ::CategoríaNodo::NODO_DEFINE_FUNCIÓN)
    {
        return _analizaDefiniciónFunción(nodo, tablaSímbolos);
    }
    else if(nodo->categoría == Ñ::CategoríaNodo::NODO_DECLARA_FUNCIÓN)
    {
        return _analizaDeclaraciónFunción(nodo, tablaSímbolos);
    }
    else if(nodo->categoría == Ñ::CategoríaNodo::NODO_BLOQUE)
    {
        for(Ñ::Nodo* n : nodo->ramas)
        {
            if(n == nullptr)
            {
                resultado.error("He recibido un nodo nulo.");
                return resultado;
            }

            if(n->categoría == Ñ::CategoríaNodo::NODO_BLOQUE)
            {
                Ñ::TablaSímbolos* subTabla = new Ñ::TablaSímbolos(tablaSímbolos);
                resultado = _analiza(n, subTabla);
                if(resultado.error())
                {
                    delete subTabla;
                    return resultado;
                }
            }
            else
            {
                resultado = _analiza(n, tablaSímbolos);
                if(resultado.error())
                {
                    return resultado;
                }
            }
        }

        resultado.éxito();
        return resultado;
    }
    else
    {
        resultado.error("El nodo tiene una categoría inesperada: " + Ñ::obténNombreDeNodo(nodo->categoría) + ".");
        resultado.posición(nodo->posición());
        return resultado;
    }
}

Ñ::Resultado Ñ::analizaSemántica(Ñ::Nodo* nodo, Ñ::TablaSímbolos* tablaSímbolos)
{
    Ñ::Resultado resultado;

    if(nodo == nullptr)
    {
        resultado.error("El nodo raíz es nulo.");
        return resultado;
    }

    Ñ::Resultado rAnálisisSemántico = _analiza(nodo, tablaSímbolos);
    if(rAnálisisSemántico.error())
    {
        resultado.error(rAnálisisSemántico.mensaje());
        resultado.posición(rAnálisisSemántico.posición());
        return resultado;
    }

    resultado.éxito();
    return resultado;
}