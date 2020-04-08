//
// Created by Duong Ngan Ha on 08/04/2020.
//
#include "Player.h"
#ifndef GAME_AIPLAYER_H
#define GAME_AIPLAYER_H

class AIPlayer : public Player {
public:
    AIPlayer();
    void move(vector<int>& matrix);
    ~AIPlayer(){}
};

#endif //GAME_AIPLAYER_H
