//
// Created by Duong Ngan Ha on 12/04/2020.
//

#include "game.h"
#include "VARIABLES_PROTOTYPE.h"
using namespace std;


//ham tao
Game :: Game(){
    NPiles = 0;
    playMode = 1;
    level = 1;
    firstturn = 1;
    select = false;
    pileNow = -1;
    for (int i=0; i<6; i++){
        for (int j=0; j<13 ; j++){
            Stone[i][j].setPile(i+1);
            Stone[i][j].setCol(j+1);
        }
    }
    for (int i=0; i<6; i++){
        vector<bool> tmp;
        for (int j=0; j<13; j++){
            tmp.push_back(false);
        }
        isrend.push_back(tmp);
    }
}

//ham huy
Game :: ~Game(){
    for (int i=0; i<6; i++){
        for (int j=0; j<13; j++){
            Stone[i][j].obj.free();
            Stone[i][j].brick02.free();
        }
    }
}


//tao mang luu so stones moi pile
void Game :: setStones(){
    NStones = chooseLevel(level,data);
    NPiles = NStones.size();

}

//khoi tao nguoi choi dua vao mode va first turn
void Game :: setPlayers(){
    if (playMode == 1) { //human vs human
        human1.id = 1;
        human1.name = "Player 1";
        human1.play = 1;
        human2.id = 2;
        human2.name = "Player 2";
        human2.play = 1;
        if (firstturn == 1) {
            human1.Isyourturn = true;
            human2.Isyourturn = false;
        }
        else {
            human1.Isyourturn = false;
            human2.Isyourturn = true;
        }
        human1.Isthewinner = 0;
        human2.Isthewinner = 0;
        human1.hint = 1;
        human2.hint = 1;

        AI.Isthewinner = 0;
        AI.Isyourturn = 0;
        AI.pileChoose = 0;
        AI.stonesChoose = 0;
        AI.play = 0;

        smart.Isthewinner = 0;
        smart.Isyourturn = 0;
        smart.pileChoose = 0;
        smart.stonesChoose = 0;
        smart.play = 0;
    }
    else if (playMode == 2) { //AIPlayer vs human
        AI.play = 1;
        human2.id = 2;
        human2.name = "Player 2";
        human2.play = 1;
        if (firstturn == 1) {
            AI.Isyourturn = true;
            human2.Isyourturn = false;
        }
        else {
            AI.Isyourturn = false;
            human2.Isyourturn = true;
        }
        AI.Isthewinner = 0;
        AI.pileChoose = 0;
        AI.stonesChoose = 0;
        human2.Isthewinner = 0;
        human2.hint = 1;

        smart.Isthewinner = 0;
        smart.Isyourturn = 0;
        smart.pileChoose = 0;
        smart.stonesChoose = 0;
        smart.play = 0;

        human1.Isthewinner = 0;
        human1.Isyourturn = 0;
        human1.play = 0;
        human1.hint = 1;
    }
    else if (playMode == 3) { //SmartAIPlayer vs human
        smart.play = 1;
        human2.id = 2;
        human2.name = "Player 2";
        human2.play = 1;
        if (firstturn == 1) {
            smart.Isyourturn = true;
            human2.Isyourturn = false;
        }
        else {
            smart.Isyourturn = false;
            human2.Isyourturn = true;
        }
        smart.Isthewinner = 0;
        smart.pileChoose = 0;
        smart.stonesChoose = 0;
        human2.Isthewinner = 0;
        human2.hint = 1;

        AI.Isthewinner = 0;
        AI.Isyourturn = 0;
        AI.pileChoose = 0;
        AI.stonesChoose = 0;
        AI.play = 0;

        human1.Isthewinner = 0;
        human1.Isyourturn = 0;
        human1.play = 0;
        human1.hint = 1;
    }
}

//kiem tra co nguoi chien thang : tra ve 1 neu co ng thang
bool Game :: checkWin(){
    bool check = 1;
    for (int i=0; i<NPiles; i++){
        for (int j=0; j<13;j++){
            if (isrend[i][j]) {
                check = 0;
                break;
            }
        }
    }
    return check;
}


