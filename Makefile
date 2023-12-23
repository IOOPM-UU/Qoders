CC = gcc
CFLAGS = -Wall 
LDFLAGS = -lgvoc -lcunit

# Directories
MAIN_DIR = src
DEMO_DIR = demo
TEST_DIR = test

# Source Files
MAIN_SOURCES = $(wildcard $(MAIN_DIR)/*.c)
DEMO_SOURCES = $(wildcard $(DEMO_DIR)/*.c)
TEST_SOURCES = $(wildcard $(TEST_DIR)/*.c)
UNIT_TESTS = tests.c #FIXME: change name of unit test file if alternate name is given

# Include directory
INC_DIR = -I$(MAIN_DIR) -I$(DEMO_DIR) -I$(TEST_DIR)

# Build directory
BUILD_DIR = build

# Executables
MAIN_EXECUTABLE = $(BUILD_DIR)/main
UNIT_TESTS_EXECUTABLE = $(BUILD_DIR)/tests

# Object files
MAIN_OBJECTS = $(patsubst $(MAIN_DIR)/%.c,$(BUILD_DIR)/%.o,$(MAIN_SOURCES))
DEMO_OBJECTS = $(patsubst $(DEMO_DIR)/%.c,$(BUILD_DIR)/%.o,$(DEMO_SOURCES))
TEST_OBJECTS = $(patsubst $(TEST_DIR)/%.c,$(BUILD_DIR)/%.o,$(TEST_SOURCES))
UNIT_TESTS_OBJECTS = $(BUILD_DIR)/unit_tests.o

# Default target
.DEFAULT_GOAL := all

# Targets
all: clean_build
all: build_directory
all: $(MAIN_EXECUTABLE)
all: run_main

unit_tests: clean_build
unit_tests: build_directory
unit_tests: $(UNIT_TESTS_EXECUTABLE)
unit_tests: run_tests

run_tests:
	./build/tests

run_main:
	./build/main

clean_build: 
	make clean

build_directory:
	mkdir build

$(MAIN_EXECUTABLE): $(MAIN_OBJECTS) #$(DEMO_OBJECTS)
	$(CC) $(CFLAGS) $(INC_DIR) -o $@ $^

$(UNIT_TESTS_EXECUTABLE): $(UNIT_TESTS_OBJECTS) $(MAIN_OBJECTS)
	$(CC) $(CFLAGS) $(INC_DIR) -o $@ $^ -lcunit

$(BUILD_DIR)/%.o: $(MAIN_DIR)/%.c
	$(CC) $(CFLAGS) $(INC_DIR) -o $@ -c $<

$(BUILD_DIR)/%.o: $(DEMO_DIR)/%.c
	$(CC) $(CFLAGS) $(INC_DIR) -o $@ -c $<

$(BUILD_DIR)/unit_tests.o: $(TEST_DIR)/tests.c
	$(CC) $(CFLAGS) $(INC_DIR) -o $@ -c $<

.PHONY: clean

clean:
	rm -rf $(BUILD_DIR)

build: all
