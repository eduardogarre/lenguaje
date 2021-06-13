#include <iostream>
#include <map>
#include <string>
//#include <utility>
#include <vector>

#include "llvm/ADT/APFloat.h"
#include "llvm/ADT/APint.h"
#include "llvm/ADT/APSint.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Verifier.h"

#include "nodo.hpp"
#include "promotor.hpp"
#include "tipo.hpp"

namespace Ñ
{
    enum CategoríaLlvm {
        FUNCIÓN_LLVM,
        BLOQUE_LLVM,
        VALOR_LLVM
    };

    class ResultadoLlvm
    {
    private:
        bool _error;
        std::string _mensaje;

        CategoríaLlvm categoría;

        union {
            llvm::Function *    _función;
            llvm::BasicBlock *  _bloque;
            llvm::Value *  _valor;
        } entidad;

    public:
        ResultadoLlvm() : _error(true) {}

        bool error() { return _error; }
        void error(std::string mensaje) { _error = true; _mensaje = mensaje; }
        void éxito() { _error = false; }
        std::string mensaje() { return (_error ? _mensaje : ""); }

        void función(llvm::Function* fn) { categoría = Ñ::CategoríaLlvm::FUNCIÓN_LLVM; entidad._función = fn; }
        llvm::Function* función() { return (_error ? nullptr : entidad._función); }

        void bloque(llvm::BasicBlock* blq) { categoría = Ñ::CategoríaLlvm::BLOQUE_LLVM; entidad._bloque = blq; }
        llvm::BasicBlock* bloque() { return (_error ? nullptr : entidad._bloque); }

        void valor(llvm::Value* val) { categoría = Ñ::CategoríaLlvm::VALOR_LLVM; entidad._valor = val; }
        llvm::Value* valor() { return (_error ? nullptr : entidad._valor); }
    };

    class Promotor
    {
    public:
        llvm::LLVMContext contextoLlvm;
        llvm::Module* móduloLlvm;
        llvm::IRBuilder<> constructorLlvm;
        std::map<std::string, llvm::Value *> tablaSímbolosLlvm;

    public:
        Promotor() : constructorLlvm(contextoLlvm)
        {

        }

        Ñ::ResultadoLlvm construyeMódulo(Ñ::Nodo* nodo)
        {
            Ñ::ResultadoLlvm resultado;
            
            // Comprobaciones de error
            Ñ::Módulo* módulo;
            if(nodo == nullptr)
            {
                resultado.error("He recibido un nodo nulo, esperaba un módulo");
                return resultado;
            }
            else if(nodo->categoría == Ñ::CategoríaNodo::NODO_MÓDULO)
            {
                // Convierto Ñ::Nodo* a Ñ::Módulo*
                módulo = (Ñ::Módulo*)nodo;
            }
            else
            {
                resultado.error("El nodo no es un módulo");
                return resultado;
            }

            // Creo el módulo LLVM y le asigno el nombre de mi módulo
            móduloLlvm = new llvm::Module(módulo->módulo, contextoLlvm);

            for(auto n : nodo->ramas)
            {
                if(n == nullptr)
                {
                    resultado.error("Uno de las ramas del módulo '" + módulo->módulo + "' es nula");
                    return resultado;
                }
                else if(n->categoría == Ñ::CategoríaNodo::NODO_DEFINE_FUNCIÓN)
                {
                    resultado = construyeDefiniciónFunción(n);
                }
            }

            resultado.éxito();
            return resultado;
        }

        Ñ::ResultadoLlvm construyeDefiniciónFunción(Ñ::Nodo* nodo)
        {
            Ñ::ResultadoLlvm resultado;
            
            // Comprobaciones de error
            Ñ::DefineFunción* función;
            if(nodo == nullptr)
            {
                resultado.error("He recibido un nodo nulo, esperaba una definición de función");
                return resultado;
            }
            else if(nodo->categoría == Ñ::CategoríaNodo::NODO_DEFINE_FUNCIÓN)
            {
                // Convierto Ñ::Nodo* a Ñ::DefineFunción*
                función = (Ñ::DefineFunción*)nodo;
            }
            else
            {
                resultado.error("El nodo no es una definición de función");
                return resultado;
            }

            resultado = construyeDeclaraciónFunción(función->nombre, nodo->ramas[0], nodo->ramas[1]);
            
            llvm::Function * funciónLlvm;
            
            funciónLlvm = móduloLlvm->getFunction(función->nombre);

            if(!funciónLlvm)
            {
                resultado.error("Error, no se ha registrado la función '" + función->nombre + "()'");
                return resultado;
            }
            else if(!funciónLlvm->empty())
            {
                resultado.error("La función ya está definida, no puedo redefinirla.");
                return resultado;
            }

            tablaSímbolosLlvm.clear();

            for(auto &argumento : funciónLlvm->args())
            {
                tablaSímbolosLlvm[argumento.getName().str()] = &argumento;
            }

            Ñ::Nodo* bloque = nodo->ramas[2];

            resultado = construyeBloque("entrada", bloque, funciónLlvm);

            llvm::verifyFunction(*funciónLlvm);

            funciónLlvm->print(llvm::errs(), nullptr);

            return resultado;
        }

