#ifndef gBasics 
#define gBasics

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <vector>
#include <iostream>
#include <list>

/*                      *
*     Window Section    *      
*                       */

class gWindow{
    public:
    gWindow();
    ~gWindow();

    bool gInit(const char* title, int xpos, int ypos, int x, int y, int flags);
    bool running();
    void render();
    void handleEvent();
    void update();
    void frameRate();

    protected:
    SDL_Window *window = 0;
    SDL_Renderer *gRender = 0;
    SDL_Event event;
    std::vector <SDL_Texture *> imageList;
    bool gRun = false;
};

/*                      *
*    Objects section    *      
*                       */
                                        
class bObj:public gWindow{              //basic object
    public:
    bObj();
    ~bObj();
    void setRenderer(SDL_Renderer *destination);
    void addObjToRen();
    int colX, colY;                     //here is where we define the hit box
    bool collision = true;              //collision detection (auto set to true)
    bool getCollision(bObj* other);
    void draw();
    bool loadImage(std::string filename);
    int startX, startY;
    int speed;
    void setSize(int w, int h);
    void setPos(int x, int y);

    protected:
    SDL_Texture *image;
    SDL_Rect pos;
};

class mObj:public bObj{                 //movable object
    public:
    const char* name;
    void move(int x, int y);
    protected:
    bool eMove = true;                  //enable move (auto set to true)
};

class aObj:public bObj{                 //animated object 
    public:
    virtual ~aObj();
    bool addImage(std::string filePath);
    bool loadAnimation(std::string prefix, int imageIndex, std::string extention);
    void next();
    void freeImages();
    void setFPS(int FPS);
    //virtual void update(int tick);
    
    protected:
    int frameCount = 0;
    std::vector <SDL_Texture *> images;
    int desiredDelta;
};

class m_aObj:public mObj, public aObj{  //movable and animated object
};

#endif