#include <iostream>
#include <string>
#include <vector>

#include "lexema.hpp"
#include "lexico.hpp"
#include "nodo.hpp"
#include "salida.hpp"
#include "sintaxis.hpp"

uint32_t cursor;

std::vector<Ñ::Lexema*> lexemas;

bool notación(std::string carácter);
Ñ::Literal* literal();
Ñ::Tipo* tipo();
Ñ::Identificador* identificador();
Ñ::DeclaraVariable* declaraVariable();
Ñ::LlamaFunción* llamaFunción();
Ñ::Asigna* asigna();
Ñ::Expresión* expresión();
Ñ::Término* término();
Ñ::Factor* factor();
Ñ::Nodo* Ñ::analizaSintaxis(std::vector<Ñ::Lexema*> _lexemas);


bool notación(std::string carácter)
{
	//std::cout << "notación(\"" << carácter << "\")" << std::endl;
	//std::cout << "cursor[" << cursor << "]" << std::endl;
	
	uint32_t c = cursor;

	if(cursor < lexemas.size())
	{
		if(lexemas[cursor]->categoría == Ñ::CategoríaLexema::LEXEMA_NOTACIÓN)
		{
			if(lexemas[cursor]->contenido == carácter)
			{
				cursor++;
				return true;
			}
		}
	}

	cursor = c;
	return false;
}

Ñ::Literal* literal()
{
	//std::cout << "literal()" << std::endl;
	//std::cout << "cursor[" << cursor << "]" << std::endl;
	
	uint32_t c = cursor;

	Ñ::Literal* l;

	if(lexemas[cursor]->categoría == Ñ::CategoríaLexema::LEXEMA_NÚMERO)
	{
		l = new Ñ::Literal();
		l->dato = lexemas[cursor]->contenido;
		cursor++;
		return l;
	}
	else if(lexemas[cursor]->categoría == Ñ::CategoríaLexema::LEXEMA_TEXTO)
	{
		l = new Ñ::Literal();
		l->dato = lexemas[cursor]->contenido;
		cursor++;
		return l;
	}

	cursor = c;
	return nullptr;
}

Ñ::Expresión* expresión()
{
	//std::cout << "expresión()" << std::endl;
	//std::cout << "cursor[" << cursor << "]" << std::endl;

	uint32_t c = cursor;

	if(cursor < lexemas.size())
	{
		std::string operación;

		Ñ::Expresión* e;
		Ñ::Término* t;

		if(t = término())
		{
			if(notación("+"))
			{
				operación = "+";
			}
			else if(notación("-"))
			{
				operación = "-";
			}
			else
			{
				e = new Ñ::Expresión();
				((Ñ::Nodo*)e)->ramas.push_back((Ñ::Nodo*)t);
				return e;
			}
			
			//std::cout << "[operación:" << operación << "]" << std::endl;
			
			if(Ñ::Expresión* e2 = expresión())
			{
				e = new Ñ::Expresión();
				e->operación = operación;
				((Ñ::Nodo*)e)->ramas.push_back((Ñ::Nodo*)(e2));
				((Ñ::Nodo*)e)->ramas.push_back((Ñ::Nodo*)(t));
				return e;
			}

			delete t;
			cursor = c;
			return nullptr;
		}
	}

	cursor = c;
	return nullptr;
}

Ñ::Término* término()
{
	//std::cout << "término()" << std::endl;
	//std::cout << "cursor[" << cursor << "]" << std::endl;

	uint32_t c = cursor;

	if(cursor < lexemas.size())
	{
		std::string operación;

		Ñ::Término* t;
		Ñ::Factor* f;

		if(f = factor())
		{
			if(notación("*"))
			{
				operación = "*";
			}
			else if(notación("/"))
			{
				operación = "/";
			}
			else
			{
				t = new Ñ::Término();
				((Ñ::Nodo*)t)->ramas.push_back((Ñ::Nodo*)(f));
				return t;
			}
			
			//std::cout << "[operación:" << operación << "]" << std::endl;
			
			if(Ñ::Término* t2 = término())
			{
				t = new Ñ::Término();
				t->operación = operación;
				((Ñ::Nodo*)t)->ramas.push_back((Ñ::Nodo*)(t2));
				((Ñ::Nodo*)t)->ramas.push_back((Ñ::Nodo*)(f));
				return t;
			}

			delete f;
			cursor = c;
			return nullptr;
		}
	}

	cursor = c;
	return nullptr;
}

