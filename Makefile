CC = g++ -std=gnu++0x
CFLAGS 	= -c -Wall -O3  -I ./include/

#Include Libs
#include OpenCV
CFLAGS 		+= $(shell pkg-config opencv --cflags)
LDFLAGS 	+= $(shell pkg-config opencv --libs)

SOURCES		= $(wildcard ./*.cpp)

OBJECTS		= $(SOURCES:.cpp=.o)

EXECUTABLE = dupercolor

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $(CURDIR)/$< -o $@

clean:
	rm -rf ./*.o $(EXECUTABLE)

