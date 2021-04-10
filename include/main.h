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
#include <string>

#include "game.h"

/**
 * @brief Clears the screen so the console appears non-dirty.
 * 
 */
inline void clearScreen();

/**
 * @brief Checks if a given string represents a number or not.
 * 
 * @param s the string to check
 * @return true if s represents a number, false otherwise
 */
inline bool isNumber(const std::string& s);

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
 * @return std::vector<std::string> a vector with the lines of the file, or an empty vector if the file does not exist/an error occurs
 */
std::vector<std::string> readFileLines(std::string filename);

/**
 * @brief Checks if the given file exists or not.
 * 
 * @param filename the name of the file to check
 * @return true if the file exists, false otherwise
 */
bool fileExists(std::string filename);

/**
 * @brief Exits the game and performs any cleanup necessary.
 * 
 */
void makeExit();

/**
 * @brief Plays the game using the specified board.
 * 
 * @param board the board to play the game on
 */
void play(Board& board);