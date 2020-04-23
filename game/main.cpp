#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL_mixer.h>
#include <cmath>
#include <string>
#include "HumanPlayer.h"
#include "AIPlayer.h"
#include "SmartAIPlayer.h"
#include "game.h"
#include "VARIABLES_PROTOTYPE.h"
#include "LTexture.h"
using namespace std;

const double SCREEN_WIDTH = 532.992;
const double SCREEN_HEIGHT = 666.24;

//the window
SDL_Window* window = nullptr;

//the window renderer
SDL_Renderer* renderer = nullptr;

//current displayed texture
SDL_Texture* Texture = nullptr; //chuyen load anh

//globally used font
TTF_Font* font = nullptr;

//rendered texture
LTexture texttexture;  //chuyen load text

//music
Mix_Music *gMusic = nullptr;
Mix_Chunk *selectBrick = nullptr;
Mix_Chunk *selectNode = nullptr;
Mix_Chunk *win = nullptr;
Mix_Chunk *switchTurn = nullptr;


//path
const char pathdata[] = "../Stones.txt";
char* pathfont = "../font/Sriracha-Regular.ttf";


LTexture background[7]; //0: nen tron, 1 la nen winner, 2-6: nen theo so pile
LTexture brick;
LTexture brick_02;
LTexture active;
LTexture unactive;
LTexture hint;
LTexture menu;
LTexture nextnode;
LTexture minusnode;
LTexture plusnode;
LTexture text_input;

vector<vector<int>>data;



int main(int argc, char** argv) {
    if ( !init() ){
        cout << "Failed to initialize!\n";
    }
    else {
        class Game yourGame;
        //load cac anh cho san
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

        if (!brick.loadFFile("../image/brick-01.png")){
            cout << "Failed to load brick" << endl;
        }
        if (!brick_02.loadFFile("../image/brick02.png")){
            cout << "Failed to load brick02" << endl;
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
        loadData(pathdata);

        if (!loadMusic()){
            cout << "Unable to load music!" << endl;
        }

        SDL_Event e;
        bool quit = false;
        int WinCase = 1;

        while (!quit){
            //if there is no music
            if (Mix_PlayingMusic()==0){
                //play
                Mix_PlayMusic(gMusic, -1);
            }

            while (SDL_PollEvent(&e)){
                if (e.type == SDL_QUIT){
                    quit = true;
                }
                switch (WinCase){
                    case 1: {
                        handleEventCase1(&e, quit, WinCase);
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
                    yourGame.winner();
                    break;
                }
            }
        }

        close();
    }

    return 0;
}