all: server client  main xclient
objects = SocketThread.h server.cpp

server : $(objects)
	# g++ -o server $(objects)
	g++ -lpthread -o server $(objects)  -std=c++0x

client : client.cpp
	g++ -o client client.cpp

main : main.cpp XTcp.h XTcp.cpp XThread.h
	g++ -lpthread -o main main.cpp XTcp.cpp  -std=c++0x

xclient : xclient.cpp XTcp.h XTcp.cpp
	g++ -o xclient xclient.cpp XTcp.cpp -std=c++0x

.PHONY : clean
clean :
	-rm  server client main
