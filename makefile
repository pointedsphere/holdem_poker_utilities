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
SRC_FILES := mainfile.cpp \
             $(wildcard $(SRC_DIR)/tools/*.cpp) \
             $(wildcard $(SRC_DIR)/holdem/*.cpp) \
             $(wildcard $(SRC_DIR)/test/*.cpp)
SRC_FILES_PY := wrapper.cpp \
             $(wildcard $(SRC_DIR)/tools/*.cpp) \
             $(wildcard $(SRC_DIR)/holdem/*.cpp) \
             $(wildcard $(SRC_DIR)/test/*.cpp)
OBJ = $(SRC_FILES:.cpp=.o)

opt: $(OBJ)
	$(CC) -o holdem_tools.out $(CFLAGS) $^

# Note for the bash variables we use the double $$ to escape the makefile std $
python:
	g++ -O3 -Wall -shared -std=c++11 -undefined dynamic_lookup $$(python3 -m pybind11 --includes) -fPIC $(python3 -m pybind11 --includes) $(SRC_FILES_PY) -o holdEm$$(python3-config --extension-suffix)

# Setup and/or clean
dir:
	mkdir -p $(BUILDDIR)

clean:
	rm *.o 2> /dev/null || true
	rm $(SRC_DIR)/tools/*.o 2> /dev/null || true
	rm $(SRC_DIR)/holdem/*.o 2> /dev/null || true
	rm $(SRC_DIR)/test/*.o 2> /dev/null || true

