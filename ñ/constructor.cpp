/*
This Source Code Form is subject to the terms of the Mozilla Public License, v.
2.0. If a copy of the MPL was not distributed with this file, You can obtain one
at http://mozilla.org/MPL/2.0/.

This Source Code Form is "Incompatible With Secondary Licenses", as defined by
the Mozilla Public License, v. 2.0.
*/

#include <algorithm>
#include <iostream>
#include <map>
#include <string>
//#include <utility>
#include <vector>

#include "llvm/ADT/APFloat.h"
#include "llvm/ADT/APInt.h"
#include "llvm/ADT/APSInt.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/Bitcode/BitcodeWriter.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Value.h"
#include "llvm/IR/Verifier.h"
#include "llvm/Support/Host.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/TargetRegistry.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Support/TypeName.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/Transforms/InstCombine/InstCombine.h"
#include "llvm/Transforms/Utils.h"
#include "llvm/Transforms/Scalar.h"
#include "llvm/Transforms/Scalar/GVN.h"

//#include "constructor.hpp"
#include "entorno.hpp"
#include "justoatiempo.hpp"
#include "nodo.hpp"
#include "constructor.hpp"
#include "resultadollvm.hpp"
#include "simbolos.hpp"
#include "tipo.hpp"

namespace Ñ
{
    static Ñ::ConstructorJAT* jat = nullptr;

    EntornoConstrucción *entorno = nullptr;

    class Constructor
    {
        Ñ::Símbolos* tablaSímbolos = nullptr;

    public:
        llvm::Module* móduloLlvm;

        Constructor()
        {
            tablaSímbolos = new Ñ::Símbolos;
        }

        ~Constructor()
        {
            if(entorno != nullptr && tablaSímbolos != nullptr)
            {
                delete tablaSímbolos;
            }
        }

        void preparaMódulo(std::string nombre)
        {

            // Creo el módulo LLVM y le asigno el nombre de mi módulo
            móduloLlvm = new llvm::Module(nombre, entorno->contextoLlvm);

            //std::cout << "Nombre del módulo: " << móduloLlvm->getModuleIdentifier() << std::endl;

            //preparaPasesDeOptimización();
        }

        void preparaMóduloJAT(std::string nombre)
        {

            // Creo el módulo LLVM y le asigno el nombre de mi módulo
            móduloLlvm = new llvm::Module(nombre, entorno->contextoLlvm);

            móduloLlvm->setDataLayout(jat->leeDisposiciónDatos());
        }

        void preparaPasesDeOptimización()
        {
            entorno->gestorPasesOptimización = new llvm::legacy::FunctionPassManager(móduloLlvm);

            // Intenta convertir variables en RAM a registros
            entorno->gestorPasesOptimización->add(llvm::createPromoteMemoryToRegisterPass());

            if(entorno->optimización > 0)
            {
                // Optimizaciones se secuencias cortas y pequeños reordenamientos.
                entorno->gestorPasesOptimización->add(llvm::createInstructionCombiningPass());
                // Reassociate expressions.
                entorno->gestorPasesOptimización->add(llvm::createReassociatePass());
                // Elimina subexpresiones comunes.
                entorno->gestorPasesOptimización->add(llvm::createGVNPass());
                // Simplifica el grafo de flujo de ejecución (elimina bloques inalcanzables, etc)
                entorno->gestorPasesOptimización->add(llvm::createCFGSimplificationPass());
                // Intenta convertir variables en RAM a registros
                entorno->gestorPasesOptimización->add(llvm::createPromoteMemoryToRegisterPass());
                // Intenta simplificar el control de flujo cuando los saltos condicionales están
                // predeterminados por valores ya establecidos
                entorno->gestorPasesOptimización->add(llvm::createJumpThreadingPass());
            }

            entorno->gestorPasesOptimización->doInitialization();
        }

        void ponId(std::string id, llvm::Value* valor)
        {
            if(tablaSímbolos != nullptr)
            {
                tablaSímbolos->ponId(id, valor);
            }
            else
            {
                //std::cout << "Error, no puedo guardar el símbolo '" << id << "' en la tabla" << std::endl;
            }
        }

        llvm::Value* leeId(std::string id)
        {
            if(tablaSímbolos != nullptr)
            {
                return tablaSímbolos->leeId(id);
            }
            
            return nullptr;
        }

        llvm::Type* creaTipoLlvm(Ñ::Tipo* tipo)
        {
            switch (tipo->tipo)
            {
            case TIPO_NADA:
                return llvm::Type::getVoidTy(entorno->contextoLlvm);
                break;
            
            case TIPO_BOOLEANO:
                return llvm::Type::getInt1Ty(entorno->contextoLlvm);
                break;
            
            case TIPO_NATURAL_8:
                return llvm::Type::getInt8Ty(entorno->contextoLlvm);
                break;
            
            case TIPO_NATURAL_16:
                return llvm::Type::getInt16Ty(entorno->contextoLlvm);
                break;
            
            case TIPO_NATURAL_32:
                return llvm::Type::getInt32Ty(entorno->contextoLlvm);
                break;
            
            case TIPO_NATURAL_64:
                return llvm::Type::getInt64Ty(entorno->contextoLlvm);
                break;
            
            case TIPO_ENTERO_8:
                return llvm::Type::getInt8Ty(entorno->contextoLlvm);
                break;
            
            case TIPO_ENTERO_16:
                return llvm::Type::getInt16Ty(entorno->contextoLlvm);
                break;
            
            case TIPO_ENTERO_32:
                return llvm::Type::getInt32Ty(entorno->contextoLlvm);
                break;
            
            case TIPO_ENTERO_64:
                return llvm::Type::getInt64Ty(entorno->contextoLlvm);
                break;
            
            case TIPO_REAL_32:
                return llvm::Type::getFloatTy(entorno->contextoLlvm);
                break;
            
            case TIPO_REAL_64:
                return llvm::Type::getDoubleTy(entorno->contextoLlvm);
                break;
            
            case TIPO_VECTOR:
                {
                    Ñ::Nodo* nodo = (Ñ::Nodo*)tipo;
                    uint32_t tamaño = tipo->tamaño();
                    Ñ::Tipo* subtipo = tipo->subtipo();
                    llvm::Type* subtipollvm = creaTipoLlvm(subtipo);
                    if(subtipollvm == nullptr)
                    {
                        return nullptr;
                    }
                    return llvm::VectorType::get(subtipollvm, tamaño, false);
                }
                break;
            
            case TIPO_PUNTERO:
                {
                    Ñ::Nodo* nodo = (Ñ::Nodo*)tipo;
                    Ñ::Tipo* subtipo = tipo->subtipo();
                    llvm::Type* subtipollvm = creaTipoLlvm(subtipo);
                    if(subtipollvm == nullptr)
                    {
                        return nullptr;
                    }
                    return llvm::PointerType::get(subtipollvm, 0);
                }
                break;
            
            default:
                return nullptr;
                break;
            }

            return nullptr;
        }