Ñ::Factor* factor()
{
	//std::cout << "factor()" << std::endl;
	//std::cout << "cursor[" << cursor << "]" << std::endl;

	uint32_t c = cursor;

	if(cursor < lexemas.size())
	{
		std::string factor;

		if(Ñ::Literal* l = literal())
		{
			//std::cout << "[subexpresión]" << std::endl;
			Ñ::Factor* f = new Ñ::Factor();
			((Ñ::Nodo*)f)->ramas.push_back((Ñ::Nodo*)(l));
			return f;
		}
		else if(notación("("))
		{
			Ñ::Factor* f;
			Ñ::Expresión* e;

			if(e = expresión())
			{
				if(notación(")"))
				{
					//std::cout << "[subexpresión]" << std::endl;
					f = new Ñ::Factor();
					((Ñ::Nodo*)f)->ramas.push_back((Ñ::Nodo*)(e));
					return f;
				}
				else
				{
					delete e;
					cursor = c;
					return nullptr;
				}
			}

			cursor = c;
			return nullptr;
		}
		else if(Ñ::LlamaFunción* fn = llamaFunción())
		{
			//std::cout << "[subexpresión]" << std::endl;
			Ñ::Factor* f = new Ñ::Factor();
			((Ñ::Nodo*)f)->ramas.push_back((Ñ::Nodo*)(fn));
			return f;
		}
		else if(Ñ::Identificador* id = identificador())
		{
			//std::cout << "[subexpresión]" << std::endl;
			Ñ::Factor* f = new Ñ::Factor();
			((Ñ::Nodo*)f)->ramas.push_back((Ñ::Nodo*)(id));
			return f;
		}
		else
		{
			cursor = c;
			return nullptr;
		}
	}

	cursor = c;
	return nullptr;
}

Ñ::Identificador* identificador()
{
	//std::cout << "tipo()" << std::endl;
	//std::cout << "cursor[" << cursor << "]" << std::endl;

	uint32_t c = cursor;

	if(cursor < lexemas.size())
	{
		if(lexemas[cursor]->categoría == Ñ::CategoríaLexema::LEXEMA_IDENTIFICADOR)
		{
			

			Ñ::Identificador* id = new Ñ::Identificador();
			id->id = lexemas[cursor]->contenido;
			cursor++;
			return id;
		}
	}

	cursor = c;
	return nullptr;
}

Ñ::Tipo* tipo()
{
	//std::cout << "tipo()" << std::endl;
	//std::cout << "cursor[" << cursor << "]" << std::endl;

	uint32_t c = cursor;

	if(cursor < lexemas.size())
	{
		std::string tipo;

		if(lexemas[cursor]->categoría == Ñ::CategoríaLexema::LEXEMA_IDENTIFICADOR)
		{
			tipo = lexemas[cursor]->contenido;

			cursor++;
		}
		else if(lexemas[cursor]->categoría == Ñ::CategoríaLexema::LEXEMA_RESERVADO)
		{
			if( (lexemas[cursor]->contenido == "bool")
			 || (lexemas[cursor]->contenido == "entero")
			 || (lexemas[cursor]->contenido == "ent8")
			 || (lexemas[cursor]->contenido == "ent16")
			 || (lexemas[cursor]->contenido == "ent32")
			 || (lexemas[cursor]->contenido == "ent64")
			 || (lexemas[cursor]->contenido == "natural")
			 || (lexemas[cursor]->contenido == "nat8")
			 || (lexemas[cursor]->contenido == "nat16")
			 || (lexemas[cursor]->contenido == "nat32")
			 || (lexemas[cursor]->contenido == "nat64")
			 || (lexemas[cursor]->contenido == "real")
			 || (lexemas[cursor]->contenido == "rea16")
			 || (lexemas[cursor]->contenido == "rea32")
			 || (lexemas[cursor]->contenido == "rea64")
			 || (lexemas[cursor]->contenido == "txt")
			)
			{
				tipo = lexemas[cursor]->contenido;

				cursor++;
			}
			else
			{
				cursor = c;
				return nullptr;
			}
		}
		else
		{
			cursor = c;
			return nullptr;
		}

		uint32_t c2 = cursor;

		if(notación("["))
		{
			if(notación("]"))
			{
				Ñ::Tipo* t = new Ñ::Tipo();
				t->tipo = tipo;
				t->vector = true;
				return t;
			}
			else
			{
				cursor = c2;
			}
		}
		else
		{
			cursor = c2;
		}
		
		Ñ::Tipo* t = new Ñ::Tipo();
		t->tipo = tipo;
		t->vector = false;
		return t;
	}

	cursor = c;
	return nullptr;
}

