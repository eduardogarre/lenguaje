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
Ñ::Nodo* ladoDerechoAsignación();
Ñ::Nodo* declaraVariable();
Ñ::Nodo* asigna();
Ñ::Nodo* llamaFunción();
Ñ::Nodo* expresión();
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

Ñ::Nodo* literal()
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

Ñ::Nodo* ladoDerechoAsignación()
{
	//std::cout << "opSumaResta()" << std::endl;
	//std::cout << "cursor[" << cursor << "]" << std::endl;

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
	//std::cout << "opSumaResta()" << std::endl;
	//std::cout << "cursor[" << cursor << "]" << std::endl;

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
			
			//std::cout << "[operación:" << operación << "]" << std::endl;
			
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
	//std::cout << "opMultiplicaciónDivisión()" << std::endl;
	//std::cout << "cursor[" << cursor << "]" << std::endl;

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
			
			//std::cout << "[operación:" << operación << "]" << std::endl;
			
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
	//std::cout << "factor()" << std::endl;
	//std::cout << "cursor[" << cursor << "]" << std::endl;

	uint32_t c = cursor;

	if(cursor < lexemas.size())
	{
		std::string factor;

		if(Ñ::Nodo* lit = literal())
		{
			//std::cout << "[subexpresión]" << std::endl;
			return lit;
		}
		else if(notación("("))
		{
			Ñ::Nodo* lda;

			if(lda = ladoDerechoAsignación())
			{
				if(notación(")"))
				{
					//std::cout << "[subexpresión]" << std::endl;
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
			//std::cout << "[subexpresión]" << std::endl;
			return fn;
		}
		else if(Ñ::Nodo* id = identificador())
		{
			//std::cout << "[subexpresión]" << std::endl;
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
			return (Ñ::Nodo*)id;
		}
	}

	cursor = c;
	return nullptr;
}

Ñ::Nodo* tipo()
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
	//std::cout << "declaraVariable()" << std::endl;
	//std::cout << "cursor[" << cursor << "]" << std::endl;

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
		((Ñ::Nodo*)dvar)->ramas.push_back(t);
		dvar->variable = v;
		return ((Ñ::Nodo*)dvar);
	}

	cursor = c;
	return nullptr;
}

Ñ::Nodo* asigna()
{
	//std::cout << "asigna() - cursor[" << cursor << "]" << std::endl;

	uint32_t c = cursor;

	if(cursor < lexemas.size())
	{
		//std::cout << "cursor[" << cursor << "]" << std::endl;

		if(Ñ::Nodo* dv = declaraVariable())
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

				if(Ñ::Nodo* lda = ladoDerechoAsignación())
				{
					//std::cout << "LadoDerechoAsignación - cursor[" << cursor << "]" << std::endl;

					Ñ::Asigna* a = new Ñ::Asigna();
					((Ñ::Nodo*)a)->ramas.push_back(dv);
					((Ñ::Nodo*)a)->ramas.push_back(lda);

					return ((Ñ::Nodo*)a);
				}

				//std::cout << "no es una asignación a una declaración" << std::endl;
			}
			
			delete dv;
		}
		else if(Ñ::Nodo* id = identificador())
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

				if(Ñ::Nodo* lda = ladoDerechoAsignación())
				{
					//std::cout << "LadoDerechoAsignación - cursor[" << cursor << "]" << std::endl;

					Ñ::Asigna* a = new Ñ::Asigna();
					((Ñ::Nodo*)a)->ramas.push_back(id);
					((Ñ::Nodo*)a)->ramas.push_back(lda);

					return ((Ñ::Nodo*)a);
				}

				//std::cout << "no es una asignación" << std::endl;
			}
			
			delete id;
		}
	}

	cursor = c;
	return nullptr;
}

Ñ::Nodo* llamaFunción()
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
		return (Ñ::Nodo*)fn;
	}

	cursor = c;
	return nullptr;
}

Ñ::Nodo* expresión()
{
	//std::cout << "expresión()" << std::endl;
	//std::cout << "cursor[" << cursor << "]" << std::endl;

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