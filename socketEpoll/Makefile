all : server client
server : server.cpp XTcp.cpp XTcp.h XThread.h
	g++ -o $@ $+ -lpthread -std=c++0x

client: client.cpp XTcp.cpp XTcp.h XThread.h
	g++ -o $@	$+ -lpthread -std=c++0x

.PHONY : clean
clean :
	-rm  server client
