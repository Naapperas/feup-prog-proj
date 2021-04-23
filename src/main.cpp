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
#include <cmath>

//PROJECT includes
#include "../include/main.h"
#include "../include/game.h"
#include "../include/leaderboard.h"

// the relative path of the mazes, to be changed when project is submitted
#define MAZE_PATH "./resources/mazes/"

// the relative path of the leaderboards, to be changed when project is submitted
#define LEADERBOARD_PATH "./resources/leaderboards/"

// the max number of chars that a stream can hold, used for clearing the standard input 
#define MAX_CHARS std::numeric_limits <std::streamsize>::max()

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

inline bool operator==(const Robot& r1, const Robot& r2) {
    return r1.id == r2.id;
}

inline bool operator<(const Node& lhs, const Node& rhs) {
    return lhs.score < rhs.score;
}

int getRobotID() {
    static int id = 1; // the starting robot id

    return id++; 
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

        std::cout << '\n' << "1) Rules" << '\n' << "2) Play" << '\n' << "0) Exit" << "\n\n" << "Option: ";

        if (!(std::cin >> response) || std::cin.peek() != '\n') { // input is not a number
            clearInput();
            clearScreen();
            std::cout << "\nPlease input a number.\n" << std::endl;
            continue;
        }

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
    if (std::cin.peek() == '\n') std::cin.ignore(MAX_CHARS, '\n');
}

std::vector<std::string> readFileLines(const std::string& filename, const std::string& relativePath) {

    std::vector<std::string> fileLines;

    std::fstream f;

    f.open(relativePath + filename, std::ios::in);

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

        if(fileExists(mazeFileName, MAZE_PATH)) return mazeFileName;

        std::cout << "The given maze does not exist. Please choose another maze to play.\n" << std::endl;

    }
}

bool fileExists(const std::string& fileName, const std::string& relativePath) {

    std::ifstream file(relativePath + fileName);

    if (file.is_open()) {
        file.close();
        return file.good(); // the file could be deleted by an external process unknown to us, by returning 'file.good()' we ensure that even if the file does get deleted, the correct status is returned.
    }

    return false; // default behavior
}

void fillBoard(Board &board, const std::vector<std::string> &fileLines) {
    
    std::string line = fileLines.at(0); // get first line, containing the maze size

    std::stringstream ss(line);

    char sep; // use this char as a separator because with the extraction operator defined in std::stringstream, we can ignore an arbitrary amount of white spaces, so we don't need to worry about not correctly reading the dimensions of the board

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
                case 'r':
                case 'R': { // robot found

                    Robot robotPog;
                    
                    robotPog.pos = {j, i};
                    robotPog.alive = c == 'R'; // there can be dead robots at the start of the game serving just as obstacles
                    robotPog.id = getRobotID();
                    board.robots.push_back(robotPog);

                    board.aliveRobots += c == 'R'; // if this is an alive robot, this expression evaluates to true, aka, 1
                    
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
}

char getMovementInput(const Board &board) {
    
    static const std::vector<char> validMoves = {'q', 'w', 'e', 'd', 'c', 'x', 'z', 'a', 's'}; // define as 'static const' as to create it only once, and not modify it after creation.
    
    // TODO: better move validation
    while (true) {
        char movement;

        std::cout << "What movement do you want to make: ";
        std::cin >> movement;

        if (std::cin.eof()) { // the user wants to quit the game gracefully

            std::cout << std::endl;

            exit(0);
        }

        clearInput();

        char auxMov = tolower(movement);
        
        if (std::find(validMoves.begin(), validMoves.end(), auxMov) == validMoves.end()) { // the move that the user entered is not one of the valid moves
            clearScreen();
            std::cout << "Not a valid move.\n" << std::endl;
            printBoard(board);
        } else return auxMov;
    }

}

bool isValidPlayerPosition(const Board& board, const Position& pos){
    // if (pos.x < 1 || pos.x > board.width - 2 || pos.y < 1 || pos.y > board.height - 2) return false; bounds are fences, so they can still kill us
    
    switch (board.gameBoard.at(pos.y).at(pos.x)) {
        case 'r': return false; // non-eletric fences
        default: return true; // we are only prohibited from moving into dead robots, so every ther move counts as valid
    }
}

bool movePlayer(Board &board) {
    char move = getMovementInput(board);

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
            clearScreen();
            return true; // we do not wish to move, we can simply return from the function call, return true to signal valid movement
        }

        // no need for a default case because we make sure that only valid moves are passed in to this function
    }

    if(!isValidPlayerPosition(board, newPos)) {
        
        clearScreen();
        std::cout << "That is not a valid position to move into.\n" << std::endl;

        return false;
    }

    char atPos = board.gameBoard.at(newPos.y).at(newPos.x);

    if (atPos == ' ') { // we are moving into a blank position 

        board.gameBoard.at(newPos.y).at(newPos.x) = 'H';
        board.gameBoard.at(prevPos.y).at(prevPos.x) = ' ';
        board.player.pos = newPos;
    } else { // we got electrocuted/we got caught, player lost

        board.gameBoard.at(newPos.y).at(newPos.x) = 'h';
        board.gameBoard.at(prevPos.y).at(prevPos.x) = ' ';
        board.player.alive = false;

    }

    clearScreen();

    return true;
}

