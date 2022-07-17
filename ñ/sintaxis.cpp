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

void Ñ::Sintaxis::apuntaError(Ñ::Posición* p, std::string error)
{
	if((!últimaPosición) || (p->cursor() > últimaPosición->cursor()))
	{
		delete últimaPosición;
		últimaPosición = new Ñ::Posición;
		*últimaPosición = *p;
		mensajeError = error;
	}
}

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
	else if(lexemas[cursor]->categoría == Ñ::CategoríaLexema::LEXEMA_TEXTO)
	{
		l = new Ñ::Literal(lexemas[cursor]->posición());
		l->tipo = Ñ::CategoríaTipo::TIPO_SERIE;
		l->dato = lexemas[cursor]->contenido;

		const char* texto = l->dato.c_str();
		for(int i = 0; i < strlen(texto); i++)
		{
			Ñ::Literal* sublit = new Ñ::Literal(l->posición());
			sublit->tipo = Ñ::CategoríaTipo::TIPO_NATURAL_8;
			sublit->dato = std::to_string((int)texto[i]);
			l->ramas.push_back(sublit);
		}
		
		// Añado el carácter de fin de cadena
		Ñ::Literal* sublit = new Ñ::Literal(l->posición());
		sublit->tipo = Ñ::CategoríaTipo::TIPO_NATURAL_8;
		sublit->dato = std::to_string(0);
		l->ramas.push_back(sublit);

		cursor++;
		return (Ñ::Nodo*)l;
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
					apuntaError(lexemas[cursor]->posición(), "Esperaba un valor que añadir a la serie.");
					cursor = c;
					return nullptr;
				}

				if(!notación(","))
				{
					break;
				}
			}
			
			l->tipo = Ñ::CategoríaTipo::TIPO_SERIE;

			if(!notación("]"))
			{
				delete l;
				apuntaError(lexemas[cursor - 1]->posición(), "Esperaba ']' al final de la serie.");
				cursor = c;
				return nullptr;
			}

			return (Ñ::Nodo*)l;
		}
	}

	apuntaError(lexemas[cursor]->posición(), "Esperaba un valor literal.");
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
		else if(Ñ::Nodo* ptr = puntero())
		{
			return ptr;
		}
	}

	apuntaError(lexemas[cursor]->posición(), "Esperaba un LIA (lado izquierdo de la asignación).");
	cursor = c;
	return nullptr;
}

Ñ::Nodo* Ñ::Sintaxis::ladoDerechoAsignación()
{
	uint32_t c = cursor;

	if(cursor < lexemas.size())
	{
		Ñ::Nodo* cmp = comparación();
		
		return cmp;
	}

	apuntaError(lexemas[cursor]->posición(), "Esperaba un LDA (lado derecho de la asignación).");
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
						goto operacionEncontrada;
					}
					else
					{
						operación = ">";
						goto operacionEncontrada;
					}
				}
				else if(notación("<"))
				{
					if(notación("="))
					{
						operación = "<=";
						goto operacionEncontrada;
					}
					else
					{
						operación = "<";
						goto operacionEncontrada;
					}
				}
				else
				{
					cursor = cN;
				}

				if(notación("!"))
				{
					if(notación("="))
					{
						operación = "!=";
						goto operacionEncontrada;
					}
					else
					{
						cursor = cN;
					}
				}
				else
				{
					cursor = cN;
				}
				
				if(notación("="))
				{
					if(notación("="))
					{
						operación = "==";
						goto operacionEncontrada;
					}
					else
					{
						cursor = cN;
					}
				}
				else
				{
					cursor = cN;
				}

				cursor = cN;
				
				if(cursor == cN) // Si no hemos avanzado
				{
					break;
				}

				operacionEncontrada:

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
					apuntaError(lexemas[cursor]->posición(), "Esperaba un 'término' a la derecha de la operación '" + operación + "'.");
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

	apuntaError(lexemas[cursor]->posición(), "Esperaba una 'comparación'.");
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
					apuntaError(lexemas[cursor]->posición(), "Esperaba un 'factor' a la derecha de la operación '" + operación + "'.");
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

	apuntaError(lexemas[cursor]->posición(), "Esperaba un 'término'.");
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
				else if(notación("%"))
				{
					operación = "%";
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
					apuntaError(lexemas[cursor]->posición(), "Esperaba una 'operación unaria' a la derecha de la operación '" + operación + "'.");
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

	apuntaError(lexemas[cursor]->posición(), "Esperaba un 'factor'.");
	cursor = c;
	return nullptr;
}

