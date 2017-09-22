libmysocket.so : XTcp.cpp XThread.h XTcp.h
	g++  -fPIC -shared -lpthread  -o $@  $+ -std=c++0x

.PHONY : clean
clean :
	-rm  libmysocket.so
