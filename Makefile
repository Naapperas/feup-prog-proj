# -*- Makefile -*-

# builds the final executable, taken from https://stackoverflow.com/questions/40621451/makefile-automatically-compile-all-c-files-keeping-o-files-in-separate-folde

# ty baltaboss <3

# source folder, object files folder and executable folder
SRC := ./src
OBJ := ./build
BIN := ./bin
EXECUTABLE_NAME := robo-maze

# compiler
CC := g++

# source file and object file names
SOURCES := $(wildcard $(SRC)/*.cpp)
OBJECTS := $(patsubst $(SRC)/%.cpp, $(OBJ)/%.o, $(SOURCES))

# compiles every object into the final executable
# $^ = the name of all dependencies of this recipe
all: $(OBJECTS) makeBin
	$(CC) $< -o $(BIN)/$(EXECUTABLE_NAME)

# compiles every source file into its respective object file
# $@ = name of rule/recipe target
# $< = name of first dependency of this recipe
$(OBJ)/%.o: $(SRC)/%.cpp makeBuild
	$(CC) -c $< -o $@

# create the build folder if it doesn't already exist
makeBuild:
	mkdir -p $(OBJ)/

# create the bin folder if it doesn't already exist
makeBin:
	mkdir -p $(BIN)/

# remove the build folder
clean:
	rm -rf $(OBJ)/

# remove the bin folder
uninstall: clean
	rm -rf $(BIN)/