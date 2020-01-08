#ifndef __WINDOW__
#define __WINDOW__

#include <SDL2/SDL.h>
#include <string>
#include <vector>
#include <objects.h>

/**
 * Represents the main game window.
 *  - first add objects to your window
 *  - in your main SDL loop, pass SDL_Events so that it can reflect on your objects
 *
 * */
class GameWindow {
    public:
        GameWindow( std::string gameName, int width, int height );

        // adds a simple renderable object to screen
        void addObject( std::string path, int spriteSize, int width, int height );

        // enables you to creater a custom object by extending the basic one
        void addObject( RenderObject* object );

        void update( SDL_Event e );
        
        // returns window renderer
        SDL_Renderer* getRenderer();
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


#endif