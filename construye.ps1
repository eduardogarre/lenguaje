rm obra -Force -Recurse -ErrorAction SilentlyContinue
rm proyecto -Force -Recurse -ErrorAction SilentlyContinue

mkdir obra
mkdir proyecto

cd obra
cmake ..
cmake --build .
cd ..

rm obra -Force -Recurse -ErrorAction SilentlyContinue

mv ./proyecto/compilador.exe ./proyecto/ñ.exe

echo ""
echo ""
echo "Ejecutando ñ"
echo ""

proyecto/ñ.exe