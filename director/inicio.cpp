/*
SPDX-License-Identifier: MPL-2.0-no-copyleft-exception

This Source Code Form is subject to the terms of the Mozilla Public License, v.
2.0. If a copy of the MPL was not distributed with this file, You can obtain one
at http://mozilla.org/MPL/2.0/.

This Source Code Form is "Incompatible With Secondary Licenses", as defined by
the Mozilla Public License, v. 2.0.

Copyright © 2021 Eduardo Garre Muñoz
*/

#include <cctype>
#include <cstdlib>
#include <exception>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

#include "configuracion.hpp"
#include "docopt.h"
#include "compilador/ñ.hpp"
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
	Ñ::EntornoConstrucción *entorno = new Ñ::EntornoConstrucción;
	Ñ::Resultado resultado;

	std::vector<Ñ::Lexema*> lexemas;
	Ñ::Nodo* nodos;

	Ñ::Léxico léxico;
	Ñ::Sintaxis sintaxis;
	
	lexemas = léxico.analiza(comando, entorno);

	if(lexemas.empty())
	{
		Ñ::errorConsola(u8"Error durante el análisis léxico, comando incorrecto.");
		return;
	}

	resultado = sintaxis.analizaComando(lexemas);

	if(resultado.error())
	{
		Ñ::errorConsola(resultado.mensaje());
		muestraLexemas(lexemas);
		return;
	}
	nodos = resultado.nodo();

	Ñ::Resultado rSemántico = Ñ::analizaSemántica(nodos, tablaSímbolos);

	if(rSemántico.error())
	{
		std::cout << rSemántico.mensaje() << std::endl;
		muestraNodos(nodos, tablaSímbolos);
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

	Ñ::ResultadoLlvm rConstrucción = Ñ::construye(nodos, entorno, Ñ::CategoríaNodo::NODO_EXPRESIÓN);
	if(rConstrucción.error())
	{
		std::cout << rConstrucción.mensaje() << std::endl;
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

static const char VERSIÓN[] = u8R"(Ñ 0.0.1)";

static const char USO[] = 
u8R"(Ñ 0.0.1 - Compilador del lenguaje de programación Ñ

Uso:
 ñ
 ñ <archivo>... [--salida <nombre>] [--hablador] [-O=<nivel>]
 ñ --ayuda
 ñ --version
Opciones:
 -a, --ayuda                      Muestra este mensaje.
 -h, --hablador                   Muestra mensajes sobre el funcionamiento interno.
 -O=<nivel>                       Escoge el nivel de optimización. [predefinido: 0]
 -s=<nombre>, --salida=<nombre>   Pon nombre al archivo generado.
 -v, --version                    Muestra versión.
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

	Director::Configuración cfg;

	std::string nombreArchivoDestino = "programa";
	if(args["--salida"].isString())
	{
		cfg.nombreArchivoDestino = args["--salida"].asString();
	}

	uint8_t optimización = 0;
	if(args["-O"].isString())
	{
		std::string opttxt = args["-O"].asString();

		optimización = std::stoi(opttxt.c_str());
	}
	if(optimización > 0)
	{
		cfg.optimización = 1;
	}
	else
	{
		cfg.optimización = 0;
	}

	if(args["--hablador"].isBool())
	{
		cfg.HABLADOR = args["--hablador"].asBool();
	}

	if(args["<archivo>"].isStringList())
	{
		cfg.archivos = args["<archivo>"].asStringList();

		return Director::compila(cfg);
	}

	return interpretaEnLínea();
}