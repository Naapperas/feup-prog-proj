/**
 * @file utils.h
 * @author Nuno Pereira (up202007865@edu.fe.up.pt)
 * @author Luís Osório (up202004653@edu.fe.up.pt)
 * @brief Header containing utility functions that might be used throughout the program
 * @version 1.0
 * @date 2021-03-29
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <iostream>
#include <string>

void clearScreen() {
    std::cout << std::string( 100, '\n' ) << std::endl;
}