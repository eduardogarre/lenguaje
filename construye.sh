#!/bin/sh

#This Source Code Form is subject to the terms of the Mozilla Public License, v.
#2.0. If a copy of the MPL was not distributed with this file, You can obtain one
#at http://mozilla.org/MPL/2.0/.
#
#This Source Code Form is "Incompatible With Secondary Licenses", as defined by
#the Mozilla Public License, v. 2.0.

rm -rf build
rm -rf obra
rm -rf proyecto

mkdir obra
mkdir proyecto

cd obra
cmake ..
cmake --build . --parallel=4
cd ..

rm -rf obra

mv ./proyecto/compilador ./proyecto/ñ

echo ""
echo ""
echo "Paso Pruebas"
echo ""

./proyecto/pruebas

echo ""
echo ""
echo "Ejecuto ñ"
echo ""

./proyecto/ñ