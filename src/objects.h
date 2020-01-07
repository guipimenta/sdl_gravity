#ifndef GRAVITY
#define GRAVITY

#include <iostream>
#include <vector>
#include <string>
#include <SDL2/SDL.h>

class RenderObject {

    public:
        RenderObject( std::string path, int spriteSize, SDL_Renderer* renderer, int width, int height  );
        void render( int x, int y, SDL_Rect* clip );
        SDL_Rect updateClip();
        void processInput(SDL_Event e);
    private:
        void loadTexture( std::string path );
        SDL_Renderer* renderer = NULL;
        std::vector<SDL_Texture*> texture;
        bool success;
        int height;
        int width;
        int spriteSize;
        int imgNum = 0;
        int count = 0;
        int x = 0;
        int y = 0;
        bool animate;
};





class GravitableObject {
public:
    void moveX(float increment);
    void moveY(float increment);
private:
    float x;
    float y;
};


class Gravity {

public:
    void addObject(GravitableObject object);
    void applyGravity();

private:
    std::vector<GravitableObject> gravitableObjects;
    
};


class Scene {
public:
    void processInputs(SDL_Event e);
    void applyGravity(SDL_Event e);
private:
    Gravity gravityEngine;
};


#endif