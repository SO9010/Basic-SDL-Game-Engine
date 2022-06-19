#include "gBasics.h"

gWindow* gGame = 0;
SDL_Renderer *screen = 0;

int main(){
    gGame = new gWindow();
    gGame->setRenderer(screen);

    bObj bob;
    bob.loadImage("img.png");
    bob.setPos(250, 50);
    bob.setSize(60, 87);
    bob.addObjToRen();    
      

    gGame->gInit("Game",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
        1200, 800, 
        SDL_WINDOW_SHOWN);

    while(gGame->running()){
        gGame->handleEvent();

        gGame->render();
    }
    return 0;
}