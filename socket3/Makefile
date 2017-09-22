all: xserver xclient

xserver : xserver.cpp XTcp.h XTcp.cpp XThread.h
	g++ -lpthread -o xserver xserver.cpp XTcp.cpp  -std=c++0x

xclient : xclient.cpp XTcp.h XTcp.cpp
	g++ -o $@ $+ -std=c++0x

.PHONY : clean
clean :
	-rm  xserver xclient
