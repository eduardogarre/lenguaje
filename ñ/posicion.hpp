#pragma once

#include <stdint.h>
#include <string>

namespace Ñ
{
    class Posición
    {
    private:
        uint64_t _cursor;
        uint64_t _línea;
        uint64_t _columna;
        uint64_t _lexema;
        std::string _archivo;

    public:
        uint64_t cursor();
        uint64_t línea();
        uint64_t columna();
        uint64_t lexema();
        std::string archivo();

        void cursor(uint64_t cursor);
        void línea(uint64_t línea);
        void columna(uint64_t columna);
        void lexema(uint64_t lexema);
        void archivo(std::string archivo);
    };

} // namespace Ñ
