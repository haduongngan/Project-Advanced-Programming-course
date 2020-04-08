//
// Created by Duong Ngan Ha on 08/04/2020.
//

#include "AIPlayer.h"
#include <vector>


    AIPlayer :: AIPlayer(){
        setType("AIPlayer");
        setName("AIPlayer");
    }
    void AIPlayer :: move(vector<int>& matrix){
        int pile, stones=0;
        int Npiles = matrix.size();
        while (stones==0){
            pile = rand() % Npiles;
            if (matrix[pile]) stones = rand() % (matrix[pile]) + 1;
        }
        matrix[pile] -= stones;
        cout << getname() << " lay " << stones << " vien da tu coc " << pile + 1 << endl;
    }
