#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include "Game.h"

using namespace std;

#define FPS 60.0
#define DELAY_TIME = 1000.0f / FPS

bool startEngine();

int main(int argc, char** argv ){

  if (!startEngine()){
    return 1;
  }  

  Game* game = Game::getTheInstance();
  if (!game->startGame()){
    cout << "Failed to start game." << endl;
    return 1;
  }


  while (game->isGameRunning()){

    Uint32 frameStart, frameTime;
    frameStart = SDL_GetTicks();

    game->update();
    game->render();

    frameTime - SDL_GetTicks() - frameStart;
    if (frameTime < DELAY_TIME){
      SDL_Delay(int(DELAY_TIME - frameTime));
    }
  }

  delete game;
  return 0;

}

bool startEngine(){
  if (SDL_Init(SDL_INIT_VIDEO) == -1){
    cout << "Could not start SDL." << endl << SDL_GetError() << endl;
    return false;
  }
  if (! IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG){
    cout << "Could not start SDL_Image." << endl << IMG_GetError() << endl;
    return false;

  }
  if (TTF_Init() == -1){
    cout << "Could not start SDL_TTF." << endl << TTF_GetError() << endl;
    return false;
  }
  if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 ) { 
    cout << "Could not start SDL_Mixer." << endl;
    return false; 
  }
  return true;
}