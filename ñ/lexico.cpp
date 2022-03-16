/*
SPDX-License-Identifier: MPL-2.0-no-copyleft-exception

This Source Code Form is subject to the terms of the Mozilla Public License, v.
2.0. If a copy of the MPL was not distributed with this file, You can obtain one
at http://mozilla.org/MPL/2.0/.

This Source Code Form is "Incompatible With Secondary Licenses", as defined by
the Mozilla Public License, v. 2.0.

Copyright © 2021 Eduardo Garre Muñoz
*/

#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

#include "entorno.hpp"
#include "lexema.hpp"
#include "lexico.hpp"
#include "posicion.hpp"
#include "salida.hpp"

namespace Ñ
{

// Compilación condicional: si estamos en pruebas ya hemos declarado las funciones en la cabecera
#ifndef EVALUANDO_PRUEBAS
    bool esdígito(std::string c);
    bool espuntuación(std::string c);
    bool esnuevalínea(std::string c);
    bool esespacio(std::string c);
    bool esalfa(std::string c);
    bool esalfanum(std::string c);
#endif
    void Léxico::incrementaCursor(std::string txt)
    {
        uint64_t paso = std::mblen(txt.c_str() + posición->cursor(), std::min((uint64_t)MB_CUR_MAX, (uint64_t)txt.size() - posición->cursor()));

        //std::cout << "incrementaCursor(" << txt << ") - paso:" << paso << "  - posición->cursor():" << posición->cursor() << "  - txt.size():" << txt.size() << std::endl;

        if(txt.size() > posición->cursor() && paso <= txt.size() - posición->cursor())
        {
            while(paso--)
            {
                posición->incCursor();
            }
        }
    }

    std::string Léxico::siguienteCarácter(std::string txt)
    {
        uint64_t paso = std::mblen(txt.c_str() + posición->cursor(), std::min((uint64_t)MB_CUR_MAX, (uint64_t)txt.size() - posición->cursor()));
        std::string c = "";

        //std::cout << "siguienteCarácter(" << txt << ") - paso:" << paso << "  - posición->cursor():" << posición->cursor() << "  - txt.size():" << txt.size() << std::endl;
        

        if(txt.size() > posición->cursor() && paso <= txt.size() - posición->cursor())
        {
            c = txt.substr(posición->cursor(), paso);
        }

        if(esnuevalínea(c))
        {
            posición->incLínea();
            posición->empiezaColumna();
        }

        return c;
    }

    bool Léxico::esfindelarchivo(Ñ::Posición* p)
    {
        if(longitudarchivo > p->cursor() + 1)
        {
            return false;
        }
        else
        {
            return true;
        }
    }

