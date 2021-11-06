/*
SPDX-License-Identifier: MPL-2.0-no-copyleft-exception

This Source Code Form is subject to the terms of the Mozilla Public License, v.
2.0. If a copy of the MPL was not distributed with this file, You can obtain one
at http://mozilla.org/MPL/2.0/.

This Source Code Form is "Incompatible With Secondary Licenses", as defined by
the Mozilla Public License, v. 2.0.

Copyright © 2021 Eduardo Garre Muñoz
*/

#pragma once

#define ASA_COMUN_ENTRADA    ((unsigned long)-10)
#define ASA_COMUN_SALIDA     ((unsigned long)-11)
#define ASA_COMUN_ERROR      ((unsigned long)-12)

#define HEAP_NO_SERIALIZE           1
#define HEAP_GENERATE_EXCEPTIONS    4
#define HEAP_ZERO_MEMORY            8

extern __declspec(dllimport) unsigned long __stdcall GetCurrentProcessId();

extern void* __stdcall GetProcessHeap();

extern void* __stdcall GetStdHandle(
    unsigned long       asaComún
);

extern __declspec(allocator) void* HeapAlloc(
    void*               asaAlmacen,
    unsigned long       claves,
    unsigned long long  bytes
);

extern __declspec(allocator) void* HeapFree(
    void*               asaAlmacen,
    unsigned long       claves,
    void*               memoria
);

extern __declspec(dllimport) int __stdcall WriteConsoleA(
    void*               asaDeSalida,
    const void*         almacen,
    unsigned long       posicionesPorEscribir,
    unsigned long*      posicionesEscritas,
    void*               reservado
);

extern __declspec(dllimport) int __stdcall WriteConsoleW(
    void*               asaDeSalida,
    const void*         almacen,
    unsigned long       posicionesPorEscribir,
    unsigned long*      posicionesEscritas,
    void*               reservado
);