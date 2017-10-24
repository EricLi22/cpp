all : hello_static.o libhello.a libhello.so  main_s main_d

hello_static.o : hello_static.cpp
	g++ -c hello_static.cpp
	
libhello.a : hello_static.o
	ar crs libhello.a hello_static.o

libhello.so : hello_dynamic.cpp
	g++ -o $@ $+  -fPIC -shared

main_s : main.cpp
	g++  -static -o $@ $+ -I. -lhello -L.

main_d : main.cpp
	g++ -o $@ $+ -I. -lhello -L.

.PHONY : clean
clean :
	-rm hello_static.o libhello.a libhello.so main_s main_d
