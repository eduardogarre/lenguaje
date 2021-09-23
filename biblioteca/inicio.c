extern int inicia();
extern void __security_init_cookie(void);

#include "es.h"

extern int hola()
{
    txt texto = creaTxt("hola, ");
    return escribe(texto);
}

extern int mundo()
{
    txt texto = creaTxt("mundo\n");
    return escribe(texto);
}

extern int holamundo()
{
    txt texto = sumaTxt(creaTxt("hola, "), creaTxt("mundo!\n"));
    return escribe(texto);
}

int __lugar_de_inicio()
{
    return inicia();
}