        Ñ::ResultadoLlvm construyeMódulo(Ñ::Nodo* nodo)
        {
            Ñ::ResultadoLlvm resultado;
            
            // Comprobaciones de error
            Ñ::Módulo* módulo;
            if(nodo == nullptr)
            {
                resultado.error("He recibido un nodo nulo, esperaba un módulo.");
                return resultado;
            }
            else if(nodo->categoría == Ñ::CategoríaNodo::NODO_MÓDULO)
            {
                // Convierto Ñ::Nodo* a Ñ::Módulo*
                módulo = (Ñ::Módulo*)nodo;
            }
            else
            {
                resultado.error("El nodo no es un módulo.");
                resultado.posición(nodo->posición());
                return resultado;
            }

            preparaMódulo(módulo->módulo);

            preparaPasesDeOptimización();

            for(auto n : nodo->ramas)
            {
                if(n == nullptr)
                {
                    resultado.error("Uno de las ramas del módulo '" + módulo->módulo + "' es nula.");
                    resultado.posición(módulo->posición());
                    return resultado;
                }
                else if(n->categoría == Ñ::CategoríaNodo::NODO_DEFINE_FUNCIÓN)
                {
                    resultado = construyeDefiniciónFunción(n);
                    if(resultado.error())
                    {
                        return resultado;
                    }
                }
                else if(n->categoría == Ñ::CategoríaNodo::NODO_DECLARA_FUNCIÓN)
                {
                    resultado = construyeDeclaraciónFunción(n);
                    if(resultado.error())
                    {
                        return resultado;
                    }
                }

                if(resultado.error())
                {
                    return resultado;
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
                resultado.error("He recibido un nodo nulo, esperaba una definición de función.");
                return resultado;
            }
            else if(nodo->categoría == Ñ::CategoríaNodo::NODO_DEFINE_FUNCIÓN)
            {
                // Convierto Ñ::Nodo* a Ñ::DefineFunción*
                función = (Ñ::DefineFunción*)nodo;
            }
            else
            {
                resultado.error("El nodo no es una definición de función.");
                resultado.posición(nodo->posición());
                return resultado;
            }

            if(función->público)
            {
                resultado = _construyeDeclaraciónFunción(función->nombre, nodo->ramas[0], nodo->ramas[1], true);
            }
            else
            {
                resultado = _construyeDeclaraciónFunción(función->nombre, nodo->ramas[0], nodo->ramas[1], false);
            }

            if(resultado.error())
            {
                return resultado;
            }
            
            llvm::Function * funciónLlvm;
            
            funciónLlvm = móduloLlvm->getFunction(función->nombre);

            if(!funciónLlvm)
            {
                resultado.error("Todavía no has registrado la función '" + función->nombre + "()'.");
                resultado.posición(función->posición());
                return resultado;
            }
            else if(!funciónLlvm->empty())
            {
                resultado.error("Ya habías definido la función '" + función->nombre + "()', no puedo redefinirla.");
                resultado.posición(función->posición());
                return resultado;
            }

            // Inicio construcción del bloque y definición de los argumentos
            tablaSímbolos->creaÁmbito(Ñ::Ámbito::ÁMBITO_BLOQUE_FUNCIÓN);

            std::string nombreBloque = "entrada";
            llvm::BasicBlock* bloqueLlvm = llvm::BasicBlock::Create(entorno->contextoLlvm, nombreBloque, funciónLlvm);
            if(bloqueLlvm == nullptr)
            {
                resultado.error("El proceso de creación del bloque '" + nombreBloque + "' me ha devuelto un puntero nulo.");
                resultado.posición(función->posición());
                return resultado;
            }

            entorno->constructorLlvm.SetInsertPoint(bloqueLlvm);

            Ñ::Nodo* args = nodo->ramas[1];
            
            int i = 0;
            for(auto &argumento : funciónLlvm->args())
            {
                Ñ::Nodo* a = args->ramas[i];

                std::string nombre = ((Ñ::DeclaraVariable*)a)->variable;
                argumento.setName(nombre);
                llvm::Value* variable = entorno->constructorLlvm.CreateAlloca(argumento.getType(), nullptr, nombre);
                entorno->constructorLlvm.CreateStore(&argumento, variable, false);
                ponId(nombre, variable);
                i++;
            }

            Ñ::Nodo* bloque = nodo->ramas[2];

            resultado = construyeInteriorDeBloque(bloque);
            if(resultado.error())
            {
                return resultado;
            }

            

            llvm::verifyFunction(*funciónLlvm);

            //std::cout << "Ejecuto optimizaciones" << std::endl;
            
            entorno->gestorPasesOptimización->run(*funciónLlvm);
            
            //funciónLlvm->print(llvm::errs(), nullptr);

            tablaSímbolos->borraÁmbito();

            resultado.éxito();
            resultado.valor((llvm::Value*)funciónLlvm);
            return resultado;
        }

        Ñ::ResultadoLlvm construyeDeclaraciónFunción(Ñ::Nodo* nodo)
        {
            Ñ::ResultadoLlvm resultado;
            
            // Comprobaciones de error
            Ñ::DeclaraFunción* función;
            if(nodo == nullptr)
            {
                resultado.error("He recibido un nodo nulo, esperaba una declaración de función.");
                return resultado;
            }
            else if(nodo->categoría == Ñ::CategoríaNodo::NODO_DECLARA_FUNCIÓN)
            {
                // Convierto Ñ::Nodo* a Ñ::DefineFunción*
                función = (Ñ::DeclaraFunción*)nodo;
            }
            else
            {
                resultado.error("El nodo no es una declaración de función.");
                resultado.posición(nodo->posición());
                return resultado;
            }

            resultado = _construyeDeclaraciónFunción(función->nombre, nodo->ramas[0], nodo->ramas[1], función->externo);
            if(resultado.error())
            {
                return resultado;
            }
            
            llvm::Function* funciónLlvm = (llvm::Function*)resultado.valor();
            
            //funciónLlvm->print(llvm::errs(), nullptr);
            
            return resultado;
        }

        Ñ::ResultadoLlvm _construyeDeclaraciónFunción(std::string nombre, Ñ::Nodo* devuelto, Ñ::Nodo* argumentos, bool externo)
        {
            Ñ::ResultadoLlvm resultado;
            llvm::Type* tRetorno = nullptr;
            std::vector<llvm::Type*> vArgumentos = {};
            
            // Comprobaciones de error
            if(devuelto == nullptr)
            {
                auto nada = new Ñ::Tipo;
                tRetorno = creaTipoLlvm(nada);
                delete nada;
            }
            else if(devuelto->categoría != Ñ::CategoríaNodo::NODO_TIPO)
            {
                resultado.error("El tipo de retorno no es un NODO_TIPO válido.");
                resultado.posición(devuelto->posición());
                return resultado;
            }
            else
            {
                Ñ::Tipo* tDevuelto = (Ñ::Tipo*)devuelto;
                tRetorno = creaTipoLlvm(tDevuelto);
                if(tRetorno == nullptr)
                {
                    resultado.error("No puedo construir el tipo '" + obténNombreDeTipo(tDevuelto) + "'.");
                    resultado.posición(tDevuelto->posición());
                    return resultado;
                }
            }

            if(argumentos == nullptr)
            {
                
            }
            else if(argumentos->categoría != Ñ::CategoríaNodo::NODO_ARGUMENTOS)
            {
                resultado.error("El tipo de retorno no es un NODO_ARGUMENTOS válido.");
                resultado.posición(argumentos->posición());
                return resultado;
            }
            else
            {
                for(auto a : argumentos->ramas)
                {
                    if(a == nullptr)
                    {
                        resultado.error("He recibido un argumento nulo.");
                        resultado.posición(argumentos->posición());
                        return resultado;
                    }

                    if(a->categoría == Ñ::CategoríaNodo::NODO_TIPO)
                    {
                        Ñ::Tipo* arg = (Ñ::Tipo*)a;
                        llvm::Type* tipoarg = creaTipoLlvm(arg);
                        if(tipoarg == nullptr)
                        {
                            resultado.error("No puedo construir el tipo '" + obténNombreDeTipo(arg) + "'.");
                            resultado.posición(arg->posición());
                            return resultado;
                        }
                        vArgumentos.push_back(tipoarg);
                    }
                    else if(a->categoría == Ñ::CategoríaNodo::NODO_DECLARA_VARIABLE)
                    {
                        Ñ::Tipo* arg = (Ñ::Tipo*)(a->ramas[0]);
                        llvm::Type* tipoarg = creaTipoLlvm(arg);
                        if(tipoarg == nullptr)
                        {
                            resultado.error("No puedo construir el tipo '" + obténNombreDeTipo(arg) + "'.");
                            resultado.posición(arg->posición());
                            return resultado;
                        }
                        vArgumentos.push_back(tipoarg);
                    }
                    else
                    {
                        //muestraNodos(a);
                        resultado.error("He recibido un argumento de un tipo que no reconozco.");
                        resultado.posición(a->posición());
                        return resultado;
                    }
                }
            }

            llvm::FunctionType* firmaFunción = llvm::FunctionType::get(tRetorno, vArgumentos, false);

            llvm::Function* función;

            if(externo)
            {
                función = llvm::Function::Create(firmaFunción, llvm::Function::ExternalLinkage, nombre.c_str(), móduloLlvm);
            }
            else
            {
                función = llvm::Function::Create(firmaFunción, llvm::Function::PrivateLinkage, nombre.c_str(), móduloLlvm);
            }

            resultado.éxito();
            resultado.función(función);
            return resultado;
        }

        Ñ::ResultadoLlvm construyeInteriorDeBloque(Ñ::Nodo* nodo)
        {
            Ñ::ResultadoLlvm resultado;

            for(auto n : nodo->ramas)
            {
                Ñ::ResultadoLlvm resultadoIntermedio = construyeExpresión(n);
                if(resultadoIntermedio.error())
                {
                    return resultadoIntermedio;
                }
            }

            resultado.éxito();
            return resultado;
        }

        Ñ::ResultadoLlvm construyeExpresiónPrimerNivel(Ñ::Nodo* nodo)
        {
            Ñ::ResultadoLlvm resultado;
            Ñ::Expresión* expresión;

            if(nodo == nullptr)
            {
                resultado.error("He recibido un nodo nulo, esperaba una expresión de primer nivel.");
                return resultado;
            }
            else if(nodo->categoría == Ñ::CategoríaNodo::NODO_EXPRESIÓN)
            {
                // Convierto Ñ::Nodo* a Ñ::DefineFunción*
                expresión = (Ñ::Expresión*)nodo;
            }
            else
            {
                resultado.error("El nodo no es una expresión de primer nivel.");
                resultado.posición(nodo->posición());
                return resultado;
            }

            preparaMóduloJAT("");

            for(auto const&[nombre, tipo] : entorno->globales)
            {
                llvm::GlobalVariable* varGlobal = new llvm::GlobalVariable(*(móduloLlvm), tipo, false, llvm::GlobalValue::ExternalLinkage, 0, nombre);
            }

            resultado = _construyeDeclaraciónFunción("__función_anónima__", nullptr, nullptr, true);
            if(resultado.error())
            {
                return resultado;
            }
            
            llvm::Function * funciónLlvm;
            
            funciónLlvm = móduloLlvm->getFunction("__función_anónima__");

            if(!funciónLlvm)
            {
                resultado.error("Todavía no has registrado la función '__función_anónima__()'.");
                return resultado;
            }
            else if(!funciónLlvm->empty())
            {
                resultado.error("Ya habías definido la función '__función_anónima__()', no puedo redefinirla.");
                return resultado;
            }

            // Inicio construcción del bloque, no hay argumentos que definir
            // PENDIENTE: No debo usar una tabla de símbolos local
            tablaSímbolos->creaÁmbito(Ñ::Ámbito::ÁMBITO_BLOQUE_FUNCIÓN);

            std::string nombreBloque = "entrada";
            llvm::BasicBlock* bloqueLlvm = llvm::BasicBlock::Create(entorno->contextoLlvm, nombreBloque, funciónLlvm);
            if(bloqueLlvm == nullptr)
            {
                resultado.error("El proceso de creación del bloque '" + nombreBloque + "' me ha devuelto un puntero nulo.");
                return resultado;
            }

            entorno->constructorLlvm.SetInsertPoint(bloqueLlvm);

            auto rExpresión = construyeExpresión(nodo);
            if(rExpresión.error())
            {
                return rExpresión;
            }
            entorno->constructorLlvm.CreateRetVoid();
            entorno->constructorLlvm.CreateUnreachable();

            llvm::verifyFunction(*funciónLlvm);

            //gestorPasesOptimización->run(*funciónLlvm);

            //funciónLlvm->print(llvm::errs(), nullptr);

            tablaSímbolos->borraÁmbito();
            delete tablaSímbolos;
            tablaSímbolos = nullptr;

            resultado.éxito();
            resultado.valor((llvm::Value*)funciónLlvm);
            return resultado;
        }

        Ñ::ResultadoLlvm construyeExpresión(Ñ::Nodo* nodo)
        {
            Ñ::ResultadoLlvm resultado;

            if(nodo == nullptr)
            {
                resultado.error("He recibido un nullptr, esperaba una expresión.");
                return resultado;
            }

            if(nodo->ramas.size() != 1)
            {
                resultado.error("He recibido una expresión que no contiene ningún hijo.");
                resultado.posición(nodo->posición());
                return resultado;
            }

            auto n = nodo->ramas[0];

            if(n == nullptr)
            {
                resultado.error("No puedo leer el hijo de la expresión, está vacío.");
                resultado.posición(n->posición());
                return resultado;
            }

            switch (n->categoría)
            {
            case Ñ::CategoríaNodo::NODO_DEVUELVE:
                resultado = construyeDevolución(n);
                break;
            
            case Ñ::CategoríaNodo::NODO_PARA_BUCLE:
                resultado = construyeParaBucle(n);
                break;
            
            case Ñ::CategoríaNodo::NODO_DECLARA_VARIABLE:
                if(jat)
                {
                    resultado = construyeDeclaraciónVariableGlobal(n);
                }
                else
                {
                    resultado = construyeDeclaraciónVariable(n);
                }
                resultado = construyeDeclaraciónVariable(n);
                break;
            
            case Ñ::CategoríaNodo::NODO_ASIGNA:
                resultado = construyeAsignación(n);
                break;
            
            case Ñ::CategoríaNodo::NODO_LITERAL:
            case Ñ::CategoríaNodo::NODO_CONVIERTE_TIPOS:
            case Ñ::CategoríaNodo::NODO_IDENTIFICADOR:
            case Ñ::CategoríaNodo::NODO_COMPARACIÓN:
            case Ñ::CategoríaNodo::NODO_TÉRMINO:
            case Ñ::CategoríaNodo::NODO_FACTOR:
            case Ñ::CategoríaNodo::NODO_LLAMA_FUNCIÓN:
                resultado = construyeLDA(n);
                break;
            
            case Ñ::CategoríaNodo::NODO_SI_CONDICIONAL:
                resultado = construyeSiCondicional(n);
                break;
            
            case Ñ::CategoríaNodo::NODO_BUCLE_MIENTRAS:
                resultado = construyeBucleMientras(n);
                break;
            
            default:
                resultado.error("No reconozco la expresión.");
                resultado.posición(nodo->posición());
                //muestraNodos(nodo);
                break;
            }

            return resultado;
        }

        Ñ::ResultadoLlvm construyeSiCondicional(Ñ::Nodo* nodo)
        {
            Ñ::ResultadoLlvm resultado;

            if(nodo == nullptr)
            {
                resultado.error("El nodo vale nullptr, esperaba un si-condicional.");
                return resultado;
            }

            if(nodo->categoría != Ñ::CategoríaNodo::NODO_SI_CONDICIONAL)
            {
                resultado.error("El nodo no es un si-condicional.");
                resultado.posición(nodo->posición());
                return resultado;
            }

            bool continúa = true;
            bool sino = false;

            llvm::Function *funciónActual = entorno->constructorLlvm.GetInsertBlock()->getParent();

            int64_t índice = 0;
            
            // Declaro y preparo punteros de los diferentes bloques
            llvm::BasicBlock *bloquePrevio = entorno->constructorLlvm.GetInsertBlock();
            llvm::BasicBlock *bloqueSiCnd = nullptr;
            llvm::BasicBlock *bloqueSiBlq = nullptr;
            llvm::BasicBlock *bloqueSino = nullptr;
            llvm::BasicBlock *bloqueContinúa = nullptr;

            if(continúa) // La función contiene más expresiones después del SiCondicional
            {
                bloqueContinúa = llvm::BasicBlock::Create(entorno->contextoLlvm, "continúa");
            }

            if(nodo->ramas.size() % 2 == 1) // Hay un bloqueSino
            {
                sino = true;
                bloqueSino = llvm::BasicBlock::Create(entorno->contextoLlvm, "sino");
            }
            else // No hay bloqueSino
            {
                // Para cubrir todas las rutas de ejecución, si no hay expresiones
                // tras el SiCondicional, éste debe tener un bloqueSino
                if(!continúa)
                {
                    resultado.error("La condición debería incluir un bloque 'sino'.");
                    resultado.posición(nodo->posición());
                    return resultado;
                }
                else // El bloqueSino cuando no se cumple la condición es bloqueContinúa
                {
                    bloqueSino = bloqueContinúa;
                }
            }

            // Crea nuevo bloqueSiCnd
            bloqueSiCnd = llvm::BasicBlock::Create(entorno->contextoLlvm, "si_condic");

            // Inserto salto en el bloque de donde venimos
            entorno->constructorLlvm.CreateBr(bloqueSiCnd);

            for(índice = 0; índice < (nodo->ramas.size() - 1); índice+=2) // SI / SINO SI
            {
                // CONDICIÓN
                // Desde ahora inserto nuevas instrucciones en el bloqueSiCnd
                funciónActual->getBasicBlockList().push_back(bloqueSiCnd);
                entorno->constructorLlvm.SetInsertPoint(bloqueSiCnd);

                // Construye condición dentro del bloqueSiCnd
                Ñ::Nodo* condición = nodo->ramas[índice];
                Ñ::ResultadoLlvm resultadoCondición = construyeLDA(condición);

                if(resultadoCondición.error())
                {
                    return resultadoCondición;
                }

                llvm::Value* valorCondición = resultadoCondición.valor();

                // SiCond# CndBr ->  [SiBlq#]   [SiCond#+1 || (SinoBlq || Continúa)]
                // Debemos determinar si, en caso de incumplir la condición,
                // saltaremos (y crearemos) un SiCond + 1, un SinoBlq o Continúa

                bloqueSiBlq = llvm::BasicBlock::Create(entorno->contextoLlvm, "si_bloque");

                llvm::BasicBlock* bloqueSiCndNuevo = nullptr;
                // ¿Existe un nuevo par de bloques Si Condicional?
                if(índice < (((int64_t)(nodo->ramas.size())) - 3))
                {
                    // Creo un nuevo SiCond
                    bloqueSiCndNuevo = llvm::BasicBlock::Create(entorno->contextoLlvm, "si_condic");
                    // Creo salto condicional entre SiBlq y nuevo SiCond
                    entorno->constructorLlvm.CreateCondBr(valorCondición, bloqueSiBlq, bloqueSiCndNuevo);
                    bloqueSiCnd = bloqueSiCndNuevo;
                }
                // ¿No, pero existe un SinoBlq al final del SiCondicional?
                else if(índice == (((int64_t)(nodo->ramas.size())) - 3))
                {
                    // Creo salto condicional entre SiBlq y SinoBlq existente
                    entorno->constructorLlvm.CreateCondBr(valorCondición, bloqueSiBlq, bloqueSino);
                }
                // ¿No, y este par SiCnd-SiBlq es el último par del SiCondicional?
                else if(índice == (((int64_t)(nodo->ramas.size())) - 2))
                {
                    // ¿Existe el bloqueContinúa
                    if(continúa)
                    {
                        // Creo salto condicional entre SiBlq y bloqueContinúa existente
                        entorno->constructorLlvm.CreateCondBr(valorCondición, bloqueSiBlq, bloqueContinúa);
                    }
                    else
                    {
                        // Error: (Cuando la función debe devolver un valor)
                        // No se recogen todas las posibles vías de ejecución.
                        resultado.error("No se definen todas las posibles vías de ejecución.");
                        resultado.posición(nodo->posición());
                        return resultado;

                        // Truco: (Cuando la función devuelve 'nada')
                        // Creo un bloqueContinúa final
                        // Creo salto condicional entre SiBlq y bloqueContinúa
                        // Activo inserción en bloqueContinúa
                        // Introduzco la instrucción 'vuelve'
                    }
                }

                // Desde ahora inserto nuevas instrucciones en el bloqueSiBlq
                funciónActual->getBasicBlockList().push_back(bloqueSiBlq);
                entorno->constructorLlvm.SetInsertPoint(bloqueSiBlq);
                // Relleno el bloqueSiBlq

                Ñ::Nodo* nodoBloque = nodo->ramas[índice + 1];

                tablaSímbolos->creaÁmbito(Ñ::Ámbito::ÁMBITO_SUBBLOQUE_FUNCIÓN);
                resultado = construyeInteriorDeBloque(nodoBloque);
                tablaSímbolos->borraÁmbito();
                if(resultado.error())
                {
                    return resultado;
                }
            
                //Después de construir el interior del bloque, puedo haber creado
                //otros bloques (por ejemplo, con sies anidados). Por tanto el bloque actual
                //puede haber cambiado. Por eso, releemos el bloque actual.
                bloqueSiBlq = entorno->constructorLlvm.GetInsertBlock();

                //Introduzco, al final del bloque actual, un salto hasta el bloque tras el condicional
                if(continúa)
                {
                    entorno->constructorLlvm.CreateBr(bloqueContinúa);
                }
                //else
                //{
                //    resultado.error("No se definen todas las posibles vías de ejecución.");
                //    resultado.posición(nodoBloque->posición());
                //    return resultado;
                //}
            }
            
            // BLOQUE SINO
            if( nodo->ramas.size() == (índice + 1)
                && nodo->ramas[índice] != nullptr
                && nodo->ramas[índice]->categoría == Ñ::NODO_BLOQUE)
            {
                //Inserto el bloque Sino al final de la función
                funciónActual->getBasicBlockList().push_back(bloqueSino);
                entorno->constructorLlvm.SetInsertPoint(bloqueSino);

                //Relleno el bloque Sino
                Ñ::Nodo* nodoBloque = nodo->ramas[índice];
                resultado = construyeInteriorDeBloque(nodoBloque);
                if(resultado.error())
                {
                    return resultado;
                }

                bloqueSino = entorno->constructorLlvm.GetInsertBlock();

                if(continúa)
                {
                    entorno->constructorLlvm.CreateBr(bloqueContinúa);
                }

                ++índice;
            }
            
            // BLOQUE CONTINÚA
            if(continúa)
            {
                funciónActual->getBasicBlockList().push_back(bloqueContinúa);
                entorno->constructorLlvm.SetInsertPoint(bloqueContinúa);
            }

            resultado.éxito();
            return resultado;
        }

        Ñ::ResultadoLlvm construyeBucleMientras(Ñ::Nodo* nodo)
        {
            Ñ::ResultadoLlvm resultado;

            if(nodo == nullptr)
            {
                resultado.error("El nodo vale nullptr, esperaba un bucle-mientras.");
                return resultado;
            }

            if(nodo->categoría != Ñ::CategoríaNodo::NODO_BUCLE_MIENTRAS)
            {
                resultado.error("El nodo no es un bucle-mientras.");
                resultado.posición(nodo->posición());
                return resultado;
            }

            bool continúa = true;

            llvm::Function *funciónActual = entorno->constructorLlvm.GetInsertBlock()->getParent();

            int64_t índice = 0;
            
            // Declaro y preparo punteros de los diferentes bloques
            llvm::BasicBlock *bloquePrevio = entorno->constructorLlvm.GetInsertBlock();
            llvm::BasicBlock *bloqueMientrasCnd = llvm::BasicBlock::Create(entorno->contextoLlvm, "mientras_condic");
            llvm::BasicBlock *bloqueMientrasBlq = llvm::BasicBlock::Create(entorno->contextoLlvm, "mientras_blq");
            llvm::BasicBlock *bloqueContinúa = nullptr;

            if(continúa) // La función contiene más expresiones después del SiCondicional
            {
                bloqueContinúa = llvm::BasicBlock::Create(entorno->contextoLlvm, "continúa");
            }
            else
            {
                resultado.error("No se definen todas las posibles vías de ejecución.");
                resultado.posición(nodo->posición());
                return resultado;
            }

            // Inserto salto en el bloque de donde venimos
            entorno->constructorLlvm.CreateBr(bloqueMientrasCnd);

            // CONDICIÓN
            // Desde ahora inserto nuevas instrucciones en el bloqueMientrasCnd
            funciónActual->getBasicBlockList().push_back(bloqueMientrasCnd);
            entorno->constructorLlvm.SetInsertPoint(bloqueMientrasCnd);

            // Construye condición dentro del bloqueMientrasCnd
            Ñ::Nodo* condición = nodo->ramas[0];
            Ñ::ResultadoLlvm resultadoCondición = construyeLDA(condición);

            if(resultadoCondición.error())
            {
                return resultadoCondición;
            }

            llvm::Value* valorCondición = resultadoCondición.valor();

            // MientrasCond CndBr ->  [MientrasBlq]   [Continúa]
            // Debemos determinar si saltaremos al MientrasBlq o ContinúaBlq
            entorno->constructorLlvm.CreateCondBr(valorCondición, bloqueMientrasBlq, bloqueContinúa);

            // Desde ahora inserto nuevas instrucciones en el bloqueMientrasBlq
            funciónActual->getBasicBlockList().push_back(bloqueMientrasBlq);
            entorno->constructorLlvm.SetInsertPoint(bloqueMientrasBlq);
            // Relleno el bloqueMientrasBlq

            Ñ::Nodo* nodoBloque = nodo->ramas[1];

            tablaSímbolos->ponBloqueDestino(bloqueContinúa);
            tablaSímbolos->creaÁmbito(Ñ::Ámbito::ÁMBITO_SUBBLOQUE_FUNCIÓN);
            resultado = construyeInteriorDeBloque(nodoBloque);
            tablaSímbolos->borraÁmbito();
            tablaSímbolos->borraBloqueDestino();

            if(resultado.error())
            {
                return resultado;
            }
            
            //Después de construir el interior del bloque, puedo haber creado
            //otros bloques (por ejemplo, con sies anidados). Por tanto el bloque actual
            //puede haber cambiado. Por eso, releemos el bloque actual.
            bloqueMientrasBlq = entorno->constructorLlvm.GetInsertBlock();

            //Introduzco al final del bloque un salto atrás, hasta el bloque MientrasCnd
            if(continúa)
            {
                entorno->constructorLlvm.CreateBr(bloqueMientrasCnd);
            }
            //else
            //{
            //    resultado.error("No se definen todas las posibles vías de ejecución.");
            //    resultado.posición(nodoBloque->posición());
            //    return resultado;
            //}
            
            // BLOQUE CONTINÚA
            if(continúa)
            {
                funciónActual->getBasicBlockList().push_back(bloqueContinúa);
                entorno->constructorLlvm.SetInsertPoint(bloqueContinúa);
            }

            resultado.éxito();
            return resultado;
        }

        Ñ::ResultadoLlvm construyeAsignación(Ñ::Nodo* nodo)
        {
            Ñ::ResultadoLlvm resultado;

            if(nodo == nullptr)
            {
                resultado.error("He recibido un nodo de valor nullptr, no puedo leer la asignación.");
                return resultado;
            }

            if(nodo->categoría != Ñ::CategoríaNodo::NODO_ASIGNA)
            {
                resultado.error("He recibido un nodo que no es una asignación.");
                resultado.posición(nodo->posición());
                return resultado;
            }

            if(nodo->ramas.size() == 2)
            {
                Ñ::ResultadoLlvm rLia;
                if(jat)
                {
                    rLia = construyeLIAJAT(nodo->ramas[0]);
                }
                else
                {
                    rLia = construyeLIA(nodo->ramas[0]);
                }

                if(rLia.error())
                {
                    return rLia;
                }

                llvm::Value* vLia = rLia.valor();
            
                //std::cout << "construyeAsignación() LDA" << std::endl;
                Ñ::ResultadoLlvm rLda = construyeLDA(nodo->ramas[1]);
                //std::cout << "construyeAsignación() LDA Hecho" << std::endl;
                if(rLda.error())
                {
                    return rLda;
                }

                llvm::Value* vLda = rLda.valor();

                entorno->constructorLlvm.CreateStore(vLda, vLia);

                resultado.éxito();
                return resultado;
            }
            else
            {
                resultado.error("He recibido una asignación mal estructurada, tiene " + std::to_string(nodo->ramas.size()) + " ramas.");
                resultado.posición(nodo->posición());
                return resultado;
            }
        }

        Ñ::ResultadoLlvm construyeDevolución(Ñ::Nodo* nodo)
        {
            Ñ::ResultadoLlvm resultado;

            if(nodo == nullptr)
            {
                resultado.error("He recibido un nodo de valor nullptr, no puedo leer la expresión.");
                return resultado;
            }

            if(nodo->ramas.size() == 1)
            {
                resultado = construyeLDA(nodo->ramas[0]);

                if(resultado.error())
                {
                    return resultado;
                }

                entorno->constructorLlvm.CreateRet(resultado.valor());
                
                llvm::Function *funciónActual = entorno->constructorLlvm.GetInsertBlock()->getParent();
                llvm::BasicBlock* bloqueLlvm = llvm::BasicBlock::Create(entorno->contextoLlvm, "inalcanzable", funciónActual);
                entorno->constructorLlvm.SetInsertPoint(bloqueLlvm);

                entorno->constructorLlvm.CreateUnreachable();

                resultado.éxito();
                return resultado;
            }
            else if(nodo->ramas.size() == 0)
            {
                entorno->constructorLlvm.CreateRetVoid();

                llvm::Function *funciónActual = entorno->constructorLlvm.GetInsertBlock()->getParent();
                llvm::BasicBlock* bloqueLlvm = llvm::BasicBlock::Create(entorno->contextoLlvm, "inalcanzable", funciónActual);
                entorno->constructorLlvm.SetInsertPoint(bloqueLlvm);

                entorno->constructorLlvm.CreateUnreachable();
                resultado.éxito();
                return resultado;
            }
            else
            {
                resultado.error("He recibido un nodo de devolución que tiene más de 1 hijo.");
                resultado.posición(nodo->posición());
                return resultado;
            }
        }

        Ñ::ResultadoLlvm construyeParaBucle(Ñ::Nodo* nodo)
        {
            Ñ::ResultadoLlvm resultado;

            if(nodo == nullptr)
            {
                resultado.error("He recibido un nodo de valor nullptr, no puedo leer la expresión.");
                return resultado;
            }

            if(nodo->ramas.size() == 0)
            {
                llvm::BasicBlock* bucleDestino = tablaSímbolos->leeBloqueDestino();
                if(bucleDestino == nullptr)
                {
                    resultado.error("Instrucción 'para' fuera de un bucle.");
                    resultado.posición(nodo->posición());
                    return resultado;
                }
                entorno->constructorLlvm.CreateBr(bucleDestino);

                llvm::Function *funciónActual = entorno->constructorLlvm.GetInsertBlock()->getParent();
                llvm::BasicBlock* bloqueLlvm = llvm::BasicBlock::Create(entorno->contextoLlvm, "inalcanzable", funciónActual);
                entorno->constructorLlvm.SetInsertPoint(bloqueLlvm);

                entorno->constructorLlvm.CreateUnreachable();

                resultado.éxito();
                return resultado;
            }
            else
            {
                resultado.error("He recibido un nodo de parada de bucle que tiene hijos ¿?.");
                resultado.posición(nodo->posición());
                return resultado;
            }
        }

        Ñ::ResultadoLlvm construyeLIA(Ñ::Nodo* nodo)
        {
            Ñ::ResultadoLlvm resultado;
            
            if(nodo == nullptr)
            {
                resultado.error("He recibido un nodo de valor nullptr, no puedo leer la expresión.");
                return resultado;
            }

            switch (nodo->categoría)
            {
            case Ñ::CategoríaNodo::NODO_DECLARA_VARIABLE:
                resultado = construyeDeclaraciónVariable(nodo);
                break;
            
            case Ñ::CategoríaNodo::NODO_IDENTIFICADOR:
                resultado = construyeVariableLIA(nodo);
                break;
            
            case Ñ::CategoríaNodo::NODO_PUNTERO:
                resultado = construyePunteroLIA(nodo);
                break;
            
            default:
                resultado.error("No sé construir el nodo '" + obténNombreDeNodo(nodo->categoría) + "' como LIA.");
                resultado.posición(nodo->posición());
                break;
            }

            return resultado;
        }

        Ñ::ResultadoLlvm construyeLIAJAT(Ñ::Nodo* nodo)
        {
            Ñ::ResultadoLlvm resultado;
            
            if(nodo == nullptr)
            {
                resultado.error("He recibido un nodo de valor nullptr, no puedo leer la expresión.");
                return resultado;
            }

            switch (nodo->categoría)
            {
            case Ñ::CategoríaNodo::NODO_DECLARA_VARIABLE:
                resultado = construyeDeclaraciónVariableGlobal(nodo);
                break;
            
            case Ñ::CategoríaNodo::NODO_IDENTIFICADOR:
                resultado = construyeVariableLIA(nodo);
                break;
            
            default:
                resultado.error("No puedo construir el nodo '" + obténNombreDeNodo(nodo->categoría) + "' como LIA.");
                resultado.posición(nodo->posición());
                break;
            }

            return resultado;
        }

        Ñ::ResultadoLlvm construyeLDA(Ñ::Nodo* nodo)
        {
            Ñ::ResultadoLlvm resultado;

            if(nodo == nullptr)
            {
                resultado.error("He recibido un nodo de valor nullptr, no puedo leer la expresión.");
                return resultado;
            }

            switch (nodo->categoría)
            {
            case Ñ::CategoríaNodo::NODO_LITERAL:
                //std::cout << "construyeLDA(NODO_LITERAL)" << std::endl;
                resultado = construyeLiteral(nodo);
                //std::cout << "construyeLDA(NODO_LITERAL) Hecho" << std::endl;
                break;
            
            case Ñ::CategoríaNodo::NODO_CONVIERTE_TIPOS:
                resultado = construyeConversorTipos(nodo);
                break;
            
            case Ñ::CategoríaNodo::NODO_IDENTIFICADOR:
                resultado = construyeVariableLDA(nodo);
                break;
                
            case Ñ::CategoríaNodo::NODO_COMPARACIÓN:
                resultado = construyeOperaciónComparación(nodo);
                break;

            case Ñ::CategoríaNodo::NODO_TÉRMINO:
                resultado = construyeOperaciónTérmino(nodo);
                break;

            case Ñ::CategoríaNodo::NODO_FACTOR:
                resultado = construyeOperaciónFactor(nodo);
                break;

            case Ñ::CategoríaNodo::NODO_ELEMENTO_VECTOR:
                resultado = construyeLeeElementoVector(nodo);
                break;

            case Ñ::CategoríaNodo::NODO_LLAMA_FUNCIÓN:
                resultado = construyeLlamadaFunción(nodo);
                break;

            case Ñ::CategoríaNodo::NODO_OP_UNARIA:
                resultado = construyeOperaciónUnaria(nodo);
                break;
            
            default:
                resultado.error("No sé cómo construir el nodo '" + obténNombreDeNodo(nodo->categoría) + "' como LDA.");
                resultado.posición(nodo->posición());
                break;
            }

            return resultado;
        }

        Ñ::ResultadoLlvm construyeDeclaraciónVariable(Ñ::Nodo* nodo)
        {
            Ñ::ResultadoLlvm resultado;

            if(nodo == nullptr)
            {
                resultado.error("He recibido un nodo de valor nullptr, no puedo leer la declaración de variable.");
                return resultado;
            }

            if(nodo->categoría != Ñ::CategoríaNodo::NODO_DECLARA_VARIABLE)
            {
                resultado.error("El nodo no es una declaración de variable, no puedo construirlo.");
                resultado.posición(nodo->posición());
                return resultado;
            }
            
            if(nodo->ramas.size() != 1)
            {
                resultado.error("El nodo 'declaración de variable' no tiene las ramas esperadas, no puedo construirlo.");
                resultado.posición(nodo->posición());
                return resultado;
            }

            std::string nombre;
            llvm::Type* tipo;

            Ñ::DeclaraVariable* dv = (Ñ::DeclaraVariable*)nodo;
            Ñ::Tipo* t = (Ñ::Tipo*)(nodo->ramas[0]);
            tipo = creaTipoLlvm(t);
            if(tipo == nullptr)
            {
                resultado.error("No puedo construir el tipo '" + obténNombreDeTipo(t) + "'.");
                resultado.posición(t->posición());
                return resultado;
            }

            nombre = dv->variable;

            llvm::Value* variable = entorno->constructorLlvm.CreateAlloca(tipo, nullptr, nombre);

            ponId(nombre, variable);

            resultado.éxito();
            resultado.valor(variable);
            return resultado;
        }

        Ñ::ResultadoLlvm construyeDeclaraciónVariableGlobal(Ñ::Nodo* nodo)
        {
            Ñ::ResultadoLlvm resultado;

            if(nodo == nullptr)
            {
                resultado.error("He recibido un nodo de valor nullptr, no puedo leer la declaración de variable.");
                return resultado;
            }

            if(nodo->categoría != Ñ::CategoríaNodo::NODO_DECLARA_VARIABLE)
            {
                resultado.error("El nodo no es una declaración de variable, no puedo construirlo.");
                resultado.posición(nodo->posición());
                return resultado;
            }
            
            if(nodo->ramas.size() != 1)
            {
                resultado.error("El nodo 'declaración de variable' no tiene las ramas esperadas, no puedo construirlo.");
                resultado.posición(nodo->posición());
                return resultado;
            }

            std::string nombre;
            llvm::Type* tipo;

            Ñ::DeclaraVariable* dv = (Ñ::DeclaraVariable*)nodo;
            Ñ::Tipo* t = (Ñ::Tipo*)(nodo->ramas[0]);
            tipo = creaTipoLlvm(t);
            if(tipo == nullptr)
            {
                resultado.error("No puedo construir el tipo '" + obténNombreDeTipo(t) + "'.");
                resultado.posición(t->posición());
                return resultado;
            }

            nombre = dv->variable;

            entorno->globales[nombre] = tipo;

            llvm::Constant* CERO = llvm::ConstantInt::get(tipo, 0);

            //llvm::Value* variable = constructorLlvm.CreateAlloca(tipo, nullptr, nombre);
            llvm::GlobalVariable* varGlobal = new llvm::GlobalVariable(*(móduloLlvm), tipo, false, llvm::GlobalValue::CommonLinkage, CERO, nombre);
            //varGlobal->setAlignment(llvm::MaybeAlign(8));

            ponId(nombre, varGlobal);

            resultado.éxito();
            resultado.valor(varGlobal);
            return resultado;
        }

        Ñ::ResultadoLlvm construyePunteroLIA(Ñ::Nodo* nodo)
        {
            Ñ::ResultadoLlvm resultado;

            if(nodo == nullptr)
            {
                resultado.error("He recibido un nodo de valor nullptr, no puedo leer la variable.");
                return resultado;
            }

            if(nodo->categoría != Ñ::CategoríaNodo::NODO_PUNTERO)
            {
                resultado.error("El nodo no es un puntero, no puedo construir su lectura.");
                resultado.posición(nodo->posición());
                return resultado;
            }
            
            if(nodo->ramas.size() != 1)
            {
                resultado.error("El nodo 'puntero' no tiene las ramas esperadas, no puedo construir su lectura.");
                resultado.posición(nodo->posición());
                return resultado;
            }

            std::string nombre;
            Ñ::Identificador* id;
            llvm::Value* variable;

            id = (Ñ::Identificador*)nodo->ramas[0];
            nombre = id->id;

            variable = leeId(nombre);
            if(variable == nullptr)
            {
                resultado.error("No puedo leer la variable '" + nombre + "'.");
                resultado.posición(id->posición());
                return resultado;
            }

            llvm::Value* variableFinal = entorno->constructorLlvm.CreateLoad(variable);
            if(variableFinal == nullptr)
            {
                resultado.error("No puedo leer la referencia guardada en '" + nombre + "'.");
                resultado.posición(id->posición());
                return resultado;
            }

            resultado.éxito();
            resultado.valor(variableFinal);
            return resultado;
        }

        Ñ::ResultadoLlvm construyeVariableLIA(Ñ::Nodo* nodo)
        {
            Ñ::ResultadoLlvm resultado;

            if(nodo == nullptr)
            {
                resultado.error("He recibido un nodo de valor nullptr, no puedo leer la variable.");
                return resultado;
            }

            if(nodo->categoría != Ñ::CategoríaNodo::NODO_IDENTIFICADOR)
            {
                resultado.error("El nodo no es una variable, no puedo construir su lectura.");
                resultado.posición(nodo->posición());
                return resultado;
            }
            
            if(nodo->ramas.size() != 0)
            {
                resultado.error("El nodo 'identificador' no tiene las ramas esperadas, no puedo construir su lectura.");
                resultado.posición(nodo->posición());
                return resultado;
            }

            std::string nombre;
            Ñ::Identificador* id;
            llvm::Value* variable;

            id = (Ñ::Identificador*)nodo;
            nombre = id->id;

            variable = leeId(nombre);
            if(variable == nullptr)
            {
                resultado.error("No puedo leer la variable '" + nombre + "'.");
                resultado.posición(id->posición());
                return resultado;
            }

            resultado.éxito();
            resultado.valor(variable);
            return resultado;
        }

        Ñ::ResultadoLlvm construyeVariableLDA(Ñ::Nodo* nodo)
        {
            Ñ::ResultadoLlvm resultado;

            if(nodo == nullptr)
            {
                resultado.error("He recibido un nodo de valor nullptr, no puedo leer la variable.");
                return resultado;
            }

            if(nodo->categoría != Ñ::CategoríaNodo::NODO_IDENTIFICADOR)
            {
                resultado.error("El nodo no es una variable, no puedo construir su lectura.");
                resultado.posición(nodo->posición());
                return resultado;
            }
            
            if(nodo->ramas.size() != 0)
            {
                resultado.error("El nodo 'identificador' no tiene las ramas esperadas, no puedo construir su lectura.");
                resultado.posición(nodo->posición());
                return resultado;
            }

            std::string nombre;
            Ñ::Identificador* id;
            llvm::Value* variable;

            id = (Ñ::Identificador*)nodo;
            nombre = id->id;

            if(jat)
            {
                variable = móduloLlvm->getGlobalVariable(nombre, true);
            }
            else
            {
                variable = leeId(nombre);
                if(variable == nullptr)
                {
                    resultado.error("No puedo leer la variable '" + nombre + "'.");
                    resultado.posición(id->posición());
                    return resultado;
                }
            }

            llvm::Value* valor = entorno->constructorLlvm.CreateLoad(variable, nombre);

            resultado.éxito();
            resultado.valor(valor);
            return resultado;
        }

        llvm::Value* convierteValorLlvmATipoLlvm(llvm::Value* valor, Ñ::Tipo* tipoInicial, Ñ::Tipo* tipoDestino)
        {
            llvm::Value* valorFinal;

            if(valor == nullptr)
            {
                return nullptr;
            }

            if(tipoInicial == nullptr)
            {
                return nullptr;
            }

            if(tipoInicial->categoría != Ñ::CategoríaNodo::NODO_TIPO)
            {
                return nullptr;
            }

            if(tipoDestino == nullptr)
            {
                return nullptr;
            }

            if(tipoDestino->categoría != Ñ::CategoríaNodo::NODO_TIPO)
            {
                return nullptr;
            }
            
            llvm::Type* tDestinoLlvm = creaTipoLlvm(tipoDestino);
            if(tDestinoLlvm == nullptr)
            {
                return nullptr;
            }
            
            switch (tipoDestino->tipo)
            {
            case TIPO_BOOLEANO:
            case TIPO_NATURAL_8:
            case TIPO_NATURAL_16:
            case TIPO_NATURAL_32:
            case TIPO_NATURAL_64:
                valorFinal = entorno->constructorLlvm.CreateIntCast(valor, tDestinoLlvm, false);
                break;
            
            case TIPO_ENTERO_8:
            case TIPO_ENTERO_16:
            case TIPO_ENTERO_32:
                valorFinal = entorno->constructorLlvm.CreateIntCast(valor, tDestinoLlvm, true);
                break;

            case TIPO_ENTERO_64:
                if(tipoInicial->tipo == Ñ::CategoríaTipo::TIPO_PUNTERO)
                {
                    valorFinal = entorno->constructorLlvm.CreatePointerCast(valor, tDestinoLlvm);
                }
                else
                {
                    valorFinal = entorno->constructorLlvm.CreateIntCast(valor, tDestinoLlvm, true);
                }
                break;
            
            case TIPO_REAL_32:
            case TIPO_REAL_64:
                switch (tipoInicial->tipo)
                {
                case TIPO_BOOLEANO:
                case TIPO_NATURAL_8:
                case TIPO_NATURAL_16:
                case TIPO_NATURAL_32:
                case TIPO_NATURAL_64:
                    valorFinal = entorno->constructorLlvm.CreateUIToFP(valor, tDestinoLlvm);
                    break;
                
                case TIPO_ENTERO_8:
                case TIPO_ENTERO_16:
                case TIPO_ENTERO_32:
                case TIPO_ENTERO_64:
                    valorFinal = entorno->constructorLlvm.CreateSIToFP(valor, tDestinoLlvm);
                    break;
            
                case TIPO_REAL_32:
                case TIPO_REAL_64:
                    valorFinal = entorno->constructorLlvm.CreateFPCast(valor, tDestinoLlvm);
                    break;
                
                default:
                    valorFinal = nullptr;
                    break;
                }
                break;

            case TIPO_VECTOR:
                if(valor->getType()->isVectorTy())
                {
                    llvm::Type* tipVectorInicial = valor->getType();
                    llvm::Type* tipElementoInicial = tipVectorInicial->getScalarType();
                    llvm::Type* tipVectorDestino = creaTipoLlvm(tipoDestino);
                    llvm::Type* tipElementoDestino = tipVectorDestino->getScalarType();
                    uint64_t tamañoVector = tipoInicial->tamaño();

                    llvm::Value *vectorVacío = llvm::UndefValue::get(tipVectorDestino);
                    valorFinal = vectorVacío;
                    entorno->constructorLlvm.Insert(valorFinal);

                    for(int i = 0; i < tamañoVector; i++)
                    {
                        llvm::Constant* índice = llvm::Constant::getIntegerValue(tipElementoInicial, llvm::APInt(64, i));
                        llvm::Value* valElemento = llvm::ExtractElementInst::Create(valor, índice);
                        entorno->constructorLlvm.Insert(valElemento);

                        Ñ::Tipo* subtipoInicial = tipoInicial->subtipo();
                        Ñ::Tipo* subtipoDestino = tipoDestino->subtipo();
                        valElemento = convierteValorLlvmATipoLlvm(valElemento, subtipoInicial, subtipoDestino);
                        
                        valorFinal = llvm::InsertElementInst::Create(valorFinal, valElemento, índice);
                        entorno->constructorLlvm.Insert(valorFinal);
                    }
                }
                else
                {
                    valorFinal = nullptr;
                }
                break;

            case TIPO_PUNTERO:
                if(tipoInicial->tipo == Ñ::CategoríaTipo::TIPO_VECTOR)
                {
                    //if(!(valor->getType()->isVectorTy()))
                    //{
                    //    return nullptr;
                    //}

                    llvm::Type* tipoEnt64 = llvm::IntegerType::getInt64Ty(entorno->contextoLlvm);
                    auto cero = llvm::ConstantInt::get(entorno->contextoLlvm, llvm::APInt(64, 0, false));
                    llvm::Constant* índicePrimerElemento = llvm::ConstantInt::get(tipoEnt64, 0, false);
                    llvm::Type* tipoInicialLlvm = creaTipoLlvm(tipoInicial);
                    llvm::Type* tipoDestinoLlvm = creaTipoLlvm(tipoDestino);
                    llvm::Type* subtipoInicialLlvm = creaTipoLlvm(tipoInicial->subtipo());
                    llvm::Type* subtipoDestinoLlvm = creaTipoLlvm(tipoDestino->subtipo());
                    if( tipoEnt64 == nullptr ||
                        índicePrimerElemento == nullptr ||
                        tipoInicialLlvm == nullptr ||
                        subtipoInicialLlvm == nullptr ||
                        !(tipoInicialLlvm->isVectorTy()) ||
                        tipoDestinoLlvm == nullptr ||
                        subtipoDestinoLlvm == nullptr ||
                        subtipoDestinoLlvm != subtipoInicialLlvm ||
                        !(tipoDestinoLlvm->isPointerTy())
                      )
                    {
                        return nullptr;
                    }
                    //valorFinal = entorno->constructorLlvm.CreateGEP(tipoInicialLlvm, valor, índicePrimerElemento);
                    //valorFinal = entorno->constructorLlvm.CreateGEP(valor, {cero, índicePrimerElemento});
                    valorFinal = entorno->constructorLlvm.CreateBitCast(valor, tipoDestinoLlvm);
                    //valorFinal = llvm::GetElementPtrInst::Create(tipoDestinoLlvm, valor, { cero, índicePrimerElemento });
                    //valorFinal = llvm::GetElementPtrInst::Create(subtipoInicialLlvm, valor, { cero, índicePrimerElemento }, "", entorno->constructorLlvm.GetInsertBlock());
                    //entorno->constructorLlvm.Insert(valorFinal);
                }
                else
                {
                    valorFinal = entorno->constructorLlvm.CreateIntToPtr(valor, tDestinoLlvm);
                }
                break;

            default:
                valorFinal = nullptr;
                break;
            }

            return valorFinal;
        }

        Ñ::ResultadoLlvm construyeConversorTipos(Ñ::Nodo* nodo)
        {
            Ñ::ResultadoLlvm resultado;

            if(nodo == nullptr)
            {
                resultado.error("He recibido un nodo de valor nullptr, no puedo leer la conversión.");
                return resultado;
            }

            if(nodo->categoría != Ñ::CategoríaNodo::NODO_CONVIERTE_TIPOS)
            {
                resultado.error("El nodo no es un conversor de tipos, no puedo construirlo.");
                resultado.posición(nodo->posición());
                return resultado;
            }

            if(nodo->ramas.size() != 1)
            {
                resultado.error("El nodo conversor de tipos, está mal definido, tiene " + std::to_string(nodo->ramas.size()) + " hijos.");
                resultado.posición(nodo->posición());
                return resultado;
            }

            Ñ::ConvierteTipos* conv = (Ñ::ConvierteTipos*)nodo;

            if(esPuntero(conv->destino))
            {
                resultado = construyeLIA(nodo->ramas[0]);
            }
            else
            {
                resultado = construyeLDA(nodo->ramas[0]);
            }
            if(resultado.error())
            {
                return resultado;
            }

            llvm::Value* valorPrevio = resultado.valor();
            Ñ::Tipo* tOrigen = conv->origen;
            Ñ::Tipo* tDestino = conv->destino;
            llvm::Value* valorFinal = convierteValorLlvmATipoLlvm(valorPrevio, tOrigen, tDestino);
            
            if(valorFinal == nullptr)
            {
                resultado.error("No he conseguido convertir con éxito el valor.");
                resultado.posición(tDestino->posición());
                return resultado;
            }
            else
            {
                resultado.éxito();
                resultado.valor(valorFinal);
                return resultado;
            }
        }

        Ñ::ResultadoLlvm construyeLiteral(Ñ::Nodo* nodo)
        {
            Ñ::ResultadoLlvm resultado;
            
            if(nodo == nullptr)
            {
                resultado.error("He recibido un nodo de valor nullptr, no puedo leer la expresión.");
                return resultado;
            }

            if(nodo->categoría != Ñ::CategoríaNodo::NODO_LITERAL)
            {
                resultado.error("El nodo no es un literal, no puedo construirlo.");
                resultado.posición(nodo->posición());
                return resultado;
            }

            Ñ::Literal* literal = (Ñ::Literal*)nodo;
            Ñ::Tipo* tipo = obténTipoDeLiteral(literal);
            llvm::Type* tipoLlvm;
            uint64_t número;
            float real32;
            double real64;

            switch (tipo->tipo)
            {
            case Ñ::CategoríaTipo::TIPO_BOOLEANO:
                tipoLlvm = creaTipoLlvm(tipo);
                if(tipoLlvm == nullptr)
                {
                    resultado.error("No puedo construir el tipo '" + obténNombreDeTipo(tipo) + "'.");
                    resultado.posición(tipo->posición());
                    return resultado;
                }
                if(literal->dato == "cierto")
                {
                    número = 1;
                }
                else if(literal->dato == "falso")
                {
                    número = 0;
                }
                else
                {
                    número = std::stoull(literal->dato);
                    if(número != 0)
                    {
                        número = 1;
                    }
                }
                resultado.éxito();
                resultado.valor(llvm::ConstantInt::get(tipoLlvm, número));
                break;
                
            case Ñ::CategoríaTipo::TIPO_NATURAL_8:
                tipoLlvm = creaTipoLlvm(tipo);
                if(tipoLlvm == nullptr)
                {
                    resultado.error("No puedo construir el tipo '" + obténNombreDeTipo(tipo) + "'.");
                    resultado.posición(tipo->posición());
                    return resultado;
                }
                número = std::stoull(literal->dato);
                resultado.éxito();
                resultado.valor(llvm::ConstantInt::get(tipoLlvm, número));
                break;
                
            case Ñ::CategoríaTipo::TIPO_NATURAL_16:
                tipoLlvm = creaTipoLlvm(tipo);
                if(tipoLlvm == nullptr)
                {
                    resultado.error("No puedo construir el tipo '" + obténNombreDeTipo(tipo) + "'.");
                    resultado.posición(tipo->posición());
                    return resultado;
                }
                número = std::stoull(literal->dato);
                resultado.éxito();
                resultado.valor(llvm::ConstantInt::get(tipoLlvm, número));
                break;
                
            case Ñ::CategoríaTipo::TIPO_NATURAL_32:
                tipoLlvm = creaTipoLlvm(tipo);
                if(tipoLlvm == nullptr)
                {
                    resultado.error("No puedo construir el tipo '" + obténNombreDeTipo(tipo) + "'.");
                    resultado.posición(tipo->posición());
                    return resultado;
                }
                número = std::stoull(literal->dato);
                resultado.éxito();
                resultado.valor(llvm::ConstantInt::get(tipoLlvm, número));
                break;

            case Ñ::CategoríaTipo::TIPO_NATURAL_64:
                tipoLlvm = creaTipoLlvm(tipo);
                if(tipoLlvm == nullptr)
                {
                    resultado.error("No puedo construir el tipo '" + obténNombreDeTipo(tipo) + "'.");
                    resultado.posición(tipo->posición());
                    return resultado;
                }
                número = std::stoull(literal->dato);
                resultado.éxito();
                resultado.valor(llvm::ConstantInt::get(tipoLlvm, número));
                break;
            
            case Ñ::CategoríaTipo::TIPO_ENTERO_8:
                tipoLlvm = creaTipoLlvm(tipo);
                if(tipoLlvm == nullptr)
                {
                    resultado.error("No puedo construir el tipo '" + obténNombreDeTipo(tipo) + "'.");
                    resultado.posición(tipo->posición());
                    return resultado;
                }
                número = std::stoll(literal->dato);
                resultado.éxito();
                resultado.valor(llvm::ConstantInt::get(tipoLlvm, número, true));
                break;
            
            case Ñ::CategoríaTipo::TIPO_ENTERO_16:
                tipoLlvm = creaTipoLlvm(tipo);
                if(tipoLlvm == nullptr)
                {
                    resultado.error("No puedo construir el tipo '" + obténNombreDeTipo(tipo) + "'.");
                    resultado.posición(tipo->posición());
                    return resultado;
                }
                número = std::stoll(literal->dato);
                resultado.éxito();
                resultado.valor(llvm::ConstantInt::get(tipoLlvm, número, true));
                break;
            
            case Ñ::CategoríaTipo::TIPO_ENTERO_32:
                tipoLlvm = creaTipoLlvm(tipo);
                if(tipoLlvm == nullptr)
                {
                    resultado.error("No puedo construir el tipo '" + obténNombreDeTipo(tipo) + "'.");
                    resultado.posición(tipo->posición());
                    return resultado;
                }
                número = std::stoll(literal->dato);
                resultado.éxito();
                resultado.valor(llvm::ConstantInt::get(tipoLlvm, número, true));
                break;
            
            case Ñ::CategoríaTipo::TIPO_ENTERO_64:
                tipoLlvm = creaTipoLlvm(tipo);
                if(tipoLlvm == nullptr)
                {
                    resultado.error("No puedo construir el tipo '" + obténNombreDeTipo(tipo) + "'.");
                    resultado.posición(tipo->posición());
                    return resultado;
                }
                número = std::stoll(literal->dato);
                resultado.éxito();
                resultado.valor(llvm::ConstantInt::get(tipoLlvm, número, true));
                break;
            
            case Ñ::CategoríaTipo::TIPO_REAL_32:
                tipoLlvm = creaTipoLlvm(tipo);
                if(tipoLlvm == nullptr)
                {
                    resultado.error("No puedo construir el tipo '" + obténNombreDeTipo(tipo) + "'.");
                    resultado.posición(tipo->posición());
                    return resultado;
                }
                real32 = std::stof(literal->dato);
                resultado.éxito();
                resultado.valor(llvm::ConstantFP::get(tipoLlvm, real32));
                break;
            
            case Ñ::CategoríaTipo::TIPO_REAL_64:
                tipoLlvm = creaTipoLlvm(tipo);
                if(tipoLlvm == nullptr)
                {
                    resultado.error("No puedo construir el tipo '" + obténNombreDeTipo(tipo) + "'.");
                    resultado.posición(tipo->posición());
                    return resultado;
                }
                real64 = std::stod(literal->dato);
                resultado.éxito();
                resultado.valor(llvm::ConstantFP::get(tipoLlvm, real64));
                break;
            
            case Ñ::CategoríaTipo::TIPO_VECTOR:
                {
                    //std::cout << "construyeLiteral(TIPO_VECTOR)" << std::endl;

                    tipoLlvm = creaTipoLlvm(tipo);
                    if(tipoLlvm == nullptr)
                    {
                        resultado.error("No puedo construir el tipo '" + obténNombreDeTipo(tipo) + "'.");
                        resultado.posición(tipo->posición());
                        return resultado;
                    }
                    llvm::Value *vectorVacío = llvm::UndefValue::get(tipoLlvm);
                    llvm::Value* vectorFinal = vectorVacío;
                    int64_t índice = 0;
                    for(Ñ::Nodo* subnodo : literal->ramas)
                    {
                        //std::cout << "construyeLiteral(TIPO_VECTOR) subtipo" << índice << std::endl;

                        //std::cout << "construyeLiteral(TIPO_VECTOR) extraigo subvalor de subnodo" << índice << std::endl;

                        //llvm::Constant* índiceLlvm = llvm::Constant::getIntegerValue(tipoLlvm->getScalarType(), llvm::APInt(64, índice));
                        ResultadoLlvm rSubvalor = construyeLiteral(subnodo);
                        if(rSubvalor.error())
                        {
                            return rSubvalor;
                        }
                        llvm::Value* subvalor = rSubvalor.valor();

                        //std::cout << "construyeLiteral(TIPO_VECTOR) inserto subvalor en vector" << índice << std::endl;

                        llvm::Value* nuevoVectorFinal = entorno->constructorLlvm.CreateInsertElement(vectorFinal, subvalor, índice);

                        //llvm::Value* nuevoVectorFinal = llvm::InsertElementInst::Create(vectorFinal, subvalor, índiceLlvm);
                        vectorFinal = nuevoVectorFinal;
                        
                        //std::cout << "construyeLiteral(TIPO_VECTOR) añado la instrucción al constructor" << índice << std::endl;

                        //entorno->constructorLlvm.Insert(vectorFinal);
                        
                        índice++;
                    }
                    
                    //std::cout << "construyeLiteral(TIPO_VECTOR) éxito"<< std::endl;

                    resultado.éxito();
                    resultado.valor(vectorFinal);
                }
                break;
            
            default:
                resultado.error("No reconozco el tipo del literal.");
                resultado.posición(nodo->posición());
                break;
            }

            return resultado;
        }

        Ñ::ResultadoLlvm construyeOperaciónComparación(Ñ::Nodo* nodo)
        {
            Ñ::ResultadoLlvm resultado;
            llvm::Value* v1;
            llvm::Value* v2;

            Ñ::ResultadoLlvm rV1 = construyeLDA(nodo->ramas[0]);
            if(rV1.error())
            {
                return rV1;
            }
            v1 = rV1.valor();
            
            for(int i = 1; i < nodo->ramas.size(); i++)
            {
                Ñ::Nodo* nOp = nodo->ramas[i];

                if(nOp == nullptr)
                {
                    resultado.error("Esperaba una operación binaria y he recibido un nodo nulo.");
                    resultado.posición(nodo->posición());
                    return resultado;
                }
                else if(nOp->categoría != Ñ::CategoríaNodo::NODO_OP_BINARIA)
                {
                    resultado.error("Esperaba una operación binaria y he recibido un nodo de otro tipo.");
                    resultado.posición(nodo->ramas[i]->posición());
                    return resultado;
                }

                Ñ::ResultadoLlvm rV2 = construyeLDA(nOp->ramas[0]);
                if(rV2.error())
                {
                    return rV2;
                }
                v2 = rV2.valor();

                Ñ::OperaciónBinaria* op = (Ñ::OperaciónBinaria*)nOp;

                Ñ::Tipo* tipo = op->tipo;

                if(esBooleano(tipo) || esNatural(tipo))
                {
                    if(op->operación == "<")
                    {
                        v1 = entorno->constructorLlvm.CreateICmpULT(v1, v2, "cmp_menorque_tmp");
                    }
                    else if(op->operación == ">")
                    {
                        v1 = entorno->constructorLlvm.CreateICmpUGT(v1, v2, "cmp_mayorque_tmp");
                    }
                    else if(op->operación == "==")
                    {
                        v1 = entorno->constructorLlvm.CreateICmpEQ(v1, v2, "cmp_igualque_tmp");
                    }
                    else if(op->operación == "!=")
                    {
                        v1 = entorno->constructorLlvm.CreateICmpNE(v1, v2, "cmp_distintoa_tmp");
                    }
                    else if(op->operación == "<=")
                    {
                        v1 = entorno->constructorLlvm.CreateICmpULE(v1, v2, "cmp_menorigual_tmp");
                    }
                    else if(op->operación == ">=")
                    {
                        v1 = entorno->constructorLlvm.CreateICmpUGE(v1, v2, "cmp_mayorigual_tmp");
                    }
                }
                else if(esPuntero(tipo) || esEntero(tipo))
                {
                    if(op->operación == "<")
                    {
                        v1 = entorno->constructorLlvm.CreateICmpSLT(v1, v2, "cmp_menorque_tmp");
                    }
                    else if(op->operación == ">")
                    {
                        v1 = entorno->constructorLlvm.CreateICmpSGT(v1, v2, "cmp_mayorque_tmp");
                    }
                    else if(op->operación == "==")
                    {
                        v1 = entorno->constructorLlvm.CreateICmpEQ(v1, v2, "cmp_igualque_tmp");
                    }
                    else if(op->operación == "!=")
                    {
                        v1 = entorno->constructorLlvm.CreateICmpNE(v1, v2, "cmp_distintoa_tmp");
                    }
                    else if(op->operación == "<=")
                    {
                        v1 = entorno->constructorLlvm.CreateICmpSLE(v1, v2, "cmp_menorigual_tmp");
                    }
                    else if(op->operación == ">=")
                    {
                        v1 = entorno->constructorLlvm.CreateICmpSGE(v1, v2, "cmp_mayorigual_tmp");
                    }
                }
                else if(esReal(tipo))
                {
                    if(op->operación == "<")
                    {
                        v1 = entorno->constructorLlvm.CreateFCmpULT(v1, v2, "cmp_menorque_tmp");
                    }
                    else if(op->operación == ">")
                    {
                        v1 = entorno->constructorLlvm.CreateFCmpUGT(v1, v2, "cmp_mayorque_tmp");
                    }
                    else if(op->operación == "==")
                    {
                        v1 = entorno->constructorLlvm.CreateFCmpUEQ(v1, v2, "cmp_igualque_tmp");
                    }
                    else if(op->operación == "==")
                    {
                        v1 = entorno->constructorLlvm.CreateFCmpUNE(v1, v2, "cmp_distintoa_tmp");
                    }
                    else if(op->operación == "<=")
                    {
                        v1 = entorno->constructorLlvm.CreateFCmpULE(v1, v2, "cmp_menorigual_tmp");
                    }
                    else if(op->operación == ">=")
                    {
                        v1 = entorno->constructorLlvm.CreateFCmpUGE(v1, v2, "cmp_mayorigual_tmp");
                    }
                }
                else
                {
                    resultado.error("No sé comparar operandos de tipo '" + obténNombreDeTipo(tipo) + "'.");
                    resultado.posición(op->posición());
                    return resultado;
                }
            }

            resultado.éxito();
            resultado.valor(v1);
            return resultado;
        }

        Ñ::ResultadoLlvm construyeOperaciónTérmino(Ñ::Nodo* nodo)
        {
            Ñ::ResultadoLlvm resultado;
            llvm::Value* v1;
            llvm::Value* v2;

            Ñ::ResultadoLlvm rV1 = construyeLDA(nodo->ramas[0]);
            if(rV1.error())
            {
                return rV1;
            }
            v1 = rV1.valor();
            
            for(int i = 1; i < nodo->ramas.size(); i++)
            {
                Ñ::Nodo* nOp = nodo->ramas[i];

                if(nOp == nullptr)
                {
                    resultado.error("Esperaba una operación binaria y he recibido un nodo nulo.");
                    resultado.posición(nodo->posición());
                    return resultado;
                }
                else if(nOp->categoría != Ñ::CategoríaNodo::NODO_OP_BINARIA)
                {
                    resultado.error("Esperaba una operación binaria y he recibido un nodo de otro tipo.");
                    resultado.posición(nodo->ramas[i]->posición());
                    return resultado;
                }

                Ñ::ResultadoLlvm rV2 = construyeLDA(nOp->ramas[0]);
                if(rV2.error())
                {
                    return rV2;
                }
                v2 = rV2.valor();

                Ñ::OperaciónBinaria* op = (Ñ::OperaciónBinaria*)nOp;

                Ñ::Tipo* tipo = op->tipo;

                if(op->operación == "+")
                {
                    if(esReal(tipo))
                    {
                        v1 = entorno->constructorLlvm.CreateFAdd(v1, v2, "suma");
                    }
                    else if(esEntero(tipo) || esNatural(tipo))
                    {
                        v1 = entorno->constructorLlvm.CreateAdd(v1, v2, "suma");
                    }
                    else
                    {
                        resultado.error("No puedo realizar la operación '" + op->operación + "', tipos incompatibles.");
                        resultado.posición(op->posición());
                        return resultado;
                    }
                }
                else if(op->operación == "-")
                {
                    if(esReal(tipo))
                    {
                        v1 = entorno->constructorLlvm.CreateFSub(v1, v2, "resta");
                    }
                    else if(esEntero(tipo) || esNatural(tipo))
                    {
                        v1 = entorno->constructorLlvm.CreateSub(v1, v2, "resta");
                    }
                    else
                    {
                        resultado.error("No puedo realizar la operación '" + op->operación + "', tipos incompatibles.");
                        resultado.posición(op->posición());
                        return resultado;
                    }
                }
                else
                {
                    resultado.error("No reconozco la operación '" + op->operación + "'.");
                    resultado.posición(op->posición());
                    return resultado; 
                }
            }

            resultado.éxito();
            resultado.valor(v1);
            return resultado;
        }

        Ñ::ResultadoLlvm construyeOperaciónFactor(Ñ::Nodo* nodo)
        {
            Ñ::ResultadoLlvm resultado;
            llvm::Value* v1;
            llvm::Value* v2;

            Ñ::ResultadoLlvm rV1 = construyeLDA(nodo->ramas[0]);
            if(rV1.error())
            {
                return rV1;
            }
            v1 = rV1.valor();
            
            for(int i = 1; i < nodo->ramas.size(); i++)
            {
                Ñ::Nodo* nOp = nodo->ramas[i];

                if(nOp == nullptr)
                {
                    resultado.error("Esperaba una operación binaria y he recibido un nodo nulo.");
                    resultado.posición(nodo->posición());
                    return resultado;
                }
                else if(nOp->categoría != Ñ::CategoríaNodo::NODO_OP_BINARIA)
                {
                    resultado.error("Esperaba una operación binaria y he recibido un nodo de otro tipo.");
                    resultado.posición(nOp->posición());
                    return resultado;
                }

                Ñ::ResultadoLlvm rV2 = construyeLDA(nOp->ramas[0]);
                if(rV2.error())
                {
                    return rV2;
                }
                v2 = rV2.valor();

                Ñ::OperaciónBinaria* op = (Ñ::OperaciónBinaria*)nOp;

                Ñ::Tipo* tipo = op->tipo;

                if(op->operación == "*")
                {
                    if(esReal(tipo))
                    {
                        v1 = entorno->constructorLlvm.CreateFMul(v1, v2, "multiplicación");
                    }
                    else if(esEntero(tipo) || esNatural(tipo))
                    {
                        v1 = entorno->constructorLlvm.CreateMul(v1, v2, "multiplicación");
                    }
                    else
                    {
                        resultado.error("No puedo realizar la operación '" + op->operación + "', tipos incompatibles.");
                        resultado.posición(op->posición());
                        return resultado;
                    }
                }
                else if(op->operación == "/")
                {
                    if(esReal(tipo))
                    {
                        v1 = entorno->constructorLlvm.CreateFDiv(v1, v2, "división");
                    }
                    else if(esEntero(tipo))
                    {
                        v1 = entorno->constructorLlvm.CreateSDiv(v1, v2, "división");
                    }
                    else if(esNatural(tipo))
                    {
                        v1 = entorno->constructorLlvm.CreateUDiv(v1, v2, "división");
                    }
                    else
                    {
                        resultado.error("No puedo realizar la operación '" + op->operación + "', tipos incompatibles.");
                        resultado.posición(op->posición());
                        return resultado;
                    }
                }
                else if(op->operación == "%")
                {
                    if(esReal(tipo))
                    {
                        v1 = entorno->constructorLlvm.CreateFRem(v1, v2, "resto");
                    }
                    else if(esEntero(tipo))
                    {
                        v1 = entorno->constructorLlvm.CreateSRem(v1, v2, "resto");
                    }
                    else if(esNatural(tipo))
                    {
                        v1 = entorno->constructorLlvm.CreateURem(v1, v2, "resto");
                    }
                    else
                    {
                        resultado.error("No puedo realizar la operación '" + op->operación + "', tipos incompatibles.");
                        resultado.posición(op->posición());
                        return resultado;
                    }
                }
                else
                {
                    resultado.error("No reconozco la operación '" + op->operación + "'.");
                    resultado.posición(op->posición());
                    return resultado; 
                }
            }

            resultado.éxito();
            resultado.valor(v1);
            return resultado;
        }

        Ñ::ResultadoLlvm construyeOperaciónUnaria(Ñ::Nodo* nodo)
        {
            Ñ::ResultadoLlvm resultado;
            Ñ::OperaciónUnaria* op = (Ñ::OperaciónUnaria*)nodo;
            Ñ::Nodo* hijo = nodo->ramas[0];
            llvm::Value* valor;
            llvm::Value* valorFinal;
            
            if(op->operación == "@")
            {
                if(hijo == nullptr)
                {
                    resultado.error("No puedo leer la dirección de memoria.");
                    resultado.posición(nodo->posición());
                    return resultado;
                }

                if(hijo->categoría != Ñ::CategoríaNodo::NODO_IDENTIFICADOR)
                {
                    resultado.error("No puedes leer la dirección de memoria de un '" + obténNombreDeNodo(hijo->categoría) + "'.");
                    resultado.posición(hijo->posición());
                    return resultado;
                }

                Ñ::Identificador* id = (Ñ::Identificador*)hijo;
                valorFinal = leeId(id->id);

                if(valorFinal == nullptr)
                {
                    resultado.error("No puedo leer la dirección de memoria de la variable '" + id->id + "'.");
                    resultado.posición(nodo->posición());
                    return resultado;
                }

                resultado.éxito();
                resultado.valor(valorFinal);
                return resultado;
            }
            else if(op->operación == "*")
            {
                if(hijo == nullptr)
                {
                    resultado.error("No puedo leer la dirección de memoria.");
                    resultado.posición(nodo->posición());
                    return resultado;
                }

                Ñ::ResultadoLlvm rValor = construyeLDA(hijo);
                if(rValor.error())
                {
                    return rValor;
                }
                
                // Lee contenido de dirección de memoria
                valorFinal = entorno->constructorLlvm.CreateLoad(rValor.valor());

                if(valorFinal == nullptr)
                {
                    resultado.error("No puedo leer el contenido de la dirección de memoria.");
                    resultado.posición(nodo->posición());
                    return resultado;
                }

                resultado.éxito();
                resultado.valor(valorFinal);
                return resultado;
            }

            resultado.error("No sé construir la operación '" + op->operación + "'.");
            resultado.posición(nodo->posición());
            return resultado;
        }

        Ñ::ResultadoLlvm construyeLeeElementoVector(Ñ::Nodo* nodo)
        {
            Ñ::ResultadoLlvm resultado;
            llvm::Value* vec;
            llvm::Value* pos;

            Ñ::ResultadoLlvm rVec = construyeLDA(nodo->ramas[0]);
            if(rVec.error())
            {
                return rVec;
            }
            vec = rVec.valor();

            Ñ::ResultadoLlvm rPos = construyeLDA(nodo->ramas[1]);
            if(rPos.error())
            {
                return rPos;
            }
            pos = rPos.valor();

            llvm::Value* vElemento = entorno->constructorLlvm.CreateExtractElement(vec, pos);

            resultado.éxito();
            resultado.valor(vElemento);
            return resultado;
        }

        Ñ::ResultadoLlvm construyeLlamadaFunción(Ñ::Nodo* nodo)
        {
            Ñ::ResultadoLlvm resultado;
            
            if(nodo == nullptr)
            {
                resultado.error("Esperaba una llamada a una función, pero el nodo es nulo.");
                return resultado;
            }

            if(nodo->categoría != Ñ::CategoríaNodo::NODO_LLAMA_FUNCIÓN)
            {
                resultado.error("Esperaba una llamada a una función, pero el nodo es de una categoría inesperada.");
                resultado.posición(nodo->posición());
                return resultado;
            }

            Ñ::LlamaFunción* fn = (Ñ::LlamaFunción*)nodo;
            llvm::Function* funciónLlvm = móduloLlvm->getFunction(fn->nombre);
            
            if(!funciónLlvm)
            {
                resultado.error("Esperaba una llamada a una función, pero parece que la función \"" + fn->nombre + "()\" no existe.");
                resultado.posición(nodo->posición());
                return resultado;
            }
            
            std::vector<llvm::Value*> argumentos;

            // Preparando argumentos
            Ñ::Nodo* args = nodo->ramas[0];

            std::vector<llvm::Value*> valoresArgumentos;
            
            for(Ñ::Nodo* n : args->ramas)
            {
                resultado = construyeLDA(n);
                if(resultado.error())
                {
                    return resultado;
                }

                valoresArgumentos.push_back(resultado.valor());

            }

            if(funciónLlvm->getReturnType()->isVoidTy())
            {
                entorno->constructorLlvm.CreateCall(funciónLlvm, valoresArgumentos);
                resultado.éxito();
                resultado.valor(nullptr);
            }
            else
            {
                llvm::Value* devuelto = entorno->constructorLlvm.CreateCall(funciónLlvm, valoresArgumentos, fn->nombre);
                resultado.éxito();
                resultado.valor(devuelto);
            }

            return resultado;
        }
    };

