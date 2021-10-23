rm build -Force -Recurse -ErrorAction SilentlyContinue
rm obra -Force -Recurse -ErrorAction SilentlyContinue
rm -ErrorAction SilentlyContinue *.o

#cp ./biblioteca/kernel32.lib ./proyecto/kernel32.lib
#cp ./biblioteca/libcmt.lib ./proyecto/libcmt.lib
#cp ./biblioteca/ntdll.lib ./proyecto/ntdll.lib

cp ./biblioteca/base.lib ./proyecto/base.lib

mkdir obra

cd obra
cmake -DCMAKE_BUILD_TYPE=Release ../biblioteca
cmake --build . --parallel 4
cd ..

rm -ErrorAction SilentlyContinue ./proyecto/biblioteca.lib
mv ./proyecto/Debug/biblioteca.lib ./proyecto/biblioteca.lib
#cp ./biblioteca/lld-link.exe ./proyecto/lld-link.exe

rm build -Force -Recurse -ErrorAction SilentlyContinue
rm obra -Force -Recurse -ErrorAction SilentlyContinue
rm ./proyecto/Debug -Force -Recurse -ErrorAction SilentlyContinue

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