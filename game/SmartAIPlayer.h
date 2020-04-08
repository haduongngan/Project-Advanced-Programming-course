//
// Created by Duong Ngan Ha on 08/04/2020.
//
#include "Player.h"
#ifndef GAME_SMARTAIPLAYER_H
#define GAME_SMARTAIPLAYER_H

class SmartAIPlayer : public Player {
public:
    SmartAIPlayer();
    bool RemainOnePile(const vector<int>& matrix);
    void moveOnePile(vector<int>& matrix);
    bool RemainTwoPiles(const vector<int>& matrix);
    void moveTwoPiles(vector<int>& matrix);
    bool IsgoodPos(int NimSum);
    int NimSum(const vector<int>& matrix);
    vector<int> XOR(const vector<int>& matrix);
    void move(vector<int>& matrix);
    ~SmartAIPlayer(){}
};

#endif //GAME_SMARTAIPLAYER_H
