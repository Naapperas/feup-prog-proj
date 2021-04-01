/**
 * @file main.cpp
 * @author Nuno Pereira (up202007865@edu.fe.up.pt)
 * @author Luís Osório (up202004653@edu.fe.up.pt)
 * @brief The main file whose sole purpose is to be the entrypoint of the application
 * @version 1.0
 * @date 2021-03-29
 * 
 * @copyright Copyright (c) 2021
 * 
 */

//STL includes
#include <iostream> // for access to in/out streams 
#include <string> // for string manipulation
#include <vector> // for operations with vectors

//PROJECT includes
#include "../include/utils.h"
#include "../include/game.h"

/**
 * @brief Options avalaible when in the menu.
 * 
 */
enum GameMenuOption {
    EXIT, RULES, PLAY
};

/**
 * @brief Shows the rules of the game.
 * 
 * @param out the stream to write the rules to
 */
inline void showRules(std::ostream& out) { 
    // declare this function inline to let the compiler generate more efficient code, since this is only a handfull of console prints.
    
    clearScreen();
    std::cout << "This is a robot maze game.\nYour goal is to escape all of the robots that exist in the labirinth.\nBut beaware: the fences and posts are electric, and you will get electrocuted if you touch them. So, you know... don't.\nEach time you make a move, the robots also move, and they will always move towards you in the direction of the shortest path.\nUse the:\n-AWDX keys to move vertically and horizontally.\n-QECZ keys to move diagonally.\n-S key to stay in place.\n\nIf you get captured by one of the robots or touch the fences/posts, you lose. If not, you win.\nRobots that collide with each other get destroyed/stuck, obstructing a cell that you can't move into.\nThat said, good luck.\n" << std::endl;
}

/**
 * @brief Shows the game's menu.
 * 
 * @param out the stream to write the menu to
 */
bool showMenu(std::ostream& out, std::istream& in) {
    
    int response;

    out << "Robot Maze" << '\n' ;
    
    while (true) {
        out << "Menu:" << '\n' << "1) Rules" << '\n' << "2) Play" << '\n' << "0) Exit" << '\n' << "Option: ";
        in >> response;

        // Sanitize response, i.e., if response is not one of the options, inform the player.

        switch (response) {
            case RULES:
                showRules(out);
                break;
            
            case PLAY:
                return true;

            case EXIT:
                return false;
            
            default:
                out << "Invalid option, please input a valid option out of the list.";
        };
    }
}

/**
 * @brief This is the entrypoint for the program itself, required by the compiler.
 * 
 * @return int the exit code, default to 0;
 */
int main() {

    clearScreen();

    while (true) {
        if (showMenu(std::cout, std::cin)) { // we are to play the game, play it
            clearScreen();
            if (Game::play(std::cout, std::cin)) // this function did not return 0 i.e. the game was played.
                break;
        } else break;
    }

    return 0;
}
