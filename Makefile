# Simple Makefile for Montaigne Engine
CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -Iinclude
LIBS = -lGL -lglfw -lGLEW

SRC = src/main.cpp
OBJ = $(SRC:.cpp=.o)
TARGET = bin/montaigne

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET) $(LIBS)

clean:
	rm -f $(OBJ) $(TARGET)