    Ñ::ResultadoLlvm construye(Ñ::Nodo* árbol, Ñ::EntornoConstrucción* entorno, Ñ::CategoríaNodo categoríaNodo)
    {
        //std::cout << "construye(nodo)" << std::endl;

        Ñ::entorno = entorno;

        Ñ::ResultadoLlvm resultado;

        Ñ::Constructor* constructor = new Ñ::Constructor;

        //std::cout << std::endl;

        //muestraNodos(árbol);

        //std::cout << std::endl;
        //std::cout << std::endl;

        if(categoríaNodo == Ñ::CategoríaNodo::NODO_MÓDULO && árbol->categoría == Ñ::CategoríaNodo::NODO_MÓDULO)
        {
            Ñ::ResultadoLlvm rMódulo = constructor->construyeMódulo(árbol);
            if(rMódulo.error())
            {
                return rMódulo;
            }

            resultado.módulo(constructor->móduloLlvm);
        }
        else if(categoríaNodo == Ñ::CategoríaNodo::NODO_EXPRESIÓN && árbol->categoría == Ñ::CategoríaNodo::NODO_EXPRESIÓN)
        {
            //std::cout << "Preparando construcción 'justo a tiempo'" << std::endl << std::endl;
            
            llvm::InitializeNativeTarget();
            llvm::InitializeNativeTargetAsmPrinter();
            llvm::InitializeNativeTargetAsmParser();

            if(!jat)
            {
                jat = Ñ::ConstructorJAT::Crea();
            }
            
            Ñ::ResultadoLlvm rExpresión = constructor->construyeExpresiónPrimerNivel(árbol);
            
            if(rExpresión.error())
            {
                resultado.error(rExpresión.mensaje());
                return resultado;
            }

            constructor->móduloLlvm->print(llvm::outs(), nullptr);
            resultado.módulo(constructor->móduloLlvm);

            std::unique_ptr<llvm::Module> módulo(constructor->móduloLlvm);
            jat->añadeMódulo(std::move(módulo));

            llvm::Expected<llvm::JITEvaluatedSymbol> funciónEvaluadaJAT = jat->busca("__función_anónima__");

            if(auto error = funciónEvaluadaJAT.takeError())
            {
                resultado.error("El constructor JAT no encuentra el símbolo '__función_anónima__()'.");
                return resultado;
            }
            
            void (*funciónJAT)() = (void (*)())(*funciónEvaluadaJAT).getAddress();

            std::cout << "ejecutando '__función_anónima__()' ...";

            funciónJAT();

            std::cout << "Elimino '__función_anónima__()' ...";
            
            jat->eliminaSímbolo("__función_anónima__");

            llvm::Expected<llvm::JITEvaluatedSymbol> variableEvaluadaJAT = jat->busca("a");

            if(auto error = variableEvaluadaJAT.takeError())
            {
                resultado.error("El constructor JAT no encuentra el símbolo 'a()'.");
                return resultado;
            }
            
            int64_t* entero = (int64_t*)(*variableEvaluadaJAT).getAddress();

            std::cout << "La variable global 'a' vale '" << std::to_string(*entero) << "'." << std::endl;
        }

        resultado.éxito();
        return resultado;
    }
}