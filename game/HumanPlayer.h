//
// Created by Duong Ngan Ha on 08/04/2020.
//

#include "Player.h"
#ifndef GAME_HUMANPLAYER_H
#define GAME_HUMANPLAYER_H

class HumanPlayer : public Player {
public:
    HumanPlayer();
    void move(vector<int>& matrix);
    void getName();
    bool hoplepile(const vector<int>& matrix, const int &pile);
    bool hoplestone(const vector<int>& matrix, const int &pile, const int &stones);
    ~HumanPlayer() = default;
};

#endif //GAME_HUMANPLAYER_H
