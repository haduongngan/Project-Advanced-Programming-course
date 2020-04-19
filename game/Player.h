//
// Created by Duong Ngan Ha on 08/04/2020.
//

#include<iostream>
#include <string>
using namespace std;

#ifndef GAME_PLAYER_H
#define GAME_PLAYER_H

class Player {
public:
    string name;
    int id; //nguoi choi so 1 hay so 2
    bool Isyourturn;
    bool Isthewinner;

    virtual void move(vector<int>& matrix) = 0;
    virtual ~Player() = default;
};
#endif //GAME_PLAYER_H
