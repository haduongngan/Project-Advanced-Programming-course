//
// Created by Duong Ngan Ha on 08/04/2020.
//

#include "SmartAIPlayer.h"
#include <vector>


SmartAIPlayer :: SmartAIPlayer(){
    name = "SmartAIPlayer";
    id = 1;
    Isthewinner = 0;
    Isyourturn = 0;
    pileChoose = 0;
    stonesChoose = 0;
    play = 0;
}

bool SmartAIPlayer :: RemainOnePile(const vector<int>& matrix){
    int size = matrix.size();
    int count = 0;
    for (int i=0; i<size; i++){
        if (matrix[i] != 0) count++;
    }
    if (count == 1) return true;
    return false;
}

void SmartAIPlayer :: moveOnePile(vector<int>& matrix){
    pileChoose = 0;
    stonesChoose = 0;
    int size = matrix.size();
    for (int i=0; i<size; i++){
        if (matrix[i]>0){
            pileChoose = i;
            break;
        }
    }
    stonesChoose = matrix[pileChoose];
    matrix[pileChoose] = 0;
}

bool SmartAIPlayer :: RemainTwoPiles(const vector<int>& matrix){
    int size = matrix.size();
    int count = 0;
    for (int i=0; i<size; i++){
        if (matrix[i] != 0) count++;
    }
    if (count == 2) return true;
    return false;
}

void SmartAIPlayer :: moveTwoPiles(vector<int>& matrix){
    pileChoose = 0;
    stonesChoose = 0;
    int index1, index2;
    int size = matrix.size();
    for (int i=0; i<size; i++){
        if (matrix[i]>0){
            index1 = i;
            break;
        }
    }
    for (int i=index1+1; i<size; i++){
        if (matrix[i]>0){
            index2 = i;
            break;
        }
    }
    if (matrix[index1]>matrix[index2]){
        pileChoose = index1;
        stonesChoose = matrix[index1] - matrix[index2];
        matrix[index1]=matrix[index2];
    }
    else if (matrix[index1]<matrix[index2]){
        pileChoose = index2;
        stonesChoose = matrix[index2] - matrix[index1];
        matrix[index2] = matrix[index1];
    }
    else{
        int Npiles = matrix.size();
        while (stonesChoose==0){
            srand(time(0));
            pileChoose = rand() % Npiles;
            if (matrix[pileChoose]) stonesChoose = rand() % (matrix[pileChoose]) + 1;
        }
        matrix[pileChoose] -= stonesChoose;
    }
}

int SmartAIPlayer :: NimSum(const vector<int>& matrix){
    int sum = 0;
    int size = matrix.size();
    for (int i=0; i<size; i++){
        sum = sum ^ matrix[i];
    }
    return sum;
}

bool SmartAIPlayer :: IsgoodPos(int NimSum){
    if (NimSum != 0) return true;
    return false;
}

vector<int> SmartAIPlayer :: XOR(const vector<int>& matrix){
    int size = matrix.size();
    vector<int>a;
    int nimsum = NimSum(matrix);
    for (int i=0; i< size; i++){
        int tmp = nimsum ^ matrix[i];
        a.push_back(tmp);
    }
    return a;
}

void SmartAIPlayer :: move(vector<int>& matrix){
    if (RemainOnePile(matrix)) moveOnePile(matrix);
    else if (RemainTwoPiles(matrix)) moveTwoPiles(matrix);
    else {
        pileChoose = 0;
        stonesChoose = 0;
        int nimsum = NimSum(matrix);
        if (IsgoodPos(nimsum)){
            vector<int>x = XOR(matrix);
            int size = matrix.size();
            int index;
            for (int i=0; i<size; i++){
                if (matrix[i]>x[i]){
                    index = i;
                    break;
                }
            }
            stonesChoose = matrix[index] - x[index];
            pileChoose = index;
            matrix[pileChoose] -= stonesChoose;
        }
        else {
            int Npiles = matrix.size();
            while (stonesChoose==0){
                srand(time(0));
                pileChoose = rand() % Npiles;
                if (matrix[pileChoose]) stonesChoose = rand() % (matrix[pileChoose]) + 1;
            }
            matrix[pileChoose] -= stonesChoose;
        }
    }
}

SmartAIPlayer :: ~SmartAIPlayer() = default;