# Compiler to use
CXX = g++
CC = $(CXX)

# Compiler flags for development
#  -g         :: Debug info
#  -wall      :: Run all error checks
#  -Wpedantic :: Be pedantic with warnings
CFLAGS = -Wall -Wextra -g -O3 -std=c++11
CXXFLAGS        = $(CFLAGS)
CCFLAGS         = $(CXXFLAGS)

CXXCFLAGS = -std=c++14

# Directories things are stored in
SRC_DIR   := src
OBJ_DIR   := obj
# $(wildcard *.cpp)
SRC_FILES := $(wildcard *.cpp) \
             $(wildcard ../../$(SRC_DIR)/tools/*.cpp) \
             $(wildcard ../../$(SRC_DIR)/holdem/*.cpp) \
             $(wildcard ../../machine_gen_code/*.cpp)
OBJ = $(SRC_FILES:.cpp=.o)

opt: $(OBJ)
	$(CC) -o gen.out $(CFLAGS) $^

# Setup and/or clean
dir:
	mkdir -p $(BUILDDIR)

clean:
	rm *.o 2> /dev/null || true
	rm $(SRC_DIR)../../tools/*.o 2> /dev/null || true
	rm $(SRC_DIR)../../holdem/*.o 2> /dev/null || true

