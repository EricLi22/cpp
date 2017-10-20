all : main first second third fourth

main : main.cpp
	g++ -o $@ $+ -lpthread

first : First.cpp
	g++ -o $@ $+ -lpthread

second : Second.cpp
	g++ -o $@ $+ -lpthread

third : Third.cpp
	g++ -o $@ $+ -lpthread

fourth : Fourth.cpp
	g++ -o $@ $+ -lpthread

.PHONY : clean
clean :
	-rm  main first second third fourth
