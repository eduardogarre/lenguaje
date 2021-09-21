#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "llvm/Support/Host.h"
#include "llvm/Support/FileSystem.h"
#include "llvm/Support/TargetRegistry.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Target/TargetMachine.h"

#include "configuracion.hpp"
#include "herramientas.hpp"
#include "ñ/ñ.hpp"
#include "promotor.hpp"

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

std::string creaNombreMódulo(std::string archivo)
{
	std::filesystem::path p = archivo;
	std::string antes = p.string();
	std::string después = p.stem().string();
    std::cout << "Antes: " << antes << std::endl;
    std::cout << "Después: " << después << std::endl;

	return después;
}

Ñ::ResultadoLlvm construyeArchivo(std::string archivo, Ñ::EntornoConstrucción *entorno)
{
	Ñ::ResultadoLlvm resultado;

	std::string código = "";

	std::string nombreMódulo = creaNombreMódulo(archivo);

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

	nodos = sintaxis.analiza(lexemas, nombreMódulo);

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

int Compilador::compila(Compilador::Configuración cfg)
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

    for(std::string archivo : cfg.archivos)
    {
        Ñ::ResultadoLlvm resultado = construyeArchivo(archivo, entorno);
        if(resultado.error())
        {
			std::cout << "ERROR FATAL: " << resultado.mensaje() << std::endl;
            return -1;
        }

		llvm::Module* móduloLlvm = resultado.módulo();

		móduloLlvm->setDataLayout(máquinaDestino->createDataLayout());
		móduloLlvm->setTargetTriple(tripleteDestino);

		std::cout << std::endl << "Archivo de representación intermedia:" << std::endl << std::endl;
		móduloLlvm->print(llvm::outs(), nullptr);

		std::string nombreMódulo = creaNombreMódulo(archivo);

		std::string nombreArchivoDestino = nombreMódulo + ".o";
		std::error_code códigoError;
		llvm::raw_fd_ostream archivoDestino(nombreArchivoDestino, códigoError, llvm::sys::fs::OF_None);

		if (códigoError) {
			std::cout << ("No he podido abrir el archivo: " + códigoError.message()) << std::endl;
			return -1;
		}

		llvm::legacy::PassManager paseDeCódigoObjeto;
		auto tipoArchivo = llvm::CGFT_ObjectFile;

		if(máquinaDestino->addPassesToEmitFile(paseDeCódigoObjeto, archivoDestino, nullptr, tipoArchivo))
		{
			std::cout << ("No he podido emitir un archivo de este tipo") << std::endl;
			return -1;
		}

		paseDeCódigoObjeto.run(*(móduloLlvm));
		archivoDestino.flush();

		std::cout << "He construido el archivo \"" + nombreArchivoDestino + "\"." << std::endl;
    }

	std::string archivoDestino = cfg.nombreArchivoDestino + cfg.extensión;
	
	ejecutaPrograma("proyecto/lld-link.exe",
					"lld *.o proyecto/biblioteca.lib /entry:__punto_de_entrada /subsystem:console /nodefaultlib /out:" + archivoDestino);

    return 0;
}