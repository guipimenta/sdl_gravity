#include <gravity.h>



int main( int argc, char* args[] ) {
    GameWindow window( "Mega Man", 800, 600 );

    window.addObject( "../resources/Run", 10, 363, 458 );
    SDL_Event e;
    bool quit = false;
    while(!quit) {
        while(SDL_PollEvent(&e) != 0) {
            if(e.type == SDL_QUIT) {
                quit = true;
            }
        }
        window.update();
    }
}