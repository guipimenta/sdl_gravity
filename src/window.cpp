#include <window.h>

GameWindow::GameWindow(std::string gameName, int width, int height) {
    if( SDL_Init(SDL_INIT_VIDEO) > 0 ) {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        this->windowState = false;
    } else {
        this->window = SDL_CreateWindow(gameName.c_str(), SDL_WINDOWPOS_UNDEFINED, 
        SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
        if(this->window == NULL) {
            printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
            this->windowState = false;
        } else {
            
            this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED  | SDL_RENDERER_PRESENTVSYNC );
            if(this->renderer == NULL) {
                printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
                this->windowState = false;
            }
            // init was successful
            this->windowState = true;
        }
    }
}

void GameWindow::addObject( std::string path, int spriteSize, int width, int height ) {
    RenderObject* obj = new RenderObject( path, spriteSize, this->renderer, width, height );
    this->screenObjects.push_back(obj);
}

void GameWindow::addObject( RenderObject* object ) {
    this->screenObjects.push_back( object );
}

void GameWindow::update(SDL_Event e) {
    SDL_RenderClear( this->renderer );
    for(int i = 0; i < this->screenObjects.size(); i++) {
        RenderObject* obj = this->screenObjects[i];
        obj->processInput(e);
        
        SDL_Rect clip = obj->updateClip();
        obj->render( 0, 0, &clip );
        SDL_RenderPresent( this->renderer );
    }
}

SDL_Renderer* GameWindow::getRenderer() {
    return this->renderer;
}