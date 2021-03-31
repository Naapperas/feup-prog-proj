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

#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

/**
 * @brief Clears the screen so the console appears non-dirty.
 * 
 */
inline void clearScreen() {
    std::cout << std::string( 100, '\n' ) << std::endl;
}

/**
 * @brief Reads a file given by the specified filename and returns a vector containing every line in the file.
 * 
 * @param filename the name of the file to read.
 * @return std::vector<std::string> a vector with the lines of the file, or an empty vector if the file does not exist/an error occurs
 */
std::vector<std::string> readFileLines(std::string filename) {

    std::vector<std::string> fileLines;

    std::string fullPath = "../resources/" + filename;

    std::ifstream f;

    f.open(fullPath);

    if(f.is_open()) {

        // file exists, read lines

    }

    return fileLines;
}