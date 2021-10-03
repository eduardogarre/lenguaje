#include <string>

#include "nodo.hpp"
#include "posicion.hpp"
#include "resultadollvm.hpp"

Ñ::ResultadoLlvm::ResultadoLlvm() : _error(true)
{

}

Ñ::Posición* Ñ::ResultadoLlvm::posición()
{
    return _posición;
}

void Ñ::ResultadoLlvm::posición(Ñ::Posición* pos)
{
    if(pos != nullptr)
    {
        _posición = new Ñ::Posición;
        *_posición = *pos;
    }
}

bool Ñ::ResultadoLlvm::error()
{
    return _error;
}

void Ñ::ResultadoLlvm::error(std::string mensaje)
{
    _error = true;
    _mensaje = mensaje;
}

void Ñ::ResultadoLlvm::éxito()
{
    _error = false;
}

std::string Ñ::ResultadoLlvm::mensaje()
{
    return (_error ? _mensaje : "");
}

void Ñ::ResultadoLlvm::bloque(llvm::BasicBlock* blq)
{
    categoría = Ñ::CategoríaLlvm::BLOQUE_LLVM;
    entidad._bloque = blq;
}

llvm::BasicBlock* Ñ::ResultadoLlvm::bloque()
{
    return (_error ? nullptr : entidad._bloque);
}

void Ñ::ResultadoLlvm::función(llvm::Function* fn)
{
    categoría = Ñ::CategoríaLlvm::FUNCIÓN_LLVM;
    entidad._función = fn;
}

llvm::Function* Ñ::ResultadoLlvm::función()
{
    return (_error ? nullptr : entidad._función);
}

void Ñ::ResultadoLlvm::módulo(llvm::Module* mod)
{
    categoría = Ñ::CategoríaLlvm::MÓDULO_LLVM;
    entidad._módulo = mod;
}

llvm::Module* Ñ::ResultadoLlvm::módulo()
{
    return (_error ? nullptr : entidad._módulo);
}

void Ñ::ResultadoLlvm::valor(llvm::Value* val)
{
    categoría = Ñ::CategoríaLlvm::VALOR_LLVM;
    entidad._valor = val;
}

llvm::Value* Ñ::ResultadoLlvm::valor()
{
    return (_error ? nullptr : entidad._valor);
}