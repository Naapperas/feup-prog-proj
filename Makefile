# -*- Makefile -*-

#added 'all' recipe as a convention, besides providing the grounds for future work.
all: robot-maze

robot-maze: src/main.cpp
	g++ -o bin/robot-maze -I./include ./src/main.cpp

#link:
#