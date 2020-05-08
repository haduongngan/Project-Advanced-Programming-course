//
// Created by Duong Ngan Ha on 08/04/2020.
//

#ifndef GAME_PLAYER_H
#define GAME_PLAYER_H

#include<iostream>
#include <string>
#include <vector>
#include <cstdlib>
using namespace std;

/*
 * Human Player : 2 member functions
 */
struct HumanPlayer{
    string name;
    int id; //player1 or player2
    bool Isyourturn; //true if now is own turn
    bool Isthewinner; //true if this player win
    bool play; //true if in this game, this player is playing
    bool hint; //true if the hint button has not used

    //constructor
    HumanPlayer();

    //destructor
    ~HumanPlayer();
};

/*
 * AI Player : 3 member functions
 * moves randomly
 */
struct AIPlayer{
    string name;
    int id; //player1 or player2
    bool Isyourturn; //true if now is own turn
    bool Isthewinner; //true if this player win
    bool play; //true if in this game, this player is playing
    int pileChoose; //id of pile which selected
    int stonesChoose; //number of bricks which selected

    //constructor
    AIPlayer();

    /*
     * determine how AIPlyer moves
     * take a matrix which saves number bricks of each stones as a parameter
     * output : update matrix, pileChoose and stonesChoose
     */
    void move(vector<int>& matrix);

    //destructor
    ~AIPlayer();
};

/*
 * SmartAI Player : 10 member functions
 * moves optimally
 */
struct SmartAIPlayer{
    string name;
    int id; //player1 or player2
    bool Isyourturn; //true if now is own turn
    bool Isthewinner; //true if this player win
    bool play; //true if in this game, this player is playing
    int pileChoose; //id of pile which selected
    int stonesChoose; //number of bricks which selected

    //constructor
    SmartAIPlayer();

    /*
     * check whether the game remain exactly one pile which has bricks
     * take a matrix which saves number bricks of each stones as a parameter
     */
    bool RemainOnePile(const vector<int>& matrix);

    /*
     * determine how smart moves in case that there is only 1 pile which has bricks
     * take a matrix which saves number bricks of each stones as a parameter
     * output : update matrix, pileChoose and stonesChoose
     */
    void moveOnePile(vector<int>& matrix);

    /*
     * check whether the game remain exactly 2 piles which has bricks
     * take a matrix which saves number bricks of each stones as a parameter
     */
    bool RemainTwoPiles(const vector<int>& matrix);

    /*
     * determine how smart moves in case that there is only 2 piles which has bricks
     * take a matrix which saves number bricks of each stones as a parameter
     * output : update matrix, pileChoose and stonesChoose
     */
    void moveTwoPiles(vector<int>& matrix);

    /*
     * check whether this SmartAIPlayer was in the good Position(can be win - NimSum != 0)
     * take a the NimSum as a parameter
     */
    bool IsgoodPos(int NimSum);

    /*
     * compute the NimSum now of the game.
     * Use XOR
     * take a matrix which saves number bricks of each stones as a parameter
     */
    int NimSum(const vector<int>& matrix);

    /*
     * compute the XOR of NimSum with number of bricks in each pile
     * Use XOR
     * take a matrix which saves number bricks of each stones as a parameter
     */
    vector<int> XOR(const vector<int>& matrix);

    /*
     * determine how SmartAIPlyer moves (best move to win). If own positive if not good, player will move randomly
     * take a matrix which saves number bricks of each stones as a parameter
     * output : update matrix, pileChoose and stonesChoose
     */
    void move(vector<int>& matrix);

    ~SmartAIPlayer();
};


#endif //GAME_PLAYER_H
