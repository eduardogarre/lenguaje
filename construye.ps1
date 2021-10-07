rm build -Force -Recurse -ErrorAction SilentlyContinue
rm proyecto -Force -Recurse -ErrorAction SilentlyContinue
rm obra -Force -Recurse -ErrorAction SilentlyContinue
rm -ErrorAction SilentlyContinue *.o
rm -ErrorAction SilentlyContinue *.exe

mkdir obra
mkdir proyecto

cd obra
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build . --parallel 4
cd ..

rm build -Force -Recurse -ErrorAction SilentlyContinue
rm obra -Force -Recurse -ErrorAction SilentlyContinue

./construyeBiblioteca.ps1

./pruebasFuncionales.ps1

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