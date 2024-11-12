OS := $(shell uname)

output: main.o
ifeq ($(OS), Linux)
	g++ main.o -o output
else
	g++ main.o -o output -lws2_32
endif

main.o: main.cpp
	g++ -c main.cpp

clear:
ifeq ($(OS), Linux)
	rm -f *.o output
else
	del /F *.o output.exe
endif
