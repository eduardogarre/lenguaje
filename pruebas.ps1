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

echo "[33m" "Pruebas de Construcción" "[0m"

.\proyecto\ñ.exe .\pruebas\constructor\*.ñ -s pruebas -O1
.\pruebas.exe
rm -ErrorAction SilentlyContinue *.o
rm -ErrorAction SilentlyContinue *.exe

echo "[33m" "Pruebas de Interpretación" "[0m"

Get-ChildItem ".\pruebas\intérprete" -Filter *.ñ | 
Foreach-Object {
    $archivoPrueba = $_.FullName
    .\proyecto\ñ.exe $archivoPrueba -i
}
