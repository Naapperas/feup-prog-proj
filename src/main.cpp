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

//PROJECT includes
#include "../include/utils.h"

/**
 * @brief Enum holding constants representing the menu options.
 * 
 */
enum GameMenuOption {
    EXIT, RULES, PLAY
};

/**
 * @brief Shows the game's menu.
 * 
 * @param out the stream to write the menu to.
 */
GameMenuOption showMenu(std::ostream& out, std::istream& in) {
    
    int response;

    out << "Robot Maze" << '\n' << "Menu:" << '\n' << "1) Rules" << '\n' << "2) Play" << '\n' << "0) Exit" << '\n' << "Option: ";
    
    do {
        in >> response;

        // Sanitize response, i.e., if response is not one of the options, inform the player.

    } while (response != 0 || response != 1 || response != 2); 

    return static_cast<GameMenuOption>(response);

}

/**
 * @brief This is the entrypoint for the program itself, required by the compiler.
 * 
 * @return int the exit code, default to 0;
 */
int main() {

    clearScreen();

    switch (showMenu(std::cout, std::cin)) {
        
        case EXIT:
            break;

        case RULES:
            break;

        case PLAY:
            break;
        
        default:
            break;
    }

    return 0;
}
