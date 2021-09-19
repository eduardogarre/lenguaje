#include <cctype>
#include <cstdlib>
#include <exception>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

#include "docopt.h"
#include "ñ/ñ.hpp"
#include "promotor.hpp"

bool EJECUTA_INTÉRPRETE = false;

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

	nodos = sintaxis.analizaComando(lexemas);

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
		return;
	}
	//else
	//{
	//	auto resultado = Ñ::interpretaNodos(nodos, tablaSímbolos);
	//	if(resultado.error())
	//	{
	//		std::cout << resultado.mensaje() << std::endl;
	//		muestraNodos(nodos);
	//	}
	//}

	Ñ::EntornoConstrucción *entorno = new Ñ::EntornoConstrucción;

	resultado = Ñ::construye(nodos, entorno, Ñ::CategoríaNodo::NODO_EXPRESIÓN);
	if(resultado.error())
	{
		std::cout << resultado.mensaje() << std::endl;
		return;
	}

	for(auto l : lexemas)
	{
		delete l;
	}
	lexemas.clear();
	delete nodos;
}

int interpretaEnLínea()
{
	Ñ::TablaSímbolos* tablaSímbolos = new Ñ::TablaSímbolos;

	EJECUTA_INTÉRPRETE = true;

	while (EJECUTA_INTÉRPRETE)
	{
		std::string comando = _esperaComando();
		if(comando.size() == 0)
		{
			continue;
		}
		_interpretaComando(comando, tablaSímbolos);
	}

	delete tablaSímbolos;

	return 0;
}

static const char VERSIÓN[] = u8R"(Ñ 0.1)";

static const char USO[] =
u8R"(Compilador Ñ.

    Usage:
	  ñ
	  ñ <archivo>...
      ñ (-a | --ayuda)
      ñ (-v | --version)

    Options:
      -a --ayuda    Muestra este mensaje
      -v --version  Muestra versión.
)";

void muestraAyuda()
{
	std::cout << USO << std::endl;
}

void muestraVersión()
{
	std::cout << VERSIÓN << std::endl;
}

int main(int argc, char** argv)
{

	if(!(std::numeric_limits< double >::is_iec559))
	{
		std::cout << "Requiero el estándar IEEE 754 para los números reales" << std::endl;
		return -1;
	}

    std::map<std::string, docopt::value> args;
	args = docopt::docopt(USO, { argv + 1, argv + argc }, false);

	if(args["--ayuda"].isBool())
	{
		if(args["--ayuda"].asBool() == true)
		{
			muestraAyuda();
			return 0;
		}
	}

	if(args["--version"].isBool())
	{
		if(args["--version"].asBool() == true)
		{
			muestraVersión();
			return 0;
		}
	}

	if(args["<archivo>"].isStringList())
	{
		std::vector<std::string> archivos = args["<archivo>"].asStringList();

		return Compilador::construyeArchivos(archivos);
	}

	return interpretaEnLínea();
}