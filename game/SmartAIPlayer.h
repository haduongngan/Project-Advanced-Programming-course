//
// Created by Duong Ngan Ha on 08/04/2020.
//
#include<iostream>
#include <string>
using namespace std;

#ifndef GAME_SMARTAIPLAYER_H
#define GAME_SMARTAIPLAYER_H

class SmartAIPlayer{
public:
    string name;
    int id; //nguoi choi so 1 hay so 2
    bool Isyourturn;
    bool Isthewinner;
    bool play;
    int pileChoose;
    int stonesChoose;

    SmartAIPlayer();

    bool RemainOnePile(const vector<int>& matrix);

    void moveOnePile(vector<int>& matrix);

    bool RemainTwoPiles(const vector<int>& matrix);

    void moveTwoPiles(vector<int>& matrix);

    bool IsgoodPos(int NimSum);

    int NimSum(const vector<int>& matrix);

    vector<int> XOR(const vector<int>& matrix);

    void move(vector<int>& matrix);

    ~SmartAIPlayer();
};

#endif //GAME_SMARTAIPLAYER_H