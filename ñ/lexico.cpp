#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

#include "lexema.hpp"
#include "lexico.hpp"
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
        int paso = std::mblen(txt.c_str() + cursor, std::min((int)MB_CUR_MAX, (int)txt.size() - cursor));

        //std::cout << "incrementaCursor(" << txt << ") - paso:" << paso << "  - cursor:" << cursor << "  - txt.size():" << txt.size() << std::endl;

        if(txt.size() > cursor && paso <= txt.size() - cursor)
        {
            cursor += paso;
        }
    }

    std::string Léxico::siguienteCarácter(std::string txt)
    {
        int paso = std::mblen(txt.c_str() + cursor, std::min((int)MB_CUR_MAX, (int)txt.size() - cursor));
        std::string c = "";

        //std::cout << "siguienteCarácter(" << txt << ") - paso:" << paso << "  - cursor:" << cursor << "  - txt.size():" << txt.size() << std::endl;
        

        if(txt.size() > cursor && paso <= txt.size() - cursor)
        {
            c = txt.substr(cursor, paso);
        }

        return c;
    }

    bool Léxico::nuevaLínea(std::string txt)
    {
        try {
            //std::cout << "nuevaLínea(" << txt << ")" << std::endl;

            bool resultado = false;
            int c = cursor;

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
                cursor = c;
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
                
                if(cursor == (txt.length() - 1))
                {
                    return false;
                }

                nuevaLínea(txt);
                incrementaCursor(txt);
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

                Ñ::Lexema* l = new Ñ::Lexema();
                l->categoría = Ñ::CategoríaLexema::LEXEMA_NOTACIÓN;
                l->contenido = carácter;

                //std::cout << "Creo nuevo lexema" << std::endl;
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

            int c = cursor;

            std::string carácter = siguienteCarácter(txt);

            while(Ñ::esalfa(carácter))
            {
                //std::cout << "_nombre:: isalpha(" << carácter << ")" << std::endl;
                
                resultado = true;
                do {
                    if(cursor == (txt.length()+1))
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

            int c = cursor;

            if(_nombre(txt))
            {
                std::string s = txt.substr(c, cursor-c);

                if( (s == "cierto")
                 || (s == "falso")
                 || (s == "nulo")
                 || (s == "var")
                 || (s == "bool")
                 || (s == "entero")
                 || (s == "ent8")
                 || (s == "ent16")
                 || (s == "ent32")
                 || (s == "ent64")
                 || (s == "natural")
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
                    
                    Ñ::Lexema* l = new Ñ::Lexema();
                    l->categoría = Ñ::CategoríaLexema::LEXEMA_RESERVADO;
                    l->contenido = s;

                    //std::cout << "Creo nuevo lexema" << std::endl;
                    lexemas.push_back(l);
                }
                else
                {
                    cursor = c;
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

            int c = cursor;

            std::string carácter = siguienteCarácter(txt);

            if(carácter == "-")
            {
                incrementaCursor(txt);
                carácter = siguienteCarácter(txt);
            }
                
            while(Ñ::esdígito(carácter) && (cursor < (txt.length()-1)))
            {
                resultado = true;
                incrementaCursor(txt);
                carácter = siguienteCarácter(txt);
            }

            if(carácter != ".")
            {
                cursor = c;
                return false;
            }
            
            if(cursor == (txt.length()-1))
            {
                cursor = c;
                return false;
            }

            incrementaCursor(txt);
            carácter = siguienteCarácter(txt);

            do {
                resultado = true;
                incrementaCursor(txt);
                carácter = siguienteCarácter(txt);
            } while(Ñ::esdígito(carácter) && (cursor < (txt.length()-1)));

            std::string e = "e";
            std::string E = "E";
            if((carácter != e) && (carácter != E))
            {
                cursor = c;
                return false;
            }
            
            if(cursor == (txt.length()-1))
            {
                cursor = c;
                return false;
            }

            incrementaCursor(txt);
            carácter = siguienteCarácter(txt);
            
            if(cursor < (txt.length() - 1) && (carácter == "-") || (carácter == "+") )
            {
                incrementaCursor(txt);
                carácter = siguienteCarácter(txt);
            }

            while(Ñ::esdígito(carácter) && (cursor < (txt.length()-1)))
            {
                resultado = true;
                incrementaCursor(txt);
                carácter = siguienteCarácter(txt);
            }

            if(resultado)
            {
                std::string s = txt.substr(c, cursor-c);

                //double n = to!double(s);

                Ñ::Lexema* l = new Ñ::Lexema();
                l->categoría = Ñ::CategoríaLexema::LEXEMA_NÚMERO_REAL;
                l->contenido = s;

                //std::cout << "Creo nuevo lexema" << std::endl;
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

            int c = cursor;

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
                if(cursor == (txt.length()-1))
                {
                    //std::cout << ":: Salida -> hemos llegado al final del código" << std::endl;
                    cursor = c;
                    return false;
                }
                incrementaCursor(txt);
                carácter = siguienteCarácter(txt);
            }

            if(carácter != ".")
            {
                //std::cout << ":: Salida -> falta el punto decimal" << std::endl;
                cursor = c;
                return false;
            }
            
            if(cursor == (txt.length()-1))
            {
                //std::cout << ":: Salida -> hemos llegado al final del código" << std::endl;
                cursor = c;
                return false;
            }
            
            incrementaCursor(txt);
            carácter = siguienteCarácter(txt);
                
            if(!Ñ::esdígito(carácter))
            {
                //std::cout << ":: Salida -> no es un dígito" << std::endl;
                cursor = c;
                return false;
            }

            do {
                //std::cout << ":: añado dígito decimal" << std::endl;
                resultado = true;
                if(cursor == (txt.length()-1))
                {
                    //std::cout << ":: Salida -> hemos llegado al final del código" << std::endl;
                    cursor = c;
                    return false;
                }
                incrementaCursor(txt);
                carácter = siguienteCarácter(txt);
            } while(Ñ::esdígito(carácter));

            if(resultado)
            {
                //std::cout << ":: resultado" << std::endl;
                std::string s = txt.substr(c, cursor-c);

                //double n = to!double(s);

                Ñ::Lexema* l = new Ñ::Lexema();
                l->categoría = Ñ::CategoríaLexema::LEXEMA_NÚMERO_REAL;
                l->contenido = s;
                
                //std::cout << "Creo nuevo lexema" << std::endl;
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

            int c = cursor;

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
                    if(cursor == (txt.length()+1))
                    {
                        return true;
                    }
                    incrementaCursor(txt);
                    carácter = siguienteCarácter(txt);
                } while(Ñ::esdígito(carácter));
            }

            if(resultado)
            {
                std::string s = txt.substr(c, cursor-c);

                //int n = to!int(s);

                Ñ::Lexema* l = new Ñ::Lexema();
                l->categoría = Ñ::CategoríaLexema::LEXEMA_NÚMERO;
                l->contenido = s;
                
                //std::cout << "Creo nuevo lexema" << std::endl;
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
                int c = cursor;

                std::string texto;

                Ñ::Lexema* l = new Ñ::Lexema();

                while((carácter != "\"") && (cursor < txt.length()-1))
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
                            texto.append("\0");
                        }
                    }
                    else
                    {
                        texto.append(carácter);
                    }
                    
                    incrementaCursor(txt);
                    carácter = siguienteCarácter(txt);
                }

                l->categoría = Ñ::CategoríaLexema::LEXEMA_TEXTO;
                l->contenido = texto;

                if(carácter != "\"")
                {
                    cursor = c;
                    Ñ::errorConsola(u8"Error, esperaba un cierre de comilla doble [\"]");
                }

                incrementaCursor(txt);

                //std::cout << "Creo nuevo lexema" << std::endl;
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
            
            int c = cursor;

            //std::cout << "c: " << c << std::endl;
            //std::cout << "cursor: " << cursor << std::endl;

            bool resultado = _nombre(txt);

            //std::cout << "c: " << c << std::endl;
            //std::cout << "cursor: " << cursor << std::endl;
            
            if(resultado)
            {
                std::string texto = txt.substr(c, cursor-c);

                //std::cout << "identificador->contenido" << texto << std::endl;

                Ñ::Lexema* l = new Ñ::Lexema();
                l->categoría = Ñ::CategoríaLexema::LEXEMA_IDENTIFICADOR;
                l->contenido = texto;


                //std::cout << "Creo nuevo lexema" << std::endl;
                lexemas.push_back(l);
                //std::cout << "lexema creado" << std::endl;
            }

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

    std::vector<Ñ::Lexema*> Léxico::analiza(std::string comando)
    {
        std::vector<Ñ::Lexema*> vacía;
        if(!lexemas.empty())
        {
            lexemas.clear();
        }

        try {
            //std::cout << "_analizaLéxico(" << comando << ")" << std::endl;

            std::string cmd = comando + " ";

            cursor = 0;

            while(cursor <= cmd.length())
            {
                //std::cout << "cursor: " << cursor << std::endl;
                int c = cursor;
                if(nuevaLínea(cmd))
                {
                    continue;
                }
                cursor = c;
                
                if(espacio(cmd))
                {
                    continue;
                }
                cursor = c;

                if(texto(cmd))
                {
                    continue;
                }
                cursor = c;

                if(notación(cmd))
                {
                    continue;
                }
                cursor = c;

                if(reservada(cmd))
                {
                    continue;
                }
                cursor = c;

                if(número(cmd))
                {
                    continue;
                }
                cursor = c;

                if(identificador(cmd))
                {
                    continue;
                }
                cursor = c;

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

        Ñ::Lexema* fin = new Ñ::Lexema();
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
            c == u8"\u0085" // Next line
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