Ñ::Nodo* Ñ::Sintaxis::elementoSerie()
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
					apuntaError(lexemas[cursor - 1]->posición(), "Esperaba ']'.");
					cursor = c;
					return nullptr;
				}

				Ñ::ElementoSerie* ev = new Ñ::ElementoSerie(prim->posición());
				Ñ::Nodo* nev = (Ñ::Nodo*)ev;
				nev->ramas.push_back(prim);
				nev->ramas.push_back(lda);
				return nev;
			}
		}
	}

	apuntaError(lexemas[cursor]->posición(), "Esperaba un 'elemento serie'.");
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
		else if(notación("*"))
		{
			if(Ñ::Nodo* u = operaciónUnaria())
			{
				Ñ::OperaciónUnaria* op = new Ñ::OperaciónUnaria(pop);
				op->operación = "*";
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
		else if(Ñ::Nodo* ev = elementoSerie())
		{
			return ev;
		}
	}

	apuntaError(lexemas[cursor]->posición(), "Esperaba una 'operación unaria'.");
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
					apuntaError(lexemas[cursor]->posición(), "Esperaba ')'.");
					cursor = c;
					return nullptr;
				}
			}

			apuntaError(lexemas[cursor]->posición(), "Esperaba un LDA (lado derecho de la asignación).");
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
			apuntaError(lexemas[cursor]->posición(), "Esperaba un 'primario'.");
			cursor = c;
			return nullptr;
		}
	}

	apuntaError(lexemas[cursor]->posición(), "Esperaba un 'primario'.");
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

	apuntaError(lexemas[cursor]->posición(), "Esperaba un 'identificador'.");
	cursor = c;
	return nullptr;
}

Ñ::Nodo* Ñ::Sintaxis::puntero()
{
	uint32_t c = cursor;

	if(cursor < lexemas.size())
	{
		Ñ::Posición* p = lexemas[cursor]->posición();

		if(notación("*"))
		{
			Ñ::Puntero* ptr;

			if(Ñ::Nodo* id = identificador())
			{
				ptr = new Ñ::Puntero(p);
				ptr->ramas.push_back(id);
				return ptr;
			}
		}
	}

	apuntaError(lexemas[cursor]->posición(), "Esperaba un '*'.");
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
				apuntaError(lexemas[cursor]->posición(), "Esperaba un tipo válido.");
				cursor = c;
				return nullptr;
			}
		}
		else
		{
			apuntaError(lexemas[cursor]->posición(), "Esperaba un tipo.");
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
				t->tipo = CategoríaTipo::TIPO_SERIE;
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

	apuntaError(lexemas[cursor]->posición(), "Esperaba un tipo.");
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
			apuntaError(lexemas[cursor]->posición(), "Esperaba un tipo.");
			cursor = c;
			return nullptr;
		}
		
		if(cursor >= lexemas.size())
		{
			delete t;
			apuntaError(lexemas[cursor]->posición(), "Esperaba un identificador, pero he llegado al final del archivo.");
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
			apuntaError(lexemas[cursor]->posición(), "Esperaba un identificador.");
			cursor = c;
			return nullptr;
		}

		Ñ::DeclaraVariable* dvar = new Ñ::DeclaraVariable(lexemas[cursor]->posición());

		cursor++;
		
		dvar->ramas.push_back(t);
		dvar->variable = v;
		return ((Ñ::Nodo*)dvar);
	}

	apuntaError(lexemas[cursor]->posición(), "Esperaba una declaración de variable.");
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
					apuntaError(lexemas[cursor]->posición(), "Esperaba una asignación '=' pero has escrito una comparación '=='.");
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

	apuntaError(lexemas[cursor]->posición(), "Esperaba una asignación.");
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

	apuntaError(lexemas[cursor]->posición(), "Esperaba una declaración de un argumento.");
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

	apuntaError(lexemas[cursor]->posición(), "Esperaba declaraciones de argumentos.");
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

	apuntaError(lexemas[cursor]->posición(), "Esperaba que pusieras un argumento.");
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

	apuntaError(lexemas[cursor]->posición(), "Esperaba que pusieras argumentos.");
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
			apuntaError(lexemas[cursor]->posición(), "Esperaba el identificador de la función a la que quieres llamar.");
			cursor = c;
			return nullptr;
		}

		if(!notación("("))
		{
			apuntaError(lexemas[cursor]->posición(), "Esperaba encontrar '(' para pasar los argumentos a la llamada a la función.");
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
			apuntaError(lexemas[cursor - 1]->posición(), "Esperaba encontrar ')' al final de la llamada a la función.");
			cursor = c;
			return nullptr;
		}

		Ñ::LlamaFunción* fn = new Ñ::LlamaFunción(p);
		fn->nombre = nombre;
		fn->ramas.push_back(args);
		return (Ñ::Nodo*)fn;
	}

	apuntaError(lexemas[cursor]->posición(), "Esperaba una llamada a una función.");
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

	apuntaError(lexemas[cursor]->posición(), "Esperaba 'vuelve'.");
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

	apuntaError(lexemas[cursor]->posición(), "Esperaba 'devuelve'.");
	cursor = c;
	return nullptr;
}

