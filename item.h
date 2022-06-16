#ifndef IMAGESANDITEMS
#define IMAGESANDITEMS

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <vector>
#include <iostream>


void itemInit();
void itemQuit();

struct circle{
    int x, y, r;
};

class item{
    public:
    item();
    virtual ~item();
    void setRenderer(SDL_Renderer *renderer);
    bool loadImage(std::string filename);
    void setSize(int w, int h);
    void setPos(int x, int y);
    void freeImage();
    SDL_Rect *getPos();
    void move(int x, int y);
    bool getCollision(item* other);
    bool isClicked(int x, int y);
    circle getCenter();
    void setCenter(int x, int y, int r);
    void draw(double angle);
    void draw();
    //virtual void update(int tick);


    protected:
    SDL_Renderer *ren;
    SDL_Texture *image;
    SDL_Rect pos;
    circle center;
    int oldTick;
};

class animation:public item{
    public:
    animation();
    virtual ~animation();
    bool addImage(std::string filePath);
    bool loadAnimation(std::string pref, int zbuf, std::string extention);
    void next();
    void freeImages();
    void setFPS(int FPS);
    virtual void update(int tick);

    protected:
    int frameCount = 0;
    std::vector <SDL_Texture *> images;
    int desiredDelta;
};

class group : public item{
    public: 
    void draw();
    void addRef(item *other);
    void move(int x, int y);

    public:
    std::vector <item *> items;
};



#endif