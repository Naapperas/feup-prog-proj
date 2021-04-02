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

/**
 * @brief Clears the screen so the console appears non-dirty.
 * 
 */
void clearScreen();

/**
 * @brief Shows the rules of the game.
 * 
 * @param out the stream to write the rules to
 */
void showRules();

/**
 * @brief Shows the game's menu.
 * 
 * @param out the stream to write the menu to
 */
bool showMenu();

/**
 * @brief Reads a file given by the specified filename and returns a vector containing every line in the file.
 * 
 * @param filename the name of the file to read.
 * @return std::vector<std::string> a vector with the lines of the file, or an empty vector if the file does not exist/an error occurs
 */
std::vector<std::string> readFileLines(std::string filename)