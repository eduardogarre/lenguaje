#pragma once

namespace Ñ
{
    class Símbolo
    {
    public:
        Símbolo();
        ~Símbolo();

        bool esEjecutable();
        void ejecuta();
        void añadeEjecución(void (*fn)());
        void borraEjecución();
        
    private:
        bool _ejecutable = false;

        void (*_ejecuta)();
    };
}