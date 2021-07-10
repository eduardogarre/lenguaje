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
#include "llvm/Support/TargetSelect.h"
#include "llvm/Support/TypeName.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/Transforms/InstCombine/InstCombine.h"
#include "llvm/Transforms/Scalar.h"
#include "llvm/Transforms/Scalar/GVN.h"

#include "constructor.hpp"
#include "justoatiempo.hpp"
#include "nodo.hpp"
#include "promotor.hpp"
#include "resultadollvm.hpp"
#include "tipo.hpp"

namespace Ñ
{
    class Símbolos
    {
    private:
        std::vector<std::map<std::string, llvm::Value*>> tabla;

    public:
        Símbolos() {}

        ~Símbolos() {}

        void abreBloque()
        {
            std::map<std::string, llvm::Value*> ámbito;
            tabla.push_back(ámbito);
        }

        void cierraBloque()
        {
            tabla.pop_back();
        }

        void ponId(std::string id, llvm::Value* valor)
        {
            if(tabla.size() < 1)
            {
                std::cout << "Error, no es posible guardar el identificador '" << id << "', la tabla de símbolos tiene " << std::to_string(tabla.size()) << " niveles" << std::endl;
                return;
            }

            tabla[tabla.size() - 1][id] = valor;
        }

        llvm::Value* leeId(std::string id)
        {
            llvm::Value* valor = nullptr;

            for(int i = tabla.size() - 1; i >= 0; i--)
            {
                valor = tabla.at(i).at(id);
                if(valor != nullptr)
                {
                    return valor;
                }
            }
            
            return nullptr;
        }
    };

    class Promotor
    {
    public:
        llvm::LLVMContext contextoLlvm;
        llvm::Module* móduloLlvm = nullptr;
        llvm::legacy::FunctionPassManager* gestorPasesOptimización = nullptr;
        llvm::IRBuilder<> constructorLlvm;
        Ñ::Símbolos* tablaSímbolos = nullptr;
        Ñ::ConstructorJAT* jat = nullptr;

    public:
        Promotor() : constructorLlvm(contextoLlvm)
        {

        }

        ~Promotor()
        {
            if(tablaSímbolos != nullptr)
            {
                delete tablaSímbolos;
            }
        }

        void preparaMódulo(std::string nombre)
        {

            // Creo el módulo LLVM y le asigno el nombre de mi módulo
            móduloLlvm = new llvm::Module(nombre, contextoLlvm);

            gestorPasesOptimización = new llvm::legacy::FunctionPassManager(móduloLlvm);

            // Optimizaciones se secuencias cortas y pequeños reordenamientos.
            gestorPasesOptimización->add(llvm::createInstructionCombiningPass());
            // Reassociate expressions.
            gestorPasesOptimización->add(llvm::createReassociatePass());
            // Elimina subexpresiones comunes.
            gestorPasesOptimización->add(llvm::createGVNPass());
            // Simplifica el grafo de flujo de ejecución (elimina bloques inalcanzables, etc)
            gestorPasesOptimización->add(llvm::createCFGSimplificationPass());

            gestorPasesOptimización->doInitialization();
        }

        void preparaMóduloJAT(std::string nombre)
        {

            // Creo el módulo LLVM y le asigno el nombre de mi módulo
            móduloLlvm = new llvm::Module(nombre, contextoLlvm);

            móduloLlvm->setDataLayout(jat->leeDisposiciónDatos());
        }

        void preparaPasesDeOptimización()
        {
            gestorPasesOptimización = new llvm::legacy::FunctionPassManager(móduloLlvm);

            // Optimizaciones se secuencias cortas y pequeños reordenamientos.
            gestorPasesOptimización->add(llvm::createInstructionCombiningPass());
            // Reassociate expressions.
            gestorPasesOptimización->add(llvm::createReassociatePass());
            // Elimina subexpresiones comunes.
            gestorPasesOptimización->add(llvm::createGVNPass());
            // Simplifica el grafo de flujo de ejecución (elimina bloques inalcanzables, etc)
            gestorPasesOptimización->add(llvm::createCFGSimplificationPass());

            gestorPasesOptimización->doInitialization();
        }

