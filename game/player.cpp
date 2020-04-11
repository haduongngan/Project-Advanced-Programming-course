//
// Created by Duong Ngan Ha on 08/04/2020.
//
#include "Player.h"

    string Player::getname() const {
        return name;
    }

    void Player :: setName(string _name){
        name = _name;
    }
    void Player :: setType(string _type){
        type = _type;
    }
    void Player :: setId(int _id){
        id = _id;
    }
    //void Player :: setMode(int _mode){
      //  mode = _mode;
    //}
    //virtual void getType() = 0;
    //void Player :: setTurn(int turn){
      //  if (id==turn) Isyourturn = true;
        //else Isyourturn = false;
    //}
   // void Player :: setIsthewinner(int winner){
      //  if (id==winner) Isthewinner = true;
    //    else Isthewinner = false;
    //}
    void move(vector<int>& matrix);
    //Player :: Player() {}

