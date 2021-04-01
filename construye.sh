#!/bin/sh

rm -rf obra
rm -rf proyecto/*

mkdir obra
mkdir proyecto

cd obra
cmake ..
cmake --build .
cd ..

rm -rf obra

mv ./proyecto/compilador ./proyecto/ñ

echo ""
echo ""
echo "Ejecutando ñ"
echo ""

./proyecto/ñ