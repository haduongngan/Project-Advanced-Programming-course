//
// Created by Duong Ngan Ha on 12/04/2020.
//

#include "welcome.h"
using namespace std;

void welcometogame(){
    //Initialize SDL
    if ( !init() ){
        cout << "Failed to initialize!\n";
    }
    else {
        //load media
        extern char* path;
        path = "../image/color-01.png";
        //image = loadSurface(path);

        //apply the image
        //SDL_BlitSurface(image, nullptr, screenSurface, nullptr);
        //Update
        //SDL_UpdateWindowSurface(window);

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
    //free resourses and close
    //close();
}
