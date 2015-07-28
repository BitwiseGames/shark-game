#ifndef GAME_H
#define GAME_H

#include <string>
#include <iostream>
#include "SDL.h"
#include "GameStateHandler.h"

using namespace std;

class Game {
  public:

    static Game* getTheInstance();

    bool startGame();
    void update();
    void render();

    void quitGame();

    bool isGameRunning()
    { return gameRunning; };

    int getScreenWidth()
    { return screenWidth; };

    int getScreenHeight()
    { return screenHeight; };

    SDL_Renderer* getRenderer()
    { return renderer; };

    GameStateHandler* getStateHandler()
    { return stateHandler; };

  private:
    Game(){};
    static Game* theInstance;
    bool gameRunning;
    int screenHeight = 600;
    int screenWidth = 800;
    string gameTitle = "Shark Game";
    SDL_Renderer* renderer;
    SDL_Window* gameWindow;
    GameStateHandler* stateHandler;

};

#endif
