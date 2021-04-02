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

/**
 * @brief The 'Robot' entity.
 * 
 */
struct Robot { };

/**
 * @brief The 'Player' entity.
 * 
 */
struct Player { };

/**
 * @brief The board that the game will be played on.    
 * 
 */
struct Board { };

/**
 * @brief Starts to play the game. At this point, the user is asked to choose a number between 1 and 99 to play the respective maze, or 0 to return to the initial menu. 
 * 
 * @param out the output stream to write to
 * @param in the input stream to read input from
 * @return true if a map was chosen, false otherwise
 */
bool play();