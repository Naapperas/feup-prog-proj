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
 * @brief Check if two positions are equal.
 * 
 * @param p1 the first position
 * @param p2 the second position
 * @return true if the positions are the same, false otherwise
 */
inline bool operator==(const Position& p1, const Position& p2); // no need to declare this as a friend function because structs are public by nature

/**
 * @brief The 'Robot' entity.
 * 
 */
struct Robot { 
    
    // the coords of this robot
    Position pos;

    bool alive = true;
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

    std::vector<Position> nonEletricObstacles;

    // the player of the game
    Player player;

};

/**
 * @brief Prints the specified board to the screen.
 * 
 * @param board the board to print
 */
void printBoard(const Board& board);

/**
 * @brief Asks the user for a maze to play and returns the respective maze file name.
 * 
 * @return std::string the name of the maze file to read
 */
std::string pickMaze();

/**
 * @brief fills the game board with the character read from the maze file.
 * 
 * @param board the board to full with charatchers
 */
void fillBoard(Board& board, const std::vector<std::string>& fileLines);

/**
 * @brief get the next movement of the player.
 * 
 * @return char the char representing the next movement of the player
 */
char getMovementInput();

/**
 * @brief Moves the player in the board.
 * 
 * @param board the board in which to move the player
 */
void movePlayer(Board &board);

/**
 * @brief Checks if the given position is valid for the player to move to
 * 
 * @param board the game board
 * @param pos the new desired position for the player
 * @return true if the given position is valid , false otherwise
 */
bool isValidPlayerPosition(const Board& board, const Position& pos);