//de cho case 5: thong bao nguoi chien thang while(!quit)
void Game :: winner(){
    //load back case 5
    background[0].render(0,0);
    background[1].render(0,0);

    //thong bao chien thang : load text

    if (human1.Isthewinner){
        if (loadText(pathfont, "Congratulation!!!", 30)) {
            texttexture.render(160, 200);
        }
        if (loadText(pathfont, "The winner is", 28)) {
            texttexture.render(186, 232);
        }
        if (loadText(pathfont, "Player 1", 32)) {
            texttexture.render(217, 260);
        }
    }
    else if (human2.Isthewinner && select){
        if (loadText(pathfont, "Congratulation!!!", 30)) {
            texttexture.render(160, 200);
        }
        if (loadText(pathfont, "The winner is", 28)) {
            texttexture.render(186, 232);
        }
        if (loadText(pathfont, "Player 2", 32)) {
            texttexture.render(217, 260);
        }
    }
    else if (AI.Isthewinner) {
        if (loadText(pathfont, "Congratulation!!!", 30)) {
            texttexture.render(160, 200);
        }
        if (loadText(pathfont, "The winner is", 28)) {
            texttexture.render(186, 232);
        }
        if (loadText(pathfont, "AIPlayer", 32)) {
            texttexture.render(200, 260);
        }
    }
    else if (smart.Isthewinner) {
        if (loadText(pathfont, "Congratulation!!!", 30)) {
            texttexture.render(160, 200);
        }
        if (loadText(pathfont, "The winner is", 28)) {
            texttexture.render(186, 232);
        }
        if (loadText(pathfont, "SmartAIPlayer", 32)) {
            texttexture.render(167, 260);
        }
    }

    //load cac node
    //get mouse position
    int x, y;
    SDL_GetMouseState(&x, &y);

    //check if mourse is in button
    bool inNext = true;
    bool inquit = true;
    bool inMenu = true;
    if (x < 241) inquit = false;
    else if (x > 241 + 52) inquit = false;
    else if (y < 438) inquit = false;
    else if (y > 438 + 23) inquit = false;

    if (x < 212) inNext = false;
    else if (x > 212 + 127) inNext = false;
    else if (y < 332) inNext = false;
    else if (y > 332 + 26) inNext = false;

    if (x < 238) inMenu = false;
    else if (x > 238 + 70) inMenu = false;
    else if (y < 378) inMenu = false;
    else if (y > 378 + 26) inMenu = false;


    if (inNext){
        if (loadTextNew(pathfont, "Next level", 28)) {
            texttexture.render(212, 318);
        }
    }
    else {
        if (loadText(pathfont, "Next level", 28)) {
            texttexture.render(212, 318);
        }
    }

    if (inMenu){
        if (loadTextNew(pathfont, "Menu", 28)) {
            texttexture.render(238, 365);
        }
    }
    else {
        if (loadText(pathfont, "Menu", 28)) {
            texttexture.render(238, 365);
        }
    }

    if (inquit){
        if (loadTextNew(pathfont, "Quit", 28)) {
            texttexture.render(241, 420);
        }
    }
    else {
        if (loadText(pathfont, "Quit", 28)) {
            texttexture.render(241, 420);
        }
    }

    //update screen
    SDL_RenderPresent(renderer);
}

