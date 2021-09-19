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

bool Ñ::Sintaxis::reservada(std::string palabra)
{
	uint32_t c = cursor;

	if(cursor < lexemas.size())
	{
		if(lexemas[cursor]->categoría == Ñ::CategoríaLexema::LEXEMA_RESERVADO)
		{
			if(lexemas[cursor]->contenido == palabra)
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
		l->tipo = Ñ::CategoríaTipo::TIPO_NATURAL_64;
		cursor++;
		return (Ñ::Nodo*)l;
	}
	else if(lexemas[cursor]->categoría == Ñ::CategoríaLexema::LEXEMA_NÚMERO_REAL)
	{
		l = new Ñ::Literal();
		l->tipo = Ñ::CategoríaTipo::TIPO_REAL_64;
		l->dato = lexemas[cursor]->contenido;
		cursor++;
		return (Ñ::Nodo*)l;
	}
	else if(lexemas[cursor]->categoría == Ñ::CategoríaLexema::LEXEMA_TEXTO)
	{
		l = new Ñ::Literal();
		l->tipo = Ñ::CategoríaTipo::TIPO_TEXTO;
		l->dato = lexemas[cursor]->contenido;
		cursor++;
		return (Ñ::Nodo*)l;
	}
	else if(lexemas[cursor]->categoría == Ñ::CategoríaLexema::LEXEMA_RESERVADO)
	{
		if(lexemas[cursor]->contenido == "cierto")
		{
			l = new Ñ::Literal();
			l->tipo = Ñ::CategoríaTipo::TIPO_BOOLEANO;
			l->dato = lexemas[cursor]->contenido;
			cursor++;
			return (Ñ::Nodo*)l;
		}
		else if(lexemas[cursor]->contenido == "falso")
		{
			l = new Ñ::Literal();
			l->tipo = Ñ::CategoríaTipo::TIPO_BOOLEANO;
			l->dato = lexemas[cursor]->contenido;
			cursor++;
			return (Ñ::Nodo*)l;
		}
		else if(lexemas[cursor]->contenido == "nulo")
		{
			l = new Ñ::Literal();
			l->tipo = Ñ::CategoríaTipo::TIPO_NADA;
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
			Ñ::Nodo* ig = nullptr;

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
					if(ig == nullptr)
					{
						ig = (Ñ::Nodo*)(new Ñ::Igualdad);
						ig->ramas.push_back(cmp1);
					}
					ig->ramas.push_back(op);
				}
				else
				{
					delete ig;
					cursor = cN;
					return nullptr;
				}
			}

			if(ig == nullptr)
			{
				return cmp1;
			}
			else
			{
				return ig;
			}
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
			Ñ::Nodo* cmp = nullptr;

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
					if(cmp == nullptr)
					{
						cmp = (Ñ::Nodo*)(new Ñ::Comparación);
						cmp->ramas.push_back(t1);
					}
					cmp->ramas.push_back(op);
				}
				else
				{
					delete cmp;
					cursor = cN;
					return nullptr;
				}
			}

			if(cmp == nullptr)
			{
				return t1;
			}
			else
			{
				return cmp;
			}
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
			Ñ::Nodo* t = nullptr;

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
					if(t == nullptr)
					{
						t = (Ñ::Nodo*)(new Ñ::Término);
						t->ramas.push_back(f1);
					}
					t->ramas.push_back(op);
				}
				else
				{
					delete t;
					cursor = cN;
					return nullptr;
				}
			}

			if(t == nullptr)
			{
				return f1;
			}
			else
			{
				return t;
			}
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
			Ñ::Nodo* f = nullptr;

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
					if(f == nullptr)
					{
						f = (Ñ::Nodo*)(new Ñ::Factor);
						f->ramas.push_back(u1);
					}
					f->ramas.push_back(op);
				}
				else
				{
					delete f;
					cursor = cN;
					return nullptr;
				}
			}

			if(f == nullptr)
			{
				return u1;
			}
			else
			{
				return f;
			}
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
		CategoríaTipo tipo;

		if(lexemas[cursor]->categoría == Ñ::CategoríaLexema::LEXEMA_IDENTIFICADOR)
		{
			tipo = obténTipoDeNombre(lexemas[cursor]->contenido);

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
				tipo = obténTipoDeNombre(lexemas[cursor]->contenido);

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
				Ñ::Tipo* subT = new Ñ::Tipo();
				subT->tipo = tipo;
				t->tipo = CategoríaTipo::TIPO_VECTOR;
				((Ñ::Nodo*)t)->ramas.push_back((Ñ::Nodo*)subT);
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

Ñ::Nodo* Ñ::Sintaxis::vuelve()
{
	uint32_t c = cursor;

	if(cursor < lexemas.size())
	{
		if(lexemas[cursor]->categoría == Ñ::CategoríaLexema::LEXEMA_RESERVADO)
		{
			if(lexemas[cursor]->contenido == "vuelve")
			{
				cursor++;
				Ñ::Nodo* dv = (Ñ::Nodo*)(new Ñ::Devuelve);
				return dv;
			}
		}
	}

	cursor = c;
	return nullptr;
}

Ñ::Nodo* Ñ::Sintaxis::devuelve()
{
	uint32_t c = cursor;

	if(cursor < lexemas.size())
	{
		if(lexemas[cursor]->categoría == Ñ::CategoríaLexema::LEXEMA_RESERVADO)
		{
			if(lexemas[cursor]->contenido == "devuelve")
			{
				cursor++;
				
				if(Ñ::Nodo* lda = ladoDerechoAsignación())
				{
					Ñ::Nodo* dv = (Ñ::Nodo*)(new Ñ::Devuelve);
					dv->ramas.push_back(lda);
					return dv;
				}
			}
		}
	}

	cursor = c;
	return nullptr;
}

Ñ::Nodo* Ñ::Sintaxis::siCondicional()
{
	uint32_t c = cursor;

	if(cursor < lexemas.size())
	{
		Ñ::SiCondicional* sc = nullptr;

		if(!reservada("si"))
		{
			cursor = c;
			return nullptr;
		}

		if(!notación("("))
		{
			cursor = c;
			return nullptr;
		}

		if(Ñ::Nodo* lda = ladoDerechoAsignación())
		{
			if(!notación(")"))
			{
				delete lda;
				cursor = c;
				return nullptr;
			}

			if(Ñ::Nodo* blq = bloque())
			{
				sc = new Ñ::SiCondicional();
				((Ñ::Nodo*)sc)->ramas.push_back(lda);
				((Ñ::Nodo*)sc)->ramas.push_back(blq);
			}
			else
			{
				delete lda;
				cursor = c;
				return nullptr;
			}
		}
		else
		{
			cursor = c;
			return nullptr;
		}

		while(reservada("sino"))
		{
			if(!reservada("si"))
			{
				if(Ñ::Nodo* blq = bloque())
				{
					((Ñ::Nodo*)sc)->ramas.push_back(blq);
					break;
				}
				else
				{
					delete sc;
					cursor = c;
					return nullptr;
				}
			}

			if(!notación("("))
			{
				delete sc;
				cursor = c;
				return nullptr;
			}

			if(Ñ::Nodo* lda = ladoDerechoAsignación())
			{
				if(!notación(")"))
				{
					delete lda;
					delete sc;
					cursor = c;
					return nullptr;
				}

				if(Ñ::Nodo* blq = bloque())
				{
					((Ñ::Nodo*)sc)->ramas.push_back(lda);
					((Ñ::Nodo*)sc)->ramas.push_back(blq);
				}
				else
				{
					delete lda;
					delete sc;
					cursor = c;
					return nullptr;
				}
			}
			else
			{
				delete sc;
				cursor = c;
				return nullptr;
			}
		}

		return (Ñ::Nodo*)sc;
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
				Ñ::Expresión* ex = new Ñ::Expresión();
				((Ñ::Nodo*)ex)->ramas.push_back(as);
				return ((Ñ::Nodo*)ex);
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
				Ñ::Expresión* ex = new Ñ::Expresión();
				((Ñ::Nodo*)ex)->ramas.push_back(fn);
				return ((Ñ::Nodo*)ex);
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
				Ñ::Expresión* ex = new Ñ::Expresión();
				((Ñ::Nodo*)ex)->ramas.push_back(dv);
				return ((Ñ::Nodo*)ex);
			}
			else
			{
				delete dv;
			}
		}
		
		if(Ñ::Nodo* v = vuelve())
		{
			if(notación(";"))
			{
				Ñ::Expresión* ex = new Ñ::Expresión();
				((Ñ::Nodo*)ex)->ramas.push_back(v);
				return ((Ñ::Nodo*)ex);
			}
			else
			{
				delete v;
			}
		}
		
		if(Ñ::Nodo* dv = devuelve())
		{
			if(notación(";"))
			{
				Ñ::Expresión* ex = new Ñ::Expresión();
				((Ñ::Nodo*)ex)->ramas.push_back(dv);
				return ((Ñ::Nodo*)ex);
			}
			else
			{
				delete dv;
			}
		}
		
		if(Ñ::Nodo* sc = siCondicional())
		{
			Ñ::Expresión* ex = new Ñ::Expresión();
			((Ñ::Nodo*)ex)->ramas.push_back(sc);
			return ((Ñ::Nodo*)ex);
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
		bool público = false;

		if(reservada("público"))
		{
			público = true;
		}
		else if(reservada("privado"))
		{
			público = false;
		}

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
		dfn->público = público;
		((Ñ::Nodo*)dfn)->ramas.push_back(t);
		((Ñ::Nodo*)dfn)->ramas.push_back(args);
		((Ñ::Nodo*)dfn)->ramas.push_back(bq);

		return (Ñ::Nodo*)dfn;
	}

	cursor = c;
	return nullptr;
}

