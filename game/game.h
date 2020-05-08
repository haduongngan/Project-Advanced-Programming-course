//
// Created by Duong Ngan Ha on 12/04/2020.
//

#ifndef GAME_GAME_H
#define GAME_GAME_H

#include <iostream>
#include <vector>
#include "Player.h"
#include "brick.h"
using namespace std;

//path
extern const char pathdata[];

//data
extern vector<vector<int>>data;

//backgr
extern LTexture background[7];

// max pile (fixed) and max bricks in each pile
extern const int MAX_PILE;
extern const int MAX_BRICK;

struct Game{
    int NPiles;
    vector<int>NStones;
    int playMode;
    int level;
    int firstturn;
    bool select;
    int pileNow;
    struct brick Stone[6][13];
    vector<vector<bool>> isrend;
    HumanPlayer human1;
    HumanPlayer human2;
    AIPlayer AI;
    SmartAIPlayer smart;

    //constructor
    Game();

    //destructor
    ~Game();

    //construct the matrix NStones based on level
    void setStones();

    //construct players based on mode and first turn
    void setPlayers();

    //check winner : return true if there is a winner
    bool checkWin();

    //set bricks's position based on level
    void setbrick();

    //set matrix isrend based on level
    void setIsrend();
};

/*construct a matrix which saves number of stones based on level
 * take game level as the 1st parameter and vector data as the another parameter
 */
vector<int> chooseLevel(int level, vector<vector<int>>data);

#endif //GAME_GAME_H