# I'm just a Makefile

EXE = imgp

SRC_DIR = src
OBJ_DIR = obj

SRC = $(wildcard $(SRC_DIR)/*.cpp)
OBJ = $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

CPPFLAGS += -Iinclude
CFLAGS += -Wall
LDFLAGS += -L lib
LDLIBS += -lSDL -llodepng

.PHONY: all clean

all: $(EXE).out

$(EXE).out: $(OBJ)
	$(CXX) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ) $(EXE).out
