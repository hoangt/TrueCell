CXX = g++

SRC_DIR = src
OBJ_DIR = build
LIB_DIR = lib
INC_DIR = include
INCLUDE = -I$(INC_DIR)

SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))
LIB = $(LIB_DIR)/libtc.so

CXXFLAGS = -g -Wall -std=c++11 -fPIC -O0
CPPFLAGS = -c $(INCLUDE)
LDFLGAS =

MAIN_LDFLAGS = -L$(LIB_DIR) -Wl,-rpath-link,$(LIB_DIR),-rpath,$(LIB_DIR)

vpath %.h $(SRC_DIR)
vpath %.h $(INC_DIR)

benchmark: build/benchmark.o $(LIB)
	g++ $(CXXFLAGS) -o $@ $< $(MAIN_LDFLAGS) -ltc

build/benchmark.o: benchmark.cpp
	g++ $(CPPFLAGS) $(CXXFLAGS) -o $@ $<

$(LIB): $(OBJS)
	g++ $(CXXFLAGS) -shared -o $@ $^ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp %.h
	g++ $(CPPFLAGS) $(CXXFLAGS) -o $@ $<

.PHONY: clean
clean:
	rm -rf $(OBJS) $(LIB) benchmark build/benchmark.o
