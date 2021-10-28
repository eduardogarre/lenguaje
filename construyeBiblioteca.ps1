#This Source Code Form is subject to the terms of the Mozilla Public License, v.
#2.0. If a copy of the MPL was not distributed with this file, You can obtain one
#at http://mozilla.org/MPL/2.0/.
#
#This Source Code Form is "Incompatible With Secondary Licenses", as defined by
#the Mozilla Public License, v. 2.0.

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