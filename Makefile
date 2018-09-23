# I'm just a Makefile

EXE = imgp

SRC_DIR = src
OBJ_DIR = obj

SRC = $(wildcard $(SRC_DIR)/*.cpp)
OBJ = $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

CPPFLAGS += -Iinclude
CXXFLAGS += -Wall -std=c++17
LDFLAGS += -Llib
LDLIBS += -lz -lpng

.PHONY: all clean

all: $(EXE).out

$(EXE).out: $(OBJ)
	$(CXX) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ) $(EXE).out
