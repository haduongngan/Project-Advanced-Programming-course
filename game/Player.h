//
// Created by Duong Ngan Ha on 08/04/2020.
//

#include<iostream>
#include <string>
using namespace std;

#ifndef GAME_PLAYER_H
#define GAME_PLAYER_H

class Player {
private:
    string name;
    string type; //loai ng choi AI, human,...
    int mode; //mode choi ...vs...
    int id; //nguoi choi so 1 hay so 2
    bool Isyourturn;
    bool Isthewinner;
public:
    string getname() const;
    void setName(string _name);
    void setType(string _type);
    void setId(int _id);
    void setMode(int _mode);
    void setTurn(int turn);
    void setIsthewinner(int winner);
    virtual void move(vector<int>& matrix) = 0;
    virtual ~Player() = default;
};
#endif //GAME_PLAYER_H
