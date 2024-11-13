OS := $(shell uname)

ifeq ($(OS), Linux)
	SOURCES = main.cpp linux_sockets.cpp
	LIBS =
else
	SOURCES = main.cpp windows_sockets.cpp
	LIBS = -lws2_32
endif

output: $(SOURCES)
	g++ $(SOURCES) -o output $(LIBS)

clean:
ifeq ($(OS), Linux)
	rm -f *.o output
else
	del output.exe
endif