        Ñ::ResultadoLlvm construyeDeclaraciónFunción(std::string nombre, Ñ::Nodo* devuelto, Ñ::Nodo* argumentos)
        {
            Ñ::ResultadoLlvm resultado;
            
            // Comprobaciones de error
            if(devuelto == nullptr)
            {
                resultado.error("He recibido un nodo nulo, esperaba un tipo de devolución");
                return resultado;
            }
            else if(devuelto->categoría != Ñ::CategoríaNodo::NODO_TIPO)
            {
                resultado.error("El tipo de retorno no es un NODO_TIPO válido.");
                return resultado;
            }

            if(argumentos == nullptr)
            {
                resultado.error("He recibido un nodo nulo, esperaba un nodo contenedor de argumentos");
                return resultado;
            }
            else if(argumentos->categoría != Ñ::CategoríaNodo::NODO_ARGUMENTOS)
            {
                resultado.error("El tipo de retorno no es un NODO_ARGUMENTOS válido.");
                return resultado;
            }

            Ñ::Tipo* tDevuelto = (Ñ::Tipo*)devuelto;
            llvm::Type* tRetorno;

            switch(tDevuelto->tipo)
            {
            case Ñ::CategoríaTipo::TIPO_NADA:
                tRetorno = llvm::Type::getVoidTy(contextoLlvm);
                break;

            case Ñ::CategoríaTipo::TIPO_BOOLEANO:
                tRetorno = llvm::Type::getInt1Ty(contextoLlvm);
                break;

            case Ñ::CategoríaTipo::TIPO_NATURAL_8:
            case Ñ::CategoríaTipo::TIPO_ENTERO_8:
                tRetorno = llvm::Type::getInt8Ty(contextoLlvm);
                break;

            case Ñ::CategoríaTipo::TIPO_NATURAL_16:
            case Ñ::CategoríaTipo::TIPO_ENTERO_16:
                tRetorno = llvm::Type::getInt16Ty(contextoLlvm);
                break;

            case Ñ::CategoríaTipo::TIPO_NATURAL_32:
            case Ñ::CategoríaTipo::TIPO_ENTERO_32:
                tRetorno = llvm::Type::getInt32Ty(contextoLlvm);
                break;

            case Ñ::CategoríaTipo::TIPO_NATURAL_64:
            case Ñ::CategoríaTipo::TIPO_ENTERO_64:
                tRetorno = llvm::Type::getInt64Ty(contextoLlvm);
                break;
                
            case Ñ::CategoríaTipo::TIPO_REAL_32:
                tRetorno = llvm::Type::getFloatTy(contextoLlvm);
                break;
                
            case Ñ::CategoríaTipo::TIPO_REAL_64:
                tRetorno = llvm::Type::getDoubleTy(contextoLlvm);
                break;

            default:
                resultado.error("No reconozco el tipo de retorno");
                return resultado;
                break;
            }

            std::vector<llvm::Type*> vArgumentos;

            for(auto a : argumentos->ramas)
            {
                if(a == nullptr)
                {
                    resultado.error("He recibido un argumento nulo");
                    return resultado;
                }

                if(a->categoría == Ñ::CategoríaNodo::NODO_TIPO)
                {
                    Ñ::Tipo* arg = (Ñ::Tipo*)a;

                    switch(arg->tipo)
                    {
                    case Ñ::CategoríaTipo::TIPO_BOOLEANO:
                        vArgumentos.push_back(llvm::Type::getInt1Ty(contextoLlvm));
                        break;

                    case Ñ::CategoríaTipo::TIPO_NATURAL_8:
                    case Ñ::CategoríaTipo::TIPO_ENTERO_8:
                        vArgumentos.push_back(llvm::Type::getInt8Ty(contextoLlvm));
                        break;

                    case Ñ::CategoríaTipo::TIPO_NATURAL_16:
                    case Ñ::CategoríaTipo::TIPO_ENTERO_16:
                        vArgumentos.push_back(llvm::Type::getInt16Ty(contextoLlvm));
                        break;

                    case Ñ::CategoríaTipo::TIPO_NATURAL_32:
                    case Ñ::CategoríaTipo::TIPO_ENTERO_32:
                        vArgumentos.push_back(llvm::Type::getInt32Ty(contextoLlvm));
                        break;

                    case Ñ::CategoríaTipo::TIPO_NATURAL_64:
                    case Ñ::CategoríaTipo::TIPO_ENTERO_64:
                        vArgumentos.push_back(llvm::Type::getInt64Ty(contextoLlvm));
                        break;
                        
                    case Ñ::CategoríaTipo::TIPO_REAL_32:
                        vArgumentos.push_back(llvm::Type::getFloatTy(contextoLlvm));
                        break;
                        
                    case Ñ::CategoríaTipo::TIPO_REAL_64:
                        vArgumentos.push_back(llvm::Type::getDoubleTy(contextoLlvm));
                        break;

                    default:
                        resultado.error("No reconozco el tipo de retorno");
                        return resultado;
                        break;
                    }
                }
            }

            llvm::FunctionType* firmaFunción = llvm::FunctionType::get(tRetorno, vArgumentos, false);

            llvm::Function* función = llvm::Function::Create(firmaFunción, llvm::Function::ExternalLinkage, nombre.c_str(), móduloLlvm);

            resultado.éxito();
            resultado.función(función);
            return resultado;
        }

