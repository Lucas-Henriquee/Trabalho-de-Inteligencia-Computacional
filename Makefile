# Compiler
CXX := g++

# Directories
SRC_DIR := source
INC_DIR := include
BUILD_DIR := build

# Source and header files
SRCS := $(wildcard $(SRC_DIR)/*.cpp) main.cpp
OBJS := $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(filter-out main.cpp, $(SRCS)))
MAIN_OBJ := $(BUILD_DIR)/main.o
DEPS := $(wildcard $(INC_DIR)/*.hpp)

# Default Compiler flags
CXXFLAGS := -std=c++17 -Wall -Wextra -I$(INC_DIR)

# OS-specific settings
ifeq ($(OS),Windows_NT)
    MKDIR_CMD = @if not exist $(BUILD_DIR) mkdir $(BUILD_DIR)
    RM_CMD = @if exist $(BUILD_DIR) rmdir /S /Q $(BUILD_DIR) && if exist $(TARGET).exe del $(TARGET).exe
    SHELL_CMD = bash
    EXEC_CMD = @if exist $(EXEC) ($(SHELL_CMD) $(EXEC)) else (echo "execAll.sh not found. Skipping auto-run.")
else
    MKDIR_CMD = @mkdir -p $(BUILD_DIR)
    RM_CMD = @rm -rf $(BUILD_DIR) $(TARGET)
    EXEC_CMD = @if [ -f $(EXEC) ]; then ./$(EXEC); else echo "execAll.sh not found. Skipping auto-run."; fi
endif

# Output executables
TARGET := aircraft_manager
EXEC := execAll.sh

# Default target
.PHONY: all clean

all: $(TARGET)

# Target for creating executable
$(TARGET): $(OBJS) $(MAIN_OBJ)
	$(CXX) $(CXXFLAGS) $(OBJS) $(MAIN_OBJ) -o $(TARGET)
	$(EXEC_CMD)

# Rule for object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp $(DEPS)
	$(MKDIR_CMD)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule for main object file
$(BUILD_DIR)/main.o: main.cpp $(DEPS)
	$(MKDIR_CMD)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean target
clean:
	$(RM_CMD)
