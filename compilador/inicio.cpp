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

void apaga(void* arg)
{
	EJECUTA_INTÉRPRETE = false;
}

void escribe(void* arg)
{
    std::cout << "hola" << std::endl;
}

void tabla(void* arg)
{
	auto tablaSímbolos = (std::map<std::string, Ñ::Símbolo>*)arg;
	Ñ::muestraTablaSímbolos(*tablaSímbolos);
}

std::map<std::string, Ñ::Símbolo>* creaTablaSímbolos()
{
	return new std::map<std::string, Ñ::Símbolo>();
}

void llenaTablaSímbolos(std::map<std::string, Ñ::Símbolo>* tablaSímbolos)
{
    Ñ::Símbolo s1;
    s1.añadeEjecución(escribe);
    (*tablaSímbolos)["escribe"] = s1;

	Ñ::Símbolo s2;
	s2.añadeEjecución(apaga);
	(*tablaSímbolos)["apaga"] = s2;

	Ñ::Símbolo s3;
	s3.añadeEjecución(tabla, tablaSímbolos);
	(*tablaSímbolos)["tabla"] = s3;
}

void _interpretaComando(std::string comando, std::map<std::string, Ñ::Símbolo>* tablaSímbolos)
{
	std::vector<Ñ::Lexema*> lexemas;
	Ñ::Nodo* nodos;
	
	lexemas = Ñ::analizaLéxico(comando);

	if(lexemas.empty())
	{
		Ñ::errorConsola(u8"Error durante el análisis léxico, comando incorrecto.");
		return;
	}

	nodos = Ñ::analizaSintaxis(lexemas);

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
		//std::cout << "Ejecuto nodos2" << std::endl;

		auto resultado = Ñ::interpretaNodos(nodos, tablaSímbolos);
		if(resultado.error())
		{
			std::cout << resultado.mensaje() << std::endl;
		}
	}

	delete nodos;
}

int main()
{
	std::map<std::string, Ñ::Símbolo>* tablaSímbolos = creaTablaSímbolos();
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

	return 0;
}