//T10_G01

/**
 * @file main.h
 * @author Nuno Pereira (up202007865@edu.fe.up.pt)
 * @author Luís Osório (up202004653@edu.fe.up.pt)
 * @brief function definitions for main.cpp 
 * @version 0.1
 * @date 2021-04-02
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once

#include <vector>
#include <cmath>
#include <string>

#include "game.h"

#define NUMBER_SIZE(num) (num <= 0) ? 0 : (floor(log10(num)) + 1)

/**
 * @brief Clears the screen so the console appears non-dirty.
 * 
 */
inline void clearScreen();

/**
 * @brief Clears the standard input stream
 * 
 */
inline void clearInput();

/**
 * @brief Shows the rules of the game.
 * 
 * @param out the stream to write the rules to
 */
inline void showRules();

/**
 * @brief Shows the game's menu.
 * 
 * @param out the stream to write the menu to
 */
bool showMenu();

/**
 * @brief Waits for the enter key to be pressed.
 * 
 */
inline void waitForEnter();

/**
 * @brief Reads a file given by the specified filename and returns a vector containing every line in the file.
 * 
 * @param filename the name of the file to read.
 * @param relativePath the relative path of the resource to read
 * @return std::vector<std::string> a vector with the lines of the file, or an empty vector if the file does not exist/an error occurs
 */
std::vector<std::string> readFileLines(const std::string& filename, const std::string& relativePath);

/**
 * @brief Checks if the given file exists or not.
 * 
 * @param filename the name of the file to check
 * @param relativePath the relative path to the file to the existance of
 * @return true if the file exists, false otherwise
 */
bool fileExists(const std::string& filename, const std::string& relativePath);

/**
 * @brief Exits the game and performs any cleanup necessary.
 * 
 */
void makeExit();

/**
 * @brief Plays the game using the specified board.
 * 
 * @param board the board to play the game on
 * @return the score of the game
 */
int play(Board& board);