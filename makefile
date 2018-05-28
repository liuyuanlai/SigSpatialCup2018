CC=g++
#CC_FLAGS=-Wall -ansi -g
CC_FLAGS=-g
EXEC=ssc.out
SOURCES=$(wildcard *.cpp)
OBJECTS=$(SOURCES:.cpp=.o)

$(EXEC): $(OBJECTS)
	$(CC) $(OBJECTS) -o  $(EXEC)

%.o: %.cpp
	$(CC) -c -std=c++11 -I /opt/local/include/ $(CC_FLAGS) $< -o $@

clean:
	rm -f $(EXEC) $(OBJECTS)
