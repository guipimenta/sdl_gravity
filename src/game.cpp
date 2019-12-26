#include <gravity.h>

class MegamanObject : public RenderObject {
    
};

int main( int argc, char* args[] ) {
    GameWindow window( "Mega Man", 800, 600 );

    window.addObject( "../resources/megaman_walk.png", 4180, 6460 );
    SDL_Event e;
    bool quit = false;
    while(!quit) {
        while(SDL_PollEvent(&e) != 0) {
            if(e.type == SDL_QUIT) {
                quit = true;
            }
        }
        window.update();
        SDL_Delay(170);
    }
}