#include <objects.h>
#include <window.h>



int main( int argc, char* args[] ) {
    GameWindow window( "Ninja Man", 800, 600 );

    // Adding a simple object to the screen, it will create a basic render object
    MovableObject *ninja = new MovableObject( "../resources/Run", 10,  window.getRenderer(), 363, 458 );
    window.addObject(ninja);

    SDL_Event e;
    bool quit = false;
    while(!quit) {
        while(SDL_PollEvent(&e) != 0) {
            if(e.type == SDL_QUIT) {
                quit = true;
            }
        }
        window.update(e);
    }
}