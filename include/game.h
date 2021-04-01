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

// we partition definitions in namespaces in order to group relevant/similar code together.

/**
 * @brief namespace for bundling together all mechanics-related functions.
 * 
 */
namespace Game {

    /**
     * @brief The Base entity struct that serves as a foundation to every other entity.
     * 
     */
    struct _BaseEntity {

        protected: // declare these properties 'protected' so children structs have access to them.
            bool alive = true; // straightforward, are we alive or not.
            char aliveSymbol, deadSymbl; // how we are represented in the game.

        private:


    };

    /**
     * @brief The 'Robot' entity.
     * 
     */
    struct Robot : _BaseEntity {

        /**
         * @brief Construct a new Robot object
         * 
         */
        Robot() {
            this->aliveSymbol = 'R';
            this->deadSymbl = 'r';
            this->robotID = generateRobotID();
        }

        private:
            int generateRobotID() {
                static int id = 1;
                return id++;
            }

            int robotID;

    };

    /**
     * @brief The 'Player' entity.
     * 
     */
    struct Player : _BaseEntity {

        /**
         * @brief Construct a new Player object
         * 
         */
        Player() {
            this->aliveSymbol = 'H';
            this->deadSymbl = 'h';
        }

    };

    /**
     * @brief The board that the game will be played on.    
     * 
     */
    struct Board {

        /**
         * @brief Construct a new Board object
         * 
         * @param _cols the number of columns in the board
         * @param _rows the number of rows in the board
         */
        Board(int _cols, int _rows) : cols(_cols), rows(_rows) {

        }

        private:
            char fenceOrPostSymbol = '*';
            int cols, rows;
            std::vector<std::vector<char>> board;

    };

    /**
     * @brief Starts to play the game. At this point, the user is asked to choose a number between 1 and 99 to play the respective maze, or 0 to return to the initial menu. 
     * 
     * @param out the output stream to write to
     * @param in the input stream to read input from
     * @return true if a map was chosen, false otherwise
     */
    bool play(std::ostream& out, std::istream& in);



}