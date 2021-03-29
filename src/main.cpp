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
 * @brief This is the entrypoint for the porgram itself, required by the compiler.
 * 
 * @return int the exit code, default to 0;
 */
int main() {

    clearScreen();

    std::cout << "********************************" << std::endl;

    char c;
    std::cin >> c;

    clearScreen();

    std::cout << "********************************" << std::endl;

    std::cin >> c;

    return 0;
}