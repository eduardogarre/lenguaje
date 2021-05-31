#include <iostream>
#include <string>
#include <vector>

#include "lexema.hpp"
#include "lexico.hpp"
#include "nodo.hpp"
#include "salida.hpp"
#include "sintaxis.hpp"
#include "tipo.hpp"
#include "valor.hpp"

bool Ñ::Sintaxis::notación(std::string carácter)
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

Ñ::Nodo* Ñ::Sintaxis::literal()
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
	else if(lexemas[cursor]->categoría == Ñ::CategoríaLexema::LEXEMA_RESERVADO)
	{
		if(lexemas[cursor]->contenido == "cierto")
		{
			l = new Ñ::Literal();
			l->dato = lexemas[cursor]->contenido;
			cursor++;
			return (Ñ::Nodo*)l;
		}
		else if(lexemas[cursor]->contenido == "falso")
		{
			l = new Ñ::Literal();
			l->dato = lexemas[cursor]->contenido;
			cursor++;
			return (Ñ::Nodo*)l;
		}
		else if(lexemas[cursor]->contenido == "nulo")
		{
			l = new Ñ::Literal();
			l->dato = lexemas[cursor]->contenido;
			cursor++;
			return (Ñ::Nodo*)l;
		}
	}

	cursor = c;
	return nullptr;
}

Ñ::Nodo* Ñ::Sintaxis::ladoIzquierdoAsignación()
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

Ñ::Nodo* Ñ::Sintaxis::ladoDerechoAsignación()
{
	uint32_t c = cursor;

	if(cursor < lexemas.size())
	{
		Ñ::Nodo* ig = igualdad();
		
		return ig;
	}

	cursor = c;
	return nullptr;
}

Ñ::Nodo* Ñ::Sintaxis::igualdad()
{
	uint32_t c = cursor;

	if(cursor < lexemas.size())
	{
		Ñ::Nodo* cmp1;

		if(cmp1 = comparación())
		{
			Ñ::Nodo* ig = (Ñ::Nodo*)(new Ñ::Igualdad);
			ig->ramas.push_back(cmp1);

			while(true)
			{
				std::string operación;
				uint32_t cN = cursor;

				if(notación("!"))
				{
					if(notación("="))
					{
						operación = "!=";
					}
					else
					{
						cursor = cN;
						break;
					}
				}
				else if(notación("="))
				{
					if(notación("="))
					{
						operación = "==";
					}
					else
					{
						cursor = cN;
						break;
					}
				}
				else
				{
					cursor = cN;
					break;
				}

				if(Ñ::Nodo* cmpN = comparación())
				{
					Ñ::Nodo* op = (Ñ::Nodo*)(new Ñ::OperaciónBinaria);
					((Ñ::OperaciónBinaria*)op)->operación = operación;
					op->ramas.push_back(cmpN);
					ig->ramas.push_back(op);
				}
				else
				{
					delete ig;
					cursor = cN;
					return nullptr;
				}
			}

			return ig;
		}
	}

	cursor = c;
	return nullptr;
}

Ñ::Nodo* Ñ::Sintaxis::comparación()
{
	uint32_t c = cursor;

	if(cursor < lexemas.size())
	{
		Ñ::Nodo* t1;

		if(t1 = término())
		{
			Ñ::Nodo* cmp = (Ñ::Nodo*)(new Ñ::Comparación);
			cmp->ramas.push_back(t1);

			while(true)
			{
				std::string operación;
				uint32_t cN = cursor;

				if(notación(">"))
				{
					if(notación("="))
					{
						operación = ">=";
					}
					else
					{
						operación = ">";
					}
				}
				else if(notación("<"))
				{
					if(notación("="))
					{
						operación = "<=";
					}
					else
					{
						operación = "<";
					}
				}
				else
				{
					cursor = cN;
					break;
				}

				if(Ñ::Nodo* tN = término())
				{
					Ñ::Nodo* op = (Ñ::Nodo*)(new Ñ::OperaciónBinaria);
					((Ñ::OperaciónBinaria*)op)->operación = operación;
					op->ramas.push_back(tN);
					cmp->ramas.push_back(op);
				}
				else
				{
					delete cmp;
					cursor = cN;
					return nullptr;
				}
			}

			return cmp;
		}
	}

	cursor = c;
	return nullptr;
}