Ñ::DeclaraVariable* declaraVariable()
{
	//std::cout << "declaraVariable()" << std::endl;
	//std::cout << "cursor[" << cursor << "]" << std::endl;

	uint32_t c = cursor;

	if(cursor < lexemas.size())
	{
		Ñ::Tipo* t;
		std::string v;

		if(t = tipo())
		{
			
		}
		else
		{
			cursor = c;
			return nullptr;
		}
		
		if(cursor >= lexemas.size())
		{
			delete t;
			cursor = c;
			return nullptr;
		}

		if(lexemas[cursor]->categoría == Ñ::CategoríaLexema::LEXEMA_IDENTIFICADOR)
		{
			//std::cout << "reconocido un tipo" << std::endl;
			v = lexemas[cursor]->contenido;
			cursor++;
		}
		else
		{
			delete t;
			cursor = c;
			return nullptr;
		}

		//std::cout << "preparando una declaración de variable" << std::endl;

		Ñ::DeclaraVariable* dvar = new Ñ::DeclaraVariable();
		((Ñ::Nodo*)dvar)->ramas.push_back((Ñ::Nodo*)(t));
		dvar->variable = v;
		return dvar;
	}

	cursor = c;
	return nullptr;
}

Ñ::Asigna* asigna()
{
	//std::cout << "asigna() - cursor[" << cursor << "]" << std::endl;

	uint32_t c = cursor;

	if(cursor < lexemas.size())
	{
		//std::cout << "cursor[" << cursor << "]" << std::endl;

		if(Ñ::DeclaraVariable* dv = declaraVariable())
		{
			//std::cout << "Declara variable - cursor[" << cursor << "]" << std::endl;

			if(notación("="))
			{
				//std::cout << "Asigna? - cursor[" << cursor << "]" << std::endl;

				if(notación("=")) // "=="
				{
					//std::cout << "Realmente comparador - cursor[" << cursor << "]" << std::endl;
					//std::cout << "deshaciendo" << std::endl;
					delete dv;
					cursor = c;
					return nullptr;
				}

				//std::cout << "Sí es asignación" << std::endl;

				if(Ñ::Expresión* ex = expresión())
				{
					//std::cout << "Expresión - cursor[" << cursor << "]" << std::endl;

					Ñ::Asigna* a = new Ñ::Asigna();
					((Ñ::Nodo*)a)->ramas.push_back((Ñ::Nodo*)dv);
					((Ñ::Nodo*)a)->ramas.push_back((Ñ::Nodo*)ex);

					return a;
				}

				//std::cout << "no es una asignación a una declaración" << std::endl;
			}
			
			delete dv;
		}
		else if(Ñ::Identificador* id = identificador())
		{
			//std::cout << "Identificador - cursor[" << cursor << "]" << std::endl;

			if(notación("="))
			{
				//std::cout << "Asigna? - cursor[" << cursor << "]" << std::endl;

				if(notación("=")) // "=="
				{
					//std::cout << "Realmente comparador - cursor[" << cursor << "]" << std::endl;
					//std::cout << "deshaciendo" << std::endl;
					delete id;
					cursor = c;
					return nullptr;
				}

				//std::cout << "Sí es asignación" << std::endl;

				if(Ñ::Expresión* ex = expresión())
				{
					//std::cout << "Expresión - cursor[" << cursor << "]" << std::endl;

					Ñ::Asigna* a = new Ñ::Asigna();
					((Ñ::Nodo*)a)->ramas.push_back((Ñ::Nodo*)id);
					((Ñ::Nodo*)a)->ramas.push_back((Ñ::Nodo*)ex);

					return a;
				}

				//std::cout << "no es una asignación" << std::endl;
			}
			
			delete id;
		}
	}

	cursor = c;
	return nullptr;
}

Ñ::LlamaFunción* llamaFunción()
{
	//std::cout << "ejecutaFunción()" << std::endl;
	//std::cout << "cursor[" << cursor << "]" << std::endl;

	uint32_t c = cursor;

	if(cursor < lexemas.size())
	{
		std::string función;

		if(lexemas[cursor]->categoría == Ñ::CategoríaLexema::LEXEMA_IDENTIFICADOR)
		{
			función = lexemas[cursor]->contenido;

			cursor++;
		}
		else
		{
			cursor = c;
			return nullptr;
		}

		if(!notación("("))
		{
			cursor = c;
			return nullptr;
		}
		
		if(!notación(")"))
		{
			cursor = c;
			return nullptr;
		}
		
		Ñ::LlamaFunción* fn = new Ñ::LlamaFunción();
		fn->función = función;
		return fn;
	}

	cursor = c;
	return nullptr;
}

Ñ::Nodo* Ñ::analizaSintaxis(std::vector<Ñ::Lexema*> _lexemas)
{
	cursor = 0;
	lexemas = _lexemas;
	return (Ñ::Nodo*)asigna();
}