Ñ::Nodo* Ñ::Sintaxis::para()
{
	uint32_t c = cursor;

	if(cursor < lexemas.size())
	{
		if(lexemas[cursor]->categoría == Ñ::CategoríaLexema::LEXEMA_RESERVADO)
		{
			if(lexemas[cursor]->contenido == "para")
			{
				Ñ::Nodo* para = (Ñ::Nodo*)(new Ñ::ParaBucle(lexemas[cursor]->posición()));
				cursor++;
				return para;
			}
		}
	}

	apuntaError(lexemas[cursor]->posición(), "Esperaba 'para'.");
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
			apuntaError(lexemas[cursor]->posición(), "Esperaba 'si'.");
			cursor = c;
			return nullptr;
		}

		if(!notación("("))
		{
			apuntaError(lexemas[cursor]->posición(), "Esperaba encontrar '(' para colocar la expresión condicional del 'si()'.");
			cursor = c;
			return nullptr;
		}

		if(Ñ::Nodo* lda = ladoDerechoAsignación())
		{
			if(!notación(")"))
			{
				delete lda;
				apuntaError(lexemas[cursor]->posición(), "Esperaba encontrar ')' al final de la expresión condicional del 'si()'.");
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
				apuntaError(lexemas[cursor]->posición(), "Esperaba un bloque de código condicional del 'si()'.");
				cursor = c;
				return nullptr;
			}
		}
		else
		{
			apuntaError(lexemas[cursor]->posición(), "Esperaba una expresión de comparación válida para el 'si()'.");
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
					apuntaError(lexemas[cursor]->posición(), "Esperaba un bloque de código condicional del 'sino si()'.");
					cursor = c;
					return nullptr;
				}
			}

			if(!notación("("))
			{
				delete sc;
				apuntaError(lexemas[cursor]->posición(), "Esperaba encontrar '(' para colocar la expresión condicional del 'sino si()'.");
				cursor = c;
				return nullptr;
			}

			if(Ñ::Nodo* lda = ladoDerechoAsignación())
			{
				if(!notación(")"))
				{
					delete lda;
					delete sc;
					apuntaError(lexemas[cursor]->posición(), "Esperaba encontrar ')' al final de la expresión condicional del 'sino si()'.");
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
					apuntaError(lexemas[cursor]->posición(), "Esperaba un bloque de código.");
					cursor = c;
					return nullptr;
				}
			}
			else
			{
				delete sc;
				apuntaError(lexemas[cursor]->posición(), "Esperaba una expresión de comparación válida para el 'si()'.");
				cursor = c;
				return nullptr;
			}
		}

		return (Ñ::Nodo*)sc;
	}

	apuntaError(lexemas[cursor]->posición(), "Esperaba un si() condicional.");
	cursor = c;
	return nullptr;
}

