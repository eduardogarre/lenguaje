#!/bin/sh

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