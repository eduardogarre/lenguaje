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

#if defined(WIN32) || defined(WIN64)
#include <Windows.h>
#elif defined(UNIX)
#include <unistd.h>
#endif

#include "docopt.h"
#include "ñ/ñ.hpp"

#include "constructor.hpp"
#include "director.hpp"
#include "herramientas.hpp"
#include "interprete.hpp"

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

int main(int argc, char **argv)
{
	if (!(std::numeric_limits<double>::is_iec559))
	{
		std::cout << "Requiero el estándar IEEE 754 para los números reales" << std::endl;
		return -1;
	}

#if defined(WIN32) || defined(WIN64)
	SetConsoleOutputCP(65001); // Página de Códigos de UTF8
#endif

	Director::biblioteca_estándar = "bibñ.lib";

	std::map<std::string, docopt::value> args;
	args = docopt::docopt(USO, {argv + 1, argv + argc}, false);

	if (args["--ayuda"].isBool())
	{
		if (args["--ayuda"].asBool() == true)
		{
			muestraAyuda();
			return 0;
		}
	}

	if (args["--version"].isBool())
	{
		if (args["--version"].asBool() == true)
		{
			muestraVersión();
			return 0;
		}
	}

	Ñ::Entorno::Configuración cfg;

	std::string nombreArchivoDestino = "programa";
	if (args["--salida"].isString())
	{
		cfg.nombreArchivoDestino = args["--salida"].asString();
	}

	uint8_t optimización = 0;
	if (args["-O"].isString())
	{
		std::string opttxt = args["-O"].asString();

		optimización = std::stoi(opttxt.c_str());
	}
	if (optimización > 0)
	{
		cfg.optimización = 1;
	}
	else
	{
		cfg.optimización = 0;
	}

	if (args["--hablador"].isBool())
	{
		cfg.HABLADOR = args["--hablador"].asBool();
	}

	if (args["<archivo>"].isStringList())
	{
		cfg.archivos = args["<archivo>"].asStringList();
		if (cfg.archivos.size() > 0)
		{
			return Director::compila(cfg);
		}
	}

	return Director::interpretaEnLínea(cfg);
}