//
// Created by Duong Ngan Ha on 12/04/2020.
//

#include "level.h"
#include "VARIABLES_PROTOTYPE.h"
#include "LTexture.h"

extern char* path;

extern LTexture brick;
extern LTexture Backgr;
extern LTexture active;

bool loadbrick(char* path){
    bool success = true;
    //load brick
    if (!brick.loadFFile("../image/brick-01.png")){
        cout << "Failed to load brick" << endl;

        success = false;
    }
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
        //load media
        init();
        path = "../image/background2.png";
        //Clear screen
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

        if (loadbrick(path)&&loadactive(path)) {
            Backgr.render(0,0);
            brick.render(240, 190);
            brick.render(120,123);
            active.render(500, 200);

            //render texture to screen
            //SDL_RenderCopy(renderer, Texture, nullptr, nullptr);

            //update
            SDL_RenderPresent(renderer);

            eloop();
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