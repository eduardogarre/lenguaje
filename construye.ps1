rm build -Force -Recurse -ErrorAction SilentlyContinue
rm proyecto -Force -Recurse -ErrorAction SilentlyContinue
rm obra -Force -Recurse -ErrorAction SilentlyContinue

mkdir obra
mkdir proyecto

cd obra
cmake ..
cmake --build . --parallel 4
cd ..

rm obra -Force -Recurse -ErrorAction SilentlyContinue

mv ./proyecto/compilador.exe ./proyecto/ñ.exe

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