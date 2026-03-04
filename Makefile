# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
LDFLAGS = -lraylib -lopengl32 -lgdi32 -lwinmm

# Paths
RAYLIB_PATH = C:/raylib/raylib
RAYLIB_INCLUDE = $(RAYLIB_PATH)/src
RAYLIB_LIB = $(RAYLIB_PATH)/src

# Output directory
OUTPUT_DIR = output

# Source files (these are in the same folder as this Makefile)
SOURCES = Main.cpp AddTopping.cpp OrderTake.cpp PizzaCook.cpp PizzaCut.cpp Pizza.cpp
OBJECTS = $(addprefix $(OUTPUT_DIR)/,$(SOURCES:.cpp=.o))
EXECUTABLE = $(OUTPUT_DIR)/main.exe

# Default target
all: $(OUTPUT_DIR) $(EXECUTABLE)

# Create output directory
$(OUTPUT_DIR):
	mkdir $(OUTPUT_DIR)

# Link the executable
$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^ -L$(RAYLIB_LIB) $(LDFLAGS)

# Compile source files (from current directory)
$(OUTPUT_DIR)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) -I$(RAYLIB_INCLUDE) -c $< -o $@

# Clean build artifacts (Windows)
clean:
	-rmdir /S /Q $(OUTPUT_DIR)

.PHONY: all clean