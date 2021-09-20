rm *.o -Force -ErrorAction SilentlyContinue
rm *.obj -Force -ErrorAction SilentlyContinue
rm programa.exe -Force -ErrorAction SilentlyContinue

#construyo el proyecto, generando el archivo "resultado.o"
./proyecto/ñ.exe pruebas/*.ñ

#Start-Process -Wait -NoNewWindow "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvars64.bat"
#Start-Process -Wait -NoNewWindow "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Tools\MSVC\14.29.30037\bin\Hostx64\x64\cl.exe" -ArgumentList "pruebas\prueba.cpp resultado.o  /link /out:programa.exe"
./desarrolloVS.ps1
cl biblioteca/bibñ.cpp *.o  /link /out:programa.exe

./programa