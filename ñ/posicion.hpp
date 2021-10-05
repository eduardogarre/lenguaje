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
        uint64_t _longitud;
        std::string _archivo;

    public:
        Posición();

        std::string muestra();
        
        uint64_t cursor();
        uint64_t línea();
        uint64_t columna();
        uint64_t longitud();
        std::string archivo();

        void incCursor();
        void incLínea();
        void empiezaColumna();
        void incColumna();
        void longitud(uint64_t longitud);
        void archivo(std::string archivo);
    };

} // namespace Ñ