        void ponId(std::string id, llvm::Value* valor)
        {
            if(tablaSímbolos != nullptr)
            {
                tablaSímbolos->ponId(id, valor);
            }
            else
            {
                std::cout << "Error, no puedo guardar el símbolo '" << id << "' en la tabla" << std::endl;
            }
        }

        llvm::Value* leeId(std::string id)
        {
            llvm::Value* valor = nullptr;

            if(tablaSímbolos != nullptr)
            {
                valor = tablaSímbolos->leeId(id);
                if(valor != nullptr)
                {
                    return valor;
                }
            }
            else
            {
                std::cout << "Error, no se ha iniciado la tabla, no puedo guardar el símbolo '" << id << "'" << std::endl;
            }

            std::cout << "Error, no he encontrado el símbolo '" << id << "'" << std::endl;
            
            return nullptr;
        }

        llvm::Type* creaTipoLlvm(Ñ::CategoríaTipo tipo)
        {
            switch (tipo)
            {
            case TIPO_NADA:
                return llvm::Type::getVoidTy(contextoLlvm);
                break;
            
            case TIPO_BOOLEANO:
                return llvm::Type::getInt1Ty(contextoLlvm);
                break;
            
            case TIPO_NATURAL_8:
                return llvm::Type::getInt8Ty(contextoLlvm);
                break;
            
            case TIPO_NATURAL_16:
                return llvm::Type::getInt16Ty(contextoLlvm);
                break;
            
            case TIPO_NATURAL_32:
                return llvm::Type::getInt32Ty(contextoLlvm);
                break;
            
            case TIPO_NATURAL_64:
                return llvm::Type::getInt64Ty(contextoLlvm);
                break;
            
            case TIPO_ENTERO_8:
                return llvm::Type::getInt8Ty(contextoLlvm);
                break;
            
            case TIPO_ENTERO_16:
                return llvm::Type::getInt16Ty(contextoLlvm);
                break;
            
            case TIPO_ENTERO_32:
                return llvm::Type::getInt32Ty(contextoLlvm);
                break;
            
            case TIPO_ENTERO_64:
                return llvm::Type::getInt64Ty(contextoLlvm);
                break;
            
            case TIPO_REAL_32:
                return llvm::Type::getFloatTy(contextoLlvm);
                break;
            
            case TIPO_REAL_64:
                return llvm::Type::getDoubleTy(contextoLlvm);
                break;
            
            default:
                return nullptr;
                break;
            }
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

            preparaMódulo(módulo->módulo);
            preparaPasesDeOptimización();

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

            resultado = _construyeDeclaraciónFunción(función->nombre, nodo->ramas[0], nodo->ramas[1]);
            if(resultado.error())
            {
                return resultado;
            }
            
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

            // Inicio construcción del bloque y definición de los argumentos
            tablaSímbolos = new Símbolos;
            tablaSímbolos->abreBloque();

            std::string nombreBloque = "entrada";
            llvm::BasicBlock* bloqueLlvm = llvm::BasicBlock::Create(contextoLlvm, nombreBloque, funciónLlvm);
            if(bloqueLlvm == nullptr)
            {
                resultado.error("El proceso de creación del bloque '" + nombreBloque + "' me ha devuelto un puntero nulo");
                return resultado;
            }

            constructorLlvm.SetInsertPoint(bloqueLlvm);

            Ñ::Nodo* args = nodo->ramas[1];
            
            int i = 0;
            for(auto &argumento : funciónLlvm->args())
            {
                Ñ::Nodo* a = args->ramas[i];

                std::string nombre = ((Ñ::DeclaraVariable*)a)->variable;
                argumento.setName(nombre);
                llvm::Value* variable = constructorLlvm.CreateAlloca(argumento.getType(), nullptr, nombre);
                constructorLlvm.CreateStore(&argumento, variable, false);
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

            gestorPasesOptimización->run(*funciónLlvm);

            funciónLlvm->print(llvm::errs(), nullptr);

            tablaSímbolos->cierraBloque();
            delete tablaSímbolos;
            tablaSímbolos = nullptr;

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
                resultado.error("He recibido un nodo nulo, esperaba una declaración de función");
                return resultado;
            }
            else if(nodo->categoría == Ñ::CategoríaNodo::NODO_DECLARA_FUNCIÓN)
            {
                // Convierto Ñ::Nodo* a Ñ::DefineFunción*
                función = (Ñ::DeclaraFunción*)nodo;
            }
            else
            {
                resultado.error("El nodo no es una declaración de función");
                return resultado;
            }

            resultado = _construyeDeclaraciónFunción(función->nombre, nodo->ramas[0], nodo->ramas[1]);
            if(resultado.error())
            {
                return resultado;
            }
            
            llvm::Function* funciónLlvm = (llvm::Function*)resultado.valor();
            
            funciónLlvm->print(llvm::errs(), nullptr);
            
            return resultado;
        }

