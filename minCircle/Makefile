.PHONY: run clean all

CXX = g++
CXXFLAGS = -Wall -Wextra
TARGET = circle

all: $(TARGET)

$(TARGET): main.o min_circle.o
	$(CXX) main.o min_circle.o -o $(TARGET)

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

min_circle.o: min_circle.cpp
	$(CXX) $(CXXFLAGS) -c min_circle.cpp

run: all
	./$(TARGET)

clean: 
	rm -rf *.o $(TARGET)