        Ñ::ResultadoLlvm construyeBloque(std::string nombre, Ñ::Nodo* nodo, llvm::Function* función)
        {
            Ñ::ResultadoLlvm resultado;

            if(función == nullptr)
            {
                resultado.error("He recibido una función de valor nullptr, no puedo crear el bloque");
                return resultado;
            }

            llvm::BasicBlock* bloque = llvm::BasicBlock::Create(contextoLlvm, nombre, función);
            if(bloque == nullptr)
            {
                resultado.error("El proceso de creación del bloque '" + nombre + "' me ha devuelto un puntero nulo");
                return resultado;
            }

            constructorLlvm.SetInsertPoint(bloque);

            for(auto n : nodo->ramas)
            {
                resultado = construyeExpresión(n);
                if(resultado.error())
                {
                    return resultado;
                }
            }
            
            resultado.éxito();
            return resultado;
        }

        Ñ::ResultadoLlvm construyeExpresión(Ñ::Nodo* nodo)
        {
            Ñ::ResultadoLlvm resultado;

            if(nodo == nullptr)
            {
                resultado.error("He recibido un nodo de valor nullptr, no puedo leer la expresión");
                return resultado;
            }

            if(nodo->ramas.size() != 1)
            {
                resultado.error("He recibido un nodo expresión que no contiene ningún hijo.");
                return resultado;
            }

            auto n = nodo->ramas[0];

            switch (n->categoría)
            {
            case Ñ::CategoríaNodo::NODO_DEVUELVE:
                resultado = construyeRetorno(n);
                break;
            
            default:
                break;
            }

            return resultado;
        }

        Ñ::ResultadoLlvm construyeRetorno(Ñ::Nodo* nodo)
        {
            Ñ::ResultadoLlvm resultado;

            if(nodo == nullptr)
            {
                resultado.error("He recibido un nodo de valor nullptr, no puedo leer la expresión");
                return resultado;
            }

            if(nodo->ramas.size() == 1)
            {
                resultado = construyeLDA(nodo->ramas[0]);
                if(resultado.error())
                {
                    return resultado;
                }

                constructorLlvm.CreateRet(resultado.valor());

                resultado.éxito();
                return resultado;
            }
            else if(nodo->ramas.size() == 0)
            {
                constructorLlvm.CreateRetVoid();
                resultado.éxito();
                return resultado;
            }
            else
            {
                resultado.error("He recibido un nodo de devolución que tiene más de 1 hijo");
                return resultado;
            }
        }

        Ñ::ResultadoLlvm construyeLDA(Ñ::Nodo* nodo)
        {
            Ñ::ResultadoLlvm resultado;

            if(nodo == nullptr)
            {
                resultado.error("He recibido un nodo de valor nullptr, no puedo leer la expresión");
                return resultado;
            }

            switch (nodo->categoría)
            {
            case Ñ::CategoríaNodo::NODO_LITERAL:
                resultado = construyeLiteral(nodo);
                break;
            
            default:
                resultado.error("No puedo construir este nodo como LDA");
                break;
            }

            return resultado;
        }