        Ñ::ResultadoLlvm _construyeDeclaraciónFunción(std::string nombre, Ñ::Nodo* devuelto, Ñ::Nodo* argumentos)
        {
            Ñ::ResultadoLlvm resultado;
            llvm::Type* tRetorno = nullptr;
            std::vector<llvm::Type*> vArgumentos = {};
            
            // Comprobaciones de error
            if(devuelto == nullptr)
            {
                tRetorno = creaTipoLlvm(Ñ::CategoríaTipo::TIPO_NADA);
                //resultado.error("He recibido un nodo nulo, esperaba un tipo de devolución");
                //return resultado;
            }
            else if(devuelto->categoría != Ñ::CategoríaNodo::NODO_TIPO)
            {
                resultado.error("El tipo de retorno no es un NODO_TIPO válido.");
                return resultado;
            }
            else
            {
                Ñ::Tipo* tDevuelto = (Ñ::Tipo*)devuelto;
                tRetorno = creaTipoLlvm(tDevuelto->tipo);
            }

            if(argumentos == nullptr)
            {
                //resultado.error("He recibido un nodo nulo, esperaba un nodo contenedor de argumentos");
                //return resultado;
            }
            else if(argumentos->categoría != Ñ::CategoríaNodo::NODO_ARGUMENTOS)
            {
                resultado.error("El tipo de retorno no es un NODO_ARGUMENTOS válido.");
                return resultado;
            }
            else
            {
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
                        vArgumentos.push_back(creaTipoLlvm(arg->tipo));
                    }
                    else if(a->categoría == Ñ::CategoríaNodo::NODO_DECLARA_VARIABLE)
                    {
                        Ñ::Tipo* arg = (Ñ::Tipo*)(a->ramas[0]);
                        vArgumentos.push_back(creaTipoLlvm(arg->tipo));
                    }
                    else
                    {
                        muestraNodos(a);
                        resultado.error("He recibido un argumento de un tipo que no reconozco");
                        return resultado;
                    }
                }
            }

            llvm::FunctionType* firmaFunción = llvm::FunctionType::get(tRetorno, vArgumentos, false);

            llvm::Function* función = llvm::Function::Create(firmaFunción, llvm::Function::ExternalLinkage, nombre.c_str(), móduloLlvm);

