#include "item.h"
#include <ctime>
#include <cstdlib>
int fps = 75;

bool run = true;
SDL_Window *window = 0;
SDL_Renderer *screen = 0;

void gInit(const char* title, int xpos, int ypos, int x, int y, int flags){
    window = SDL_CreateWindow(title, xpos, ypos, x, y, flags);
    screen = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
    
}

void render(){
    //background colour
    SDL_SetRenderDrawColor(screen, 11, 64, 121, 255);

    //clear window to the colour
    SDL_RenderClear(screen);

    //show window 
    SDL_RenderPresent(screen); 

}
void handleEvents(SDL_Event events){
    SDL_Event ev;
    if(SDL_PollEvent(&ev)){
        switch (ev.type)
        {
        case SDL_QUIT:
            run = false;
            break;
        case SDL_MOUSEBUTTONUP:
            break;
        case SDL_KEYDOWN:
            break;
        default:
            break;
        }
    }
}

void clean(){
    
    SDL_DestroyWindow(window);
    itemQuit();
}
int main(){
    srand(time(NULL)); 
    
    itemInit();

    gInit("Banana", 
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
        1200, 800, 
        SDL_WINDOW_SHOWN);

    animation bob;
    bob.setRenderer(screen);
    bob.loadAnimation("bounce/", 0000, ".png");
    bob.setPos(50, 50);
    bob.setSize(60, 87);
    bob.setCenter(30, 30, 20);
    bob.setFPS(18);
    
    item pig;
    pig.setRenderer(screen);
    pig.loadImage("pig.png");
    pig.setPos(600, 400);
    pig.setSize(128, 128);
    pig.setCenter(32, 32, 40);

    group drawn;
    std::vector <item *> gems;
    int maxGems = 400;
    for(int i = 0; i < 400; i++){
        gems.push_back(new item());
        gems[i]->setRenderer(screen);
        gems[i]->loadImage("heart.png");
        gems[i]->setPos(rand() % 1200, rand() % 800); 
        gems[i]->setSize(32, 32);
        gems[i]->setCenter(16, 16, 20);
        drawn.addRef(gems[i]);
    }
    int desiredDelta = 1000/fps;
    bool pigHidden = false;
    while(run){
        int startLoop = SDL_GetTicks();
        SDL_Event ev;
        while(SDL_PollEvent(&ev)){
            switch(ev.type){
                case SDL_QUIT:
                    run = false;
                    break;
                case SDL_MOUSEBUTTONUP:
                    if(pig.isClicked(ev.button.x, ev.button.y)){
                        pigHidden = true;
                    }
                    break;
                case SDL_KEYDOWN:
                    switch(ev.key.keysym.sym){
                        case SDLK_UP:
                            break;
                        case SDLK_DOWN:
                            break;
                        case SDLK_RIGHT:
                            break;
                        case SDLK_LEFT:
                            break; 
                    }
                    break;
                case SDL_KEYUP:
                    switch(ev.key.keysym.sym){
                            case SDLK_UP:
                                break;  
                            case SDLK_RIGHT:
                                break;
                            case SDLK_LEFT:
                                break; 
                        }
                    break;
            }
        }
        bob.draw();

        if(!pigHidden){
            pig.draw();
        }
        drawn.draw();
        bob.update(startLoop);
        render();
    }

   
    return 0;
}