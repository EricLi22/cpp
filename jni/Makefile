libcpp.so : CppLib.cpp
	g++ -o $@ $+ -fPIC -shared -I/usr/local/java/jdk1.8.0_144/include -I/usr/local/java/jdk1.8.0_144/include/linux

.PHONY : clean
clean :
	-rm libcpp.so
