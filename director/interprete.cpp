
#include <iostream>
#include <string>

#include "director.hpp"
#include "herramientas.hpp"
#include "interprete.hpp"

namespace Director
{
	std::string esperaComando()
	{
		std::string comando;
		std::cout << "> ";
		std::getline(std::cin, comando);

		return comando;
	}

	void interpretaComando(std::string comando, Ñ::TablaSímbolos *tablaSímbolos, Ñ::EntornoConstrucción *entorno)
	{
		Ñ::Resultado resultado;

		std::vector<Ñ::Lexema *> lexemas;
		Ñ::Nodo *nodos;

		Ñ::Léxico léxico;
		Ñ::Sintaxis sintaxis;

		lexemas = léxico.analiza(comando, entorno);

		if (lexemas.empty())
		{
			Ñ::errorConsola(u8"Error durante el análisis léxico, comando incorrecto.");
			return;
		}

		resultado = sintaxis.analizaComando(lexemas);

		if (resultado.error())
		{
			Ñ::errorConsola(resultado.mensaje());
			muestraLexemas(lexemas);
			return;
		}
		nodos = resultado.nodo();

		Ñ::Resultado rSemántico = Ñ::analizaSemántica(nodos, tablaSímbolos);

		if (rSemántico.error())
		{
			std::cout << rSemántico.mensaje() << std::endl;
			muestraNodos(nodos, tablaSímbolos);
			return;
		}

		Ñ::ResultadoLlvm rConstrucción = Ñ::creaRepresentaciónIntermedia(nodos, entorno, Ñ::CategoríaNodo::NODO_EXPRESIÓN);
		if (rConstrucción.error())
		{
			std::cout << rConstrucción.mensaje() << std::endl;
			return;
		}

		for (auto l : lexemas)
		{
			delete l;
		}
		lexemas.clear();
		delete nodos;
	}

	int interpretaEnLínea(Ñ::Entorno::Configuración cfg)
	{
		Ñ::TablaSímbolos *tablaSímbolos = new Ñ::TablaSímbolos;
		
		Ñ::EntornoConstrucción *entorno = Ñ::Entorno::preparaEntornoConstrucción(cfg);

		Ñ::Entorno::preparaJAT(entorno);

		std::string ruta_biblioteca_estándar = obténCarpetaInstalación() + "/" + biblioteca_estándar;

		std::cout << "Ruta a la biblioteca estándar: '" << ruta_biblioteca_estándar << "'" << std::endl;

		EJECUTA_INTÉRPRETE = true;

		while (EJECUTA_INTÉRPRETE)
		{
			std::string comando = esperaComando();
			std::cout << "Tabla de Símbolos:" << std::endl;
			tablaSímbolos->muestra();
			if (comando.size() == 0)
			{
				continue;
			}
			else if(comando == "sal")
			{
				break;
			}
			interpretaComando(comando, tablaSímbolos, entorno);
		}

		delete tablaSímbolos;

		return 0;
	}

}