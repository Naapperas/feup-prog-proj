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
#include <iostream>
#include <string> 
#include <vector>
#include <sstream>
#include <fstream>
#include <chrono>

//PROJECT includes
#include "../include/main.h"
#include "../include/game.h"

// the relative path of the resources
#define PATH "./resources/"

// TODO: implement functionality first, refactor code later

/**
 * @brief Options avalaible when in the menu.
 * 
 */
enum GameMenuOption {
    EXIT, RULES, PLAY
};

void clearScreen() {
    std::cout << std::string(100, '\n') << std::endl;
}

void showRules() { 
    
    clearScreen();
    std::cout << "This is a robot maze game.\n\nYour goal is to escape all of the robots that exist in the labirinth.\nBut beaware: the fences and posts are electric, and you will get electrocuted if you touch them. So, you know... don't.\nEach time you make a move, the robots also move, and they will always move towards you in the direction of the shortest path.\nUse the:\n-AWDX keys to move vertically and horizontally.\n-QECZ keys to move diagonally.\n-S key to stay in place.\n\nIf you get captured by one of the robots or touch the fences/posts, you lose. If not, you win.\nRobots that collide with each other get destroyed/stuck, obstructing a cell that you can't move into.\nThat said, good luck.\n" << std::endl;
}

bool showMenu() {
    
    int response;

    std::cout << "Robot Maze" << "\n\n" << "Menu:";
    
    while (true) {

        std::cout << '\n' << "1) Rules" << '\n' << "2) Play" << '\n' << "0) Exit" << "\n\n" << "Option: ";
        std::cin >> response;

        // clean input
        std::cin.clear();
        std::cin.ignore(10000, '\n');

        // Sanitize response, i.e., if response is not one of the options, inform the player.

        switch (response) {
            case RULES:
                showRules();
                break;
            
            case PLAY:
                return true;

            case EXIT:
                return false;
            
            default:
                std::cout << "\nInvalid option, please input a valid option out of the list.\n" << std::endl;
        };
    }
}

void waitForEnter() {
    if (std::cin.peek() =='\n') std::cin.ignore(1); // TODO: search for a better way to achieve this
}

std::vector<std::string> readFileLines(std::string filename) {

    std::vector<std::string> fileLines;

    std::fstream f;

    f.open(PATH + filename, std::ios::in);

    if (f.is_open()) {

        // file exists, read lines

        std::string line;

        while (std::getline(f, line))   
            fileLines.push_back(line);      
    
        f.close();
    }

    return fileLines;
}

void printBoard(const Board& board) {

    for (auto line : board.gameBoard) {
        for (char c : line)
            std::cout << c;

        std::cout << '\n';
    }

    std::cout << std::endl;
}

/**
 * @brief This is the entrypoint for the program itself, required by the compiler.
 * 
 * @return int the exit code, default to 0;
 */
int main() {

    Board board;

    clearScreen();

    while (showMenu()) { // we are to play the game, play it
        
        clearScreen();
        
    }

    return 0;
}