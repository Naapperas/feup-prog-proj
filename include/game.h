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

/**
 * @brief Starts to play the game. At this point, the user is asked to choose a number between 1 and 99 to play the respective maze, or 0 to return to the initial menu. 
 * 
 * @param board the board on which to play the game
 * @return true if a map was chosen, false otherwise
 */
bool play(Board& board);

/**
 * @brief Fills a Board object with the fences/posts/robots/player.
 * 
 * @param board the board object on which to play the game
 * @return true if no errors occur, false otherwise
 */
bool fillBoard(Board& board, const std::vector<std::string>& fileLines);

/**
 * @brief Picks a maze to play, if it exists
 * 
 * @param mapLines the vector thats is passed by reference to contain the lines of the maze file chosen
 * @return true if a valid maze was chosen, or false if the user entered '0'
 */
bool pickMaze(std::vector<std::string>& mapLines);

/**
 * @brief 
 * 
 * @return char 
 */
char pollPlayerMove();

/**
 * @brief 
 * 
 * @param playerMove 
 */
void movePlayer(char playerMove, Board& board);