#include <gravity.h>
#include <SDL2/SDL_image.h>

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

void GameWindow::addObject( std::string path, int width, int height ) {
    printf("Loading object");
    RenderObject* obj = new RenderObject( path, this->renderer, width, height );
    this->screenObjects.push_back(obj);
}

void GameWindow::update() {
    SDL_RenderClear( this->renderer );
    for(int i = 0; i < this->screenObjects.size(); i++) {
        RenderObject* obj = this->screenObjects[i];
        obj->updateClip();
        SDL_Rect clip = obj->updateClip();
        obj->render( 0, 0, &clip );
        SDL_RenderPresent( this->renderer );
    }
}

RenderObject::RenderObject( std::string path, SDL_Renderer* renderer, int width, int height ) {
    this->renderer = renderer;
    this->width = width;
    this->height = height;
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if(loadedSurface == NULL) {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
        this->success = false;
    } else {
        this->texture = SDL_CreateTextureFromSurface(  this->renderer,  loadedSurface );
        if(this->texture == NULL) {
            printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
            this->success = false;
        }
        SDL_FreeSurface(loadedSurface);
        this->success = true;
        printf("Image loaded with success! %s", path.c_str());
    }
}

void RenderObject::render( int x, int y, SDL_Rect* clip ) {
    // set rendering space and render to screen
    SDL_Rect renderQuad = { x, y, this->width, this->height };

    // set clip rendering dimensions
    if( clip != NULL ) {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }
    // clip is related to the image source
    // renderQuad where the image will be loaded on the screen
    SDL_RenderCopy ( this->renderer, this->texture, clip, &renderQuad );
}

SDL_Rect RenderObject::updateClip() {
    if(clipCount == 0) {
        SDL_Delay(1000);
    }
    ++clipCount;
    if(clipCount > 16) { 
        clipCount = 0;
    }

    return { clipCount * 40, 0, 55, 52 };
}