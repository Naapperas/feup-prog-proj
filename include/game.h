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

// we partition definitions in namespaces in order to group relevant/similar code together.

/**
 * @brief namespace for bundling together all mechanich related functions.
 * 
 */
namespace Game {

    /**
     * @brief Entity related namespace, where all the entity definitions are.
     * 
     */
    namespace Entity {

        /**
         * @brief The Base entity struct that serves as a foundation to every other entity.
         * 
         */
        struct _BaseEntity {

            protected: // declare these properties 'protected' so children structs have acces to them.
                bool alive; // straightforward, are we alive or not.
                char aliveSymbol, deadSymbl; // how we are represented in the game.

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

    };

    /**
     * @brief Starts to play the game.
     * 
     */
    void play(std::ostream& out);

}