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
Ñ::Nodo* literal();
Ñ::Nodo* tipo();
Ñ::Nodo* identificador();
Ñ::Nodo* factor();
Ñ::Nodo* opMultiplicaciónDivisión();
Ñ::Nodo* opSumaResta();
Ñ::Nodo* ladoIzquierdoAsignación();
Ñ::Nodo* ladoDerechoAsignación();
Ñ::Nodo* declaraVariable();
Ñ::Nodo* asigna();
Ñ::Nodo* argumento();
Ñ::Nodo* argumentos();
Ñ::Nodo* llamaFunción();
Ñ::Nodo* expresión();
Ñ::Nodo* Ñ::analizaSintaxis(std::vector<Ñ::Lexema*> _lexemas);


bool notación(std::string carácter)
{
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

Ñ::Nodo* literal()
{
	uint32_t c = cursor;

	Ñ::Literal* l;

	if(lexemas[cursor]->categoría == Ñ::CategoríaLexema::LEXEMA_NÚMERO)
	{
		l = new Ñ::Literal();
		l->dato = lexemas[cursor]->contenido;
		cursor++;
		return (Ñ::Nodo*)l;
	}
	else if(lexemas[cursor]->categoría == Ñ::CategoríaLexema::LEXEMA_TEXTO)
	{
		l = new Ñ::Literal();
		l->dato = lexemas[cursor]->contenido;
		cursor++;
		return (Ñ::Nodo*)l;
	}

	cursor = c;
	return nullptr;
}

Ñ::Nodo* ladoIzquierdoAsignación()
{
	uint32_t c = cursor;

	if(cursor < lexemas.size())
	{
		if(Ñ::Nodo* dv = declaraVariable())
		{
			return dv;
		}
		else if(Ñ::Nodo* id = identificador())
		{
			return id;
		}
	}

	cursor = c;
	return nullptr;
}

Ñ::Nodo* ladoDerechoAsignación()
{
	uint32_t c = cursor;

	if(cursor < lexemas.size())
	{
		Ñ::Nodo* op = opSumaResta();
		
		if(op->ramas.size() == 1)
		{
			return op->ramas[0];
		}
		else
		{
			return op;
		}
	}

	cursor = c;
	return nullptr;
}

Ñ::Nodo* opSumaResta()
{
	uint32_t c = cursor;

	if(cursor < lexemas.size())
	{
		std::string operación;

		Ñ::Nodo* opMulDiv;

		if(opMulDiv = opMultiplicaciónDivisión())
		{
			if(notación("+"))
			{
				operación = "+";
			}
			else if(notación("-"))
			{
				operación = "-";
			}
			else // No es una operación, devuelvo opMulDiv directamente
			{
				return opMulDiv;
			}
			
			if(Ñ::Nodo* e2 = opSumaResta())
			{
				Ñ::OpSumaResta* opSumRes = new Ñ::OpSumaResta();
				opSumRes->operación = operación;
				((Ñ::Nodo*)opSumRes)->ramas.push_back(e2);
				((Ñ::Nodo*)opSumRes)->ramas.push_back(opMulDiv);
				return ((Ñ::Nodo*)opSumRes);
			}

			delete opMulDiv;
			cursor = c;
			return nullptr;
		}
	}

	cursor = c;
	return nullptr;
}

Ñ::Nodo* opMultiplicaciónDivisión()
{
	uint32_t c = cursor;

	if(cursor < lexemas.size())
	{
		std::string operación;

		Ñ::Nodo* fac;

		if(fac = factor())
		{
			if(notación("*"))
			{
				operación = "*";
			}
			else if(notación("/"))
			{
				operación = "/";
			}
			else // No es una operación, devuelvo factor directamente
			{
				return fac;
			}
			if(Ñ::Nodo* opMulDiv2 = opMultiplicaciónDivisión())
			{
				Ñ::OpMultiplicaciónDivisión* opMulDiv = new Ñ::OpMultiplicaciónDivisión();
				opMulDiv->operación = operación;
				((Ñ::Nodo*)opMulDiv)->ramas.push_back(opMulDiv2);
				((Ñ::Nodo*)opMulDiv)->ramas.push_back(fac);
				return ((Ñ::Nodo*)opMulDiv);
			}

			delete fac;
			cursor = c;
			return nullptr;
		}
	}

	cursor = c;
	return nullptr;
}

Ñ::Nodo* factor()
{
	uint32_t c = cursor;

	if(cursor < lexemas.size())
	{
		std::string factor;

		if(Ñ::Nodo* lit = literal())
		{
			return lit;
		}
		else if(notación("("))
		{
			Ñ::Nodo* lda;

			if(lda = ladoDerechoAsignación())
			{
				if(notación(")"))
				{
					return lda;
				}
				else
				{
					delete lda;
					cursor = c;
					return nullptr;
				}
			}

			cursor = c;
			return nullptr;
		}
		else if(Ñ::Nodo* fn = llamaFunción())
		{
			return fn;
		}
		else if(Ñ::Nodo* id = identificador())
		{
			return id;
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

Ñ::Nodo* identificador()
{
	uint32_t c = cursor;

	if(cursor < lexemas.size())
	{
		if(lexemas[cursor]->categoría == Ñ::CategoríaLexema::LEXEMA_IDENTIFICADOR)
		{
			Ñ::Identificador* id = new Ñ::Identificador();
			id->id = lexemas[cursor]->contenido;
			cursor++;
			return (Ñ::Nodo*)id;
		}
	}

	cursor = c;
	return nullptr;
}

Ñ::Nodo* tipo()
{
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
				return (Ñ::Nodo*)t;
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
		return (Ñ::Nodo*)t;
	}

	cursor = c;
	return nullptr;
}

Ñ::Nodo* declaraVariable()
{
	uint32_t c = cursor;

	if(cursor < lexemas.size())
	{
		Ñ::Nodo* t;
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
			v = lexemas[cursor]->contenido;
			cursor++;
		}
		else
		{
			delete t;
			cursor = c;
			return nullptr;
		}

		Ñ::DeclaraVariable* dvar = new Ñ::DeclaraVariable();
		((Ñ::Nodo*)dvar)->ramas.push_back(t);
		dvar->variable = v;
		return ((Ñ::Nodo*)dvar);
	}

	cursor = c;
	return nullptr;
}

Ñ::Nodo* asigna()
{
	uint32_t c = cursor;

	if(cursor < lexemas.size())
	{
		if(Ñ::Nodo* lia = ladoIzquierdoAsignación())
		{
			if(notación("="))
			{
				if(notación("=")) // "=="
				{
					delete lia;
					cursor = c;
					return nullptr;
				}
				
				if(Ñ::Nodo* lda = ladoDerechoAsignación())
				{
					Ñ::Asigna* a = new Ñ::Asigna();
					((Ñ::Nodo*)a)->ramas.push_back(lia);
					((Ñ::Nodo*)a)->ramas.push_back(lda);

					return ((Ñ::Nodo*)a);
				}
			}
			
			delete lia;
		}
	}

	cursor = c;
	return nullptr;
}

Ñ::Nodo* argumento()
{
	uint32_t c = cursor;

	if(cursor < lexemas.size())
	{
		return ladoDerechoAsignación();
	}

	cursor = c;
	return nullptr;
}

Ñ::Nodo* argumentos()
{
	uint32_t c = cursor;

	if(cursor < lexemas.size())
	{
		Ñ::Argumentos* args = nullptr;

		if(Ñ::Nodo* arg1 = argumento())
		{
			args = new Ñ::Argumentos();

			((Ñ::Nodo*)args)->ramas.push_back(arg1);

			while(notación(","))
			{
				Ñ::Nodo* arg2 = argumento();
				((Ñ::Nodo*)args)->ramas.push_back(arg2);
			}

			return (Ñ::Nodo*)args;
		}

		return nullptr;
	}

	cursor = c;
	return nullptr;
}

Ñ::Nodo* llamaFunción()
{
	uint32_t c = cursor;

	if(cursor < lexemas.size())
	{
		std::string función;
		Ñ::Nodo* args = nullptr;

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
			args = argumentos();

			//std::cout << "CURSOR INTERNO: " << cursor << std::endl;

			if(args == nullptr)
			{
				cursor = c;
				return nullptr;
			}
			else
			{
				if(!notación(")"))
				{
					cursor = c;
					return nullptr;
				}
			}
		}

		Ñ::LlamaFunción* fn = new Ñ::LlamaFunción();
		fn->función = función;
		((Ñ::Nodo*)fn)->ramas.push_back(args);
		return (Ñ::Nodo*)fn;
	}

	cursor = c;
	return nullptr;
}

Ñ::Nodo* expresión()
{
	uint32_t c = cursor;

	if(cursor < lexemas.size())
	{
		if(Ñ::Nodo* as = asigna())
		{
			if(notación(";"))
			{
				Ñ::Expresión* af = new Ñ::Expresión();
				((Ñ::Nodo*)af)->ramas.push_back(as);
				return ((Ñ::Nodo*)af);
			}
			else
			{
				delete as;
			}
		}
		
		if(Ñ::Nodo* fn = llamaFunción())
		{
			if(notación(";"))
			{
				Ñ::Expresión* af = new Ñ::Expresión();
				((Ñ::Nodo*)af)->ramas.push_back(fn);
				return ((Ñ::Nodo*)af);
			}
			else
			{
				delete fn;
			}
		}
		
		if(Ñ::Nodo* dv = declaraVariable())
		{
			if(notación(";"))
			{
				Ñ::Expresión* af = new Ñ::Expresión();
				((Ñ::Nodo*)af)->ramas.push_back(dv);
				return ((Ñ::Nodo*)af);
			}
			else
			{
				delete dv;
			}
		}
	}

	cursor = c;
	return nullptr;
}

Ñ::Nodo* Ñ::analizaSintaxis(std::vector<Ñ::Lexema*> _lexemas)
{
	cursor = 0;
	lexemas = _lexemas;
	return (Ñ::Nodo*)expresión();
}