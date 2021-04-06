/**
 * @file game.h
 * @author Nuno Pereira (up202007865@edu.fe.up.pt)
 * @author Luís Osório (up202004653@edu.fe.up.pt)
 * @brief The header file for the game, where all the functions related to the game mechanichs are defined.
 * @version 1.0
 * @date 2021-03-30
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once

#include <iostream>
#include <vector>
#include <string>

/**
 * @brief Simple struct for representing a pair of coordinates.
 * 
 */
struct Position {

    int x, y;
};

/**
 * @brief Check if to positions are equal.
 * 
 * @param p1 the first position
 * @param p2 the second position
 * @return true if the positionsare the same, false otherwise
 */
bool operator==(Position p1, Position p2);

/**
 * @brief The 'Robot' entity.
 * 
 */
struct Robot { 
    
    // the coords of this robot
    Position pos;
};

/**
 * @brief The 'Player' entity.
 * 
 */
struct Player { 
    
    // the coords of this robot
    Position pos;

    bool alive = true;
};

/**
 * @brief The board that the game will be played on.    
 * 
 */
struct Board { 

    // the dimensions of the board
    unsigned int width, height;

    // the 'char' values representing the board
    std::vector<std::vector<char>> gameBoard;

    std::vector<Robot> robots;
    unsigned int aliveRobots = 0;

    std::vector<Position> eletricObstacles;

    Player player;

};

