#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "lexema.hpp"
#include "lexico.hpp"
#include "nodo.hpp"
#include "posicion.hpp"
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
		l = new Ñ::Literal(lexemas[cursor]->posición());
		l->dato = lexemas[cursor]->contenido;
		l->tipo = obténMínimoNaturalVálido(std::stoull(l->dato));
		cursor++;
		return (Ñ::Nodo*)l;
	}
	else if(lexemas[cursor]->categoría == Ñ::CategoríaLexema::LEXEMA_NÚMERO_REAL)
	{
		l = new Ñ::Literal(lexemas[cursor]->posición());
		l->tipo = Ñ::CategoríaTipo::TIPO_REAL_64;
		l->dato = lexemas[cursor]->contenido;
		cursor++;
		return (Ñ::Nodo*)l;
	}
	else if(lexemas[cursor]->categoría == Ñ::CategoríaLexema::LEXEMA_RESERVADO)
	{
		if(lexemas[cursor]->contenido == "cierto")
		{
			l = new Ñ::Literal(lexemas[cursor]->posición());
			l->tipo = Ñ::CategoríaTipo::TIPO_BOOLEANO;
			l->dato = lexemas[cursor]->contenido;
			cursor++;
			return (Ñ::Nodo*)l;
		}
		else if(lexemas[cursor]->contenido == "falso")
		{
			l = new Ñ::Literal(lexemas[cursor]->posición());
			l->tipo = Ñ::CategoríaTipo::TIPO_BOOLEANO;
			l->dato = lexemas[cursor]->contenido;
			cursor++;
			return (Ñ::Nodo*)l;
		}
		else if(lexemas[cursor]->contenido == "nulo")
		{
			l = new Ñ::Literal(lexemas[cursor]->posición());
			l->tipo = Ñ::CategoríaTipo::TIPO_NADA;
			l->dato = lexemas[cursor]->contenido;
			cursor++;
			return (Ñ::Nodo*)l;
		}
	}
	else if(lexemas[cursor]->categoría == Ñ::CategoríaLexema::LEXEMA_NOTACIÓN)
	{
		Posición* p = lexemas[cursor]->posición();

		if(lexemas[cursor]->contenido == "[")
		{
			cursor++;

			l = new Ñ::Literal(p);

			while(lexemas[cursor]->contenido != "]")
			{
				if(Ñ::Nodo* n = literal())
				{
					l->ramas.push_back(n);
				}
				else
				{
					delete l;
					cursor = c;
					return nullptr;
				}

				if(!notación(","))
				{
					break;
				}
			}
			
			l->tipo = Ñ::CategoríaTipo::TIPO_VECTOR;

			if(!notación("]"))
			{
				delete l;
				cursor = c;
				return nullptr;
			}

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

				Posición* pop = lexemas[cursor]->posición();

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
					Ñ::Nodo* op = (Ñ::Nodo*)(new Ñ::OperaciónBinaria(pop));
					((Ñ::OperaciónBinaria*)op)->operación = operación;
					op->ramas.push_back(cmpN);
					if(ig == nullptr)
					{
						ig = (Ñ::Nodo*)(new Ñ::Igualdad(pop));
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

				Posición* pop = lexemas[cursor]->posición();

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
					Ñ::Nodo* op = (Ñ::Nodo*)(new Ñ::OperaciónBinaria(pop));
					((Ñ::OperaciónBinaria*)op)->operación = operación;
					op->ramas.push_back(tN);
					if(cmp == nullptr)
					{
						cmp = (Ñ::Nodo*)(new Ñ::Comparación(pop));
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

				Posición* pop = lexemas[cursor]->posición();

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
					Ñ::Nodo* op = (Ñ::Nodo*)(new Ñ::OperaciónBinaria(pop));
					((Ñ::OperaciónBinaria*)op)->operación = operación;
					op->ramas.push_back(fN);
					if(t == nullptr)
					{
						t = (Ñ::Nodo*)(new Ñ::Término(pop));
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

				Posición* pop = lexemas[cursor]->posición();

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
					Ñ::Nodo* op = (Ñ::Nodo*)(new Ñ::OperaciónBinaria(pop));
					((Ñ::OperaciónBinaria*)op)->operación = operación;
					op->ramas.push_back(uN);
					if(f == nullptr)
					{
						f = (Ñ::Nodo*)(new Ñ::Factor(pop));
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

Ñ::Nodo* Ñ::Sintaxis::elementoVector()
{
	uint32_t c = cursor;

	if(cursor < lexemas.size())
	{
		Ñ::Nodo* u1;

		if(Ñ::Nodo* prim = primario())
		{
			if(!notación("["))
			{
				return prim;
			}

			if(Ñ::Nodo* lda = ladoDerechoAsignación())
			{
				if(!notación("]"))
				{
					delete lda;
					delete prim;
					cursor = c;
					return nullptr;
				}

				Ñ::ElementoVector* ev = new Ñ::ElementoVector(prim->posición());
				Ñ::Nodo* nev = (Ñ::Nodo*)ev;
				nev->ramas.push_back(prim);
				nev->ramas.push_back(lda);
				return nev;
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
		Posición* pop = lexemas[cursor]->posición();

		if(notación("!"))
		{
			if(Ñ::Nodo* u = operaciónUnaria())
			{
				Ñ::OperaciónUnaria* op = new Ñ::OperaciónUnaria(pop);
				op->operación = "!";
				op->ramas.push_back(u);
				return (Ñ::Nodo*)op;
			}
		}
		else if(notación("-"))
		{
			if(Ñ::Nodo* u = operaciónUnaria())
			{
				Ñ::OperaciónUnaria* op = new Ñ::OperaciónUnaria(pop);
				op->operación = "-";
				op->ramas.push_back(u);
				return (Ñ::Nodo*)op;
			}
		}
		else if(notación("@"))
		{
			if(Ñ::Nodo* u = operaciónUnaria())
			{
				Ñ::OperaciónUnaria* op = new Ñ::OperaciónUnaria(pop);
				op->operación = "@";
				op->ramas.push_back(u);
				return (Ñ::Nodo*)op;
			}
		}
		else if(notación("&"))
		{
			if(Ñ::Nodo* u = operaciónUnaria())
			{
				Ñ::OperaciónUnaria* op = new Ñ::OperaciónUnaria(pop);
				op->operación = "@";
				op->ramas.push_back(u);
				return (Ñ::Nodo*)op;
			}
		}
		else if(Ñ::Nodo* ev = elementoVector())
		{
			return ev;
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
			auto lex = lexemas;
			Ñ::Lexema* lexema = lexemas[cursor];
			Ñ::Posición* pid = lexema->posición();
			Ñ::Identificador* id = new Ñ::Identificador(pid);
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

		Posición* ptp = lexemas[cursor]->posición();

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

		Ñ::Tipo* t = new Ñ::Tipo(ptp);
		t->tipo = tipo;

		if(notación("*"))
		{
			Ñ::Tipo* subT = t;
			t = new Ñ::Tipo(ptp);
			t->tipo = CategoríaTipo::TIPO_PUNTERO;
			t->ramas.push_back((Ñ::Nodo*)subT);
		}
		else
		{
			cursor = c2;
		}

		c2 = cursor;

		if(notación("["))
		{
			uint64_t tamaño = 0;
			if(Ñ::Nodo* lit = literal())
			{
				Ñ::Literal* l = (Ñ::Literal*)lit;
				tamaño = std::stoull(l->dato);
			}

			if(notación("]"))
			{
				Ñ::Tipo* subT = t;
				t = new Ñ::Tipo(ptp);
				t->tipo = CategoríaTipo::TIPO_VECTOR;
				t->tamaño(tamaño);
				t->ramas.push_back((Ñ::Nodo*)subT);
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
		}
		else
		{
			delete t;
			cursor = c;
			return nullptr;
		}

		Ñ::DeclaraVariable* dvar = new Ñ::DeclaraVariable(lexemas[cursor]->posición());

		cursor++;
		
		dvar->ramas.push_back(t);
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
			Posición* pos = lexemas[cursor]->posición();
				
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
					Ñ::Asigna* a = new Ñ::Asigna(pos);
					a->ramas.push_back(lia);
					a->ramas.push_back(lda);

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
		Ñ::Argumentos* args;

		Posición* pargs = lexemas[cursor]->posición();

		if(Ñ::Nodo* arg1 = declaraArgumento())
		{
			args = new Ñ::Argumentos(arg1->posición());
			args->ramas.push_back(arg1);

			while(notación(","))
			{
				Ñ::Nodo* arg2 = declaraArgumento();
				args->ramas.push_back(arg2);
			}

			return (Ñ::Nodo*)args;
		}
		else
		{
			args = new Ñ::Argumentos(pargs);
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
		Ñ::Argumentos* args;

		if(Ñ::Nodo* arg1 = ponArgumento())
		{
			args = new Ñ::Argumentos(arg1->posición());
			args->ramas.push_back(arg1);

			while(notación(","))
			{
				Ñ::Nodo* arg2 = ponArgumento();
				args->ramas.push_back(arg2);
			}

			return (Ñ::Nodo*)args;
		}
		else
		{
			args = new Ñ::Argumentos();
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

		Posición* p = nullptr;

		if(lexemas[cursor]->categoría == Ñ::CategoríaLexema::LEXEMA_IDENTIFICADOR)
		{
			nombre = lexemas[cursor]->contenido;
			p = lexemas[cursor]->posición();
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

		Ñ::LlamaFunción* fn = new Ñ::LlamaFunción(p);
		fn->nombre = nombre;
		fn->ramas.push_back(args);
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
				Ñ::Nodo* dv = (Ñ::Nodo*)(new Ñ::Devuelve(lexemas[cursor]->posición()));
				cursor++;
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
				Posición* p = lexemas[cursor]->posición();
				cursor++;
				
				if(Ñ::Nodo* lda = ladoDerechoAsignación())
				{
					Ñ::Nodo* dv = (Ñ::Nodo*)(new Ñ::Devuelve(p));
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

		Posición* psi = lexemas[cursor]->posición();

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
				sc = new Ñ::SiCondicional(psi);
				sc->ramas.push_back(lda);
				sc->ramas.push_back(blq);
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
					sc->ramas.push_back(blq);
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
					sc->ramas.push_back(lda);
					sc->ramas.push_back(blq);
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
				Ñ::Expresión* ex = new Ñ::Expresión(as->posición());
				ex->ramas.push_back(as);
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
				Ñ::Expresión* ex = new Ñ::Expresión(fn->posición());
				ex->ramas.push_back(fn);
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
				Ñ::Expresión* ex = new Ñ::Expresión(dv->posición());
				ex->ramas.push_back(dv);
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
				Ñ::Expresión* ex = new Ñ::Expresión(v->posición());
				ex->ramas.push_back(v);
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
				Ñ::Expresión* ex = new Ñ::Expresión(dv->posición());
				ex->ramas.push_back(dv);
				return ((Ñ::Nodo*)ex);
			}
			else
			{
				delete dv;
			}
		}
		
		if(Ñ::Nodo* sc = siCondicional())
		{
			Ñ::Expresión* ex = new Ñ::Expresión(sc->posición());
			ex->ramas.push_back(sc);
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
		Posición* pblq = lexemas[cursor]->posición();
		if(!notación("{"))
		{
			cursor = c;
			return nullptr;
		}

		Ñ::Nodo* b = (Ñ::Nodo*)(new Ñ::Bloque(pblq));

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

		Posición* pfn = nullptr;

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
			pfn = id->posición();
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

		dfn = new Ñ::DefineFunción(pfn);
		dfn->nombre = nombreFunción;
		dfn->público = público;
		dfn->ramas.push_back(t);
		dfn->ramas.push_back(args);
		dfn->ramas.push_back(bq);

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

		Posición* pfn = nullptr;

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
			pfn = id->posición();
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

		dcfn = new Ñ::DeclaraFunción(pfn);
		dcfn->nombre = nombreFunción;
		dcfn->externo = externo;
		dcfn->ramas.push_back(t);
		dcfn->ramas.push_back(args);

		return (Ñ::Nodo*)dcfn;
	}

	cursor = c;
	return nullptr;
}

Ñ::Nodo* Ñ::Sintaxis::módulo(std::string nombreMódulo)
{
	uint32_t c = cursor;

	if(cursor < lexemas.size())
	{
		Ñ::Posición* p;
		Ñ::Nodo* m;

		if(lexemas[cursor]->categoría == Ñ::CategoríaLexema::LEXEMA_IDENTIFICADOR && lexemas[cursor]->contenido == "módulo")
		{
			p = lexemas[cursor]->posición();
			m =  (Ñ::Nodo*)new Ñ::Módulo(p);
			cursor++;

			if(lexemas[cursor]->categoría == Ñ::CategoríaLexema::LEXEMA_IDENTIFICADOR)
			{
				((Ñ::Módulo*)m)->módulo = lexemas[cursor]->contenido;

				cursor++;
			}
			else
			{
				((Ñ::Módulo*)m)->módulo = nombreMódulo;
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
		else
		{
			p = new Ñ::Posición;
			m =  (Ñ::Nodo*)new Ñ::Módulo(p);
			((Ñ::Módulo*)m)->módulo = nombreMódulo;
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

Ñ::Nodo* Ñ::Sintaxis::analiza(std::vector<Ñ::Lexema*> _lexemas, std::string nombreArchivo)
{
	cursor = 0;
	lexemas = _lexemas;
	return (Ñ::Nodo*)módulo(nombreArchivo);
}

Ñ::Nodo* Ñ::Sintaxis::analizaComando(std::vector<Ñ::Lexema*> _lexemas)
{
	cursor = 0;
	lexemas = _lexemas;
	return (Ñ::Nodo*)expresión();
}