#include <gravity.h>
#include <SDL2/SDL_image.h>
#include <sstream>


/* SDL interprets each pixel as a 32-bit number, so our masks must depend
   on the endianness (byte order) of the machine */

Uint32 rmask = 0xff000000;
Uint32 gmask = 0x00ff0000;
Uint32 bmask = 0x0000ff00;
Uint32 amask = 0x000000ff;



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

RenderObject::RenderObject( std::string path, int spriteSize, SDL_Renderer* renderer, int width, int height ) {
    this->renderer = renderer;
    this->width = width;
    this->height = height;
    this->spriteSize = spriteSize;
    for(int i = 0; i < spriteSize; i++) {
        std::stringstream ss;
        ss << path << "__00" << i << ".png";
        std::string richPath = ss.str();
        SDL_Surface* loadedSurface = IMG_Load( richPath.c_str() );
        if(loadedSurface == NULL) {
            printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
            this->success = false;
        } else {
            SDL_Rect scale = { 0, 0, 60, 60 };
            SDL_Surface *blitedSurface = SDL_CreateRGBSurface(0, 640, 480, 32, rmask, gmask, bmask, amask);

            SDL_BlitScaled ( loadedSurface, NULL, blitedSurface, &scale  );
            SDL_Texture* texture = SDL_CreateTextureFromSurface(  this->renderer,  blitedSurface );
            if(texture == NULL) {
                printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
                this->success = false;
            }
            this->texture.push_back(texture);
            SDL_FreeSurface(loadedSurface);
            SDL_FreeSurface(blitedSurface);
            this->success = true;
            printf("Image loaded with success! %s\n", path.c_str());
        }
    }

}

void RenderObject::render( int x, int y, SDL_Rect* clip ) {
    // set rendering space and render to screen
    SDL_Rect renderQuad = { this->x, this->y, this->width, this->height };

    // set clip rendering dimensions
    if( clip != NULL ) {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    if(animate) {
        if(this->count % 4 == 0) {
            this->imgNum++;
        }

        if(this->imgNum == 10) {
            this->imgNum = 0;
            this->count = 0;
            this->animate = false;
        }
    } else {
        this->imgNum = 0;
    }


    // printf("Loading clip %d\n", this->imgNum);


    // clip is related to the image source
    // renderQuad where the image will be loaded on the screen
    SDL_RenderCopy ( this->renderer, this->texture[this->imgNum], clip, &renderQuad );

    this->count++;
}

SDL_Rect RenderObject::updateClip() {
    return {  0, 0, 500, 500 };
}

void RenderObject::processInput(SDL_Event e) {
    if(e.type == SDL_KEYDOWN) {
        switch(e.key.keysym.sym) {
            case SDLK_RIGHT:
                x++;
                if(x == 601) {
                    x = 0;
                }
                animate = true;
                break;
            case SDLK_LEFT:
                x--;
                if(x == -1) {
                    x = 600;
                }
                animate = true;
            break;
        }
        
    }
}