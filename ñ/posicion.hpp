#pragma once

#include <stdint.h>
#include <string>

namespace Ñ
{
    class Posición
    {
    private:
        uint64_t _línea;
        uint64_t _letra;
        uint64_t _lexema;
        std::string _archivo;

    public:
        uint64_t línea();
        uint64_t letra();
        uint64_t lexema();
        std::string archivo();

        void línea(uint64_t línea);
        void letra(uint64_t letra);
        void lexema(uint64_t lexema);
        void archivo(std::string archivo);
    };

} // namespace Ñ
