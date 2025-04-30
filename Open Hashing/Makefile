# Compiler and flags
CXX = clang++
CXXFLAGS = -Wall -Wextra -std=c++17 -g

# Created file
TARGET = test.out

# Sources
SRCS = main.cpp

# Header files
HEADERS = openhashing.h Functions.h

# Default target
all: $(TARGET)

# Build rule
$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

# Run the program
run: $(TARGET)
	./$(TARGET)

# Clean the build
clean:
	rm -f $(TARGET)

# Rebuild everything from scratch
rebuild: clean all
