//
// Created by Duong Ngan Ha on 12/04/2020.
//

#include "game.h"
#include <sstream>
#include <fstream>
#include <cstdlib>

using namespace std;



const char path[] = "../Stones.txt";
vector<int> chooseLevel(const char* f, int level){
    vector<vector<int>>data;
    ifstream infile(f);
    string line;
    while(getline(infile,line)){
        vector<int>tmp;
        int value;
        stringstream iss(line);
        while(iss>>value){
            tmp.push_back(value);
        }
        data.push_back(tmp);
    }
    int maxlevel = data.size();
    int num;
    if (level > maxlevel) num = rand() % maxlevel;
    else num = level-1;
    vector<int>a;
    for (int i=0; i<data[num][0];i++){
        a.push_back(data[num][i+1]);
    }
    return a;
}


    void Game :: setPause(){
        pause = true;
    }

    void Game :: setMode(){
        cout << "Type of game: ";
        cin >> playMode; //3 = smart vs human
        while (playMode > 3 || playMode < 1){
            cout << "Type of game: ";
            cin >> playMode;
        }
    }
    int Game :: getMode(){
        return playMode;
    }

    void Game :: setLevel(){
        cout << "Level of game: ";
        cin >> level;
        while (level > 15 || level < 1){
            cout << "Level of game: ";
            cin >> level;
        }
    }
    int Game :: getLevel(){
        return level;
    }

    void Game :: setStones(){
        Stones = chooseLevel(path,level);
        NumOfPiles = Stones.size();
    }
    vector<int> Game :: getStones(){
        return Stones;
    }

    void Game :: setPlayers(){
        if (playMode == 1) { //human vs human
            human1.setId(1);
            human1.getName();
            human2.setId(2);
            human2.getName();
        }
        else if (playMode == 2) { //AIPlayer vs human
            AI.setId(1);
            human2.setId(2);
            human2.getName();
        }
        else if (playMode == 3) { //SmartAIPlayer vs human
            smart.setId(1);
            human2.setId(2);
            human2.getName();
        }
    }


    void Game :: in(){
        for (int i=0; i<Stones.size(); i++){
            cout << "Pile " << i+1 << " : ";
            for (int j=1; j<=Stones[i]; j++){
                cout << "O ";
            }
            cout << endl;
        }
        cout << endl;
    }

    bool Game :: checkWin(){
        bool check = 1;
        for (int i=0; i<Stones.size(); i++){
            if (Stones[i]>0) {
                check = 0;
                break;
            }
        }
        return check;
    }

    void Game :: step(){
        if (playMode == 1) {
            if (turn == 1) {
                human1.move(Stones);
                turn = 2;
            } else {
                human2.move(Stones);
                turn = 1;
            }
        }

        else if (playMode == 2) {
            if (turn == 1) {
                AI.move(Stones);
                turn = 2;
            } else {
                human2.move(Stones);
                turn = 1;
            }
        }

        else if (playMode == 3) {
            if (turn == 1) {
                smart.move(Stones);
                turn = 2;
            } else {
                human2.move(Stones);
                turn = 1;
            }
        }
    }

    void Game :: winner(){
        if (playMode == 1){
            if (turn == 2) cout << "The winner is " << human1.getname() << endl;
            else cout << "The winner is " << human2.getname() << endl;
        }

        else if (playMode == 2){
            if (turn == 2) cout << "The winner is " << AI.getname() << endl;
            else cout << "The winner is " << human2.getname() << endl;
        }

        else if (playMode == 3){
            if (turn == 2) cout << "The winner is " << smart.getname() << endl;
            else cout << "The winner is " << human2.getname() << endl;
        }
    }

    void Game :: play(){
        setMode();
        setLevel();
        setStones();
        setPlayers();
        cout << "Choose who has the first turn: ";
        cin >> turn;
        while (turn > 3 || turn < 1){
            cout << "Choose who has the first turn: ";
            cin >> turn;
        }
        if (turn == 3) turn = rand()%2 +1;
        in();
        while (checkWin()==0){
            step();
            if (checkWin()==1){
                winner();
                break;
            }
            in();
        }
    }
