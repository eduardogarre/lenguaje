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
#include "llvm/IR/Instructions.h"
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
        llvm::Module* móduloLlvm;
        llvm::IRBuilder<> constructorLlvm;
        Ñ::Símbolos* tablaSímbolos = nullptr;

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

        void ponId(std::string id, llvm::Value* valor)
        {
            if(tablaSímbolos != nullptr)
            {
                tablaSímbolos->ponId(id, valor);
            }
            else
            {
                std::cout << "Error, no puedo guardar el símbolo en la tabla" << std::endl;
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
                std::cout << "Error, no se ha iniciado la tabla" << std::endl;
            }
            std::cout << "Error, no he encontrado el símbolo" << std::endl;
            
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

            // Inicio construcción del bloque y definición de los argumentos
            tablaSímbolos = new Símbolos;
            tablaSímbolos->abreBloque();
            
            for(auto &argumento : funciónLlvm->args())
            {
                ponId(argumento.getName().str(), &argumento);
            }

            Ñ::Nodo* bloque = nodo->ramas[2];

            resultado = construyeBloque("entrada", bloque, funciónLlvm);

            llvm::verifyFunction(*funciónLlvm);

            funciónLlvm->print(llvm::errs(), nullptr);

            tablaSímbolos->cierraBloque();
            delete tablaSímbolos;
            tablaSímbolos = nullptr;

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
            llvm::Type* tRetorno = creaTipoLlvm(tDevuelto->tipo);

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
                    vArgumentos.push_back(creaTipoLlvm(arg->tipo));
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
            
            case Ñ::CategoríaNodo::NODO_ASIGNA:
                resultado = construyeAsignación(n);
                break;
            
            default:
                resultado.error("No reconozco la expresión");
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
            }
            else
            {
                resultado.error("He recibido una asignación mal estructurada, tiene " + std::to_string(nodo->ramas.size()) + " ramas");
                return resultado;
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
                resultado.éxito();
                resultado = construyeDeclaraciónVariable(nodo);
                break;
            
            case Ñ::CategoríaNodo::NODO_IDENTIFICADOR:
                resultado.éxito();
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
                resultado.éxito();
                resultado = construyeLiteral(nodo);
                break;
            
            case Ñ::CategoríaNodo::NODO_CONVIERTE_TIPOS:
                resultado.éxito();
                resultado = construyeConversorTipos(nodo);
                break;
            
            case Ñ::CategoríaNodo::NODO_IDENTIFICADOR:
                resultado.éxito();
                resultado = construyeVariableLDA(nodo);
                break;

            case Ñ::CategoríaNodo::NODO_TÉRMINO:
                resultado.éxito();
                resultado = construyeOperaciónTérmino(nodo);
                break;

            case Ñ::CategoríaNodo::NODO_FACTOR:
                resultado.éxito();
                resultado = construyeOperaciónFactor(nodo);
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
            llvm::Value* valor;

            id = (Ñ::Identificador*)nodo;
            nombre = id->id;

            variable = leeId(nombre);

            valor = constructorLlvm.CreateLoad(variable, nombre);

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

            std::cout << "construyeOperaciónTérmino()" << std::endl;

            Ñ::ResultadoLlvm rV1 = construyeLDA(nodo->ramas[0]);
            if(rV1.error())
            {
                return rV1;
            }
            v1 = rV1.valor();
            
            std::cout << "Obtengo valor1" << std::endl;

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

                std::cout << "Obtengo valor2" << std::endl;

                Ñ::OperaciónBinaria* op = (Ñ::OperaciónBinaria*)nOp;

                if(op->operación == "+")
                {
                    std::cout << "Tengo que sumar... ";

                    v1 = constructorLlvm.CreateAdd(v1, v2, "sumatmp");

                    std::cout << "hecho." << std::endl;
                }
                else if(op->operación == "-")
                {
                    std::cout << "Tengo que restar... ";

                    v1 = constructorLlvm.CreateSub(v1, v2, "restatmp");

                    std::cout << "hecho." << std::endl;
                }
            }

            std::cout << "Fin construyeOperaciónTérmino()" << std::endl;

            resultado.éxito();
            resultado.valor(v1);
            return resultado;
        }

        Ñ::ResultadoLlvm construyeOperaciónFactor(Ñ::Nodo* nodo)
        {
            Ñ::ResultadoLlvm resultado;
            llvm::Value* v1;
            llvm::Value* v2;

            std::cout << "construyeOperaciónFactor()" << std::endl;

            Ñ::ResultadoLlvm rV1 = construyeLDA(nodo->ramas[0]);
            if(rV1.error())
            {
                return rV1;
            }
            v1 = rV1.valor();
            
            std::cout << "Obtengo valor1" << std::endl;

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

                std::cout << "Obtengo valor2" << std::endl;

                Ñ::OperaciónBinaria* op = (Ñ::OperaciónBinaria*)nOp;

                if(op->operación == "*")
                {
                    std::cout << "Tengo que multiplicar... ";

                    v1 = constructorLlvm.CreateMul(v1, v2, "multmp");

                    std::cout << "hecho." << std::endl;
                }
                else if(op->operación == "/")
                {
                    std::cout << "Tengo que dividir... ";
                    llvm::Type* tipoV1 = v1->getType();

                    if(tipoV1->isFloatTy() || tipoV1->isDoubleTy())
                    {
                        v1 = constructorLlvm.CreateFDiv(v1, v2, "divtmp");
                    }
                    else if(tipoV1->isIntegerTy())
                    {
                        v1 = constructorLlvm.CreateSDiv(v1, v2, "divtmp");
                    }
                    
                    std::cout << "hecho." << std::endl;
                }
            }

            std::cout << "Fin construyeOperaciónFactor()" << std::endl;

            resultado.éxito();
            resultado.valor(v1);
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