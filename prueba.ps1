rm -ErrorAction SilentlyContinue *.o
rm -ErrorAction SilentlyContinue *.exe

.\proyecto\ñ.exe .\pruebas\*.ñ -s prueba -O1
.\prueba.exe

rm -ErrorAction SilentlyContinue *.o
rm -ErrorAction SilentlyContinue *.exe