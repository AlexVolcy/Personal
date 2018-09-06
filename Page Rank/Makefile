CC=g++
CFLAGS= -Wall -g
LDFLAGS=

TARGET=pagerank
CPP_FILES=$(wildcard *.cpp)
OBJS=${CPP_FILES:%.cpp=%.o}

all: $(TARGET)


%.o: %.cpp
	$(CC) -c -o $@ $<    

$(TARGET): $(OBJS)
	$(CC) $^ -o $@

clean: 
	rm -f *.o pagerank
