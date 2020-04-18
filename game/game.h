//
// Created by Duong Ngan Ha on 12/04/2020.
//
#include <iostream>
#include <vector>
#include "Player.h"
#include "HumanPlayer.h"
#include "AIPlayer.h"
#include "SmartAIPlayer.h"
#include "VARIABLES_PROTOTYPE.h"
using namespace std;
#ifndef GAME_GAME_H
#define GAME_GAME_H


class Game{
private:
    int NumOfPiles;
    vector<int>Stones;
    int playMode;

    int level;
    int turn;
    bool pause;
public:
    HumanPlayer human1;
    HumanPlayer human2;
    AIPlayer AI;
    SmartAIPlayer smart;

    void setPause();

    void setMode();
    int getMode();

    void setLevel();
    int getLevel();

    void setStones();
    vector<int> getStones();

    void setPlayers();

    void in();

    bool checkWin();

    void step();

    void winner();

    void play();
};


#endif //GAME_GAME_H
