/**
 * @file leaderboard.h
 * @author Nuno Pereira (up202007865@edu.fe.up.pt)
 * @author Luís Osório (up202004653@edu.fe.up.pt)
 * @brief header containing definitions of leaderboard related functions and structs
 * @version 0.1
 * @date 2021-04-15
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once

#include <string>
#include <vector>

#define MAX_PLAYER_NAME_LENGTH 15

/**
 * @brief A node in the leaderboard, containing information about a player and its respective score.
 * 
 */
struct Node {

    std::string playerName;

    int score;

};

/**
 * @brief Checks if the score of the left hand side node is less than the score of the right hand side node.
 * 
 * @param lhs the first node
 * @param rhs the second node
 * @return true if the score of the left hand side node is less than the score of the right hand side node, false otherwise
 */
inline bool operator<(const Node& lhs, const Node& rhs);

/**
 * @brief The leaderboard itself
 * 
 */
struct Leaderboard {

    // the entries of the leaderboard
    std::vector<Node> leaderboardEntries;
};

/**
 * @brief get the player's name
 * 
 * @return the name of the player
 */
std::string getPlayerName();

/**
 * @brief Returns the length in letters of the players name
 * 
 * @param playerName the name to return the number of letters of
 * @return the number of letters of the given name
 */
int getPlayerNameLength(const std::string& playerName);

/**
 * @brief Sorts the leaderboard by ascending order of node scores.
 * 
 * @param leaderboard the leaderboard to sort
 */
void sortLeaderboard(Leaderboard& leaderboard);

/**
 * @brief Adds the given entry to the leaderboard
 * 
 * @param leaderboard the leaderboard to edit
 * @param newEntry the new entry to add
 */
void addEntryToLeaderboard(Leaderboard& leaderboard, Node newEntry);