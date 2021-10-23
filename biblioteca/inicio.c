extern int inicia();

#include "es.h"

extern int holamundo()
{
    txt texto = sumaTxt(creaTxt("¡hola, "), creaTxt("mundo!\n"));
    return escribetxt(texto);
}

int __stdcall __lugar_de_inicio()
{
    int devuelto = inicia();
    return devuelto;
}
