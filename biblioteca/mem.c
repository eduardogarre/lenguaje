/*
SPDX-License-Identifier: MPL-2.0-no-copyleft-exception

This Source Code Form is subject to the terms of the Mozilla Public License, v.
2.0. If a copy of the MPL was not distributed with this file, You can obtain one
at http://mozilla.org/MPL/2.0/.

This Source Code Form is "Incompatible With Secondary Licenses", as defined by
the Mozilla Public License, v. 2.0.

Copyright © 2021 Eduardo Garre Muñoz
*/

#include "mem.h"

#include "externowindows.h"

void* reserva(unsigned long long _num)
{
    void* almacen = GetProcessHeap();

    return HeapAlloc(almacen, HEAP_ZERO_MEMORY, _num);
}

int suelta(void* _mem)
{
    void* almacen = GetProcessHeap();

    return HeapFree(almacen, HEAP_ZERO_MEMORY, _mem);
}