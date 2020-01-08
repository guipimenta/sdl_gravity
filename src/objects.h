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
            virtual void processInput( SDL_Event e );
        protected:
            int x = 0;
            int y = 0;
            bool animate;
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
    };

    class MovableObject : public RenderObject {
        public:
            MovableObject ( std::string path, int spriteSize, SDL_Renderer* renderer, int width, int height );
            void processInput( SDL_Event e );
    };

#endif