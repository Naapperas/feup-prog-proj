/**
 * @file game.cpp
 * @author Nuno Pereira (up202007865@edu.fe.up.pt)
 * @author Luís Osório (up202004653@edu.fe.up.pt)
 * @brief The implementation code for the definitions in game.h
 * @version 1.0
 * @date 2021-03-30
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#define GO_BACK false

#include "../include/game.h"
#include "../include/utils.h"

bool Game::play(std::ostream& out, std::istream& in) {

    int option;
    std::vector<std::string> mapLines;

    while (true) {

        out << "What is the maze that you want to play (1 through 99, or 0 to go back to the previous menu): ";
        in >> option;

        if(!option) return GO_BACK; // we want to go back to the previous menu

        std::string mapFileName; 
        mapFileName.append("MAZE_");
        mapFileName.append(((option < 10) ? "0" : ""));
        mapFileName.append(std::to_string(option));
        mapFileName.append(".txt");

        out << mapFileName << std::endl;

        mapLines = readFileLines(mapFileName);

        in.ignore(10000, '\n');

        if (!mapLines.empty()) // the file does exist, break out of input loop and play the game
            break;
        
        out << "The specified map does not exist, please choose another one." << std::endl;
    }

    clearScreen();

    return true;

}