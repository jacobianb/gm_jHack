g++ -c -DBUILD_DLL dllmain.cpp
g++ -shared  dllmain.o -o hax_dll.dll -static
g++ dllmain.cpp hax_dll.dll
del dllmain.o