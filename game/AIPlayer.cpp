//
// Created by Duong Ngan Ha on 08/04/2020.
//

#include "AIPlayer.h"
#include <vector>
#include <cstdlib>



AIPlayer :: AIPlayer(){
    name = "AIPlayer";
    id = 1;
    Isthewinner = 0;
    Isyourturn = 0;
    pileChoose = 0;
    stonesChoose = 0;
    play = 0;
}

//chay xong se dc ket qua la lay bnhieu da o hang nao
void AIPlayer :: move(vector<int>& matrix){
    pileChoose = 0;
    stonesChoose = 0;
    int Npiles = matrix.size();
    while (stonesChoose==0){
        srand(time(0));
        pileChoose = rand() % Npiles;
        if (matrix[pileChoose]) stonesChoose = rand() % (matrix[pileChoose]) + 1;
    }
    matrix[pileChoose] -= stonesChoose;
}

AIPlayer :: ~AIPlayer() = default;