//set toa do cua brick dua theo level
void Game :: setbrick(){

    if (level==1 || level==2 || level==3){
        Stone[0][0].setPosition(42,199); //
        Stone[0][1].setPosition(77, 199); //
        Stone[0][2].setPosition(112, 199);  //
        Stone[0][3].setPosition(147,199); //
        Stone[0][4].setPosition(182,199); //
        Stone[0][5].setPosition(217,199); //
        Stone[0][6].setPosition(252,199); //
        Stone[0][7].setPosition(287,199);  //
        Stone[0][8].setPosition(322,199);  //
        Stone[0][9].setPosition(357,199); //
        Stone[0][10].setPosition(392,199); //
        Stone[0][11].setPosition(427,199); //
        Stone[0][12].setPosition(462,199); //

        Stone[1][0].setPosition(42, 334);  //
        Stone[1][1].setPosition(77, 334);
        Stone[1][2].setPosition(112,334);
        Stone[1][3].setPosition(147,334);
        Stone[1][4].setPosition(182,334);
        Stone[1][5].setPosition(217,334);
        Stone[1][6].setPosition(252,334);
        Stone[1][7].setPosition(287,334);
        Stone[1][8].setPosition(322,334);
        Stone[1][9].setPosition(357,334); //
        Stone[1][10].setPosition(392,334); //
        Stone[1][11].setPosition(427,334); //
        Stone[1][12].setPosition(462,334); //
    }


    else if (level==4 || level==5 || level==6){
        Stone[0][0].setPosition(42,135); //
        Stone[0][1].setPosition(77, 135); //
        Stone[0][2].setPosition(112, 135);  //
        Stone[0][3].setPosition(147,135); //
        Stone[0][4].setPosition(182,135); //
        Stone[0][5].setPosition(217,135); //
        Stone[0][6].setPosition(252,135); //
        Stone[0][7].setPosition(287,135);  //
        Stone[0][8].setPosition(322,135);  //
        Stone[0][9].setPosition(357,135); //
        Stone[0][10].setPosition(392,135); //
        Stone[0][11].setPosition(427,135); //
        Stone[0][12].setPosition(462,135); //

        Stone[1][0].setPosition(42, 262);  //
        Stone[1][1].setPosition(77, 262);
        Stone[1][2].setPosition(112,262);
        Stone[1][3].setPosition(147,262);
        Stone[1][4].setPosition(182,262);
        Stone[1][5].setPosition(217,262);
        Stone[1][6].setPosition(252,262);
        Stone[1][7].setPosition(287,262);
        Stone[1][8].setPosition(322,262);
        Stone[1][9].setPosition(357,262); //
        Stone[1][10].setPosition(392,262); //
        Stone[1][11].setPosition(427,262); //
        Stone[1][12].setPosition(462,262); //

        Stone[2][0].setPosition(42,388); //
        Stone[2][1].setPosition(77, 388); //
        Stone[2][2].setPosition(112, 388);  //
        Stone[2][3].setPosition(147,388); //
        Stone[2][4].setPosition(182,388); //
        Stone[2][5].setPosition(217,388); //
        Stone[2][6].setPosition(252,388); //
        Stone[2][7].setPosition(287,388);  //
        Stone[2][8].setPosition(322,388);  //
        Stone[2][9].setPosition(357,388); //
        Stone[2][10].setPosition(392,388); //
        Stone[2][11].setPosition(427,388); //
        Stone[2][12].setPosition(462,388); //
    }

    else if (level==7 || level==8 ||level==9){
        Stone[0][0].setPosition(42,108); //
        Stone[0][1].setPosition(77, 108); //
        Stone[0][2].setPosition(112, 108);  //
        Stone[0][3].setPosition(147,108); //
        Stone[0][4].setPosition(182,108); //
        Stone[0][5].setPosition(217,108); //
        Stone[0][6].setPosition(252,108); //
        Stone[0][7].setPosition(287,108);
        Stone[0][8].setPosition(322,108);
        Stone[0][9].setPosition(357,108); //
        Stone[0][10].setPosition(392,108); //
        Stone[0][11].setPosition(427,108); //
        Stone[0][12].setPosition(462,108); //

        Stone[1][0].setPosition(42, 218);  //
        Stone[1][1].setPosition(77, 218);
        Stone[1][2].setPosition(112,218);
        Stone[1][3].setPosition(147,218);
        Stone[1][4].setPosition(182,218);
        Stone[1][5].setPosition(217,218);
        Stone[1][6].setPosition(252,218);
        Stone[1][7].setPosition(287,218);
        Stone[1][8].setPosition(322,218);
        Stone[1][9].setPosition(357,218); //
        Stone[1][10].setPosition(392,218); //
        Stone[1][11].setPosition(427,218); //
        Stone[1][12].setPosition(462,218); //

        Stone[2][0].setPosition(42,323); //
        Stone[2][1].setPosition(77, 323); //
        Stone[2][2].setPosition(112, 323);  //
        Stone[2][3].setPosition(147,323); //
        Stone[2][4].setPosition(182,323); //
        Stone[2][5].setPosition(217,323); //
        Stone[2][6].setPosition(252,323); //
        Stone[2][7].setPosition(287,323);  //
        Stone[2][8].setPosition(322,323);  //
        Stone[2][9].setPosition(357,323); //
        Stone[2][10].setPosition(392,323); //
        Stone[2][11].setPosition(427,323); //
        Stone[2][12].setPosition(462,323); //

        Stone[3][0].setPosition(42,429); //
        Stone[3][1].setPosition(77, 429); //
        Stone[3][2].setPosition(112, 429);  //
        Stone[3][3].setPosition(147,429); //
        Stone[3][4].setPosition(182,429); //
        Stone[3][5].setPosition(217,429); //
        Stone[3][6].setPosition(252,429); //
        Stone[3][7].setPosition(287,429);  //
        Stone[3][8].setPosition(322,429);  //
        Stone[3][9].setPosition(357,429); //
        Stone[3][10].setPosition(392,429); //
        Stone[3][11].setPosition(427,429); //
        Stone[3][12].setPosition(462,429); //
    }

    else if (level==10 || level==11 || level==12){
        Stone[0][0].setPosition(42,94); //
        Stone[0][1].setPosition(77, 94); //
        Stone[0][2].setPosition(112, 94);  //
        Stone[0][3].setPosition(147,94); //
        Stone[0][4].setPosition(182,94); //
        Stone[0][5].setPosition(217,94); //
        Stone[0][6].setPosition(252,94); //
        Stone[0][7].setPosition(287,94);
        Stone[0][8].setPosition(322,94);
        Stone[0][9].setPosition(357,94); //
        Stone[0][10].setPosition(392,94); //
        Stone[0][11].setPosition(427,94); //
        Stone[0][12].setPosition(462,94); //

        Stone[1][0].setPosition(42, 186);  //
        Stone[1][1].setPosition(77, 186);
        Stone[1][2].setPosition(112,186);
        Stone[1][3].setPosition(147,186);
        Stone[1][4].setPosition(182,186);
        Stone[1][5].setPosition(217,186);
        Stone[1][6].setPosition(252,186);
        Stone[1][7].setPosition(287,186);
        Stone[1][8].setPosition(322,186);
        Stone[1][9].setPosition(357,186); //
        Stone[1][10].setPosition(392,186); //
        Stone[1][11].setPosition(427,186); //
        Stone[1][12].setPosition(462,186); //

        Stone[2][0].setPosition(42,275); //
        Stone[2][1].setPosition(77, 275); //
        Stone[2][2].setPosition(112,275);
        Stone[2][3].setPosition(147,275);
        Stone[2][4].setPosition(182,275);
        Stone[2][5].setPosition(217,275);
        Stone[2][6].setPosition(252,275);
        Stone[2][7].setPosition(287,275);
        Stone[2][8].setPosition(322,275);
        Stone[2][9].setPosition(357,275); //
        Stone[2][10].setPosition(392,275); //
        Stone[2][11].setPosition(427,275); //
        Stone[2][12].setPosition(462,275); //

        Stone[3][0].setPosition(42,369); //
        Stone[3][1].setPosition(77, 369); //
        Stone[3][2].setPosition(112, 369);  //
        Stone[3][3].setPosition(147,369); //
        Stone[3][4].setPosition(182,369); //
        Stone[3][5].setPosition(217,369); //
        Stone[3][6].setPosition(252,369); //
        Stone[3][7].setPosition(287,369);  //
        Stone[3][8].setPosition(322,369);  //
        Stone[3][9].setPosition(357,369); //
        Stone[3][10].setPosition(392,369); //
        Stone[3][11].setPosition(427,369); //
        Stone[3][12].setPosition(462,369); //

        Stone[4][0].setPosition(42,458); //
        Stone[4][1].setPosition(77, 458); //
        Stone[4][2].setPosition(112, 458);  //
        Stone[4][3].setPosition(147,458); //
        Stone[4][4].setPosition(182,458); //
        Stone[4][5].setPosition(217,458); //
        Stone[4][6].setPosition(252,458); //
        Stone[4][7].setPosition(287,458);  //
        Stone[4][8].setPosition(322,458);  //
        Stone[4][9].setPosition(357,458); //
        Stone[4][10].setPosition(392,458); //
        Stone[4][11].setPosition(427,458); //
        Stone[4][12].setPosition(462,458); //
    }

    else if (level==13 || level==14 || level==15){
        Stone[0][0].setPosition(42,76); //
        Stone[0][1].setPosition(77, 76); //
        Stone[0][2].setPosition(112, 76);  //
        Stone[0][3].setPosition(147,76);
        Stone[0][4].setPosition(182,76);
        Stone[0][5].setPosition(217,76);
        Stone[0][6].setPosition(252,76);
        Stone[0][7].setPosition(287,76);
        Stone[0][8].setPosition(322,76);
        Stone[0][9].setPosition(357,76); //
        Stone[0][10].setPosition(392,76); //
        Stone[0][11].setPosition(427,76); //
        Stone[0][12].setPosition(462,76); //

        Stone[1][0].setPosition(42, 152);  //
        Stone[1][1].setPosition(77, 152);
        Stone[1][2].setPosition(112,152);
        Stone[1][3].setPosition(147,152);
        Stone[1][4].setPosition(182,152);
        Stone[1][5].setPosition(217,152);
        Stone[1][6].setPosition(252,152);
        Stone[1][7].setPosition(287,152);
        Stone[1][8].setPosition(322,152);
        Stone[1][9].setPosition(357,152); //
        Stone[1][10].setPosition(392,152); //
        Stone[1][11].setPosition(427,152); //
        Stone[1][12].setPosition(462,152); //

        Stone[2][0].setPosition(42,227); //
        Stone[2][1].setPosition(77, 227); //
        Stone[2][2].setPosition(112, 227);  //
        Stone[2][3].setPosition(147,227); //
        Stone[2][4].setPosition(182,227); //
        Stone[2][5].setPosition(217,227); //
        Stone[2][6].setPosition(252,227); //
        Stone[2][7].setPosition(287,227);  //
        Stone[2][8].setPosition(322,227);
        Stone[2][9].setPosition(357,227); //
        Stone[2][10].setPosition(392,227); //
        Stone[2][11].setPosition(427,227); //
        Stone[2][12].setPosition(462,227); //

        Stone[3][0].setPosition(42,305); //
        Stone[3][1].setPosition(77, 305); //
        Stone[3][2].setPosition(112, 305);  //
        Stone[3][3].setPosition(147,305); //
        Stone[3][4].setPosition(182,305); //
        Stone[3][5].setPosition(217,305); //
        Stone[3][6].setPosition(252,305); //
        Stone[3][7].setPosition(287,305);  //
        Stone[3][8].setPosition(322,305);
        Stone[3][9].setPosition(357,305); //
        Stone[3][10].setPosition(392,305); //
        Stone[3][11].setPosition(427,305); //
        Stone[3][12].setPosition(462,305); //

        Stone[4][0].setPosition(42,384); //
        Stone[4][1].setPosition(77, 384); //
        Stone[4][2].setPosition(112, 384);  //
        Stone[4][3].setPosition(147,384); //
        Stone[4][4].setPosition(182,384); //
        Stone[4][5].setPosition(217,384); //
        Stone[4][6].setPosition(252,384); //
        Stone[4][7].setPosition(287,384);  //
        Stone[4][8].setPosition(322,384);
        Stone[4][9].setPosition(357,384); //
        Stone[4][10].setPosition(392,384); //
        Stone[4][11].setPosition(427,384); //
        Stone[4][12].setPosition(462,384); //

        Stone[5][0].setPosition(42,460); //
        Stone[5][1].setPosition(77, 460); //
        Stone[5][2].setPosition(112, 460);  //
        Stone[5][3].setPosition(147,460); //
        Stone[5][4].setPosition(182,460); //
        Stone[5][5].setPosition(217,460); //
        Stone[5][6].setPosition(252,460); //
        Stone[5][7].setPosition(287,460);  //
        Stone[5][8].setPosition(322,460);
        Stone[5][9].setPosition(357,460); //
        Stone[5][10].setPosition(392,460); //
        Stone[5][11].setPosition(427,460); //
        Stone[5][12].setPosition(462,460); //
    }
}

//tao mang isrend dua theo level
void Game :: setIsrend(){
    for (int i=0; i<6; i++){
        for (int j=0; j<13 ; j++){
            isrend[i][j] = (i < NPiles && j < NStones[i]);
        }
    }
}