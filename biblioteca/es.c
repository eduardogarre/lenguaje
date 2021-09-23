#include "txt.h"

#define ASA_COMUN_ENTRADA    ((unsigned long)-10)
#define ASA_COMUN_SALIDA     ((unsigned long)-11)
#define ASA_COMUN_ERROR      ((unsigned long)-12)

extern __declspec(dllimport) int __stdcall WriteConsoleW(
    void* asaDeSalida,
    const void* almacen,
    unsigned long posicionesPorEscribir,
    unsigned long* posicionesEscritas,
    void* reservado
    );

extern __declspec(dllimport) int __stdcall WriteConsoleA(
    void* asaDeSalida,
    const void* almacen,
    unsigned long posicionesPorEscribir,
    unsigned long* posicionesEscritas,
    void* reservado
    );

extern __declspec(dllimport) int __stdcall WriteConsoleA(
    void* asaDeSalida,
    const void* almacen,
    unsigned long posicionesPorEscribir,
    unsigned long* posicionesEscritas,
    void* reservado
    );

extern void* __stdcall GetStdHandle( unsigned long asaComún );

extern int escribe(txt texto)
{
    int escrito;
    WriteConsoleA(GetStdHandle(ASA_COMUN_SALIDA), (const void*) cadenaCdeTxt(texto), longTxt(texto), &escrito, 0);

    return escrito;
}