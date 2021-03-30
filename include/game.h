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

/**
 * @brief namespace for bundling together all mechanich related functions.
 * 
 */
namespace Game {

    /**
     * @brief Starts to play the game.
     * 
     */
    void play(std::ostream& out);

}