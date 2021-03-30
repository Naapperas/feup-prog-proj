# -*- Makefile -*-

# builds the final executable, taken from https://stackoverflow.com/questions/40621451/makefile-automatically-compile-all-c-files-keeping-o-files-in-separate-folde

# ty baltaboss <3

# source folder, object files folder and executable folder
SRC := ./src
OBJ := ./build
BIN := ./bin

# compiler
CC := g++

# source file and object file names
SOURCES := $(wildcard $(SRC)/*.cpp)
OBJECTS := $(patsubst $(SRC)/%.cpp, $(OBJ)/%.o, $(SOURCES))

# compiles every object into the final 'robo-maze' executable
# $^ = the name of all dependencies of this recipe
all: $(OBJECTS)
	$(CC) $^ -o $(BIN)/robo-maze

# compiles every source file into its respective object file
# $@ = name of rule/recipe target
# $< = name of first dependency of this recipe
$(OBJ)/%.o: $(SRC)/%.cpp
	$(CC) -c $< -o $@

# clean the build folder
clean:
	rm -rf $(OBJ)/*.o

# keeps the source files only
uninstall: clean
	rm $(BIN)/robo-maze