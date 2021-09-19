#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "llvm/Support/Host.h"
#include "llvm/Support/TargetRegistry.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Target/TargetMachine.h"

#include "promotor.hpp"
#include "ñ/ñ.hpp"

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

Ñ::ResultadoLlvm construyeArchivo(std::string archivo, Ñ::EntornoConstrucción *entorno)
{
	Ñ::ResultadoLlvm resultado;

	std::string código = "";

	try{
		código = leeArchivo(archivo);
	}
	catch (std::exception& e)
	{
		std::cout << "Error al leer el archivo" << '\n';
	}

	std::vector<Ñ::Lexema*> lexemas;
	Ñ::Nodo* nodos;

	Ñ::Léxico léxico;
	Ñ::Sintaxis sintaxis;
	
	lexemas = léxico.analiza(código);

	if(lexemas.empty())
	{
		Ñ::errorConsola(u8"Error durante el análisis léxico, código incorrecto.");
		
		for(auto l : lexemas)
		{
			delete l;
		}
		lexemas.clear();

		resultado.error("Error durante el análisis léxico, código incorrecto.");
		return resultado;
	}

	nodos = sintaxis.analiza(lexemas, archivo);

	if(nodos == nullptr)
	{
		Ñ::errorConsola(u8"Error durante el análisis sintáctico, código incorrecto.");
		muestraLexemas(lexemas);

		for(auto l : lexemas)
		{
			delete l;
		}
		lexemas.clear();

		resultado.error("Error durante el análisis sintáctico, código incorrecto.");
		return resultado;
	}

	Ñ::TablaSímbolos* tablaSímbolos = new Ñ::TablaSímbolos;
	Ñ::Resultado rSemántico = Ñ::analizaSemántica(nodos, tablaSímbolos);
	delete tablaSímbolos;

	if(rSemántico.error())
	{
		std::cout << rSemántico.mensaje() << std::endl;
		muestraNodos(nodos);
	
		for(auto l : lexemas)
		{
			delete l;
		}
		lexemas.clear();
		delete nodos;
		
		resultado.error(rSemántico.mensaje());
		return resultado;
	}
	else
	{
		//auto resultado = Ñ::interpretaNodos(nodos, tablaSímbolos);
		//if(resultado.error())
		//{
		//	std::cout << resultado.mensaje() << std::endl;
		//	muestraNodos(nodos);
		//}
	}

	resultado = Ñ::construye(nodos, entorno);

	for(auto l : lexemas)
	{
		delete l;
	}
	lexemas.clear();
	delete nodos;

	if(resultado.error())
	{
		std::cout << resultado.mensaje() << std::endl;
		return resultado;
	}

	resultado.éxito();
	return resultado;
}

int Compilador::construyeArchivos(std::vector<std::string> archivos)
{
	Ñ::EntornoConstrucción *entorno = new Ñ::EntornoConstrucción;
	
	llvm::InitializeNativeTarget();
	llvm::InitializeNativeTargetAsmParser();
	llvm::InitializeNativeTargetAsmPrinter();

	std::string tripleteDestino = llvm::sys::getDefaultTargetTriple();
	std::cout << "Tripleta de Destino: " << tripleteDestino << std::endl;

	std::string error;
	auto destino = llvm::TargetRegistry::lookupTarget(tripleteDestino, error);

	if (!destino) {
		return -1;
	}

	std::string procesador = "x86-64";
	std::string características = "";

	llvm::TargetOptions opciones;
	auto modeloReordenamiento = llvm::Optional<llvm::Reloc::Model>();
	auto máquinaDestino = destino->createTargetMachine(tripleteDestino, procesador, características, opciones, modeloReordenamiento);

	std::cout << "Preparando construcción con LLVM" << std::endl << std::endl;

    for(std::string archivo : archivos)
    {
        Ñ::ResultadoLlvm resultado = construyeArchivo(archivo, entorno);
        if(resultado.error())
        {
			std::cout << "ERROR FATAL: " << resultado.mensaje() << std::endl;
            return -1;
        }
    }
    return 0;
}