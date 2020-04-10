#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <SDL.h>
#include<SDL_image.h>
#include "Player.h"
#include "HumanPlayer.h"
#include "AIPlayer.h"
#include "SmartAIPlayer.h"
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

class Game{
private:
    int NumOfPiles;
    vector<int>Stones;
    int playMode;
    HumanPlayer human1;
    HumanPlayer human2;
    AIPlayer AI;
    SmartAIPlayer smart;
    int level;
    int turn;
    bool pause;
public:
    void setPause(){
        pause = true;
    }

    void setMode(){
        cout << "Type of game: ";
        cin >> playMode; //3 = smart vs human
    }
    int getMode(){
        return playMode;
    }

    void setLevel(){
        cout << "Level of game: ";
        cin >> level;
    }
    int getLevel(){
        return level;
    }

    void setStones(){
        Stones = chooseLevel(path,level);
        NumOfPiles = Stones.size();
    }
    vector<int> getStones(){
        return Stones;
    }

    void setPlayers(){
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
   // vector<Player> getPlayers(){
     //   return players;
    //}

    void in(){
        for (int i=0; i<Stones.size(); i++){
            cout << "Pile " << i+1 << " : ";
            for (int j=1; j<=Stones[i]; j++){
                cout << "O ";
            }
            cout << endl;
        }
        cout << endl;
    }

    bool checkWin(){
        bool check = 1;
        for (int i=0; i<Stones.size(); i++){
            if (Stones[i]>0) {
                check = 0;
                break;
            }
        }
        return check;
    }

    void step(){
        if (playMode == 1) {
            if (turn == 1) {
                human1.move(Stones);
                turn = 2;
            } else {
                human2.move(Stones);
                turn = 1;
            }
            human1.setTurn(turn);
            human2.setTurn(turn);
        }

        else if (playMode == 2) {
            if (turn == 1) {
                AI.move(Stones);
                turn = 2;
            } else {
                human2.move(Stones);
                turn = 1;
            }
            AI.setTurn(turn);
            human2.setTurn(turn);
        }

        else if (playMode == 3) {
            if (turn == 1) {
                smart.move(Stones);
                turn = 2;
            } else {
                human2.move(Stones);
                turn = 1;
            }
            smart.setTurn(turn);
            human2.setTurn(turn);
        }
    }

    void winner(){
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

    void play(){
        setMode();
        setLevel();
        setStones();
        setPlayers();
        cout << "Choose who has the first turn: ";
        cin >> turn;
        if (turn == 3) turn = rand()%2 +1; //turn = 3 is random
        if (playMode == 1){
            human1.setTurn(turn);
            human2.setTurn(turn);
        }
        else if (playMode == 2){
            AI.setTurn(turn);
            human2.setTurn(turn);
        }
        else if (playMode == 3){
            smart.setTurn(turn);
            human2.setTurn(turn);
        }
        in();
        while (checkWin()==0){
            step();
            in();
            if (checkWin()==1) winner();
        }
    }
};

//SDL

//Screen dimension const
const double SCREEN_WIDTH = 532.992;
const double SCREEN_HEIGHT = 666.24;

//the window
SDL_Window* window = nullptr;

//surface
SDL_Surface* screenSurface = nullptr;

//the image
SDL_Surface* image = nullptr;

//starts up SDL and creates window
bool init(){
    bool success = true;
    if ( SDL_Init(SDL_INIT_VIDEO) < 0 ){
        cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << endl;
        success = false;
    }
    else {
        //Create window
        window = SDL_CreateWindow("NIM GAME", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if ( window == nullptr ){
            cout << "Window could not be created! SDL_Error: " << SDL_GetError() << endl;
            success = false;
        }
        else {
            //get window surface
            screenSurface = SDL_GetWindowSurface(window);

        }
    }
    return success;
}

//Load media
bool loadMedia(){
    bool success = true;

    //load image
    //image = IMG_Load("../color-01.png");
    image = IMG_Load("../background4.png");
    //image = SDL_LoadBMP("../backgr.bmp");
    if (image == nullptr){
        cout << "Unable to load image! SDL Error: " << SDL_GetError() << endl;
        success = false;
    }
    return success;
}

//Frees media and shuts down SDl
void close(){
    SDL_FreeSurface(image);
    image = nullptr;

    SDL_DestroyWindow(window); //se take care screensurface
    window = nullptr;

    SDL_Quit();
}

void eloop(){
    SDL_Event e;
    bool quit = false;
    while (!quit){
        while (SDL_PollEvent(&e)){
            if (e.type == SDL_QUIT){
                quit = true;
            }
        }
    }
}

int main(int argc, char** argv) {


    //Initialize SDL
    if ( !init() ){
        cout << "Failed to initialize!\n";
    }
    else {
        //load media
        if ( !loadMedia() ){
            cout << "Failed to load media!\n ";
        }
        else {
            //apply the image
            SDL_BlitSurface(image, nullptr, screenSurface, nullptr);
            //Update
            SDL_UpdateWindowSurface(window);

            eloop();
        }
    }
    //free resourses and close
    close();
    return 0;
}
