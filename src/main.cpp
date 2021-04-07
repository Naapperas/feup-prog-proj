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
#include <limits>

//PROJECT includes
#include "../include/main.h"
#include "../include/game.h"

// the relative path of the resources, to be changed when project is submitted
#define PATH "./resources/"

// the max number of chars that a stream can hold, used for clearing the standard input 
#define MAX_CHARS std::numeric_limits <std::streamsize>::max()

// TODO: implement functionality first, refactor code later

/**
 * @brief Options avalaible when in the menu.
 * 
 */
enum GameMenuOption {
    EXIT, RULES, PLAY
};

bool operator==(const Position& pos1, const Position& pos2) {
    return pos1.x == pos2.x && pos1.y == pos2.y;
}

void clearScreen() {
    std::cout << std::string(500, '\n') << std::endl; // 500 should be a large enough number for the user not to scroll up
}

void showRules() { 
    
    clearScreen();
    std::cout << "This is a robot maze game.\n\nYour goal is to escape all of the robots that exist in the labirinth.\nBut beaware: the fences and posts are electric, and you will get electrocuted if you touch them. So, you know... don't.\nEach time you make a move, the robots also move, and they will always move towards you in the direction of the shortest path.\nUse the:\n-AWDX keys to move vertically and horizontally.\n-QECZ keys to move diagonally.\n-S key to stay in place.\n\nIf you get captured by one of the robots or touch the fences/posts, you lose. If not, you win.\nRobots that collide with each other get destroyed/stuck, obstructing a cell that you can't move into.\nThat said, good luck.\n" << std::endl;
}

bool showMenu() {
    
    int response;

    std::cout << "Robot Maze" << "\n\n" << "Menu:";
    
    while (true) {

        std::string responseStr;

        std::cout << '\n' << "1) Rules" << '\n' << "2) Play" << '\n' << "0) Exit" << "\n\n" << "Option: ";
        std::cin >> responseStr;

        // clean input
        std::cin.clear();
        std::cin.ignore(MAX_CHARS, '\n');

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
                clearScreen();
                std::cout << "\nInvalid option, please input a valid option out of the list.\n" << std::endl;
        };
    }
}

void waitForEnter() {
    std::cout << "Press ENTER to continue..." << std::endl;
    if (std::cin.peek() =='\n') std::cin.ignore(MAX_CHARS, '\n'); // if we 
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

std::string pickMaze() {

    int mazeNumber;

    while (true) { // make while (true) because the user can keep giving wrong inputs, maybe change later ?
        
        std::cout << "Write the number, from 1 to 99, of the maze you want to play.\nIf you wish to return to the previous menu enter 0 instead.\n" << std::endl; // flush this string immediately
        std::cout << "Maze number: ";
        std::cin >> mazeNumber;

        // clean input stream
        std::cin.clear();
        std::cin.ignore(MAX_CHARS, '\n');

        clearScreen();
        if (!mazeNumber) return "RETURN"; // the user wishes to go back to the previous menu, return special string indicating so

        // check if number is within boundaries

        if (mazeNumber < 0 || mazeNumber > 99) {
            std::cout << "\nThe specified number is out of bounds, please input another number.\n" << std::endl;
            continue;
        }

        // build the file name

        auto mazeFileName = std::string("MAZE_") + ((mazeNumber < 10) ? "0" : "") + std::to_string(mazeNumber) + ".TXT";

        // check if file file exists

        if(fileExists(mazeFileName)) return mazeFileName;

        std::cout << "The given maze does not exist. Please choose another maze to play.\n" << std::endl;

    }
}

bool fileExists(std::string fileName) {

    std::ifstream file(PATH + fileName);

    if (file.is_open()) {
        file.close();
        return file.good(); // the file could be deleted by an external process unknown to us, by returning 'file.good()' we ensure that even if the file does get deleted, the correct status is returned.
    }

    return false; // default behavior
}

/**
 * @brief This is the entrypoint for the program itself, required by the compiler.
 * 
 * @return int the exit code, default to 0;
 */
int main() {

    Board board;

    clearScreen();

    std::string mazeName = "NO_MAZE"; // initialize this string with this value to indicate that no maze has been selected, should be altered in the following loop if the player chooses to play the game
    while (showMenu()) { // show the menu, ask for a maze to pick, rinse and repeat until we get an existing maze

        clearScreen();

        // first we need to chose a maze to play.

        mazeName = pickMaze();

        if (mazeName != "RETURN") break; // if 'pickMaze' returns "RETURNS", we should iterate again through the menu.
    }

    if(mazeName != "NO_MAZE") { // user might leave right away, test if the file name is the initialized

        // at this point it is garanteed that the file exists, so we can just read it;
        auto fileLines = readFileLines(mazeName);
    }

    waitForEnter();

    std::cout << "Until next time :-)" << std::endl;

    return 0;
}