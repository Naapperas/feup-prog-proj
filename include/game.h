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

        void die() { this->alive = false; }
        bool isAlive() const { return this->alive; }

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
        }

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

        /**
         * @brief Prints the board to the screen.
         * 
         */
        void showBoard(std::ostream& out);

        private:
            char fenceOrPostSymbol = '*';
            int cols, rows;
            std::vector<std::vector<char>> board;

    };

    /**
     * @brief Starts to play the game.
     * 
     */
    void play(std::ostream& out);

}