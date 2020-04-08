//
// Created by Duong Ngan Ha on 08/04/2020.
//

#include "SmartAIPlayer.h"
#include <vector>


    SmartAIPlayer :: SmartAIPlayer(){
        setType("SmartAIPlayer");
        setName("SmartAIPlayer");
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
        int index;
        int size = matrix.size();
        for (int i=0; i<size; i++){
            if (matrix[i]>0){
                index = i;
                break;
            }
        }
        cout << getname() << " lay " << matrix[index] << " vien da tu coc " << index + 1 << endl;
        matrix[index] = 0;
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
            cout << getname() << " lay " << matrix[index1] - matrix[index2] << " vien da tu coc " << index1 + 1 << endl;
            matrix[index1]=matrix[index2];
        }
        else if (matrix[index1]<matrix[index2]){
            cout << getname() << " lay " << matrix[index2] - matrix[index1] << " vien da tu coc " << index2 + 1 << endl;
            matrix[index2]=matrix[index1];
        }
        else{
            int pile, stones=0;
            while (stones==0){
                pile = index1;
                stones = rand() % (matrix[pile]) + 1;
            }
            matrix[pile] -= stones;
            cout << getname() << " lay " << stones << " vien da tu coc " << pile + 1 << endl;
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
                cout<< getname() << " lay " << matrix[index] - x[index] << " vien da tu coc " << index + 1 << endl;
                matrix[index] = x[index];
            }
            else {
                int pile, stones=0;
                int Npiles = matrix.size();
                while (stones==0){
                    pile = rand() % Npiles;
                    if (matrix[pile]) stones = rand() % (matrix[pile]) + 1;
                }
                matrix[pile] -= stones;
                cout << getname() << " lay " << stones << " vien da tu coc " << pile + 1 << endl;
            }
        }
    }
