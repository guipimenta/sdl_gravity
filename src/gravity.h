#ifndef GRAVITY
#define GRAVITY

#include <iostream>
#include <vector>
#include <string>
#include <SDL2/SDL.h>

class RenderObject {

    public:
        RenderObject( std::string path, SDL_Renderer* renderer, int width, int height  );
        void render( int x, int y, SDL_Rect* clip );
        SDL_Rect updateClip();
    private:
        void loadTexture( std::string path );
        SDL_Renderer* renderer = NULL;
        SDL_Texture* texture = NULL;
        bool success;
        int height;
        int width;
        int clipCount = 0;
        int currentClip = 0;

};


class GameWindow {
    public:
        GameWindow( std::string gameName, int width, int height );

        void addObject( std::string path, int width, int height );

        void update();
        
    private:

        // initialize game window
        void init();
    
        // defines if window was initialized correctly 
        bool windowState;

        // managed window
        SDL_Window* window = NULL;

        // default window rednerer
        SDL_Renderer* renderer = NULL;

        // list of objects
        std::vector<RenderObject*> screenObjects;
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