#include <cctype>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

#include "ñ/ñ.hpp"

// Extiendo nodos para pasar argumentos
#include "nodos.hpp"

bool EJECUTA_INTÉRPRETE = true;

void _muestraTexto(std::string txt)
{
	std::cout << txt << std::endl;
}

std::string _esperaComando()
{
	std::string comando;
	std::cout << "> ";
	std::getline(std::cin, comando);

	return comando;
}

void apaga(Ñ::Argumentos* args)
{
	EJECUTA_INTÉRPRETE = false;
}

void escribe(Ñ::Argumentos* args)
{
	if(args == nullptr)
	{
		return;
	}
	else if(((Ñ::Nodo*)args)->categoría == Ñ::CategoríaNodo::NODO_ARGUMENTOS)
	{
		if(((Ñ::Nodo*)args)->ramas.size() == 0)
		{
			delete args;
			return;
		}
		else if(((Ñ::Nodo*)args)->ramas.size() > 0)
		{
			for(auto arg : ((Ñ::Nodo*)args)->ramas)
			{
				if(arg == nullptr)
				{
					continue;
				}
				else if(arg->categoría == Ñ::CategoríaNodo::NODO_LITERAL)
				{
					std::string dato = ((Ñ::Literal*)arg)->dato;
					std::cout << dato;
				}
				else
				{
					std::cout << "He recibido un Ñ::Nodo* que no es un Literal" << std::endl;
					std::cout << "categoría :: " << arg->categoría << std::endl;
				}
			}
			delete args;
		}
	}
}

void tabla(Ñ::Argumentos* args)
{
	if(args == nullptr)
	{
		return;
	}
	else if(((Ñ::Nodo*)args)->categoría == Ñ::CategoríaNodo::NODO_ARGUMENTOS)
	{
		if(((Ñ::Nodo*)args)->ramas.size() == 0)
		{
			return;
		}
		else if(((Ñ::Nodo*)args)->ramas.size() == 1)
		{
			Ñ::Nodo* arg = ((Ñ::Nodo*)args)->ramas[0];
			if(arg == nullptr)
			{
				return;
			}
			else if(arg->categoría == Ñ::CategoríaNodo::NODO_EXPANDIDO)
			{
				auto tablaSímbolos = ((NTablaSímbolos*)arg)->tablaSímbolos;
				tablaSímbolos->muestra();
			}
		}
	}
}

Ñ::TablaSímbolos* creaTablaSímbolos()
{
	return new Ñ::TablaSímbolos;
}

void llenaTablaSímbolos(Ñ::TablaSímbolos* tablaSímbolos)
{
	// Añado una función
	tablaSímbolos->declaraFunción("escribe");
	tablaSímbolos->defineFunciónEjecutable("escribe", escribe);

	// Añado una función
	tablaSímbolos->declaraFunción("apaga");
	tablaSímbolos->defineFunciónEjecutable("apaga", apaga);

	// Añado una función con un argumento prefijado, ntabla
	tablaSímbolos->declaraFunción("tabla");
	NTablaSímbolos* ntabla = new NTablaSímbolos(tablaSímbolos);
	Ñ::Argumentos* args = new Ñ::Argumentos();
	((Ñ::Nodo*)args)->ramas.push_back((Ñ::Nodo*)ntabla);
	tablaSímbolos->defineFunciónEjecutable("tabla", tabla, (Ñ::Nodo*)args);
}

void _interpretaComando(std::string comando, Ñ::TablaSímbolos* tablaSímbolos)
{
	std::vector<Ñ::Lexema*> lexemas;
	Ñ::Nodo* nodos;

	Ñ::Léxico léxico;
	Ñ::Sintaxis sintaxis;
	
	lexemas = léxico.analiza(comando);

	if(lexemas.empty())
	{
		Ñ::errorConsola(u8"Error durante el análisis léxico, comando incorrecto.");
		return;
	}

	nodos = sintaxis.analiza(lexemas);

	if(nodos == nullptr)
	{
		Ñ::errorConsola(u8"Error durante el análisis sintáctico, comando incorrecto.");
		muestraLexemas(lexemas);
		return;
	}

	Ñ::Resultado resultado = Ñ::analizaSemántica(nodos, tablaSímbolos);

	if(resultado.error())
	{
		std::cout << resultado.mensaje() << std::endl;
		muestraNodos(nodos);
	}
	else
	{
		auto resultado = Ñ::interpretaNodos(nodos, tablaSímbolos);
		if(resultado.error())
		{
			std::cout << resultado.mensaje() << std::endl;
			muestraNodos(nodos);
		}
	}

	for(auto l : lexemas)
	{
		delete l;
	}
	lexemas.clear();
	delete nodos;
}

int main()
{
	Ñ::TablaSímbolos* tablaSímbolos = creaTablaSímbolos();
	llenaTablaSímbolos(tablaSímbolos);

	while (EJECUTA_INTÉRPRETE)
	{
		std::string comando = _esperaComando();
		if(comando.size() == 0)
		{
			continue;
		}
		_interpretaComando(comando, tablaSímbolos);

		std::this_thread::yield();
	}

	delete tablaSímbolos;

	return 0;
}