Ñ::Nodo* Ñ::Sintaxis::término()
{
	uint32_t c = cursor;

	if(cursor < lexemas.size())
	{
		Ñ::Nodo* f1;

		if(f1 = factor())
		{
			Ñ::Nodo* t = (Ñ::Nodo*)(new Ñ::Término);
			t->ramas.push_back(f1);

			while(true)
			{
				std::string operación;
				uint32_t cN = cursor;

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
					cursor = cN;
					break;
				}
				
				if(Ñ::Nodo* fN = factor())
				{
					Ñ::Nodo* op = (Ñ::Nodo*)(new Ñ::OperaciónBinaria);
					((Ñ::OperaciónBinaria*)op)->operación = operación;
					op->ramas.push_back(fN);
					t->ramas.push_back(op);
				}
				else
				{
					delete t;
					cursor = cN;
					return nullptr;
				}
			}

			return t;
		}
	}

	cursor = c;
	return nullptr;
}

Ñ::Nodo* Ñ::Sintaxis::factor()
{
	uint32_t c = cursor;

	if(cursor < lexemas.size())
	{
		Ñ::Nodo* u1;

		if(u1 = operaciónUnaria())
		{
			Ñ::Nodo* f = (Ñ::Nodo*)(new Ñ::Factor);
			f->ramas.push_back(u1);

			while(true)
			{
				std::string operación;
				uint32_t cN = cursor;

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
					cursor = cN;
					break;
				}

				if(Ñ::Nodo* uN = operaciónUnaria())
				{
					Ñ::Nodo* op = (Ñ::Nodo*)(new Ñ::OperaciónBinaria);
					((Ñ::OperaciónBinaria*)op)->operación = operación;
					op->ramas.push_back(uN);
					f->ramas.push_back(op);
				}
				else
				{
					delete f;
					cursor = cN;
					return nullptr;
				}
			}

			return f;
		}
	}

	cursor = c;
	return nullptr;
}

Ñ::Nodo* Ñ::Sintaxis::operaciónUnaria()
{
	uint32_t c = cursor;

	if(cursor < lexemas.size())
	{
		if(notación("!"))
		{
			if(Ñ::Nodo* u = operaciónUnaria())
			{
				Ñ::OperaciónUnaria* op = new Ñ::OperaciónUnaria;
				op->operación = "!";
				((Ñ::Nodo*)op)->ramas.push_back(u);
				return (Ñ::Nodo*)op;
			}
		}
		else if(notación("-"))
		{
			if(Ñ::Nodo* u = operaciónUnaria())
			{
				Ñ::OperaciónUnaria* op = new Ñ::OperaciónUnaria;
				op->operación = "-";
				((Ñ::Nodo*)op)->ramas.push_back(u);
				return (Ñ::Nodo*)op;
			}
		}
		else if(Ñ::Nodo* p = primario())
		{
			return p;
		}
	}

	cursor = c;
	return nullptr;
}

