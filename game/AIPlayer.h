//
// Created by Duong Ngan Ha on 08/04/2020.
//

#include<iostream>
#include <string>
using namespace std;

#ifndef GAME_AIPLAYER_H
#define GAME_AIPLAYER_H

class AIPlayer{
public:
    string name;
    int id; //nguoi choi so 1 hay so 2
    bool Isyourturn;
    bool Isthewinner;
    int pileChoose;
    int stonesChoose;

    AIPlayer();

    void move(vector<int>& matrix);

    ~AIPlayer();
};

#endif //GAME_AIPLAYER_H
