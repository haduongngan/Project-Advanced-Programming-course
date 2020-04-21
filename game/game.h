//
// Created by Duong Ngan Ha on 12/04/2020.
//

#ifndef GAME_GAME_H
#define GAME_GAME_H

#include <iostream>
#include <vector>
#include "HumanPlayer.h"
#include "AIPlayer.h"
#include "SmartAIPlayer.h"
#include "VARIABLES_PROTOTYPE.h"
#include "brick.h"
using namespace std;
extern vector<vector<int>>data;
extern const char pathdata[];
extern char* pathfont;
extern LTexture background[7];

class Game{
public:
    int NPiles;
    vector<int>NStones;
    int playMode;
    int level;
    int firstturn;
    bool select;
    int pileNow;
    class brick Stone[6][13];
    vector<vector<bool>> isrend;
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
