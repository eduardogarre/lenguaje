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

#include "txt.h"

int escribetxt(txt texto);
int escribe(char* _texto);
int escribeln(char* _texto);
int escribeletra(char _letra);
int escribeletraln(char _letra);
int escribenat(unsigned int _num);
int escribenatln(unsigned int _num);
int escribeent(int _num);
int escribeentln(int _num);
