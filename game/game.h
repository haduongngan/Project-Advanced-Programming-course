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
#include "brick.h"
using namespace std;
#ifndef GAME_GAME_H
#define GAME_GAME_H

extern vector<vector<int>>data;
extern const char pathdata[];
extern char* pathfont;
extern LTexture Backgr;

class Game{
public:
    int NPiles;
    vector<int>NStones;
    int playMode;
    int level;
    int firstturn;
    bool hint;
    class brick Stone[6][13];
    bool isrend[6][13];
    HumanPlayer human1;
    HumanPlayer human2;
    AIPlayer AI;
    SmartAIPlayer smart;

    //ham tao
    Game();

    //ham huy
    ~Game();

    //tao mang luu so stones moi pile
    void setStones();

    //khoi tao nguoi choi dua vao mode
    void setPlayers();

    //kiem tra co nguoi chien thang
    bool checkWin();

    //de cho case 5: thong bao nguoi chien thang
    void winner();

    //tao mang brick dua theo level
    void setbrick();

    //tao mang isrend dua theo level
    void setIsrend();
};


#endif //GAME_GAME_H
