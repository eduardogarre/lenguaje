#include <cctype>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

#include "ñ/ñ.hpp"

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

void apaga()
{
	EJECUTA_INTÉRPRETE = false;
}

void escribe()
{
    std::cout << "hola" << std::endl;
}

std::map<std::string, Ñ::Símbolo> creaTablaSímbolos()
{
    std::map<std::string, Ñ::Símbolo> tablaSímbolos = *(new std::map<std::string, Ñ::Símbolo>());

    Ñ::Símbolo s1;
    s1.añadeEjecución(escribe);
    tablaSímbolos["escribe"] = s1;

	Ñ::Símbolo s2;
	s2.añadeEjecución(apaga);
	tablaSímbolos["apaga"] = s2;

	return tablaSímbolos;
}

void _interpretaComando(std::string comando, std::map<std::string, Ñ::Símbolo>& tablaSímbolos)
{
	std::vector<Ñ::Lexema*> lexemas;
	Ñ::Nodo* nodos;
	
	lexemas = Ñ::analizaLéxico(comando);

	if(lexemas.empty())
	{
		Ñ::errorConsola(u8"Error durante el análisis léxico, comando incorrecto.");
		return;
	}

	//muestraLexemas(lexemas);

	nodos = Ñ::analizaSintaxis(lexemas);

	if(nodos == nullptr)
	{
		Ñ::errorConsola(u8"Error durante el análisis sintáctico, comando incorrecto.");
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
		//std::cout << "Ejecuto nodos2" << std::endl;

		auto resultado = Ñ::interpretaNodos(nodos, tablaSímbolos);
		if(resultado.error())
		{
			std::cout << resultado.mensaje() << std::endl;
		}
	}

	Ñ::muestraTablaSímbolos(tablaSímbolos);

	delete nodos;
}

int main()
{
	std::map<std::string, Ñ::Símbolo> tablaSímbolos = creaTablaSímbolos();

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

	return 0;
}