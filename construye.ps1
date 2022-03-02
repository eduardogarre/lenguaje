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

rm build -Force -Recurse -ErrorAction SilentlyContinue
rm proyecto -Force -Recurse -ErrorAction SilentlyContinue
rm obra -Force -Recurse -ErrorAction SilentlyContinue
rm -ErrorAction SilentlyContinue *.o
rm -ErrorAction SilentlyContinue *.exe

mkdir obra
mkdir proyecto

$crono = [system.diagnostics.stopwatch]::startNew()

cd obra
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build . --parallel 4
cd ..

rm build -Force -Recurse -ErrorAction SilentlyContinue
rm obra -Force -Recurse -ErrorAction SilentlyContinue

./construyeBiblioteca.ps1

$crono.Stop()

./prueba.ps1

$tConstrucción = $crono.Elapsed.TotalSeconds

echo [33m
echo "Duración de la construcción: $tConstrucción segundos"
echo [0m

#echo ""
#echo ""
#echo "Paso Pruebas"
#echo ""
#
#./proyecto/pruebas.exe
#
#echo ""
#echo ""
#echo "Ejecuto ñ"
#echo ""
#
#./proyecto/ñ.exe