            resultado.éxito();
            resultado.función(función);
            return resultado;
        }

        Ñ::ResultadoLlvm construyeInteriorDeBloque(Ñ::Nodo* nodo)
        {
            Ñ::ResultadoLlvm resultado;

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

        Ñ::ResultadoLlvm construyeExpresiónPrimerNivel(Ñ::Nodo* nodo)
        {
            Ñ::ResultadoLlvm resultado;
            Ñ::Expresión* expresión;

            if(nodo == nullptr)
            {
                resultado.error("He recibido un nodo nulo, esperaba una expresión de primer nivel");
                return resultado;
            }
            else if(nodo->categoría == Ñ::CategoríaNodo::NODO_EXPRESIÓN)
            {
                // Convierto Ñ::Nodo* a Ñ::DefineFunción*
                expresión = (Ñ::Expresión*)nodo;
            }
            else
            {
                resultado.error("El nodo no es una expresión de primer nivel");
                return resultado;
            }

            preparaMóduloJAT("");

            resultado = _construyeDeclaraciónFunción("__función_anónima__", nullptr, nullptr);
            if(resultado.error())
            {
                return resultado;
            }
            
            llvm::Function * funciónLlvm;
            
            funciónLlvm = móduloLlvm->getFunction("__función_anónima__");

            if(!funciónLlvm)
            {
                resultado.error("Error, no se ha registrado la función '__función_anónima__()'");
                return resultado;
            }
            else if(!funciónLlvm->empty())
            {
                resultado.error("La función ya está definida, no puedo redefinirla.");
                return resultado;
            }

            // Inicio construcción del bloque, no hay argumentos que definir
            // PENDIENTE: No debo usar una tabla de símbolos local
            tablaSímbolos = new Símbolos;
            tablaSímbolos->abreBloque();

            std::string nombreBloque = "entrada";
            llvm::BasicBlock* bloqueLlvm = llvm::BasicBlock::Create(contextoLlvm, nombreBloque, funciónLlvm);
            if(bloqueLlvm == nullptr)
            {
                resultado.error("El proceso de creación del bloque '" + nombreBloque + "' me ha devuelto un puntero nulo");
                return resultado;
            }

            constructorLlvm.SetInsertPoint(bloqueLlvm);

            auto rExpresión = construyeExpresión(nodo);
            if(rExpresión.error())
            {
                return rExpresión;
            }
            constructorLlvm.CreateRetVoid();

            llvm::verifyFunction(*funciónLlvm);

            //gestorPasesOptimización->run(*funciónLlvm);

            funciónLlvm->print(llvm::errs(), nullptr);

            tablaSímbolos->cierraBloque();
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
            
            case Ñ::CategoríaNodo::NODO_DECLARA_VARIABLE:
                resultado = construyeDeclaraciónVariable(n);
                break;
            
            case Ñ::CategoríaNodo::NODO_ASIGNA:
                resultado = construyeAsignación(n);
                break;
            
            default:
                resultado.error("No reconozco la expresión");
                muestraNodos(nodo);
                break;
            }

            return resultado;
        }

        Ñ::ResultadoLlvm construyeAsignación(Ñ::Nodo* nodo)
        {
            Ñ::ResultadoLlvm resultado;

            if(nodo == nullptr)
            {
                resultado.error("He recibido un nodo de valor nullptr, no puedo leer la asignación");
                return resultado;
            }

            if(nodo->categoría != Ñ::CategoríaNodo::NODO_ASIGNA)
            {
                resultado.error("He recibido un nodo que no es una asignación");
                return resultado;
            }

            if(nodo->ramas.size() == 2)
            {
                Ñ::ResultadoLlvm rLia = construyeLIA(nodo->ramas[0]);
                if(rLia.error())
                {
                    return rLia;
                }

                llvm::Value* vLia = rLia.valor();

                Ñ::ResultadoLlvm rLda = construyeLDA(nodo->ramas[1]);
                if(rLda.error())
                {
                    return rLda;
                }

                llvm::Value* vLda = rLda.valor();

                constructorLlvm.CreateStore(vLda, vLia, false);

                resultado.éxito();
                return resultado;
            }
            else
            {
                resultado.error("He recibido una asignación mal estructurada, tiene " + std::to_string(nodo->ramas.size()) + " ramas");
                return resultado;
            }
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

        Ñ::ResultadoLlvm construyeLIA(Ñ::Nodo* nodo)
        {
            Ñ::ResultadoLlvm resultado;
            
            if(nodo == nullptr)
            {
                resultado.error("He recibido un nodo de valor nullptr, no puedo leer la expresión");
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
            
            default:
                resultado.error("No puedo construir este nodo como LDA");
                break;
            }

            return resultado;
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
            
            case Ñ::CategoríaNodo::NODO_CONVIERTE_TIPOS:
                resultado = construyeConversorTipos(nodo);
                break;
            
            case Ñ::CategoríaNodo::NODO_IDENTIFICADOR:
                resultado = construyeVariableLDA(nodo);
                break;

            case Ñ::CategoríaNodo::NODO_TÉRMINO:
                resultado = construyeOperaciónTérmino(nodo);
                break;

            case Ñ::CategoríaNodo::NODO_FACTOR:
                resultado = construyeOperaciónFactor(nodo);
                break;

            case Ñ::CategoríaNodo::NODO_LLAMA_FUNCIÓN:
                resultado = construyeLlamadaFunción(nodo);
                break;
            
            default:
                resultado.error("No puedo construir este nodo como LDA");
                break;
            }

            return resultado;
        }

        Ñ::ResultadoLlvm construyeDeclaraciónVariable(Ñ::Nodo* nodo)
        {
            Ñ::ResultadoLlvm resultado;

            if(nodo == nullptr)
            {
                resultado.error("He recibido un nodo de valor nullptr, no puedo leer la declaración de variable");
                return resultado;
            }

            if(nodo->categoría != Ñ::CategoríaNodo::NODO_DECLARA_VARIABLE)
            {
                resultado.error("El nodo no es una declaración de variable, no puedo construirlo");
                return resultado;
            }
            
            if(nodo->ramas.size() != 1)
            {
                resultado.error("El nodo 'declaración de variable' no tiene las ramas esperadas, no puedo construirlo");
                return resultado;
            }

            std::string nombre;
            llvm::Type* tipo;

            Ñ::DeclaraVariable* dv = (Ñ::DeclaraVariable*)nodo;
            Ñ::Tipo* t = (Ñ::Tipo*)(nodo->ramas[0]);

            nombre = dv->variable;
            tipo = creaTipoLlvm(t->tipo);

            llvm::Value* variable = constructorLlvm.CreateAlloca(tipo, nullptr, nombre);

            ponId(nombre, variable);

            resultado.éxito();
            resultado.valor(variable);
            return resultado;
        }

        Ñ::ResultadoLlvm construyeVariableLIA(Ñ::Nodo* nodo)
        {
            Ñ::ResultadoLlvm resultado;

            if(nodo == nullptr)
            {
                resultado.error("He recibido un nodo de valor nullptr, no puedo leer la variable");
                return resultado;
            }

            if(nodo->categoría != Ñ::CategoríaNodo::NODO_IDENTIFICADOR)
            {
                resultado.error("El nodo no es una variable, no puedo construir su lectura");
                return resultado;
            }
            
            if(nodo->ramas.size() != 0)
            {
                resultado.error("El nodo 'identificador' no tiene las ramas esperadas, no puedo construir su lectura");
                return resultado;
            }

            std::string nombre;
            Ñ::Identificador* id;
            llvm::Value* variable;

            id = (Ñ::Identificador*)nodo;
            nombre = id->id;

            variable = leeId(nombre);

            resultado.éxito();
            resultado.valor(variable);
            return resultado;
        }

        Ñ::ResultadoLlvm construyeVariableLDA(Ñ::Nodo* nodo)
        {
            Ñ::ResultadoLlvm resultado;

            if(nodo == nullptr)
            {
                resultado.error("He recibido un nodo de valor nullptr, no puedo leer la variable");
                return resultado;
            }

            if(nodo->categoría != Ñ::CategoríaNodo::NODO_IDENTIFICADOR)
            {
                resultado.error("El nodo no es una variable, no puedo construir su lectura");
                return resultado;
            }
            
            if(nodo->ramas.size() != 0)
            {
                resultado.error("El nodo 'identificador' no tiene las ramas esperadas, no puedo construir su lectura");
                return resultado;
            }

            std::string nombre;
            Ñ::Identificador* id;
            llvm::Value* variable;

            id = (Ñ::Identificador*)nodo;
            nombre = id->id;

            variable = leeId(nombre);

            llvm::Type* tipoLia = variable->getType();
            std::string type_str;
            llvm::raw_string_ostream rso(type_str);
            tipoLia->print(rso);

            llvm::Value* valor = constructorLlvm.CreateLoad(variable, nombre);

            resultado.éxito();
            resultado.valor(valor);
            return resultado;
        }

        Ñ::ResultadoLlvm construyeConversorTipos(Ñ::Nodo* nodo)
        {
            Ñ::ResultadoLlvm resultado;

            if(nodo == nullptr)
            {
                resultado.error("He recibido un nodo de valor nullptr, no puedo leer la conversión");
                return resultado;
            }

            if(nodo->categoría != Ñ::CategoríaNodo::NODO_CONVIERTE_TIPOS)
            {
                resultado.error("El nodo no es un conversor de tipos, no puedo construirlo");
                return resultado;
            }

            if(nodo->ramas.size() != 1)
            {
                resultado.error("El nodo conversor de tipos, está mal definido, tiene " + std::to_string(nodo->ramas.size()) + " hijos");
                return resultado;
            }

            Ñ::ConvierteTipos* conv = (Ñ::ConvierteTipos*)nodo;

            resultado = construyeLDA(nodo->ramas[0]);
            if(resultado.error())
            {
                return resultado;
            }

            llvm::Type* tDestino = creaTipoLlvm(conv->destino);
            if(tDestino == nullptr)
            {
                resultado.error("Error al obtener el tipoLlvm");
                return resultado;
            }

            llvm::Value* valor;

            switch (conv->destino)
            {
            case TIPO_NATURAL_8:
            case TIPO_NATURAL_16:
            case TIPO_NATURAL_32:
            case TIPO_NATURAL_64:
                valor = constructorLlvm.CreateIntCast(resultado.valor(), tDestino, false);
                break;
            
            case TIPO_ENTERO_8:
            case TIPO_ENTERO_16:
            case TIPO_ENTERO_32:
            case TIPO_ENTERO_64:
                valor = constructorLlvm.CreateIntCast(resultado.valor(), tDestino, true);
                break;
            
            case TIPO_REAL_32:
            case TIPO_REAL_64:
                switch (conv->origen)
                {
                case TIPO_NATURAL_8:
                case TIPO_NATURAL_16:
                case TIPO_NATURAL_32:
                case TIPO_NATURAL_64:
                    valor = constructorLlvm.CreateUIToFP(resultado.valor(), tDestino);
                    break;
                
                case TIPO_ENTERO_8:
                case TIPO_ENTERO_16:
                case TIPO_ENTERO_32:
                case TIPO_ENTERO_64:
                    valor = constructorLlvm.CreateSIToFP(resultado.valor(), tDestino);
                    break;
            
                case TIPO_REAL_32:
                case TIPO_REAL_64:
                    valor = constructorLlvm.CreateFPCast(resultado.valor(), tDestino);
                    break;
                
                default:
                    valor = nullptr;
                    break;
                }
                break;

            default:
                valor = nullptr;
                break;
            }
            
            resultado.éxito();
            resultado.valor(valor);
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
                tipo = creaTipoLlvm(literal->tipo);
                número = std::stoull(literal->dato);
                resultado.éxito();
                resultado.valor(llvm::ConstantInt::get(tipo, número));
                break;
                
            case Ñ::CategoríaTipo::TIPO_NATURAL_16:
                tipo = creaTipoLlvm(literal->tipo);
                número = std::stoull(literal->dato);
                resultado.éxito();
                resultado.valor(llvm::ConstantInt::get(tipo, número));
                break;
                
            case Ñ::CategoríaTipo::TIPO_NATURAL_32:
                tipo = creaTipoLlvm(literal->tipo);
                número = std::stoull(literal->dato);
                resultado.éxito();
                resultado.valor(llvm::ConstantInt::get(tipo, número));
                break;

            case Ñ::CategoríaTipo::TIPO_NATURAL_64:
                tipo = creaTipoLlvm(literal->tipo);
                número = std::stoull(literal->dato);
                resultado.éxito();
                resultado.valor(llvm::ConstantInt::get(tipo, número));
                break;
            
            case Ñ::CategoríaTipo::TIPO_ENTERO_8:
                tipo = creaTipoLlvm(literal->tipo);
                número = std::stoll(literal->dato);
                resultado.éxito();
                resultado.valor(llvm::ConstantInt::get(tipo, número, true));
                break;
            
            case Ñ::CategoríaTipo::TIPO_ENTERO_16:
                tipo = creaTipoLlvm(literal->tipo);
                número = std::stoll(literal->dato);
                resultado.éxito();
                resultado.valor(llvm::ConstantInt::get(tipo, número, true));
                break;
            
            case Ñ::CategoríaTipo::TIPO_ENTERO_32:
                tipo = creaTipoLlvm(literal->tipo);
                número = std::stoll(literal->dato);
                resultado.éxito();
                resultado.valor(llvm::ConstantInt::get(tipo, número, true));
                break;
            
            case Ñ::CategoríaTipo::TIPO_ENTERO_64:
                tipo = creaTipoLlvm(literal->tipo);
                número = std::stoll(literal->dato);
                resultado.éxito();
                resultado.valor(llvm::ConstantInt::get(tipo, número, true));
                break;
            
            case Ñ::CategoríaTipo::TIPO_REAL_32:
                tipo = creaTipoLlvm(literal->tipo);
                real32 = std::stof(literal->dato);
                resultado.éxito();
                resultado.valor(llvm::ConstantFP::get(tipo, real32));
                break;
            
            case Ñ::CategoríaTipo::TIPO_REAL_64:
                tipo = creaTipoLlvm(literal->tipo);
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
                    resultado.error("Error, esperaba una operación binaria y he recibido un nodo nulo");
                    return resultado;
                }
                else if(nOp->categoría != Ñ::CategoríaNodo::NODO_OP_BINARIA)
                {
                    resultado.error("Error, esperaba una operación binaria y he recibido un nodo de otro tipo");
                    return resultado;
                }

                Ñ::ResultadoLlvm rV2 = construyeLDA(nOp->ramas[0]);
                if(rV2.error())
                {
                    return rV2;
                }
                v2 = rV2.valor();

                Ñ::OperaciónBinaria* op = (Ñ::OperaciónBinaria*)nOp;

                if(op->operación == "+")
                {
                    v1 = constructorLlvm.CreateAdd(v1, v2, "suma_tmp");
                }
                else if(op->operación == "-")
                {
                    v1 = constructorLlvm.CreateSub(v1, v2, "resta_tmp");
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
                    resultado.error("Error, esperaba una operación binaria y he recibido un nodo nulo");
                    return resultado;
                }
                else if(nOp->categoría != Ñ::CategoríaNodo::NODO_OP_BINARIA)
                {
                    resultado.error("Error, esperaba una operación binaria y he recibido un nodo de otro tipo");
                    return resultado;
                }

                Ñ::ResultadoLlvm rV2 = construyeLDA(nOp->ramas[0]);
                if(rV2.error())
                {
                    return rV2;
                }
                v2 = rV2.valor();

                Ñ::OperaciónBinaria* op = (Ñ::OperaciónBinaria*)nOp;

                if(op->operación == "*")
                {
                    v1 = constructorLlvm.CreateMul(v1, v2, "mul_tmp");
                }
                else if(op->operación == "/")
                {
                    llvm::Type* tipoV1 = v1->getType();

                    if(tipoV1->isFloatTy() || tipoV1->isDoubleTy())
                    {
                        v1 = constructorLlvm.CreateFDiv(v1, v2, "div_tmp");
                    }
                    else if(tipoV1->isIntegerTy())
                    {
                        v1 = constructorLlvm.CreateSDiv(v1, v2, "div_tmp");
                    }
                }
            }

            resultado.éxito();
            resultado.valor(v1);
            return resultado;
        }

        Ñ::ResultadoLlvm construyeLlamadaFunción(Ñ::Nodo* nodo)
        {
            Ñ::ResultadoLlvm resultado;
            
            if(nodo == nullptr)
            {
                resultado.error("Esperaba una llamada a una función, pero el nodo es nulo");
                return resultado;
            }

            if(nodo->categoría != Ñ::CategoríaNodo::NODO_LLAMA_FUNCIÓN)
            {
                resultado.error("Esperaba una llamada a una función, pero el nodo es de una categoría inesperada");
                return resultado;
            }

            Ñ::LlamaFunción* fn = (Ñ::LlamaFunción*)nodo;
            llvm::Function* funciónLlvm = móduloLlvm->getFunction(fn->nombre);
            
            if(!funciónLlvm)
            {
                resultado.error("Esperaba obtener una referencia a una función pero LLVM me ha devuelto un valor desconocido");
                return resultado;
            }
            
            std::vector<llvm::Value*> argumentos;

            // Preparando argumentos
            Ñ::Nodo* args = nodo->ramas[0];
            
            std::vector<llvm::Value*> vArgs;
            
            for(Ñ::Nodo* n : args->ramas)
            {
                resultado = construyeLDA(n);
                if(resultado.error())
                {
                    return resultado;
                }

                vArgs.push_back(resultado.valor());

            }

            llvm::Value* devuelto = constructorLlvm.CreateCall(funciónLlvm, vArgs, "llamda");

            resultado.éxito();
            resultado.valor(devuelto);
            return resultado;
        }
    };

    Ñ::Resultado promueve(Ñ::Nodo* árbol, Ñ::CategoríaNodo categoríaNodo)
    {
        std::cout << "promueve(nodo)" << std::endl;

        Ñ::Resultado resultado;

        Ñ::Promotor* promotor = new Ñ::Promotor;

        std::cout << std::endl;

        muestraNodos(árbol);

        std::cout << std::endl;
        std::cout << std::endl;

        if(categoríaNodo == Ñ::CategoríaNodo::NODO_MÓDULO && árbol->categoría == Ñ::CategoríaNodo::NODO_MÓDULO)
        {
            std::cout << "Preparando construcción con LLVM" << std::endl << std::endl;

            Ñ::ResultadoLlvm rMódulo = promotor->construyeMódulo(árbol);
            if(rMódulo.error())
            {
                resultado.error(rMódulo.mensaje());
                return resultado;
            }
        }
        else if(categoríaNodo == Ñ::CategoríaNodo::NODO_EXPRESIÓN && árbol->categoría == Ñ::CategoríaNodo::NODO_EXPRESIÓN)
        {
            std::cout << "Preparando construcción 'justo a tiempo'" << std::endl << std::endl;
            
            llvm::InitializeNativeTarget();
            llvm::InitializeNativeTargetAsmPrinter();
            llvm::InitializeNativeTargetAsmParser();
            if(auto JatoError = Ñ::ConstructorJAT::Crea())
            {
                promotor->jat = *JatoError;
            }

            Ñ::ResultadoLlvm rExpresión = promotor->construyeExpresiónPrimerNivel(árbol);
            if(rExpresión.error())
            {
                resultado.error(rExpresión.mensaje());
                return resultado;
            }

            std::unique_ptr<llvm::Module> módulo(promotor->móduloLlvm);
            promotor->jat->añadeMódulo(std::move(módulo));
        }

        return resultado;
    }
}