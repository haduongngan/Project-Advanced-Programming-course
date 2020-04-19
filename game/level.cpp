//
// Created by Duong Ngan Ha on 12/04/2020.
//

#include "level.h"
#include "VARIABLES_PROTOTYPE.h"
#include "LTexture.h"
#include "brick.h"
#include <fstream>
#include <sstream>
#include "game.h"

const char lev[] = "../Stones.txt";


extern char* path;

extern LTexture brick;
extern LTexture Backgr;
extern LTexture active;
extern LTexture unactive;

int pileNow = 0; //ktra xem dang chon o pile nao

bool loadbrick(){
    bool success = true;
    //load brick
    if (!brick.loadFFile("../image/brick-01.png")){
        cout << "Failed to load brick" << endl;

        success = false;
    }
    return success;
}

bool loadback(char* path){
    bool success = true;
    //load back
    if (!Backgr.loadFFile(path)){
        cout << "Failed to load backgr" << endl;
        success = false;
    }
    return success;
}

bool loadactive(){
    bool success = true;
    //load active
    if (!active.loadFFile("../image/active_character-01.png")){
        cout << "Failed to load active" << endl;

        success = false;
    }
    return success;
}

bool loadunactive(){
    bool success = true;
    //load active
    if (!unactive.loadFFile("../image/unactive_character-01.png")){
        cout << "Failed to load active" << endl;

        success = false;
    }
    return success;
}

void loadLevel1(){
    //if ( !init() ){
      //  cout << "Failed to initialize!\n";
   // }
   // else {
        //load media
        //init();
        path = "../image/background2.png";
    //Clear screen
    SDL_RenderClear(renderer);

    if (loadImage(path)) {
        //render texture to screen
        SDL_RenderCopy(renderer, Texture, nullptr, nullptr);

        //update
        SDL_RenderPresent(renderer);

        eloop();
    }
    //free resourses and close
    //close();
}

void loadLevel2(){
    path = "../image/background6.png";
    SDL_Event e;
    bool quit = false;
    vector<int>a = chooseLevel(lev,2);
    const int Npile = 2;
    bool isrend[6][13];

    for (int i=0; i<6; i++){
        for (int j=0; j<13 ; j++){
            if (j<a[i] && i<Npile) isrend[i][j] = true;
            else isrend[i][j] = false;
        }
    }



    //Clear screen
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

    while (!quit){
        while (SDL_PollEvent(&e)){
            if (e.type == SDL_QUIT){
                quit = true;
            }

        }
        Game game1;
        //game1.play();
        if (loadbrick()&&loadactive()&&loadback(path)&&loadunactive()) {
            char* pathfont = "/../font/Xerox Sans Serif Narrow.ttf";
            Backgr.render(0,0);  //gomarice_syouwa_retro_pop.ttf

            if (game1.getMode()==2){
                if (game1.AI.Isyourturn) {
                    active.render(132, 520);
                    unactive.render(366,520);
                }
                else {
                    unactive.render(132, 520);
                    active.render(366,520);
                }
            }


            class brick p[2][13];

            p[0][0].setPosition(42,76); //
            p[0][1].setPosition(77, 152); //
            p[0][2].setPosition(112, 227);  //
            p[0][3].setPosition(147,305); //
            p[0][4].setPosition(182,384); //
            p[0][5].setPosition(217,460); //
            p[0][6].setPosition(252,199); //
            p[0][7].setPosition(287,199);  //
            p[0][8].setPosition(322,199);  //
            p[0][9].setPosition(357,199); //
            p[0][10].setPosition(392,199); //
            p[0][11].setPosition(427,199); //
            p[0][12].setPosition(462,199); //
            //p1[15].setPosition(490,199);



            for (int i=0; i<2; i++){
                for (int j=0; j<13 ; j++){
                    p[i][j].setPile(i+1);
                    p[i][j].setCol(j+1);
                }
            }
            pileNow = 1;

            for (int i=0; i<2; i++){
                for (int j=0; j<13 ; j++){
                    p[i][j].setTruepile(pileNow);
                }
            }
            for (int i=0; i<2; i++){
                for (int j=0; j<13 ; j++){
                    p[i][j].handleEvent(&e, isrend);
                }
            }

            for (int i=0; i<2; i++){
                for (int j=0; j<13 ; j++){
                    if (!p[i][j].getRen()) isrend[i][j] = false;
                }
            }

            for (int i=0; i<2; i++){
                for (int j=0; j<13 ; j++){
                    if (isrend[i][j]) p[i][j].rend();
                }
            }


            if (loadText(pathfont, "Level 2", 28)) {
                texttexture.render(212, 9);
            }

            //update screen
            SDL_RenderPresent(renderer);

        }


        //eloop();
    }



}

