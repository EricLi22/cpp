all: server client
objects = SocketThread.h server.cpp

server : $(objects)
	# g++ -o server $(objects)
	g++ -lpthread -o server $(objects)  -std=c++0x

client : client.cpp
	g++ -o client client.cpp

.PHONY : clean
clean :
	-rm  server client
