//
// Created by Duong Ngan Ha on 08/04/2020.
//
#include "HumanPlayer.h"
#include "Player.h"
#include <vector>

    HumanPlayer :: HumanPlayer(){
        setType("Human");
    }
    void HumanPlayer :: move(vector<int>& matrix){
        int pile, stones;
        do {
            cout << getname() << " lay tu coc so: ";
            cin >> pile;
        } while (!hoplepile(matrix,pile));

        do {
            cout << getname() << " lay bao nhieu vien: ";
            cin >> stones;
        } while (!hoplestone(matrix,pile,stones));

        matrix[pile-1] -= stones;
    }
    void HumanPlayer :: getName(){
        cout << "Enter your username: ";
        string _name;
        cin >> _name;
        setName(_name);
    }
    bool HumanPlayer :: hoplepile(const vector<int>& matrix, const int &pile){
        if (pile>=1 && pile <= matrix.size() && matrix[pile-1]>0) return true;
        return false;
    }
    bool HumanPlayer :: hoplestone(const vector<int>& matrix, const int &pile, const int &stones){
        if (matrix[pile-1]>=stones) return true;
        return false;
    }
    //HumanPlayer :: ~HumanPlayer(){}
