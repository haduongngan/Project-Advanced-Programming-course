//
// Created by Duong Ngan Ha on 12/04/2020.
//

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "Player.h"
#include "HumanPlayer.h"
#include "AIPlayer.h"
#include "SmartAIPlayer.h"
#include "game.h"
using namespace std;


int main(int argc, char** argv) {
    cout << "Are you ready?" << endl;
    string s;
    cin >> s;
    while (s == "Yes"){
        Game game1;
        game1.play();
        cout << "Are you ready?" << endl;
        cin >> s;
    }
    return 0;
}