Ñ::Nodo* Ñ::Sintaxis::declaraFunción()
{
	uint32_t c = cursor;

	if(cursor < lexemas.size())
	{
		Ñ::Nodo* t;
		Ñ::Nodo* id;
		Ñ::Nodo* args;
		Ñ::DeclaraFunción* dcfn;
		std::string nombreFunción;
		bool externo = false;

		externo = reservada("externo");

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
			delete t;
			cursor = c;
			return nullptr;
		}

		args = declaraArgumentos();

		if(!notación(")"))
		{
			delete t;
			cursor = c;
			return nullptr;
		}

		if(!notación(";"))
		{
			delete t;
			cursor = c;
			return nullptr;
		}

		if(Ñ::Nodo* bq = bloque())
		{
			delete t, bq;
			cursor = c;
			return nullptr;
		}

		dcfn = new Ñ::DeclaraFunción();
		dcfn->nombre = nombreFunción;
		dcfn->externo = externo;
		((Ñ::Nodo*)dcfn)->ramas.push_back(t);
		((Ñ::Nodo*)dcfn)->ramas.push_back(args);

		return (Ñ::Nodo*)dcfn;
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

		if(lexemas[cursor]->categoría == Ñ::CategoríaLexema::LEXEMA_IDENTIFICADOR && lexemas[cursor]->contenido == "módulo")
		{
			cursor++;

			if(lexemas[cursor]->categoría == Ñ::CategoríaLexema::LEXEMA_IDENTIFICADOR)
			{
				((Ñ::Módulo*)m)->módulo = lexemas[cursor]->contenido;

				cursor++;
			}

			if(lexemas[cursor]->categoría == Ñ::CategoríaLexema::LEXEMA_NOTACIÓN && lexemas[cursor]->contenido == ";")
			{
				cursor++;
			}
			else
			{
				cursor = c;
				return nullptr;
			}
		}

		while(true)
		{
			Ñ::Nodo* n;
			if(n = defineFunción())
			{
				m->ramas.push_back(n);
			}
			else if(n = declaraFunción())
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