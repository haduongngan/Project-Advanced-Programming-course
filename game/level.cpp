//
// Created by Duong Ngan Ha on 12/04/2020.
//

#include "level.h"
#include "VARIABLES_PROTOTYPE.h"
#include "LTexture.h"
#include "brick.h"

extern char* path;

extern LTexture brick;
extern LTexture Backgr;
extern LTexture active;

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

bool loadactive(char* path){
    bool success = true;
    //load active
    if (!active.loadFFile("../image/active_character-01.png")){
        cout << "Failed to load active" << endl;

        success = false;
    }
    return success;
}

bool loadunactive(char* path){
    bool success = true;
    //load active
    if (!active.loadFFile("../image/unactive_character-01.png")){
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
    SDL_Event e;
    bool quit = false;
    while (!quit){
        while (SDL_PollEvent(&e)){
            if (e.type == SDL_QUIT){
                quit = true;
            }
        }
        //load media
        // init();
        path = "../image/background2.png";
        //Clear screen
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

        if (loadbrick()&&loadactive(path)&&loadback(path)) {
            char* pathfont = "../font/Xerox Sans Serif Narrow.ttf";
            Backgr.render(0,0);
            class brick p1[5];
            p1[0].setPosition(10,20);
            p1[1].setPosition(10, 120);
            p1[2].setPosition(10, 220);
            p1[3].setPosition(10, 320);
            p1[4].setPosition(10, 420);
            p1[0].setPile(1);
            p1[1].setPile(2);
            pileNow = 1;

            for (int i=0; i<5; i++){
                p1[i].setTruepile(pileNow);
            }

            for (int i=0; i<5; i++){
                p1[i].handleEvent(&e);
            }
            for (int i=0; i<5; i++){
                p1[i].rend();
            }
            //update
            SDL_RenderPresent(renderer);

            if (loadText(pathfont, "hatnho")) {
                //render texture to screen
                //SDL_Rect Message = {100, 100, 500, 500};

                //SDL_RenderCopy(renderer, Texture, nullptr, &Message);
                texttexture.render(10, 500);
            }


            //eloop();
        }
        //close();
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