Ñ::Nodo* Ñ::Sintaxis::primario()
{
	uint32_t c = cursor;

	if(cursor < lexemas.size())
	{
		std::string primario;

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

Ñ::Nodo* Ñ::Sintaxis::identificador()
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

Ñ::Nodo* Ñ::Sintaxis::tipo()
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
			 || (lexemas[cursor]->contenido == "booleano")
			 || (lexemas[cursor]->contenido == "ent")
			 || (lexemas[cursor]->contenido == "entero")
			 || (lexemas[cursor]->contenido == "ent8")
			 || (lexemas[cursor]->contenido == "ent16")
			 || (lexemas[cursor]->contenido == "ent32")
			 || (lexemas[cursor]->contenido == "ent64")
			 || (lexemas[cursor]->contenido == "nat")
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
			 || (lexemas[cursor]->contenido == "nada")
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

Ñ::Nodo* Ñ::Sintaxis::declaraVariable()
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

Ñ::Nodo* Ñ::Sintaxis::asigna()
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

Ñ::Nodo* Ñ::Sintaxis::declaraArgumento()
{
	uint32_t c = cursor;

	if(cursor < lexemas.size())
	{
		return Ñ::Sintaxis::declaraVariable();
	}

	cursor = c;
	return nullptr;
}

Ñ::Nodo* Ñ::Sintaxis::declaraArgumentos()
{
	uint32_t c = cursor;

	if(cursor < lexemas.size())
	{
		Ñ::Argumentos* args = new Ñ::Argumentos();

		if(Ñ::Nodo* arg1 = declaraArgumento())
		{
			((Ñ::Nodo*)args)->ramas.push_back(arg1);

			while(notación(","))
			{
				Ñ::Nodo* arg2 = declaraArgumento();
				((Ñ::Nodo*)args)->ramas.push_back(arg2);
			}

			return (Ñ::Nodo*)args;
		}

		return (Ñ::Nodo*)args;
	}

	cursor = c;
	return nullptr;
}

Ñ::Nodo* Ñ::Sintaxis::ponArgumento()
{
	uint32_t c = cursor;

	if(cursor < lexemas.size())
	{
		return ladoDerechoAsignación();
	}

	cursor = c;
	return nullptr;
}

Ñ::Nodo* Ñ::Sintaxis::ponArgumentos()
{
	uint32_t c = cursor;

	if(cursor < lexemas.size())
	{
		Ñ::Argumentos* args = new Ñ::Argumentos();

		if(Ñ::Nodo* arg1 = ponArgumento())
		{
			((Ñ::Nodo*)args)->ramas.push_back(arg1);

			while(notación(","))
			{
				Ñ::Nodo* arg2 = ponArgumento();
				((Ñ::Nodo*)args)->ramas.push_back(arg2);
			}

			return (Ñ::Nodo*)args;
		}

		return (Ñ::Nodo*)args;
	}

	cursor = c;
	return nullptr;
}

Ñ::Nodo* Ñ::Sintaxis::llamaFunción()
{
	uint32_t c = cursor;

	if(cursor < lexemas.size())
	{
		std::string nombre;
		Ñ::Nodo* args = nullptr;

		if(lexemas[cursor]->categoría == Ñ::CategoríaLexema::LEXEMA_IDENTIFICADOR)
		{
			nombre = lexemas[cursor]->contenido;

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

		args = ponArgumentos();

		if(!notación(")"))
		{
			if(args != nullptr)
			{
				delete args;
			}
			cursor = c;
			return nullptr;
		}

		Ñ::LlamaFunción* fn = new Ñ::LlamaFunción();
		fn->nombre = nombre;
		((Ñ::Nodo*)fn)->ramas.push_back(args);
		return (Ñ::Nodo*)fn;
	}

	cursor = c;
	return nullptr;
}

Ñ::Nodo* Ñ::Sintaxis::expresión()
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

Ñ::Nodo* Ñ::Sintaxis::bloque()
{
	uint32_t c = cursor;

	if(cursor < lexemas.size())
	{
		if(!notación("{"))
		{
			cursor = c;
			return nullptr;
		}

		Ñ::Nodo* b = (Ñ::Nodo*)(new Ñ::Bloque);

		while(Ñ::Nodo* n = expresión())
		{
			b->ramas.push_back(n);
		}

		if(notación("}"))
		{
			return b;
		}
		else
		{
			delete b;
			cursor = c;
			return nullptr;
		}
	}

	cursor = c;
	return nullptr;
}

Ñ::Nodo* Ñ::Sintaxis::defineFunción()
{
	uint32_t c = cursor;

	if(cursor < lexemas.size())
	{
		Ñ::Nodo* t;
		Ñ::Nodo* id;
		Ñ::Nodo* args;
		Ñ::Nodo* bq;
		Ñ::DefineFunción* dfn;
		std::string nombreFunción;

		if(t = tipo())
		{
			
		}
		else
		{
			cursor = c;
			return nullptr;
		}

		if(id = identificador())
		{
			nombreFunción = ((Ñ::Identificador*)id)->id;
			delete id;
		}
		else
		{
			delete t;
			cursor = c;
			return nullptr;
		}

		if(!notación("("))
		{
			cursor = c;
			return nullptr;
		}

		args = declaraArgumentos();

		if(!notación(")"))
		{
			cursor = c;
			return nullptr;
		}

		if(bq = bloque())
		{

		}
		else
		{
			delete t;
			cursor = c;
			return nullptr;
		}

		dfn = new Ñ::DefineFunción();
		dfn->nombre = nombreFunción;
		((Ñ::Nodo*)dfn)->ramas.push_back(t);
		((Ñ::Nodo*)dfn)->ramas.push_back(args);
		((Ñ::Nodo*)dfn)->ramas.push_back(bq);

		return (Ñ::Nodo*)dfn;
	}

	cursor = c;
	return nullptr;
}

Ñ::Nodo* Ñ::Sintaxis::módulo()
{
	uint32_t c = cursor;

	if(cursor < lexemas.size())
	{
		Ñ::Nodo* m = (Ñ::Nodo*)(new Ñ::Módulo);

		while(true)
		{
			Ñ::Nodo* n;
			if(n = defineFunción())
			{
				m->ramas.push_back(n);
			}
			else if(n = expresión())
			{
				m->ramas.push_back(n);
			}
			else
			{
				break;
			}
		}

		return m;
	}

	cursor = c;
	return nullptr;
}

Ñ::Nodo* Ñ::Sintaxis::analiza(std::vector<Ñ::Lexema*> _lexemas)
{
	cursor = 0;
	lexemas = _lexemas;
	return (Ñ::Nodo*)módulo();
}

Ñ::Nodo* Ñ::Sintaxis::analizaComando(std::vector<Ñ::Lexema*> _lexemas)
{
	cursor = 0;
	lexemas = _lexemas;
	return (Ñ::Nodo*)expresión();
}