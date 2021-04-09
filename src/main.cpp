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
#include <algorithm>

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

inline bool operator==(const Position& pos1, const Position& pos2) {
    return pos1.x == pos2.x && pos1.y == pos2.y;
}

inline void clearScreen() {
    std::cout << std::string(500, '\n') << std::endl; // 500 should be a large enough number for the user not to scroll up
}

inline void clearInput() {
   
    // clean input
    std::cin.clear();
    std::cin.ignore(MAX_CHARS, '\n');
}

inline void showRules() { 
    
    clearScreen();
    std::cout << "This is a robot maze game.\n\nYour goal is to escape all of the robots that exist in the labirinth.\nBut beaware: the fences and posts are electric, and you will get electrocuted if you touch them. So, you know... don't.\nEach time you make a move, the robots also move, and they will always move towards you in the direction of the shortest path.\nUse the:\n-AWDX keys to move vertically and horizontally.\n-QECZ keys to move diagonally.\n-S key to stay in place.\n\nIf you get captured by one of the robots or touch the fences/posts, you lose. If not, you win.\nRobots that collide with each other get destroyed/stuck, obstructing a cell that you can't move into.\nThat said, good luck.\n" << std::endl;
}

bool showMenu() {
    
    // TODO: refactor this function to make it more expressive

    int response;

    std::cout << "Robot Maze" << "\n\n" << "Menu:";
    
    while (true) {

        char responseChar;

        std::cout << '\n' << "1) Rules" << '\n' << "2) Play" << '\n' << "0) Exit" << "\n\n" << "Option: ";
        std::cin >> responseChar; // even if the user inputs a multidigit number, we only look at the first character, because the input should only be one digit

        if (responseChar < '0' || responseChar > '9') { // if input is not a digit
            clearScreen();
            std::cout << "\nPlease input a number.\n" << std::endl;
            continue;
        }

        response = responseChar - '0'; // convert the char value into a integer value

        clearInput();

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

inline void waitForEnter() {
    std::cout << "Press ENTER to continue..." << std::endl;
    if (std::cin.peek() =='\n') std::cin.ignore(MAX_CHARS, '\n');
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
        if (!(std::cin >> mazeNumber) || std::cin.peek() != '\n') { // there was an error getting maze number or the user did not input just a number

            clearInput();
            clearScreen();
            std::cout << "\nPlease input just a number.\n" << std::endl;
            continue;

        }

        clearInput();

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

void fillBoard(Board &board, const std::vector<std::string> &fileLines) {
    
    std::string line = fileLines.at(0); // get first line, containing the maze size

    std::stringstream ss(line);

    char sep; // use this char as a separator because with the extraction operator, we can ignore an arbitrary amount of white spaces, so we don't need to worry about not correctly reading the dimensions of the board

    // extract size info from the first line
    ss >> board.height;
    ss >> sep;
    ss >> board.width;

    board.gameBoard.reserve(board.height);

    // use the parsed dimensions in order to not "over-read" characters
    for (int i = 0; i < board.height; i++) {
        
        line = fileLines.at(i + 1);

        std::vector<char> lineChars;
        lineChars.reserve(board.width);

        for (int j = 0; j < board.width; j++) {
            
            char c = line.at(j);

            switch (c) {
                case 'R': { // robot found

                    Robot robotPog;
                    
                    robotPog.pos = {j, i};
                    board.robots.push_back(robotPog);
                    
                    break;
                }
                
                case 'H': { // player found
                    
                    Player pogPlayer;

                    pogPlayer.pos = {j, i};
                    board.player = pogPlayer;

                    break;
                }
            }

            lineChars.push_back(c); // append character            
        }

        board.gameBoard.push_back(lineChars); // append the vector containing the lines characters
    }

    board.aliveRobots = board.robots.size();
}

char getMovementInput(){
    
    static const std::vector<char> validMoves = {'q', 'w', 'e', 'd', 'c', 'x', 'z', 'a', 's'}; // define as 'static const' as to create it only once, and not modify it after creation.
    
    // TODO: better move validation
    while (true) {
        char movement;

        std::cout << "What movement do you want to make: ";
        std::cin >> movement;

        clearInput();

        char auxMov = tolower(movement);
        
        if (std::find(validMoves.begin(), validMoves.end(), auxMov) == validMoves.end()) { // the move that the user entered is not one of the valid moves
            std::cout << "Not a valid move." << std::endl;
            // TODO: figure out how to present this without deformatting the output
        } else return auxMov;
    }

}

bool isValidPlayerPosition(const Board& board, const Position& pos){
    if (pos.x < 1 || pos.x > board.width - 2 || pos.y < 1 || pos.y > board.height - 2) return false;
    if (board.gameBoard.at(pos.y).at(pos.x) != ' ') return false; 
    return true;  
}

void movePlayer(Board &board) {
    char move = getMovementInput();

    auto prevPos = board.player.pos; // get the current position of the player

    Position newPos;

    switch (move){
        case 'w': {
            newPos = {prevPos.x, prevPos.y - 1};
            break;
        }

        case 'e': {
            newPos = {prevPos.x + 1, prevPos.y - 1};
            break;
        }

        case 'd': {
            newPos = {prevPos.x + 1, prevPos.y};
            break;
        }

        case 'c': {
            newPos = {prevPos.x + 1, prevPos.y + 1};
            break;
        }

        case 'x': {
            newPos = {prevPos.x, prevPos.y + 1};
            break;
        }

        case 'z':{
            newPos = {prevPos.x - 1, prevPos.y + 1};
            break;
        }

        case 'a': {
            newPos = {prevPos.x - 1, prevPos.y};   
            break;
        }

        case 'q': {
            newPos = {prevPos.x - 1, prevPos.y - 1};
            break;
        }

        case 's': {
            return; // we do not wish to move, we can simply return from the function call
        }

        // no need for a default case because we make sure that only valid moves are passed in to this function
    }

    if(!isValidPlayerPosition(board, newPos)) {
        
        clearScreen();
        std::cout << "That is not a valid position to move into.\n" << std::endl;

        return;
    }

    board.gameBoard.at(newPos.y).at(newPos.x) = 'H';
    board.gameBoard.at(prevPos.y).at(prevPos.x) = ' ';
    board.player.pos = newPos;
    clearScreen();
}

void play(Board& board) {

    while (board.player.alive && board.aliveRobots) {

        printBoard(board);

        movePlayer(board);
    }
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

        if (mazeName != "RETURN") break; // if 'pickMaze' returns "RETURN", we should iterate again through the menu.
    }

    if (mazeName != "NO_MAZE") { // user might leave right away, test if the file name is the one that the variable was initialized with

        // at this point it is garanteed that the file exists, so we can just read it;
        auto fileLines = readFileLines(mazeName);

        fillBoard(board, fileLines);

        play(board);

    }

    waitForEnter();

    std::cout << "Until next time :-)" << std::endl;

    return 0;
}