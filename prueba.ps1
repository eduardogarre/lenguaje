# SPDX-License-Identifier: MPL-2.0-no-copyleft-exception
#
# This Source Code Form is subject to the terms of the Mozilla Public License, v.
# 2.0. If a copy of the MPL was not distributed with this file, You can obtain one
# at http://mozilla.org/MPL/2.0/.
# 
# This Source Code Form is "Incompatible With Secondary Licenses", as defined by
# the Mozilla Public License, v. 2.0.
# 
# Copyright © 2021 Eduardo Garre Muñoz

rm -ErrorAction SilentlyContinue *.o
rm -ErrorAction SilentlyContinue *.exe

.\proyecto\ñ.exe .\pruebas\*.ñ -s prueba -O1
.\prueba.exe

rm -ErrorAction SilentlyContinue *.o
rm -ErrorAction SilentlyContinue *.exe