    bool Léxico::comentario(std::string txt)
    {
        try {
            //std::cout << "número(" << txt << ")" << std::endl;
            
            if(_comentario1L(txt))
            {
                return true;
            }
            else if(_comentarioXL(txt))
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        catch(const std::runtime_error& re)
        {
            // speciffic handling for runtime_error
            std::cerr << u8"Error en tiempo de ejecución: " << re.what() << std::endl;
            return false;
        }
        catch(const std::exception& ex)
        {
            // speciffic handling for all exceptions extending std::exception, except
            // std::runtime_error which is handled explicitly
            std::cerr << u8"Error: " << ex.what() << std::endl;
            return false;
        }
        catch(...)
        {
            // catch any other errors (that we have no information about)
            std::cerr << u8"Error desconocido. Posible corrupción de memoria." << std::endl;
            return false;
        }
    }

    bool Léxico::_comentario1L(std::string txt)
    {
        try {
            bool resultado = false;
            
            Posición p = *posición;

            std::string carácter = siguienteCarácter(txt);

            if(carácter == u8"/")
            {
                incrementaCursor(txt);
                carácter = siguienteCarácter(txt);

                if(carácter == u8"/")
                {
                    resultado = true;

                    do {
                        incrementaCursor(txt);
                        carácter = siguienteCarácter(txt);
                    } while(!esnuevalínea(carácter) && !esfindelarchivo(posición));
                    
                    if(esnuevalínea(carácter))
                    {
                        incrementaCursor(txt);
                    }
                    
                    return resultado;
                }
            }
            
            *posición = p;
            
            return resultado;
        }
        catch(const std::runtime_error& re)
        {
            // speciffic handling for runtime_error
            std::cerr << u8"Error en tiempo de ejecución: " << re.what() << std::endl;
            return false;
        }
        catch(const std::exception& ex)
        {
            // speciffic handling for all exceptions extending std::exception, except
            // std::runtime_error which is handled explicitly
            std::cerr << u8"Error: " << ex.what() << std::endl;
            return false;
        }
        catch(...)
        {
            // catch any other errors (that we have no information about)
            std::cerr << u8"Error desconocido. Posible corrupción de memoria." << std::endl;
            return false;
        }
    }

    bool Léxico::_comentarioXL(std::string txt)
    {
        try {
            bool resultado = false;
            Posición p = *posición;

            std::string carácter = siguienteCarácter(txt);

            if(carácter == u8"/")
            {
                incrementaCursor(txt);
                carácter = siguienteCarácter(txt);

                if(carácter == u8"*")
                {
                    resultado = true;

                    while(posición->cursor() < txt.length()-1)
                    {
                        incrementaCursor(txt);
                        carácter = siguienteCarácter(txt);

                        if(carácter == u8"*")
                        {
                            incrementaCursor(txt);
                            carácter = siguienteCarácter(txt);
                            
                            if(carácter == u8"/")
                            {
                                incrementaCursor(txt);
                                return true;
                            }
                        }
                    }
                }
            }
            
            *posición = p;
            return resultado;
        }
        catch(const std::runtime_error& re)
        {
            // speciffic handling for runtime_error
            std::cerr << u8"Error en tiempo de ejecución: " << re.what() << std::endl;
            return false;
        }
        catch(const std::exception& ex)
        {
            // speciffic handling for all exceptions extending std::exception, except
            // std::runtime_error which is handled explicitly
            std::cerr << u8"Error: " << ex.what() << std::endl;
            return false;
        }
        catch(...)
        {
            // catch any other errors (that we have no information about)
            std::cerr << u8"Error desconocido. Posible corrupción de memoria." << std::endl;
            return false;
        }
    }

    bool Léxico::nuevaLínea(std::string txt)
    {
        try {
            //std::cout << "nuevaLínea(" << txt << ")" << std::endl;

            bool resultado = false;
            Posición p = *posición;

            std::string carácter = "";

            carácter = siguienteCarácter(txt);

            if(esnuevalínea(carácter))
            {
                resultado = true;
                incrementaCursor(txt);
                return resultado;
            }
            else
            {
                *posición = p;
                return false;
            }
        }
        catch(const std::runtime_error& re)
        {
            // speciffic handling for runtime_error
            std::cerr << u8"Error en tiempo de ejecución: " << re.what() << std::endl;
            return false;
        }
        catch(const std::exception& ex)
        {
            // speciffic handling for all exceptions extending std::exception, except
            // std::runtime_error which is handled explicitly
            std::cerr << u8"Error: " << ex.what() << std::endl;
            return false;
        }
        catch(...)
        {
            // catch any other errors (that we have no information about)
            std::cerr << u8"Error desconocido. Posible corrupción de memoria." << std::endl;
            return false;
        }
    }

    bool Léxico::espacio(std::string txt)
    {
        try {
            //std::cout << "espacio(" << txt << ")" << std::endl;

            bool resultado = false;

            std::string carácter = siguienteCarácter(txt);

            while(Ñ::esespacio(carácter))
            {
                resultado = true;
                
                if(posición->cursor() == (txt.length() - 1))
                {
                    return false;
                }

                if(esnuevalínea(carácter))
                {
                    incrementaCursor(txt);
                    return resultado;
                }
                else
                {
                    incrementaCursor(txt);
                }
                
                carácter = siguienteCarácter(txt);
            }

            return resultado;
        }
        catch(const std::runtime_error& re)
        {
            // speciffic handling for runtime_error
            std::cerr << u8"Error en tiempo de ejecución: " << re.what() << std::endl;
            return false;
        }
        catch(const std::exception& ex)
        {
            // speciffic handling for all exceptions extending std::exception, except
            // std::runtime_error which is handled explicitly
            std::cerr << u8"Error: " << ex.what() << std::endl;
            return false;
        }
        catch(...)
        {
            // catch any other errors (that we have no information about)
            std::cerr << u8"Error desconocido. Posible corrupción de memoria." << std::endl;
            return false;
        }
    }

    bool Léxico::notación(std::string txt)
    {
        try {
            //std::cout << "notación(" << txt << ")" << std::endl;

            std::string carácter = siguienteCarácter(txt);

            if(Ñ::espuntuación(carácter))
            {
                posición->longitud(carácter.size());
                Ñ::Lexema* l = new Ñ::Lexema(posición);
                l->categoría = Ñ::CategoríaLexema::LEXEMA_NOTACIÓN;
                l->contenido = carácter;

                //std::cout << "Creo nuevo longitud" << std::endl;
                lexemas.push_back(l);

                incrementaCursor(txt);
                return true;
            }
            else
            {
                return false;
            }
        }
        catch(const std::runtime_error& re)
        {
            // speciffic handling for runtime_error
            std::cerr << u8"Error en tiempo de ejecución: " << re.what() << std::endl;
            return false;
        }
        catch(const std::exception& ex)
        {
            // speciffic handling for all exceptions extending std::exception, except
            // std::runtime_error which is handled explicitly
            std::cerr << u8"Error: " << ex.what() << std::endl;
            return false;
        }
        catch(...)
        {
            // catch any other errors (that we have no information about)
            std::cerr << u8"Error desconocido. Posible corrupción de memoria." << std::endl;
            return false;
        }
    }

    bool Léxico::_nombre(std::string txt)
    {
        try {
            //std::cout << "_nombre(" << txt << ")" << std::endl;
            
            bool resultado = false;

            Posición p = *posición;

            std::string carácter = siguienteCarácter(txt);

            while(Ñ::esalfa(carácter))
            {
                //std::cout << "_nombre:: isalpha(" << carácter << ")" << std::endl;
                
                resultado = true;
                do {
                    if(posición->cursor() == (txt.length()+1))
                    {
                        return true;
                    }
                    incrementaCursor(txt);
                    carácter = siguienteCarácter(txt);
                    //std::cout << "_nombre:: isalpha(" << carácter << ")" << std::endl;
                } while(Ñ::esalfanum(carácter));
            }

            //std::cout << "_nombre:: [" << resultado << "]" << std::endl;
                
            return resultado;
        }
        catch(const std::runtime_error& re)
        {
            // speciffic handling for runtime_error
            std::cerr << u8"Error en tiempo de ejecución: " << re.what() << std::endl;
            return false;
        }
        catch(const std::exception& ex)
        {
            // speciffic handling for all exceptions extending std::exception, except
            // std::runtime_error which is handled explicitly
            std::cerr << u8"Error: " << ex.what() << std::endl;
            return false;
        }
        catch(...)
        {
            // catch any other errors (that we have no information about)
            std::cerr << u8"Error desconocido. Posible corrupción de memoria." << std::endl;
            return false;
        }
    }

    bool Léxico::reservada(std::string txt)
    {
        try {
            //std::cout << "reservada(" << txt << ")" << std::endl;
            
            bool resultado = false;

            Posición p = *posición;

            if(_nombre(txt))
            {
                std::string s = txt.substr(p.cursor(), posición->cursor() - p.cursor());

                if( (s == "cierto")
                 || (s == "falso")
                 || (s == "nulo")
                 || (s == "vuelve")
                 || (s == "devuelve")
                 || (s == "para")
                 || (s == "var")
                 || (s == "externo")
                 || (s == "público")
                 || (s == "privado")
                 || (s == "si")
                 || (s == "sino")
                 || (s == "mientras")
                 || (s == "no")
                 || (s == "bool")
                 || (s == "ent")
                 || (s == "ent8")
                 || (s == "ent16")
                 || (s == "ent32")
                 || (s == "ent64")
                 || (s == "nat")
                 || (s == "nat8")
                 || (s == "nat16")
                 || (s == "nat32")
                 || (s == "nat64")
                 || (s == "real")
                 || (s == "rea16")
                 || (s == "rea32")
                 || (s == "rea64")
                 || (s == "txt")
                )
                {
                    resultado = true;
                    
                    p.longitud(s.size());
                    Ñ::Lexema* l = new Ñ::Lexema(&p);
                    l->categoría = Ñ::CategoríaLexema::LEXEMA_RESERVADO;
                    l->contenido = s;

                    //std::cout << "Creo nuevo longitud" << std::endl;
                    lexemas.push_back(l);
                }
                else
                {
                    *posición = p;
                }
            }

            return resultado;
        }
        catch(const std::runtime_error& re)
        {
            // speciffic handling for runtime_error
            std::cerr << u8"Error en tiempo de ejecución: " << re.what() << std::endl;
            return false;
        }
        catch(const std::exception& ex)
        {
            // speciffic handling for all exceptions extending std::exception, except
            // std::runtime_error which is handled explicitly
            std::cerr << u8"Error: " << ex.what() << std::endl;
            return false;
        }
        catch(...)
        {
            // catch any other errors (that we have no information about)
            std::cerr << u8"Error desconocido. Posible corrupción de memoria." << std::endl;
            return false;
        }
    }

    bool Léxico::_notacióncientífica(std::string txt)
    {
        try {
            //std::cout << "notacióncientífica(" << txt << ")" << std::endl;
            
            bool resultado = false;

            Posición p = *posición;

            std::string carácter = siguienteCarácter(txt);

            if(carácter == "-")
            {
                incrementaCursor(txt);
                carácter = siguienteCarácter(txt);
            }
                
            while(Ñ::esdígito(carácter) && (posición->cursor() < (txt.length()-1)))
            {
                resultado = true;
                incrementaCursor(txt);
                carácter = siguienteCarácter(txt);
            }

            if(carácter != ".")
            {
                *posición = p;
                return false;
            }
            
            if(posición->cursor() == (txt.length()-1))
            {
                *posición = p;
                return false;
            }

            incrementaCursor(txt);
            carácter = siguienteCarácter(txt);

            do {
                resultado = true;
                incrementaCursor(txt);
                carácter = siguienteCarácter(txt);
            } while(Ñ::esdígito(carácter) && (posición->cursor() < (txt.length()-1)));

            std::string e = "e";
            std::string E = "E";
            if((carácter != e) && (carácter != E))
            {
                *posición = p;
                return false;
            }
            
            if(posición->cursor() == (txt.length()-1))
            {
                *posición = p;
                return false;
            }

            incrementaCursor(txt);
            carácter = siguienteCarácter(txt);
            
            if(posición->cursor() < (txt.length() - 1) && (carácter == "-") || (carácter == "+") )
            {
                incrementaCursor(txt);
                carácter = siguienteCarácter(txt);
            }

            while(Ñ::esdígito(carácter) && (posición->cursor() < (txt.length()-1)))
            {
                resultado = true;
                incrementaCursor(txt);
                carácter = siguienteCarácter(txt);
            }

            if(resultado)
            {
                std::string s = txt.substr(p.cursor(), posición->cursor() - p.cursor());

                //double n = to!double(s);

                p.longitud(s.size());
                Ñ::Lexema* l = new Ñ::Lexema(&p);
                l->categoría = Ñ::CategoríaLexema::LEXEMA_NÚMERO_REAL;
                l->contenido = s;

                //std::cout << "Creo nuevo longitud" << std::endl;
                lexemas.push_back(l);
            }

            return resultado;
        }
        catch(const std::runtime_error& re)
        {
            // speciffic handling for runtime_error
            std::cerr << u8"Error en tiempo de ejecución: " << re.what() << std::endl;
            return false;
        }
        catch(const std::exception& ex)
        {
            // speciffic handling for all exceptions extending std::exception, except
            // std::runtime_error which is handled explicitly
            std::cerr << u8"Error: " << ex.what() << std::endl;
            return false;
        }
        catch(...)
        {
            // catch any other errors (that we have no information about)
            std::cerr << u8"Error desconocido. Posible corrupción de memoria." << std::endl;
            return false;
        }
    }

    bool Léxico::_númerodecimales(std::string txt)
    {
        try {
            //std::cout << "_númerodecimales(" << txt << ")" << std::endl;
            
            bool resultado = false;

            Posición p = *posición;

            std::string carácter = siguienteCarácter(txt);

            if(carácter == "-")
            {
                //std::cout << ":: Negativo" << std::endl;
                incrementaCursor(txt);
                carácter = siguienteCarácter(txt);
            }
                
            while(Ñ::esdígito(carácter))
            {
                //std::cout << ":: añado dígito entero" << std::endl;
                resultado = true;
                if(posición->cursor() == (txt.length()-1))
                {
                    //std::cout << ":: Salida -> hemos llegado al final del código" << std::endl;
                    *posición = p;
                    return false;
                }
                incrementaCursor(txt);
                carácter = siguienteCarácter(txt);
            }

            if(carácter != ".")
            {
                //std::cout << ":: Salida -> falta el punto decimal" << std::endl;
                *posición = p;
                return false;
            }
            
            if(posición->cursor() == (txt.length()-1))
            {
                //std::cout << ":: Salida -> hemos llegado al final del código" << std::endl;
                *posición = p;
                return false;
            }
            
            incrementaCursor(txt);
            carácter = siguienteCarácter(txt);
                
            if(!Ñ::esdígito(carácter))
            {
                //std::cout << ":: Salida -> no es un dígito" << std::endl;
                *posición = p;
                return false;
            }

            do {
                //std::cout << ":: añado dígito decimal" << std::endl;
                resultado = true;
                if(posición->cursor() == (txt.length()-1))
                {
                    //std::cout << ":: Salida -> hemos llegado al final del código" << std::endl;
                    *posición = p;
                    return false;
                }
                incrementaCursor(txt);
                carácter = siguienteCarácter(txt);
            } while(Ñ::esdígito(carácter));

            if(resultado)
            {
                //std::cout << ":: resultado" << std::endl;
                std::string s = txt.substr(p.cursor(), posición->cursor() - p.cursor());

                //double n = to!double(s);

                p.longitud(s.size());
                Ñ::Lexema* l = new Ñ::Lexema(&p);
                l->categoría = Ñ::CategoríaLexema::LEXEMA_NÚMERO_REAL;
                l->contenido = s;
                
                //std::cout << "Creo nuevo longitud" << std::endl;
                lexemas.push_back(l);
            }

            return resultado;
        }
        catch(const std::runtime_error& re)
        {
            // speciffic handling for runtime_error
            std::cerr << u8"Error en tiempo de ejecución: " << re.what() << std::endl;
            return false;
        }
        catch(const std::exception& ex)
        {
            // speciffic handling for all exceptions extending std::exception, except
            // std::runtime_error which is handled explicitly
            std::cerr << u8"Error: " << ex.what() << std::endl;
            return false;
        }
        catch(...)
        {
            // catch any other errors (that we have no information about)
            std::cerr << u8"Error desconocido. Posible corrupción de memoria." << std::endl;
            return false;
        }
    }

    bool Léxico::_número(std::string txt)
    {
        try {
            //std::cout << "_número(" << txt << ")" << std::endl;
            
            bool resultado = false;

            Posición p = *posición;

            std::string carácter = siguienteCarácter(txt);

            if(carácter == "-")
            {
                incrementaCursor(txt);
                carácter = siguienteCarácter(txt);
            }

            if(Ñ::esdígito(carácter))
            {
                resultado = true;
                do {
                    if(posición->cursor() == (txt.length()+1))
                    {
                        return true;
                    }
                    incrementaCursor(txt);
                    carácter = siguienteCarácter(txt);
                } while(Ñ::esdígito(carácter));
            }

            if(resultado)
            {
                std::string s = txt.substr(p.cursor(), posición->cursor() - p.cursor());

                //int n = to!int(s);

                p.longitud(s.size());
                Ñ::Lexema* l = new Ñ::Lexema(&p);
                l->categoría = Ñ::CategoríaLexema::LEXEMA_NÚMERO;
                l->contenido = s;
                
                //std::cout << "Creo nuevo longitud" << std::endl;
                lexemas.push_back(l);
            }

            return resultado;
        }
        catch(const std::runtime_error& re)
        {
            // speciffic handling for runtime_error
            std::cerr << u8"Error en tiempo de ejecución: " << re.what() << std::endl;
            return false;
        }
        catch(const std::exception& ex)
        {
            // speciffic handling for all exceptions extending std::exception, except
            // std::runtime_error which is handled explicitly
            std::cerr << u8"Error: " << ex.what() << std::endl;
            return false;
        }
        catch(...)
        {
            // catch any other errors (that we have no information about)
            std::cerr << u8"Error desconocido. Posible corrupción de memoria." << std::endl;
            return false;
        }
    }

    bool Léxico::número(std::string txt)
    {
        try {
            //std::cout << "número(" << txt << ")" << std::endl;
            
            if(_notacióncientífica(txt))
            {
                return true;
            }
            else if(_númerodecimales(txt))
            {
                return true;
            }
            else if(_número(txt))
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        catch(const std::runtime_error& re)
        {
            // speciffic handling for runtime_error
            std::cerr << u8"Error en tiempo de ejecución: " << re.what() << std::endl;
            return false;
        }
        catch(const std::exception& ex)
        {
            // speciffic handling for all exceptions extending std::exception, except
            // std::runtime_error which is handled explicitly
            std::cerr << u8"Error: " << ex.what() << std::endl;
            return false;
        }
        catch(...)
        {
            // catch any other errors (that we have no information about)
            std::cerr << u8"Error desconocido. Posible corrupción de memoria." << std::endl;
            return false;
        }
    }

    bool Léxico::texto(std::string txt)
    {
        try {
            //std::cout << "texto(" << txt << ")" << std::endl;

            std::string carácter = siguienteCarácter(txt);
            
            if(carácter == "\"")
            {
                incrementaCursor(txt);
                carácter = siguienteCarácter(txt);
                Posición p = *posición;

                std::string texto;

                while((carácter != "\"") && (posición->cursor() < txt.length()-1))
                {
                    if(carácter == "\\")
                    {
                        incrementaCursor(txt);
                        carácter = siguienteCarácter(txt);
                        if(carácter == "n")
                        {
                            texto.append("\n");
                        }
                        else if(carácter == "r")
                        {
                            texto.append("\r");
                        }
                        else if(carácter == "t")
                        {
                            texto.append("\t");
                        }
                        else if(carácter == "\'")
                        {
                            texto.append("\'");
                        }
                        else if(carácter == "\"")
                        {
                            texto.append("\"");
                        }
                        else if(carácter == "\\")
                        {
                            texto.append("\\");
                        }
                        else if(carácter == "0")
                        {
                            texto.append(std::string("\0", 1));
                        }
                    }
                    else
                    {
                        texto.append(carácter);
                    }
                    
                    incrementaCursor(txt);
                    carácter = siguienteCarácter(txt);
                }

                p.longitud(texto.size());
                Ñ::Lexema* l = new Ñ::Lexema(&p);

                l->categoría = Ñ::CategoríaLexema::LEXEMA_TEXTO;
                l->contenido = texto;

                //if(carácter != "\"")
                //{
                //    *posición = p;
                //    Ñ::errorConsola(u8"Error, esperaba un cierre de comilla doble [\"]");
                //}

                incrementaCursor(txt);

                //std::cout << "Creo nuevo longitud" << std::endl;
                lexemas.push_back(l);

                return true;
            }
            else
            {
                return false;
            }
        }
        catch(const std::runtime_error& re)
        {
            // speciffic handling for runtime_error
            std::string error = u8"Error en tiempo de ejecución: ";
            error += re.what();
            Ñ::errorConsola(error);
            return false;
        }
        catch(const std::exception& ex)
        {
            // speciffic handling for all exceptions extending std::exception, except
            // std::runtime_error which is handled explicitly
            std::string error = u8"Error: ";
            error += ex.what();
            Ñ::errorConsola(error);
            return false;
        }
        catch(...)
        {
            // catch any other errors (that we have no information about)
            Ñ::errorConsola(u8"Error desconocido. Posible corrupción de memoria.");
            return false;
        }
    }

    bool Léxico::identificador(std::string txt)
    {
        try {
            //std::cout << "identificador(" << txt << ")" << std::endl;
            
            Ñ::Posición* p = new Ñ::Posición;
            *p = *posición;

            //std::cout << "c: " << c << std::endl;
            //std::cout << "cursor: " << cursor << std::endl;

            bool resultado = _nombre(txt);

            //std::cout << "c: " << c << std::endl;
            //std::cout << "cursor: " << cursor << std::endl;
            
            if(resultado)
            {
                std::string texto = txt.substr(p->cursor(), posición->cursor() - p->cursor());

                //std::cout << "identificador->contenido" << texto << std::endl;

                p->longitud(texto.size());
                Ñ::Lexema* l = new Ñ::Lexema(p);

                l->categoría = Ñ::CategoríaLexema::LEXEMA_IDENTIFICADOR;
                l->contenido = texto;


                //std::cout << "Creo nuevo longitud" << std::endl;
                lexemas.push_back(l);
                //std::cout << "longitud creado" << std::endl;
            }

            delete p;
            return resultado;
        }
        catch(const std::runtime_error& re)
        {
            // speciffic handling for runtime_error
            std::string error = u8"Error en tiempo de ejecución: ";
            error += re.what();
            Ñ::errorConsola(error);
            return false;
        }
        catch(const std::exception& ex)
        {
            // speciffic handling for all exceptions extending std::exception, except
            // std::runtime_error which is handled explicitly
            std::string error = u8"Error: ";
            error += ex.what();
            Ñ::errorConsola(error);
            return false;
        }
        catch(...)
        {
            // catch any other errors (that we have no information about)
            Ñ::errorConsola(u8"Error desconocido. Posible corrupción de memoria.");
            return false;
        }
    }

    std::vector<Ñ::Lexema*> Léxico::analiza(std::string código, Ñ::EntornoConstrucción* entorno)
    {
        posición = new Ñ::Posición;
        posición->archivo(entorno->archivoActual);

        std::vector<Ñ::Lexema*> vacía;
        if(!lexemas.empty())
        {
            lexemas.clear();
        }

        try {
            //std::cout << "_analizaLéxico(" << código << ")" << std::endl;

            std::string cmd = código + " ";
            longitudarchivo = cmd.size();

            while(posición->cursor() <= cmd.length())
            {
                //std::cout << "cursor: " << cursor << std::endl;
                Posición p = *posición;
                if(comentario(cmd))
                {
                    continue;
                }
                *posición = p;
                
                if(nuevaLínea(cmd))
                {
                    continue;
                }
                *posición = p;
                
                if(espacio(cmd))
                {
                    continue;
                }
                *posición = p;

                if(texto(cmd))
                {
                    continue;
                }
                *posición = p;

                if(notación(cmd))
                {
                    continue;
                }
                *posición = p;

                if(reservada(cmd))
                {
                    continue;
                }
                *posición = p;

                if(número(cmd))
                {
                    continue;
                }
                *posición = p;

                if(identificador(cmd))
                {
                    continue;
                }
                *posición = p;

                break;
            }
        }
        catch(const std::runtime_error& re)
        {
            // speciffic handling for runtime_error
            std::string error = u8"Error en tiempo de ejecución: ";
            error += re.what();
            Ñ::errorConsola(error);
            return vacía;
        }
        catch(const std::exception& ex)
        {
            // speciffic handling for all exceptions extending std::exception, except
            // std::runtime_error which is handled explicitly
            std::string error = u8"Error: ";
            error += ex.what();
            Ñ::errorConsola(error);
            return vacía;
        }
        catch(...)
        {
            // catch any other errors (that we have no information about)
            Ñ::errorConsola(u8"Error desconocido. Posible corrupción de memoria.");
            return vacía;
        }

        posición->longitud(0);
        Ñ::Lexema* fin = new Ñ::Lexema(posición);
        fin->categoría = Ñ::CategoríaLexema::LEXEMA_FIN;
        fin->contenido = "";
        lexemas.push_back(fin);
        return lexemas;
    }

    bool esdígito(std::string c)
    {
        //std::cout << "esdígito(" << c << ")" << std::endl;
        
        bool resultado = false;

        if( c == u8"\u0030" || // 0
            c == u8"\u0031" || // 1
            c == u8"\u0032" || // 2
            c == u8"\u0033" || // 3
            c == u8"\u0034" || // 4
            c == u8"\u0035" || // 5
            c == u8"\u0036" || // 6
            c == u8"\u0037" || // 7
            c == u8"\u0038" || // 8
            c == u8"\u0039"    // 9
        )
        {
            resultado = true;
        }


        return resultado;
    }

    bool espuntuación(std::string c)
    {
        //std::cout << "espuntuación(" << c << ")" << std::endl;
        
        bool resultado = false;

        if( c == u8"." ||
            c == u8"," ||
            c == u8":" ||
            c == u8";" ||
            c == u8"-" ||
            c == u8"+" ||
            c == u8"/" ||
            c == u8"*" ||
            c == u8"'" ||
            c == u8"\"" ||
            c == u8"|" ||
            c == u8"@" ||
            c == u8"\u20AC" ||
            c == u8"€" ||
            c == u8"$" ||
            c == u8"%" ||
            c == u8"&" ||
            c == u8"(" ||
            c == u8")" ||
            c == u8"=" ||
            c == u8"¿" ||
            c == u8"?" ||
            c == u8"¡" ||
            c == u8"!" ||
            c == u8"[" ||
            c == u8"]" ||
            c == u8"{" ||
            c == u8"}" ||
            c == u8"^" ||
            c == u8"<" ||
            c == u8">" ||
            c == u8"\\"||
            c == "." ||
            c == "," ||
            c == ":" ||
            c == ";" ||
            c == "-" ||
            c == "+" ||
            c == "/" ||
            c == "*" ||
            c == "'" ||
            c == "\"" ||
            c == "|" ||
            c == "@" ||
            c == "\u20AC" ||
            c == "€" ||
            c == "$" ||
            c == "%" ||
            c == "&" ||
            c == "(" ||
            c == ")" ||
            c == "=" ||
            c == "¿" ||
            c == "?" ||
            c == "¡" ||
            c == "!" ||
            c == "[" ||
            c == "]" ||
            c == "{" ||
            c == "}" ||
            c == "^" ||
            c == "<" ||
            c == ">" ||
            c == "\\"
        )
        {
            resultado = true;
        }


        return resultado;
    }

    bool esnuevalínea(std::string c)
    {
        //std::cout << "esnuevalínea(" << c << ")" << std::endl;
        
        bool resultado = false;

        if( c == u8"\u2028" || // Line Separator
            c == u8"\u2029" || // Paragraph Separator

            c == u8"\u000D" || // Carriage return
            c == u8"\u000A" || // Line feed
            c == u8"\u000D\u000A" || // Carriage return + Line feed
            c == u8"\u0085" // Next line
        )
        {
            resultado = true;
        }


        return resultado;
    }

    bool esespacio(std::string c)
    {
        //std::cout << "esespacio(" << c << ")" << std::endl;
        
        bool resultado = false;

        if( 
            // Categoría UNICODE - Space Separator
            c == u8"\u0020" || // Space (SP)
            c == u8"\u00A0" || // No-Break Space (NBSP)
            c == u8"\u1680" || // Ogham Space Mark
            c == u8"\u2000" || // En Quad
            c == u8"\u2001" || // Em Quad
            c == u8"\u2002" || // En Space
            c == u8"\u2003" || // Em Space
            c == u8"\u2004" || // Three-Per-Em Space
            c == u8"\u2005" || // Four-Per-Em Space
            c == u8"\u2006" || // Six-Per-Em Space
            c == u8"\u2007" || // Figure Space
            c == u8"\u2008" || // Punctuation Space
            c == u8"\u2009" || // Thin Space
            c == u8"\u200A" || // Hair Space
            c == u8"\u202F" || // Narrow No-Break Space (NNBSP)
            c == u8"\u205F" || // Medium Mathematical Space (MMSP)
            c == u8"\u3000" || // Ideographic Space
            // Categoría UNICODE - Line Separator
            c == u8"\u2028" || // Line Separator
            // Categoría UNICODE - Paragraph Separator
            c == u8"\u2029" || // Paragraph Separator

            c == u8"\u0009" || // Horizontal tab
            c == u8"\u000B" || // Vertical tab
            c == u8"\u000C" || // Form feed

            c == u8"\u000D" || // Carriage return
            c == u8"\u000A" || // Line feed
            c == u8"\u000D\u000A" || // Carriage return + Line feed
            c == u8"\u0085" || // Next line
            
            c == "\t" // Tabulador
        )
        {
            resultado = true;
        }


        return resultado;
    }

    bool esalfa(std::string c)
    {
        //std::cout << "esalfa(" << c << ")" << std::endl;
        
        if(!esdígito(c) && !esespacio(c) && !espuntuación(c) && c.size() != 0)
        {
            return true;
        }
        else if(c == u8"_")
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    bool esalfanum(std::string c)
    {
        //std::cout << "esalfanum(" << c << ")" << std::endl;
        
        if(!esespacio(c) && !espuntuación(c) && c.size() != 0)
        {
            return true;
        }
        else if(c == u8"_")
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}