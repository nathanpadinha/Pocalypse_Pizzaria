# Detect OS
UNAME_S := $(shell uname -s)

# Output directory
OUTPUT_DIR = output

# Source files
SOURCES = Main.cpp OrderTake.cpp PizzaCutGame.cpp Order.cpp TicketRack.cpp TextureManager.cpp Customer.cpp AddToppingsGame.cpp Pizza.cpp Topping.cpp PizzaCook.cpp
OBJECTS = $(addprefix $(OUTPUT_DIR)/,$(SOURCES:.cpp=.o))

# OS-specific configuration
ifeq ($(UNAME_S),Darwin)
	# macOS configuration
	CXX = clang++
	CXXFLAGS = -std=c++17 -Wall -Wextra
	RAYLIB_INCLUDE = /opt/homebrew/include
	RAYLIB_LIB = /opt/homebrew/lib
	LDFLAGS = -L$(RAYLIB_LIB) -lraylib \
	          -framework IOKit -framework Cocoa -framework OpenGL
	EXECUTABLE = $(OUTPUT_DIR)/pocalypse
else
	# Windows configuration
	CXX = g++
	CXXFLAGS = -std=c++17 -Wall -Wextra
	RAYLIB_PATH = C:/raylib/raylib
	RAYLIB_INCLUDE = $(RAYLIB_PATH)/src
	RAYLIB_LIB = $(RAYLIB_PATH)/src
	LDFLAGS = -lraylib -lopengl32 -lgdi32 -lwinmm
	EXECUTABLE = main.exe
endif

# Default target
all: $(OUTPUT_DIR) $(EXECUTABLE)

# Create output directory
$(OUTPUT_DIR):
	mkdir -p $(OUTPUT_DIR)

# Link the executable
$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^ -L$(RAYLIB_LIB) $(LDFLAGS)

# Compile source files
$(OUTPUT_DIR)/%.o: %.cpp | $(OUTPUT_DIR)
	$(CXX) $(CXXFLAGS) -I$(RAYLIB_INCLUDE) -c $< -o $@

# Clean build artifacts (Windows)
clean:
ifeq ($(UNAME_S),Darwin)
	rm -rf $(OUTPUT_DIR)
else
	del /Q /S $(OUTPUT_DIR)
endif

run: $(EXECUTABLE)
	./$(EXECUTABLE)


.PHONY: all clean