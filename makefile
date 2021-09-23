# Compiler to use
CC = g++

# Compiler flags for development
#  -g         :: Debug info
#  -wall      :: Run all error checks
#  -Wpedantic :: Be pedantic with warnings
DFLAGS = -Wall -g -Wpedantic
FLAGS  = -O3

# Directories things are stored in
SRC_DIR   := src
OBJ_DIR   := obj
SRC_FILES := $(wildcard *.cpp) \
             $(wildcard $(SRC_DIR)/tools/*.cpp) \
             $(wildcard $(SRC_DIR)/test/*.cpp)
OBJ = $(SRC_FILES:.cpp=.o)

opt: $(OBJ)
	$(CC) -o $@.out $(FLAGS) $^

devel: $(OBJ)
	$(CC) -o $@.out $(DFLAGS) $^

# Setup and/or clean
dir:
	mkdir -p $(BUILDDIR)

clean:
	rm *.o 2> /dev/null || true
	rm $(SRC_DIR)/tools/*.o 2> /dev/null || true
	rm $(SRC_DIR)/test/*.o 2> /dev/null || true

