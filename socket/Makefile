all: server client
objects = server.cpp SocketThread.h

server : $(objects)
	# g++ -o server $(objects)
	g++ -lpthread -o server $(objects)  -std=c++0x

client : client.cpp
	g++ -o client client.cpp

.PHONY : clean
clean :
	-rm  server client
