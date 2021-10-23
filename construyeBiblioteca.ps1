rm build -Force -Recurse -ErrorAction SilentlyContinue
rm obra -Force -Recurse -ErrorAction SilentlyContinue
rm -ErrorAction SilentlyContinue *.o

mkdir obra

cd obra
cmake -DCMAKE_BUILD_TYPE=Release ../biblioteca
cmake --build . --parallel 4
cd ..

rm -ErrorAction SilentlyContinue ./proyecto/bibñ.lib
mv ./obra/bibñ.lib ./proyecto/bibñ.lib

rm build -Force -Recurse -ErrorAction SilentlyContinue
rm obra -Force -Recurse -ErrorAction SilentlyContinue
rm ./proyecto/Debug -Force -Recurse -ErrorAction SilentlyContinue