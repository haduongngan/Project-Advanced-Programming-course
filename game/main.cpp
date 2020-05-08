#include <iostream>
#include <SDL.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL_mixer.h>
#include "Player.h"
#include "game.h"
#include "VARIABLES_PROTOTYPE.h"
#include "LTexture.h"
using namespace std;


 // window's wigth and height
const double SCREEN_WIDTH = 532.992;
const double SCREEN_HEIGHT = 666.24;

// max pile (fixed) and max bricks in each pile
const int MAX_PILE = 6;
const int MAX_BRICK = 13;

//the window
SDL_Window* window = nullptr;

//the window renderer
SDL_Renderer* renderer = nullptr;

//globally used font
TTF_Font* font = nullptr;

//rendered text texture
LTexture texttexture;

//music + sound effect
Mix_Music *gMusic = nullptr;
Mix_Chunk *selectBrick = nullptr;
Mix_Chunk *selectNode = nullptr;
Mix_Chunk *win = nullptr;
Mix_Chunk *switchTurn = nullptr;

//path
const char pathdata[] = "../Stones.txt";
char* pathfont = "../font/Sriracha-Regular.ttf";

//Color of text
const SDL_Color textColor_white = {0xF8,0xF8,0xff};
const SDL_Color textColor_red = {0xa5,0x2a,0x2a};

//background
LTexture background[7]; //0: basic backgr, 1 : winner backgr , 2-6: backgr based on number of piles

//active means that now is your turn
LTexture active;
LTexture unactive;

//some function nodes
LTexture hint;
LTexture menu;
LTexture nextnode;

//function nodes help to set game
LTexture minusnode;
LTexture plusnode;
LTexture text_input;

//data from Stones.txt : number of bricks in levels.
vector<vector<int>>data;


int main(int argc, char** argv) {

    /* 73:
     * init SDL : window, IMG, TTF, ...
     */
    if ( !init() ){
        cout << "Failed to initialize!\n";
    }
    else {
        /* 78:
         * Init yourGame
         */
        struct Game yourGame;


        /* 84 - 132
         * load image : backgrounds, function nodes
         * (LTexture.h)
         */

        if (!background[0].loadFFile("../image/144511.png")){
            cout << "Failed to load background case 1" << endl;
        }
        if (!background[1].loadFFile("../image/cover-01.png")){
            cout << "Failed to load background case 5" << endl;
        }
        if (!background[2].loadFFile("../image/background2.png")){
            cout << "Failed to load background2" << endl;
        }
        if (!background[3].loadFFile("../image/background3.png")){
            cout << "Failed to load background3" << endl;
        }
        if (!background[4].loadFFile("../image/background4.png")){
            cout << "Failed to load background4" << endl;
        }
        if (!background[5].loadFFile("../image/background5.png")){
            cout << "Failed to load background5" << endl;
        }
        if (!background[6].loadFFile("../image/background6.png")){
            cout << "Failed to load background6" << endl;
        }

        if (!active.loadFFile("../image/active_character-01.png")){
            cout << "Failed to load active" << endl;
        }
        if (!unactive.loadFFile("../image/unactive_character-01.png")){
            cout << "Failed to load active" << endl;
        }

        if (!hint.loadFFile("../image/hint.png")){
            cout << "Failed to load hint" << endl;
        }
        if (!menu.loadFFile("../image/menu.png")){
            cout << "Failed to load menu" << endl;
        }

        if (!minusnode.loadFFile("../image/minus.png")){
            cout << "Failed to load minus" << endl;
        }
        if (!plusnode.loadFFile("../image/plus.png")){
            cout << "Failed to load plus" << endl;
        }
        if (!text_input.loadFFile("../image/text_input.png")){
            cout << "Failed to load text_input" << endl;
        }

        if (!nextnode.loadFFile("../image/function button.png")){
            cout << "Failed to load function button" << endl;
        }


        /* 141:
         * read data from file .txt
         */
        loadData(pathdata);


        /* 148 - 150
         * load music + sound effects
         */
        if (!loadMusic()){
            cout << "Unable to load music!" << endl;
        }

        //Begin event
        SDL_Event e;
        bool quit = false;
        int WinCase = 1; /* WinCase : 1 -> Welcome to Nim Game
                                      2 -> Instructions
                                      3 -> Set up game
                                      4 -> Play game
                                      5 -> announce winner */

        while (!quit){

            /* 162 - 165
             * if there is no music -> play music
             */
            if (Mix_PlayingMusic()==0){
                //play
                Mix_PlayMusic(gMusic, -1);
            }


            /* 172 - 206
             * if have event (mouse event) -> handle bases on situation
             * there are 5 cases (which is discern by WinCase)
             */
            while (SDL_PollEvent(&e)){

                //if quit
                if (e.type == SDL_QUIT){
                    quit = true;
                }

                //handle bases on situation
                switch (WinCase){
                    case 1: {
                        handleEventCase1(&e, WinCase, quit);
                        break;
                    }

                    case 2: {
                        handleEventCase2(&e, WinCase);
                        break;
                    }

                    case 3: {
                        handleEventCase3(&e, WinCase, yourGame);
                        break;
                    }

                    case 4: {
                        handleEventCase4(&e, WinCase, yourGame);
                        break;
                    }

                    case 5: {
                        handleEventCase5(&e, WinCase, yourGame, quit);
                        break;
                    }
                }
            }


            /* 213 - 238
             * if have not event -> render images, text, nodes,.. bases on situation
             * there are 5 cases (which is discern by WinCase)
             */
            switch (WinCase){
                case 1: {
                    welcome(yourGame);
                    break;
                }

                case 2: {
                    help(yourGame);
                    break;
                }

                case 3: {
                    setup(yourGame);
                    break;
                }

                case 4: {
                    level(yourGame);
                    break;
                }

                case 5: {
                    winner(yourGame);
                    break;
                }
            }
        }
        close();
    }
    return 0;
}