int play(Board& board) {

    auto startTime = std::chrono::high_resolution_clock::now();

    while (board.player.alive && board.aliveRobots) {

        printBoard(board);

        bool playerMoved = movePlayer(board);
        
        if (playerMoved) moveAllRobots(board);
    }

    auto endTime = std::chrono::high_resolution_clock::now();

    auto score = std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime).count();

    return score;
}

Position getNextRobotMove(const Board& board, const Robot& robot) {
    auto currPos = robot.pos;

    int dx, dy; // the change of movement in the robots

    dx = (currPos.x < board.player.pos.x) ? 1 : (currPos.x > board.player.pos.x) ? -1 : 0;
    dy = (currPos.y < board.player.pos.y) ? 1 : (currPos.y > board.player.pos.y) ? -1 : 0;

    return {currPos.x + dx, currPos.y + dy};
}

void moveRobot(Board& board, Robot& robot, const Position& newPos) {

    auto prevPos = robot.pos;

    board.gameBoard.at(newPos.y).at(newPos.x) = 'R';
    robot.pos = newPos;

}

void moveAllRobots(Board& board) {

    for (auto &robot : board.robots) {
        if(!robot.alive) continue; // we do not want to move dead robots
        
        bool breakLoop = false;

        Position prevPos = robot.pos;

        Position nextPos = getNextRobotMove(board, robot);

        board.gameBoard.at(prevPos.y).at(prevPos.x) = ' '; // when we move a robot, the last position is always vacant.

        switch(board.gameBoard.at(nextPos.y).at(nextPos.x)) {

            case 'R': // we got stuck on an alive robot, kill both
                
                robot.alive = false;
                
                for (auto &otherRobot : board.robots) {
                    if (otherRobot == robot) continue; // no checking ourselves twice

                    if (otherRobot.pos == nextPos) {
                        otherRobot.alive = false; // kill the other robot and stop checking for robots to kill
                        break;
                    }
                }

                board.gameBoard.at(nextPos.y).at(nextPos.x) = 'r';

                robot.pos = nextPos; // update robot position in case

                board.aliveRobots -= 2;

                break;

            case 'r': // we got stuck on a dead robot, too bad
            case '*': // we hit a fence
                board.gameBoard.at(nextPos.y).at(nextPos.x) = 'r';

                robot.alive = false;
                
                board.aliveRobots--;

                break;

            case 'H': // player lost
                board.player.alive = false;
                
                board.gameBoard.at(nextPos.y).at(nextPos.x) = 'h';
                
                breakLoop = true;
                break; // we can stop iterating through robots cause the player already died

            default: //nothing extraordinary happens, just move the robot
                moveRobot(board, robot, nextPos);
                break;

        };

        if (breakLoop) break;
    }
}

void makeExit() {

    waitForEnter();

    std::cout << "Until next time :-)" << std::endl;

}

int getPlayerNameLength(const std::string& playerName) {
    int counter = 0;

    for (char c : playerName) {
        if ((c & 0b11000000) == 0b10000000) continue; // utf-8 code points that have more than one byte always have a '10' as the most significant bits of the bytes other than the first one, we can just skip them
        counter++;
    }

    return counter;
}

std::string getPlayerName() {
    std::string name;

    while (true) {

        std::cout << "What is your name: ";

        if(!getline(std::cin, name)) { // use getline instead of the extraction operator in order to get the whole line
            clearInput();
            clearScreen();
            std::cout << "There was an error getting input from the user, please retype your name.\n" << std::endl;
            continue;
        }

        // we got no errors extracting player name, check if is within length
        int length = getPlayerNameLength(name);

        if (length < 0 || length > MAX_PLAYER_NAME_LENGTH) {
            clearScreen();
            std::cout << "Name given is longer than the max amount of characters allowed (" << MAX_PLAYER_NAME_LENGTH << "), please retype your name.\n" << std::endl;
            continue;
        }

        // name is within bounds, return it
        return name;
    }

}