Ñ::Nodo* Ñ::Sintaxis::bucleMientras()
{
	uint32_t c = cursor;

	if(cursor < lexemas.size())
	{
		Ñ::BucleMientras* bm = nullptr;

		Posición* pmi = lexemas[cursor]->posición();

		if(!reservada("mientras"))
		{
			apuntaError(lexemas[cursor]->posición(), "Esperaba 'mientras()'.");
			cursor = c;
			return nullptr;
		}

		if(!notación("("))
		{
			apuntaError(lexemas[cursor]->posición(), "Esperaba encontrar '(' para colocar la expresión condicional del 'mientras()'.");
			cursor = c;
			return nullptr;
		}

		if(Ñ::Nodo* lda = ladoDerechoAsignación())
		{
			if(!notación(")"))
			{
				delete lda;
				apuntaError(lexemas[cursor]->posición(), "Esperaba encontrar ')' al final de la expresión condicional del 'mientras()'.");
				cursor = c;
				return nullptr;
			}

			if(Ñ::Nodo* blq = bloque())
			{
				bm = new Ñ::BucleMientras(pmi);
				bm->ramas.push_back(lda);
				bm->ramas.push_back(blq);
			}
			else
			{
				delete lda;
				apuntaError(lexemas[cursor]->posición(), "Esperaba el bloque para el bucle 'mientras()'.");
				cursor = c;
				return nullptr;
			}
		}
		else
		{
			apuntaError(lexemas[cursor]->posición(), "Esperaba una expresión de comparación válida.");
			cursor = c;
			return nullptr;
		}

		return (Ñ::Nodo*)bm;
	}

	apuntaError(lexemas[cursor]->posición(), "Esperaba un bucle 'mientras()'.");
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
				apuntaError(lexemas[cursor - 1]->posición(), "Esperaba que la expresión terminara con ';'.");
				cursor = c;
				return nullptr;
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
				apuntaError(lexemas[cursor - 1]->posición(), "Esperaba que la expresión terminara con ';'.");
				cursor = c;
				return nullptr;
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
				apuntaError(lexemas[cursor - 1]->posición(), "Esperaba que la expresión terminara con ';'.");
				cursor = c;
				return nullptr;
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
				apuntaError(lexemas[cursor - 1]->posición(), "Esperaba que la expresión terminara con ';'.");
				cursor = c;
				return nullptr;
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
				apuntaError(lexemas[cursor - 1]->posición(), "Esperaba que la expresión terminara con ';'.");
				cursor = c;
				return nullptr;
			}
		}
		
		if(Ñ::Nodo* pa = para())
		{
			if(notación(";"))
			{
				Ñ::Expresión* ex = new Ñ::Expresión(pa->posición());
				ex->ramas.push_back(pa);
				return ((Ñ::Nodo*)ex);
			}
			else
			{
				delete pa;
				apuntaError(lexemas[cursor - 1]->posición(), "Esperaba que la expresión terminara con ';'.");
				cursor = c;
				return nullptr;
			}
		}
		
		if(Ñ::Nodo* sc = siCondicional())
		{
			Ñ::Expresión* ex = new Ñ::Expresión(sc->posición());
			ex->ramas.push_back(sc);
			return ((Ñ::Nodo*)ex);
		}
		
		if(Ñ::Nodo* bm = bucleMientras())
		{
			Ñ::Expresión* ex = new Ñ::Expresión(bm->posición());
			ex->ramas.push_back(bm);
			return ((Ñ::Nodo*)ex);
		}
	}

	apuntaError(lexemas[cursor]->posición(), "Esperaba una expresión.");
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
			apuntaError(lexemas[cursor]->posición(), "Esperaba que empezara un bloque de código con '{'.");
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
			apuntaError(lexemas[cursor]->posición(), "Esperaba que se cerrara un bloque de código con '}'.");
			delete b;
			cursor = c;
			return nullptr;
		}
	}

	apuntaError(lexemas[cursor]->posición(), "Esperaba un bloque de código.");
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
			apuntaError(lexemas[cursor]->posición(), "Esperaba un tipo.");
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
			apuntaError(lexemas[cursor]->posición(), "Esperaba un identificador.");
			cursor = c;
			return nullptr;
		}

		if(!notación("("))
		{
			apuntaError(lexemas[cursor]->posición(), "Esperaba '('.");
			cursor = c;
			return nullptr;
		}

		args = declaraArgumentos();

		if(!notación(")"))
		{
			apuntaError(lexemas[cursor]->posición(), "Esperaba ')'.");
			cursor = c;
			return nullptr;
		}

		if(bq = bloque())
		{

		}
		else
		{
			delete t;
			apuntaError(lexemas[cursor]->posición(), "Esperaba un bloque de código.");
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

	apuntaError(lexemas[cursor]->posición(), "Esperaba una definición de función.");
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
			apuntaError(lexemas[cursor]->posición(), "Esperaba un tipo.");
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
			apuntaError(lexemas[cursor]->posición(), "Esperaba un identificador.");
			cursor = c;
			return nullptr;
		}

		if(!notación("("))
		{
			delete t;
			apuntaError(lexemas[cursor]->posición(), "Esperaba '('.");
			cursor = c;
			return nullptr;
		}

		args = declaraArgumentos();

		if(!notación(")"))
		{
			delete t;
			apuntaError(lexemas[cursor]->posición(), "Esperaba ')'.");
			cursor = c;
			return nullptr;
		}

		if(!notación(";"))
		{
			delete t;
			apuntaError(lexemas[cursor - 1]->posición(), "Esperaba que la expresión terminara con ';'.");
			cursor = c;
			return nullptr;
		}

		if(Ñ::Nodo* bq = bloque())
		{
			delete t, bq;
			apuntaError(lexemas[cursor]->posición(), "Esperaba un bloque.");
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

	apuntaError(lexemas[cursor]->posición(), "Esperaba una declaración de función.");
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
				apuntaError(lexemas[cursor - 1]->posición(), "Esperaba ';' al final de la declaración del módulo.");
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

	apuntaError(lexemas[cursor]->posición(), "Error general en la sintaxis del módulo.");
	cursor = c;
	return nullptr;
}

