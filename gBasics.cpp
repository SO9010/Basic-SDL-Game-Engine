#include "gBasics.h"

/*                            *
*           GLOBALS           *
*                             */


SDL_Window *window;
SDL_Renderer *gRender;

std::vector <SDL_Texture *> imageList ;
std::vector <SDL_Rect> posList;

/*                            *
*   Basic gWindow functions   *
*                             */

gWindow::gWindow(){
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG);
    std::cout << "Ok Lets GO!" << std::endl;
    gRun = true;
}

gWindow::~gWindow(){
    IMG_Quit();
    SDL_Quit();
    std::cout << "Good bye!" << std::endl;
}

void gWindow::gInit(const char* title, int xpos, int ypos, int x, int y, int flags){
        window = SDL_CreateWindow(title, xpos, ypos, x, y, flags);
        gRender = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
}

void gWindow::render(){

    SDL_RenderClear(gRender);

    //Draw section 
    
    int vecSize = imageList.size();
    for(int i = 0; i < vecSize; i++){
        if(&imageList[i] != NULL){
        if(SDL_RenderCopy(gRender, imageList[i], &posList[i], NULL) == 0){
            std::cout << "Hellp image is null at draw" << std::endl;
        }
        }
        else{
            std::cout << "Hellp image is null at draw" << std::endl;
        } 
    } 
    SDL_SetRenderDrawColor(gRender, 11, 64, 121, 255);

    SDL_RenderPresent(gRender);
}

void gWindow::setRenderer(SDL_Renderer *destination){
    gRender = destination;
}

bool gWindow::running(){
    return gRun;
}

void gWindow::handleEvent(){
     SDL_Event ev;
    if(SDL_PollEvent(&ev)){
        switch (ev.type)
        {
        case SDL_QUIT:
            gRun = false;
            IMG_Quit();
            SDL_Quit();
            std::cout << "Good bye!" << std::endl;
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

/*                            *
*        Objects code         *
*                             */
                                        
bObj::bObj(){                           //basic initiliser 
    pos.x = 30;
    pos.y = 60;
    image = NULL;
    pos.w = 40;
    pos.h = 40;
}

bObj::~bObj(){                           //basic initiliser 
    if(image != NULL){
    SDL_DestroyTexture(image);
    image = NULL;
    }
}

bool bObj::loadImage(std::string filename){
    SDL_Surface *temp = IMG_Load("img.png");

    if(temp != NULL){
        image = SDL_CreateTextureFromSurface(gRender, temp);
        SDL_FreeSurface(temp);
        if(image != NULL){ 
            return true;
        }
    }
    std::cout << "Help " + filename + " is null at load" + "\nERROR MESSAGE IS: " + IMG_GetError() << std::endl;
    return false;
}

void bObj::addObjToRen(){

    imageList.push_back(image);
    posList.push_back(pos);


}

void bObj::setSize(int w, int h){
    pos.w = w;
    pos.h = h;
}

void bObj::setPos(int x, int y){
    pos.x = x;
    pos.y = y;
}
/*
bool bObj::getCollision(bObj* other){
    if(bObj )
}
*/

/*                                  *
*        Movable bjects code        *
*                                   */

void mObj::move(int x, int y){
    if(eMove){
        pos.x += x;
        pos.y += y;
    }
}

/*                                 *
*        Objects animation         *
*                                  */

aObj::~aObj(){
    this->freeImages();
}
bool aObj::addImage(std::string filePath){
    if(loadImage(filePath)){
        images.push_back(image);
        return true;
    }
    return false;
}
bool aObj::loadAnimation(std::string prefix, int imageIndex, std::string extention){
    while(addImage(prefix + std::to_string(imageIndex) + extention)){
        imageIndex++;
    }
    if(images.size() > 0){
        return true;
    }
    return false;
}
void aObj::next(){                      //Cycles through images
    frameCount++;
    image = images[frameCount % images.size()];
}
void aObj::freeImages(){
    for(int i = 0; i < images.size(); i++){
        if(images[i] != NULL){
            SDL_DestroyTexture(images[i]);
            images[i] = NULL;
        }
    }
}
void aObj::setFPS(int FPS){
    desiredDelta = 1000 / FPS;
}

