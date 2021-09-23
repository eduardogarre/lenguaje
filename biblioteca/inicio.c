extern int inicia();
extern void __security_init_cookie(void);

#include "es.h"

extern int hola()
{
    return escribe(creaTxt("hola"));
}

int __lugar_de_inicio()
{
    return inicia();
}