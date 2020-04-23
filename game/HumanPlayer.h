//
// Created by Duong Ngan Ha on 08/04/2020.
//

#include<iostream>
#include <string>
using namespace std;

#ifndef GAME_HUMANPLAYER_H
#define GAME_HUMANPLAYER_H

class HumanPlayer{
public:
    string name;
    int id; //nguoi choi so 1 hay so 2
    bool Isyourturn;
    bool Isthewinner;
    bool play;
    bool hint;

    HumanPlayer();

    ~HumanPlayer();
};

#endif //GAME_HUMANPLAYER_H