#include "item.h"

void itemInit(){
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG);
}

void itemQuit(){
    SDL_Quit();
    IMG_Quit();
}
item::item(){
    pos.x = 30;
    pos.y = 60;
    image = NULL;
    pos.w = 40;
    pos.h = 40;
    oldTick = 0;
}

item::~item(){
    if(image != NULL){
        SDL_DestroyTexture(image);
        image = NULL;
    }
}

bool item::loadImage(std::string filename){
    SDL_Surface *temp = IMG_Load(filename.c_str());
    if(temp != NULL){
        image = SDL_CreateTextureFromSurface(ren, temp);
        SDL_FreeSurface(temp);
        if(image != NULL){
            return true;
        }
    }
    return false;
}
void item::freeImage(){
    if(image != NULL){
        SDL_DestroyTexture(image);
        image = NULL;
    }
}
void item::setRenderer(SDL_Renderer *destination){
    ren = destination;
}

void item::setSize(int w, int h){
    pos.w = w;
    pos.h = h;
}

void item::move(int x, int y){
    pos.x += x;
    pos.y += y;
}
bool item::getCollision(item* other){
    int dx, dy, rs; //distance x, distance y, radius squared 
    dx = (pos.x + center.x) - (other->getPos()->x + other->getCenter().x);
    dy = (pos.y + center.y) - (other->getPos()->y + other->getCenter().y);
    rs = center.r + other->getCenter().r;
    dx *= dx;
    dy *= dy;
    rs *= rs;
    return dx + dy < rs;
}
bool item::isClicked(int x, int y){
    int dx, dy, rs; //distance x, distance y, radius squared 
    dx = (pos.x + center.x) - x;
    dy = (pos.y + center.y) - y;
    rs = center.r;
    dx *= dx;
    dy *= dy;
    rs *= rs;
    return dx + dy < rs;
}
circle item::getCenter(){
    return center;
}
void item::setCenter(int x, int y, int r){
    center.x = x;
    center.y = y;
    center.r = r;
}
void item::setPos(int x, int y){
    pos.x = x;
    pos.y = y;
}   
SDL_Rect *item::getPos(){
    return &pos;
}
void item::draw(double angle){
    if(image != NULL){
        SDL_RenderCopyEx(ren, image, NULL, &pos, angle, NULL, SDL_FLIP_NONE);
    }
    else{
        std::cout << "IMAGE IS FUCKED AT DRAW\n";
    }
}
void item::draw(){
    if(image != NULL){
        SDL_RenderCopy(ren, image, NULL, &pos);
    }
    else{
        std::cout << "IMAGE IS FUCKED AT DRAW\n";
    }
}

void item::update(int tick){
    oldTick = tick;
}

////////////// CLASS ANIMATION 
animation::animation(){

}
animation::~animation(){
    this->freeImages();
}
bool animation::addImage(std::string filePath){
    if(loadImage(filePath)){
        images.push_back(image);
        return true;
    }
    return false;
}
bool animation::loadAnimation(std::string p, int zb, std::string ext){
    while(addImage(p + std::to_string(zb) + ext)){
        zb++;
    }
    if(images.size() > 0){
        return true;
    }
    return false;
}
void animation::next(){
    frameCount++;
    image = images[frameCount % images.size()];
}
void animation::freeImages(){
    for(int i = 0; i < images.size(); i++){
        if(images[i] != NULL){
            SDL_DestroyTexture(images[i]);
            images[i] = NULL;
        }
    }
}
void animation::setFPS(int FPS){
    desiredDelta = 1000 / FPS;
}
void animation::update(int tick){
    if(tick - oldTick > desiredDelta){
        next();
        oldTick = tick;  
    }
}

/////////////////////group

void group::draw(){
    for(int i = 0; i < items.size(); i++){
        items[i]->draw();
    }
}

void group::addRef(item* other){
    items.push_back(other); 
}

void group::move(int x, int y){
    for(int i = 0; i < items.size(); i++){
        items[i]->move(x, y);
    }
}
