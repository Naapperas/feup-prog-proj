# -*- Makefile -*-

# build the final executable, taken from https://stackoverflow.com/questions/40621451/makefile-automatically-compile-all-c-files-keeping-o-files-in-separate-folde

# ty baltaboss <3

# source folder and object files folder
SRC := src
OBJ := build

# compiler
CC := g++

# source file and object file names
SOURCES := $(wildcard $(SRC)/*.cpp)
OBJECTS := $(patsubst $(SRC)/%.cpp, $(OBJ)/%.o, $(SOURCES))

# compiles every object into the final 'robo-maze' executable
# $^ = the name of all dependencies
all: $(OBJECTS)
	$(CC) $^ -o ./bin/robo-maze

# compiles every source file into its respective object file
# $@ = name of rule/recipe target
# $< = name of first dependency
$(OBJ)/%.o: $(SRC)/%.cpp
	$(CC) -c $< -o $@

# clean the build folder
clean:
	rm -rf ./build/*.o

# keeps the source files only
uninstall: clean
	rm ./bin/robo-maze