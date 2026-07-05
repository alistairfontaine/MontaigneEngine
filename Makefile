CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -Iinclude

# Driver configuration dependencies
LIBS = -lGL -lglfw -lGLEW

# Folder path definitions
SRC_DIR = src
BIN_DIR = bin

# Dynamic wildcard expansion tracking to collect all source implementation codes
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(SRC_DIR)/%.o)

# Compilation output binary targets
TARGET = $(BIN_DIR)/montaigne

all: $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(OBJS) -o $(TARGET) $(LIBS)

# Abstract rule conversion for parsing object binaries
$(SRC_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(SRC_DIR)/*.o $(TARGET)

.PHONY: all clean
