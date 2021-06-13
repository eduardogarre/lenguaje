#include <iostream>
#include <map>
#include <string>
//#include <utility>
#include <vector>

#include "llvm/ADT/APFloat.h"
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
        FUNCIÓN_LLVM
    };

    class ResultadoLlvm
    {
    private:
        bool _error;
        std::string _mensaje;

        CategoríaLlvm categoría;

        union {
            llvm::Function * _función;
        } entidad;

    public:
        ResultadoLlvm() : _error(true) {}

        bool error() { return _error; }
        void error(std::string mensaje) { _error = true; _mensaje = mensaje; }
        void éxito() { _error = false; }
        std::string mensaje() { return (_error ? _mensaje : ""); }

        void función(llvm::Function* fn) { categoría = Ñ::CategoríaLlvm::FUNCIÓN_LLVM; entidad._función = fn; }
        llvm::Function* función() { return (_error ? nullptr : entidad._función); }
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
            std::cout << "Construyendo módulo '" << módulo->módulo << "'" << std::endl;
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

            std::cout << "Construyendo definición de función '" << función->nombre << "()'... ";

            std::cout << "Declarando '" << función->nombre << "()'... " << std::endl;

            resultado = construyeDeclaraciónFunción(función->nombre, nodo->ramas[0], nodo->ramas[1]);
            
            std::cout << "Recuperando la función '" << función->nombre << "()' ya declarada" << std::endl;
            
            llvm::Function * funciónLlvm;
            
            funciónLlvm = móduloLlvm->getFunction(función->nombre);
            
            std::cout << "Función '" << función->nombre << "()' recuperada" << std::endl;

            if(!funciónLlvm)
            {
                std::cout << "Error, no se ha registrado la función '" << función->nombre << "()'" << función->nombre << "()'" << std::endl;
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
                std::cout << "arg: " << argumento.getName().str() << std::endl;
                tablaSímbolosLlvm[argumento.getName().str()] = &argumento;
            }

            llvm::BasicBlock* bloque = llvm::BasicBlock::Create(contextoLlvm, "entrada", funciónLlvm);

            constructorLlvm.SetInsertPoint(bloque);

            constructorLlvm.CreateRet(llvm::ConstantInt::get(llvm::Type::getInt64Ty(contextoLlvm), 288));

            llvm::verifyFunction(*funciónLlvm);

            funciónLlvm->print(llvm::errs(), nullptr);
            
            resultado.éxito();
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

            std::cout << "Construyendo declaración de '" << nombre << "()'" << std::endl;

            Ñ::Tipo* tDevuelto = (Ñ::Tipo*)devuelto;
            llvm::Type* tRetorno;

            std::cout << "examinando tipo de retorno de '" << nombre << "()' ... ";

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
                std::cout << "error" << std::endl;
                resultado.error("No reconozco el tipo de retorno");
                return resultado;
                break;
            }

            std::cout << "hecho." << std::endl;

            std::cout << "Ahora examino argumentos de '" << nombre << "()' ... ";
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
                        std::cout << "error" << std::endl;
                        resultado.error("No reconozco el tipo de retorno");
                        return resultado;
                        break;
                    }
                }
            }

            std::cout << "hecho." << std::endl;
            
            std::cout << "Creo firma de '" << nombre << "()'... " << std::endl;
            
            llvm::FunctionType* firmaFunción = llvm::FunctionType::get(tRetorno, vArgumentos, false);

            std::cout << "hecho." << std::endl;
            
            std::cout << "Registro '" << nombre << "()'... " << std::endl;
            
            llvm::Function* función = llvm::Function::Create(firmaFunción, llvm::Function::ExternalLinkage, nombre.c_str(), móduloLlvm);

            std::cout << "hecho." << std::endl;
            
            resultado.éxito();
            resultado.función(función);
            return resultado;
        }
    };

    Ñ::Resultado construye(Ñ::Nodo* árbol)
    {
        Ñ::Resultado resultado;

        Ñ::Promotor* promotor = new Ñ::Promotor;

        muestraNodos(árbol);

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