Ñ::Resultado Ñ::Sintaxis::analiza(std::vector<Ñ::Lexema*> _lexemas, std::string nombreArchivo)
{
	Ñ::Resultado resultado;
	cursor = 0;
	lexemas = _lexemas;
	auto rNodo = (Ñ::Nodo*)módulo(nombreArchivo);

	// Compruebo que el cursor ha llegado al penúltimo lexema
	if(cursor == _lexemas.size() - 1)
	{
		éxito = true;
	}
	
	if(éxito && rNodo)
	{
		resultado.éxito();
		resultado.nodo(rNodo);
		return resultado;
	}
	else
	{
		if(rNodo)
		{
			delete rNodo;
		}
		resultado.error(mensajeError);
		resultado.posición(últimaPosición);
		return resultado;
	}
}

Ñ::Resultado Ñ::Sintaxis::analizaComando(std::vector<Ñ::Lexema*> _lexemas)
{
	Ñ::Resultado resultado;
	cursor = 0;
	lexemas = _lexemas;
	auto rNodo = (Ñ::Nodo*)expresión();
	
	if(éxito && rNodo)
	{
		resultado.éxito();
		resultado.nodo(rNodo);
		return resultado;
	}
	else
	{
		if(rNodo)
		{
			delete rNodo;
		}
		resultado.error(mensajeError);
		resultado.posición(últimaPosición);
		return resultado;
	}
}