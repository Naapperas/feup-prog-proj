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
    if (std::cin.peek() =='\n') std::cin.ignore(1);
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

bool pickMaze(std::vector<std::string>& mapLines) {

    int option;

    while (true) {

        std::cout << "What is the maze that you want to play (1 through 99, or 0 to go back to the previous menu): ";
        std::cin >> option;

        if(!option) return false; // we want to go back to the previous menu

        std::string mapFileName; 
        mapFileName.append("MAZE_");
        mapFileName.append(((option < 10) ? "0" : ""));
        mapFileName.append(std::to_string(option));
        mapFileName.append(".TXT");

        mapLines = readFileLines(mapFileName);

        // clean input buffer
        std::cin.clear();
        std::cin.ignore(10000, '\n');

        if (!mapLines.empty()) // the file exists, signal that it does
            return true;
        
        std::cout << "The specified maze does not exist, or an error has occured while trying to open the specified maze, please choose another one." << std::endl;
    }

}

char pollPlayerMove() {
        char move;
        std::cout << "What move do you want to make: ";
        std::cin >> move;
        
        std::cin.clear();
        std::cin.ignore(1000, '\n');

        return move;
}

void movePlayer(char playerMove, Board& board) {

    auto prevPos = board.player.pos;
    Position newPos;

    switch (playerMove) {

        case 'q': // up left 
        case 'Q': {
            newPos = {prevPos.x - 1, prevPos.y - 1};
            break;
        }

        case 'w': // up
        case 'W': {
            newPos = {prevPos.x, prevPos.y - 1};
            break;
        }

        case 'e': // up right
        case 'E': {
            newPos = {prevPos.x + 1, prevPos.y - 1};

            break;
        }

        case 'a': // left
        case 'A': {
            newPos = {prevPos.x - 1, prevPos.y};

            break;
        }

        case 's': // stay in place
        case 'S': {
            newPos = {prevPos.x, prevPos.y};
            break;
        }

        case 'd': // right
        case 'D': {
            newPos = {prevPos.x + 1, prevPos.y};
            break;
        }

        case 'z': // down left
        case 'Z': {
            newPos = {prevPos.x - 1, prevPos.y + 1};
            break;
        }

        case 'x': // down 
        case 'X': {
            newPos = {prevPos.x, prevPos.y + 1};
            break;
        }

        case 'c': // down right
        case 'C': {
            newPos = {prevPos.x + 1, prevPos.y + 1};
            break;
        }

        default:
            std::cout << "Invalid movement option, please input a valid movement" << std::endl;
            return;

    }

    board.gameBoard.at(prevPos.y).at(prevPos.x) = ' ';
    board.gameBoard.at(newPos.y).at(newPos.x) = 'H';
    board.player.pos = newPos;

}

bool play(Board& board) {

    int option;
    std::vector<std::string> mapLines;

    if(!pickMaze(mapLines)) return false; // we're signaled to go back to the previous menu, returning false causes the main function to continue iterating

    clearScreen();

    if(!fillBoard(board, mapLines)) // we're signaled to exit, returning true causes the main function to exit and thus terminate the program.
        return true;

    auto initTime = std::chrono::system_clock::now(); // the time at which the game started

    while (board.player.alive && board.aliveRobots > 0) {

        clearScreen();

        printBoard(board);

        char playerMove = pollPlayerMove();

        movePlayer(playerMove, board);

        printBoard(board);

        //break; // poll user input, move the player, move the robots, repeat...
    }

    auto finalTime = std::chrono::system_clock::now(); // the time at which the game ended

    auto score = std::chrono::duration_cast<std::chrono::seconds>(finalTime - initTime).count();

    if (board.player.alive) { // game ended because all robots got stuck

    } else { // game ended because player got caught

    }

    return true;
}

bool fillBoard(Board& board, const std::vector<std::string>& fileLines) {

    std::stringstream ss;
    int width, height;
    char sep;

    ss << fileLines.at(0);

    ss >> height >> sep >> width;

    if (sep != 'x') {
        // error
        std::cout << "Error when filling board, exiting" << std::endl;
        return false;
    }

    board.height = height, board.width = width;

    for (int i = 1; i < fileLines.size(); i++) { // traverse every line in the file that is not the first

        std::vector<char> lineChars;

        auto line = fileLines.at(i);
        
        for (int j = 0; j < line.size(); j++) { // traverse each char in the given line

            char c = line.at(j);

            Position pos = {j, i-1};

            switch (c) {
 
                case '*': // found a post/eletric fence, store its position
                    board.eletricObstacles.push_back(pos);
                    break;

                case 'R': // we found a robot, store its position and add it to the collection of robots
                    Robot r;

                    r.pos = pos;

                    board.robots.push_back(r);
                    break;
                
                case 'H': // we found the player, store its position
                    Player p;

                    p.pos = pos;

                    board.player = p;
                    break;

            };

            lineChars.push_back(c);
        }

        board.gameBoard.push_back(lineChars);
    }

    board.aliveRobots = board.robots.size();

    return true;
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
        if (play(board)) // this function did not return 0 i.e. the game was played.
            break;
    }

    return 0;
}