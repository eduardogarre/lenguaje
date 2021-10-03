extern int inicia();
extern void __security_init_cookie(void);

#include "es.h"

extern int holamundo()
{
    txt texto = sumaTxt(creaTxt("hola, "), creaTxt("mundo!\n"));
    return escribe(texto);
}

int __lugar_de_inicio()
{
    return inicia();
}