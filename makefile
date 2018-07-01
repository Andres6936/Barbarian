CXX = g++
# -g For debugging flags, -O2 for optimization
OPTS = -std=c++17 -O2
LIBS = -lSDL2 -lSDL2_image

FILES := color texture sprite random console input_handlers entity tile BSP game_map fov engine main
OBJS := $(FILES:=.o)
SRC := $(OBJS:.o=.cpp)
VPATH = ./src:./include

OBJ_NAME = Barbarian

all: $(OBJ_NAME)

$(OBJ_NAME): $(OBJS)
	$(CXX) $(OPTS) -o $(OBJ_NAME) $(OBJS) $(LIBS)

$(OBJS): %.o: %.cpp
	$(CXX) $(OPTS) -c $< -o $@

clean:
	rm *o
