CC = g++
COMPILEROPTIONS = -g -Wall
LINKEROPTIONS =
NAME = program


INCLUDE = -IC:/SFML-2.6.1-windows-gcc-13.1.0-mingw-32-bit/SFML-2.6.1/include -IC:/boost_1_81_0
LIB =     -LC:/SFML-2.6.1-windows-gcc-13.1.0-mingw-32-bit/SFML-2.6.1/lib
LIBS = -lquadmath -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network

SRC = $(wildcard src/*.cpp)
HDR = $(wildcard src/*.h)
OBJ = $(patsubst src/%.cpp, obj/%.o, $(SRC))
EXE = bin/$(NAME).exe

all: $(EXE)

.PRECIOUS: bin/%.exe

reset:
	rm obj/*

recompile: reset link

$(EXE): $(OBJ)
	@echo linking $(patsubst obj/%.o, %, $(OBJ))
	$(CC) -o bin/$(NAME) $(OBJ) $(LINKEROPTIONS) $(LIB) $(LIBS)

obj/%.o: src/%.cpp $(HDR)
	@echo compiling $(patsubst %.cpp, %, $<)
	$(CC) -c $< -o $(patsubst src/%.cpp, obj/%.o, $<) $(COMPILEROPTIONS) $(INCLUDE)


run: $(EXE)
	$<

