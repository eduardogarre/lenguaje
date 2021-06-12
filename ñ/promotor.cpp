#include "llvm/IR/LLVMContext.h"

#include "nodo.hpp"
#include "promotor.hpp"

namespace Ñ
{
    class Promotor
    {
    public:
        llvm::LLVMContext contextoLlvm;
        
        Promotor();
    };

    Ñ::Promotor::Promotor()
    {

    }

    Ñ::Resultado construye(Ñ::Nodo* árbol)
    {
        Ñ::Resultado resultado;

        Ñ::Promotor* promotor = new Ñ::Promotor;

        muestraNodos(árbol);

        return resultado;
    }
}