void loadLevel3(){
        //load media
        path = "../image/background2.png";
        //Clear screen
        SDL_RenderClear(renderer);

        if (loadImage(path)) {
            //render texture to screen
            SDL_RenderCopy(renderer, Texture, nullptr, nullptr);

            //update
            SDL_RenderPresent(renderer);

            eloop();
        }
}

void loadLevel4(){
        //load media
        path = "../image/background3.png";
        //Clear screen
        SDL_RenderClear(renderer);

        if (loadImage(path)) {
            //render texture to screen
            SDL_RenderCopy(renderer, Texture, nullptr, nullptr);

            //update
            SDL_RenderPresent(renderer);

            eloop();
        }
}

void loadLevel5(){
        //load media
        path = "../image/background3.png";
        //Clear screen
        SDL_RenderClear(renderer);

        if (loadImage(path)) {
            //render texture to screen
            SDL_RenderCopy(renderer, Texture, nullptr, nullptr);

            //update
            SDL_RenderPresent(renderer);

            eloop();
        }
}

void loadLevel6(){
        //load media
        path = "../image/background3.png";
        //Clear screen
        SDL_RenderClear(renderer);

        if (loadImage(path)) {
            //render texture to screen
            SDL_RenderCopy(renderer, Texture, nullptr, nullptr);

            //update
            SDL_RenderPresent(renderer);

            eloop();
        }
}

void loadLevel7(){
        //load media
        path = "../image/background4.png";
        //Clear screen
        SDL_RenderClear(renderer);

        if (loadImage(path)) {
            //render texture to screen
            SDL_RenderCopy(renderer, Texture, nullptr, nullptr);

            //update
            SDL_RenderPresent(renderer);

            eloop();
        }
}

void loadLevel8(){
        //load media
        path = "../image/background4.png";
        //Clear screen
        SDL_RenderClear(renderer);

        if (loadImage(path)) {
            //render texture to screen
            SDL_RenderCopy(renderer, Texture, nullptr, nullptr);

            //update
            SDL_RenderPresent(renderer);

            eloop();
        }
}

void loadLevel9(){
        //load media
        path = "../image/background4.png";
        //Clear screen
        SDL_RenderClear(renderer);

        if (loadImage(path)) {
            //render texture to screen
            SDL_RenderCopy(renderer, Texture, nullptr, nullptr);

            //update
            SDL_RenderPresent(renderer);

            eloop();
        }
}

void loadLevel10(){
        //load media
        path = "../image/background5.png";
        //Clear screen
        SDL_RenderClear(renderer);

        if (loadImage(path)) {
            //render texture to screen
            SDL_RenderCopy(renderer, Texture, nullptr, nullptr);

            //update
            SDL_RenderPresent(renderer);

            eloop();
        }
}

void loadLevel11(){
        //load media
        path = "../image/background5.png";
        //Clear screen
        SDL_RenderClear(renderer);

        if (loadImage(path)) {
            //render texture to screen
            SDL_RenderCopy(renderer, Texture, nullptr, nullptr);

            //update
            SDL_RenderPresent(renderer);

            eloop();
        }
}

void loadLevel12(){
        //load media
        path = "../image/background5.png";
        //Clear screen
        SDL_RenderClear(renderer);

        if (loadImage(path)) {
            //render texture to screen
            SDL_RenderCopy(renderer, Texture, nullptr, nullptr);

            //update
            SDL_RenderPresent(renderer);

            eloop();
        }
}

void loadLevel13(){
        //load media
        path = "../image/background6.png";
        //Clear screen
        SDL_RenderClear(renderer);

        if (loadImage(path)) {
            //render texture to screen
            SDL_RenderCopy(renderer, Texture, nullptr, nullptr);

            //update
            SDL_RenderPresent(renderer);

            eloop();
        }
}

void loadLevel14(){
        //load media
        path = "../image/background6.png";
        //Clear screen
        SDL_RenderClear(renderer);

        if (loadImage(path)) {
            //render texture to screen
            SDL_RenderCopy(renderer, Texture, nullptr, nullptr);

            //update
            SDL_RenderPresent(renderer);

            eloop();
        }
}

void loadLevel15(){
        //load media
        path = "../image/background6.png";
        //Clear screen
        SDL_RenderClear(renderer);

        if (loadImage(path)) {
            //render texture to screen
            SDL_RenderCopy(renderer, Texture, nullptr, nullptr);

            //update
            SDL_RenderPresent(renderer);

            eloop();
        }
}