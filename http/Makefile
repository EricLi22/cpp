http : server.cpp XTcp.cpp XTcp.h HttpServer.cpp HttpServer.h HttpClient.h HttpClient.cpp Response.cpp Response.h
	g++ -o $@ $+ -lboost_regex-gcc-1_53 -I/root/boost_1_54_0 -lpthread -std=c++0x

.PHONY : clean
clean :
	-rm  http
