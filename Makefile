OS := $(shell uname)

ifeq ($(OS), Linux)
	SOURCES = main.cpp server_linux.cpp server.cpp
	LIBS =
else
	SOURCES = main.cpp server_windows.cpp server.cpp
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

