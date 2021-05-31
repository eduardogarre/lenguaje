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

Ñ::Nodo* FunciónEscribe(Ñ::Nodo* yo, Ñ::Nodo* args)
{
	if(args != nullptr)
	{
		if(args->ramas.size() > 0)
		{
			for(Ñ::Nodo* n : args->ramas)
			{
				if(n->categoría == Ñ::CategoríaNodo::NODO_VALOR)
				{
					Ñ::Valor* valor = (Ñ::Valor*)n;

					switch (valor->obténTipo())
					{
					case Ñ::CategoríaTipo::TIPO_NADA:
						break;
					
					case Ñ::CategoríaTipo::TIPO_BOOLEANO:
						if(valor->booleano())
						{
							std::cout << "cierto";
						}
						else
						{
							std::cout << "falso";
						}
						break;
					
					case Ñ::CategoríaTipo::TIPO_NATURAL_64:
						std::cout << valor->nat64();
						break;
					
					case Ñ::CategoríaTipo::TIPO_ENTERO_64:
						std::cout << valor->ent64();
						break;
					
					case Ñ::CategoríaTipo::TIPO_REAL_64:
						std::cout << valor->real64();
						break;
					
					case Ñ::CategoríaTipo::TIPO_TEXTO:
						std::cout << valor->texto();
						break;
					
					default:
						break;
					}
				}
			}
		}
	}
	
	return nullptr;
}

Ñ::Nodo* FunciónApaga(Ñ::Nodo* yo, Ñ::Nodo* args)
{
	if(EJECUTA_INTÉRPRETE)
	{
		EJECUTA_INTÉRPRETE = false;
	}
	else
	{
		exit(0);
	}
	
	return nullptr;
}

Ñ::TablaSímbolos* creaTablaSímbolos()
{
	Ñ::TablaSímbolos* tabla = new Ñ::TablaSímbolos;
	tabla->defineFunciónEjecutable("escribe", FunciónEscribe);
	tabla->defineFunciónEjecutable("apaga", FunciónApaga);
	return tabla;
}

void _interpretaArchivo(std::string código, Ñ::TablaSímbolos* tablaSímbolos)
{
	std::vector<Ñ::Lexema*> lexemas;
	Ñ::Nodo* nodos;

	Ñ::Léxico léxico;
	Ñ::Sintaxis sintaxis;
	
	lexemas = léxico.analiza(código);

	if(lexemas.empty())
	{
		Ñ::errorConsola(u8"Error durante el análisis léxico, código incorrecto.");
		return;
	}

	nodos = sintaxis.analiza(lexemas);

	if(nodos == nullptr)
	{
		Ñ::errorConsola(u8"Error durante el análisis sintáctico, código incorrecto.");
		muestraLexemas(lexemas);
		return;
	}

	Ñ::TablaSímbolos* tablaSímbolosSemántica = creaTablaSímbolos();
	Ñ::Resultado resultado = Ñ::analizaSemántica(nodos, tablaSímbolosSemántica);
	delete tablaSímbolosSemántica;

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

int interpretaArchivo(std::string txt)
{
	Ñ::TablaSímbolos* tablaSímbolos = creaTablaSímbolos();

	_interpretaArchivo(txt, tablaSímbolos);

	delete tablaSímbolos;

	return 0;
}

int interpretaEnLínea()
{
	Ñ::TablaSímbolos* tablaSímbolos = creaTablaSímbolos();

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
	  ñ <archivo>
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

std::string leeArchivo(std::filesystem::path archivo)
{
    // Open the stream to 'lock' the file.
    std::ifstream arc(archivo, std::ios::in | std::ios::binary);

    // Obtain the size of the file.
    const auto tamaño = std::filesystem::file_size(archivo);

    // Create a buffer.
    std::string resultado(tamaño, '\0');

    // Read the whole file into the buffer.
    arc.read(resultado.data(), tamaño);

    return resultado;
}

int main(int argc, char** argv)
{
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

	if(args["<archivo>"].isString())
	{
		std::string archivo = args["<archivo>"].asString();
		std::string contenido = "";

		try{
			contenido = leeArchivo(archivo);
		}
		catch (std::exception& e)
		{
			std::cout << "Error al leer el archivo" << '\n';
		}

		return interpretaArchivo(contenido);
	}

	return interpretaEnLínea();
}