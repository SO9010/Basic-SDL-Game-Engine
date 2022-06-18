#include "gBasics.h"

gWindow* gGame = 0;

int main(){

    bObj bob;
    bob.loadImage("heart.png");
    bob.setPos(50, 50);
    bob.addObjToRen();
    bob.setSize(60, 87);
    
    gGame = new gWindow();
    
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