#include <cctype>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

#include "apoyo.hpp"
#include "lexema.hpp"
#include "lexico.hpp"
#include "nodo.hpp"
#include "salida.hpp"
#include "sintaxis.hpp"


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

void _interpretaComando(std::string comando)
{
	std::vector<Ñ::Lexema*> lexemas;
	Ñ::Nodo* nodos;
	
	lexemas = Ñ::analizaLéxico(comando);

	if(lexemas.empty())
	{
		Ñ::errorConsola("Error durante el análisis léxico, comando incorrecto.");
		return;
	}

	//muestraLexemas(lexemas);

	nodos = Ñ::analizaSintaxis(lexemas);

	if(nodos == nullptr)
	{
		Ñ::errorConsola("Error durante el análisis sintáctico, comando incorrecto.");
		return;
	}

	muestraNodos(nodos);

	delete nodos;
}

int main()
{
	while (true)
	{
		std::string comando = _esperaComando();
		_interpretaComando(comando);

		std::this_thread::yield();
	}

	return 0;
}