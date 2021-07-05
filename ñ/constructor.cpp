#include <string>

#include "llvm/Support/Host.h"
#include "llvm/Support/TargetSelect.h"

#include "resultadollvm.hpp"

namespace Ñ
{
    Ñ::ResultadoLlvm construye()
    {
        Ñ::ResultadoLlvm resultado;

        auto TargetTriple = llvm::sys::getDefaultTargetTriple();

        llvm::InitializeAllTargetInfos();
        llvm::InitializeAllTargets();
        llvm::InitializeAllTargetMCs();
        llvm::InitializeAllAsmParsers();
        llvm::InitializeAllAsmPrinters();

        return resultado;
    }
}