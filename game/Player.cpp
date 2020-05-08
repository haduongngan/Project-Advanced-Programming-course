//
// Created by Duong Ngan Ha on 08/04/2020.
//

#include "Player.h"

/* 11 - 22
 * Human Player : 2 member functions
 */

//constructor of HumanPlayer
HumanPlayer :: HumanPlayer(){
    Isthewinner = 0;
    Isyourturn = 0;
    play = 0;
    hint = 1;
}

//destructor of HumanPlayer
HumanPlayer :: ~HumanPlayer() = default;

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/* 30 - 60
 * AI Player : 3 member functions
 * moves randomly
 */

//constructor of AIPlayer
AIPlayer :: AIPlayer(){
    name = "AIPlayer";
    id = 1;
    Isthewinner = 0;
    Isyourturn = 0;
    pileChoose = 0;
    stonesChoose = 0;
    play = 0;
}

/* 46 -56
* determine how AIPlyer moves
* take a matrix which saves number bricks of each stones as a parameter
* output : update matrix, pileChoose and stonesChoose
*/
void AIPlayer :: move(vector<int>& matrix){
    pileChoose = 0;
    stonesChoose = 0;
    int Npiles = matrix.size();
    while (!stonesChoose){
        srand(time(0));
        pileChoose = rand() % Npiles;
        if (matrix[pileChoose]) stonesChoose = rand() % (matrix[pileChoose]) + 1;
    }
    matrix[pileChoose] -= stonesChoose;
}

//destructor of AIPlayer
AIPlayer :: ~AIPlayer() = default;

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * SmartAI Player : 10 member functions
 * moves optimally
 */

//constructor of SmartAIPlayer
SmartAIPlayer :: SmartAIPlayer(){
    name = "SmartAIPlayer";
    id = 1;
    Isthewinner = 0;
    Isyourturn = 0;
    pileChoose = 0;
    stonesChoose = 0;
    play = 0;
}

/* 83 - 91
* check whether the game remain exactly one pile which has bricks
* take a matrix which saves number bricks of each stones as a parameter
*/
bool SmartAIPlayer :: RemainOnePile(const vector<int>& matrix){
    int size = matrix.size();
    int count = 0;
    for (int i=0; i<size; i++){
        if (matrix[i] != 0) count++;
    }
    if (count == 1) return true;
    return false;
}

/* 98 - 110
* determine how smart moves in case that there is only 1 pile which has bricks
* take a matrix which saves number bricks of each stones as a parameter
* output : update matrix, pileChoose and stonesChoose
*/
void SmartAIPlayer :: moveOnePile(vector<int>& matrix){
    pileChoose = 0;
    stonesChoose = 0;
    int size = matrix.size();
    for (int i = 0; i < size; i++){
        if (matrix[i] > 0){
            pileChoose = i;
            break;
        }
    }
    stonesChoose = matrix[pileChoose];
    matrix[pileChoose] = 0;
}

/* 116 - 124
* check whether the game remain exactly 2 piles which has bricks
* take a matrix which saves number bricks of each stones as a parameter
*/
bool SmartAIPlayer :: RemainTwoPiles(const vector<int>& matrix){
    int size = matrix.size();
    int count = 0;
    for (int i = 0; i < size; i++){
        if (matrix[i] != 0) count++;
    }
    if (count == 2) return true;
    return false;
}

/* 131 - 165
* determine how smart moves in case that there is only 2 piles which has bricks
* take a matrix which saves number bricks of each stones as a parameter
* output : update matrix, pileChoose and stonesChoose
*/
void SmartAIPlayer :: moveTwoPiles(vector<int>& matrix){
    pileChoose = 0;
    stonesChoose = 0;
    int index1, index2;
    int size = matrix.size();
    for (int i = 0; i < size; i++){
        if (matrix[i] > 0){
            index1 = i;
            break;
        }
    }
    for (int i = index1 + 1; i < size; i++){
        if (matrix[i] > 0){
            index2 = i;
            break;
        }
    }
    if (matrix[index1] > matrix[index2]){
        pileChoose = index1;
        stonesChoose = matrix[index1] - matrix[index2];
    }
    else if (matrix[index1] < matrix[index2]){
        pileChoose = index2;
        stonesChoose = matrix[index2] - matrix[index1];
    }
    else{
        int Npiles = matrix.size();
        while (stonesChoose == 0){
            srand(time(0));
            pileChoose = rand() % Npiles;
            if (matrix[pileChoose]) stonesChoose = rand() % (matrix[pileChoose]) + 1;
        }
    }
    matrix[pileChoose] -= stonesChoose;
}

/* 172 - 179
* compute the NimSum now of the game.
* Use XOR
* take a matrix which saves number bricks of each stones as a parameter
*/
int SmartAIPlayer :: NimSum(const vector<int>& matrix){
    int sum = 0;
    int size = matrix.size();
    for (int i = 0; i < size; i++){
        sum = sum ^ matrix[i];
    }
    return sum;
}

/* 185 - 188
* check whether this SmartAIPlayer was in the good Position(can be win - NimSum != 0)
* take a the NimSum as a parameter
*/
bool SmartAIPlayer :: IsgoodPos(int NimSum){
    if (NimSum != 0) return true;
    return false;
}

/* 195 - 204
* compute the XOR of NimSum with number of bricks in each pile
* Use XOR
* take a matrix which saves number bricks of each stones as a parameter
*/
vector<int> SmartAIPlayer :: XOR(const vector<int>& matrix){
    int size = matrix.size();
    vector<int> a;
    int nimsum = NimSum(matrix);
    for (int i = 0; i < size; i++){
        int tmp = nimsum ^ matrix[i];
        a.push_back(tmp);
    }
    return a;
}

/* 206 - 242
* determine how SmartAIPlyer moves (best move to win). If own positive if not good, player will move randomly
* take a matrix which saves number bricks of each stones as a parameter
* output : update matrix, pileChoose and stonesChoose
*/
void SmartAIPlayer :: move(vector<int>& matrix){
    if (RemainOnePile(matrix)) moveOnePile(matrix);
    else if (RemainTwoPiles(matrix)) moveTwoPiles(matrix);
    else {
        pileChoose = 0;
        stonesChoose = 0;
        int nimsum = NimSum(matrix);
        if (IsgoodPos(nimsum)){
            vector<int> x = XOR(matrix);
            int size = matrix.size();
            int index;
            for (int i = 0; i < size; i++){
                if (matrix[i] > x[i]){
                    index = i;
                    break;
                }
            }
            stonesChoose = matrix[index] - x[index];
            pileChoose = index;
        }
        else {
            int Npiles = matrix.size();
            while (stonesChoose == 0){
                srand(time(0));
                pileChoose = rand() % Npiles;
                if (matrix[pileChoose]) stonesChoose = rand() % (matrix[pileChoose]) + 1;
            }

        }
        matrix[pileChoose] -= stonesChoose;
    }
}

//destructor of SmartAIPlayer
SmartAIPlayer :: ~SmartAIPlayer() = default;