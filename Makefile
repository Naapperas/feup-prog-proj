# -*- Makefile -*-

#added 'all' recipe as a convention, besides providing the grounds for future work.
all: robot-maze clean

robot-maze: src/main.cpp
	g++ -o bin/robot-maze -I ./include ./src/main.cpp

# clean the build folder
clean:
	rm -rf ./build/*.o