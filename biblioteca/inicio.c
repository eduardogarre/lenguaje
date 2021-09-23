extern int inicia();
extern void __security_init_cookie(void);

#include "es.h"

extern int hola()
{
    txt texto = creaTxt("hola españoles\n");
    return escribe(texto);
}

int __lugar_de_inicio()
{
    return inicia();
}