        Ñ::ResultadoLlvm construyeLiteral(Ñ::Nodo* nodo)
        {
            Ñ::ResultadoLlvm resultado;

            if(nodo == nullptr)
            {
                resultado.error("He recibido un nodo de valor nullptr, no puedo leer la expresión");
                return resultado;
            }

            if(nodo->categoría != Ñ::CategoríaNodo::NODO_LITERAL)
            {
                resultado.error("El nodo no es un literal, no puedo construirlo");
                return resultado;
            }

            Ñ::Literal* literal = (Ñ::Literal*)nodo;
            llvm::Type* tipo;
            uint64_t número;
            float real32;
            double real64;

            switch (literal->tipo)
            {
            case Ñ::CategoríaTipo::TIPO_NATURAL_8:
                tipo = llvm::Type::getInt8Ty(contextoLlvm);
                número = std::stoull(literal->dato);
                resultado.éxito();
                resultado.valor(llvm::ConstantInt::get(tipo, número));
                break;
                
            case Ñ::CategoríaTipo::TIPO_NATURAL_16:
                tipo = llvm::Type::getInt16Ty(contextoLlvm);
                número = std::stoull(literal->dato);
                resultado.éxito();
                resultado.valor(llvm::ConstantInt::get(tipo, número));
                break;
                
            case Ñ::CategoríaTipo::TIPO_NATURAL_32:
                tipo = llvm::Type::getInt32Ty(contextoLlvm);
                número = std::stoull(literal->dato);
                resultado.éxito();
                resultado.valor(llvm::ConstantInt::get(tipo, número));
                break;

            case Ñ::CategoríaTipo::TIPO_NATURAL_64:
                tipo = llvm::Type::getInt64Ty(contextoLlvm);
                número = std::stoull(literal->dato);
                resultado.éxito();
                resultado.valor(llvm::ConstantInt::get(tipo, número));
                break;
            
            case Ñ::CategoríaTipo::TIPO_ENTERO_8:
                tipo = llvm::Type::getInt8Ty(contextoLlvm);
                número = std::stoll(literal->dato);
                resultado.éxito();
                resultado.valor(llvm::ConstantInt::get(tipo, número, true));
                break;
            
            case Ñ::CategoríaTipo::TIPO_ENTERO_16:
                tipo = llvm::Type::getInt16Ty(contextoLlvm);
                número = std::stoll(literal->dato);
                resultado.éxito();
                resultado.valor(llvm::ConstantInt::get(tipo, número, true));
                break;
            
            case Ñ::CategoríaTipo::TIPO_ENTERO_32:
                tipo = llvm::Type::getInt32Ty(contextoLlvm);
                número = std::stoll(literal->dato);
                resultado.éxito();
                resultado.valor(llvm::ConstantInt::get(tipo, número, true));
                break;
            
            case Ñ::CategoríaTipo::TIPO_ENTERO_64:
                tipo = llvm::Type::getInt64Ty(contextoLlvm);
                número = std::stoll(literal->dato);
                resultado.éxito();
                resultado.valor(llvm::ConstantInt::get(tipo, número, true));
                break;
            
            case Ñ::CategoríaTipo::TIPO_REAL_32:
                tipo = llvm::Type::getFloatTy(contextoLlvm);
                real32 = std::stof(literal->dato);
                resultado.éxito();
                resultado.valor(llvm::ConstantFP::get(tipo, real32));
                break;
            
            case Ñ::CategoríaTipo::TIPO_REAL_64:
                tipo = llvm::Type::getDoubleTy(contextoLlvm);
                real64 = std::stod(literal->dato);
                resultado.éxito();
                resultado.valor(llvm::ConstantFP::get(tipo, real64));
                break;
            
            default:
                resultado.error("Error, no reconozco el tipo del literal");
                break;
            }

            return resultado;
        }
    };

    Ñ::Resultado construye(Ñ::Nodo* árbol)
    {
        Ñ::Resultado resultado;

        Ñ::Promotor* promotor = new Ñ::Promotor;

        std::cout << std::endl;

        muestraNodos(árbol);

        std::cout << std::endl;

        if(árbol->categoría == Ñ::CategoríaNodo::NODO_MÓDULO)
        {
            Ñ::ResultadoLlvm rMódulo = promotor->construyeMódulo(árbol);
            if(rMódulo.error())
            {
                resultado.error(rMódulo.mensaje());
                return resultado;
            }
        }

        return resultado;
    }
}