void addEntryToLeaderboard(Leaderboard& leaderboard, Node newEntry) {
    leaderboard.leaderboardEntries.push_back(newEntry);
}

void sortLeaderboard(Leaderboard& leaderboard) {

    std::sort(leaderboard.leaderboardEntries.begin(), leaderboard.leaderboardEntries.end(), [](const Node& a, const Node& b){return a < b;});

}

void readLeaderboardFromFile(const std::string& fileName, Leaderboard& leaderboard) {

    if (!fileExists(fileName, LEADERBOARD_PATH)) return; 

    auto fileLines = readFileLines(fileName, LEADERBOARD_PATH);

    // the first 2 lines are header information, we can skip them
    for (int i = 2; i < fileLines.size(); i++) {

        auto line = fileLines.at(i);

        // the last CHARS_PER_SCORE characters are the score

        int score = 0;

        // extract the score
        for (int j = 0; j < CHARS_PER_SCORE; j++) {
            char c = line.at(line.size() - CHARS_PER_SCORE + j);
            score = score * 10 + ((c == ' ' ? '0' : c) - '0');
        }

        // the name that the user inputted might have more than 2 words, store each in tmp and work from there
        std::string name, tmp;

        std::stringstream ss(line);

        ss >> tmp; // read first token

        name += tmp;

        ss.ignore(100, ' '); // try to clear as many blank spaces as possible, 100 is a reasonable ammount of space between name tokens

        if (ss.peek() != '-') {
            ss >> tmp;
            name += (' ' + tmp);
        }

        addEntryToLeaderboard(leaderboard, {name, score});

    }
}

void writeLeaderboardToFile(const std::string& fileName, const Leaderboard& leaderboard) {

    std::ofstream file;

    file.open(LEADERBOARD_PATH + fileName);

    file << "Player";
    file << std::string(16 - std::string("Player").length(), ' ');
    file << "- Time";
    file << '\n';

    file << "----------------------" << '\n';

    for (auto entry : leaderboard.leaderboardEntries) {
        file << entry.playerName;
        file << std::string(16 - getPlayerNameLength(entry.playerName), ' ');
        file << "- ";

        int numDigitsInScore = (entry.score <= 0) ? 0 : floor(log10(entry.score)) + 1;

        file << std::string(CHARS_PER_SCORE - numDigitsInScore, ' '); // allign scores to the right
        file << entry.score;
        file << '\n';
    }

    file.close();
}

/**
 * @brief This is the entrypoint for the program itself, required by the compiler.
 * 
 * @return int the exit code, default to 0;
 */
int main() {

    atexit(makeExit); // we want to gracefuly terminate the program if exit() is called, so register this method

    Board board;
    Leaderboard leaderboard;

    clearScreen();

    std::string mazeName = "NO_MAZE"; // initialize this string with this value to indicate that no maze has been selected, should be altered in the following loop if the player chooses to play the game
    while (showMenu()) { // show the menu, ask for a maze to pick, rinse and repeat until we get an existing maze

        clearScreen();

        // first we need to chose a maze to play.

        mazeName = pickMaze();

        if (mazeName != "RETURN") break; // if 'pickMaze' returns "RETURN", we should iterate again through the menu.
    }

    if (mazeName != "NO_MAZE" && mazeName != "RETURN") { // user might leave right away, test if the file name is the one that the variable was initialized with

        // at this point it is garanteed that the file exists, so we can just read it;
        auto fileLines = readFileLines(mazeName, MAZE_PATH);

        fillBoard(board, fileLines);

        auto score = play(board);

        if (board.player.alive) { // all robots were destroyed, player wins
            
            clearScreen();

            printBoard(board);

            std::cout << "\nCongratulations, you won the game!\n" << std::endl;

            std::string playerName = getPlayerName();

            // build the leaderboard file name from the maze file name already obtained earlier
            std::string leaderboardFileName = std::string("MAZE_") + mazeName.at(5) + mazeName.at(6) + "_WINNERS.TXT";

            readLeaderboardFromFile(leaderboardFileName, leaderboard);

            addEntryToLeaderboard(leaderboard, {playerName, score});

            sortLeaderboard(leaderboard);

            writeLeaderboardToFile(leaderboardFileName, leaderboard);

        } else { // player lost, too bad

            printBoard(board);

            std::cout << "\nIt seems that you have lost, but don't worry, you can still try to beat the game next time.\n" << std::endl;

        }
    }

    // makeExit(); this gets called after main returns, so we don't need to call it here

    return 0;
}