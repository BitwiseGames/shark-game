#include "Game.h"
#include "GameObjectFactory.h"
#include "MenuButton.h"
#include "Player.h"
#include "MainMenuState.h"
#include "InputHandler.h"
#include "SoundHandler.h"

Game* Game::theInstance = nullptr;

Game* Game::getTheInstance(){
  if (theInstance == nullptr){
    theInstance = new Game();
  }
  return theInstance;
}

bool Game::startGame(){
  gameWindow = SDL_CreateWindow(gameTitle.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
  if (gameWindow == nullptr){
    cout << "Failed to create window." << endl;
    return false;
  }
  renderer = SDL_CreateRenderer(gameWindow, -1, SDL_RENDERER_ACCELERATED);
  if (renderer == nullptr){
    cout << "Failed to create renderer." << endl;
    return false;
  }
    SoundHandler::getTheInstance()->load("Audio/Sound Effects/gun shot 2.wav", "gunshot", SOUND_EFFECT);

  // anything that is not created at runtime (bullets, explosions, ect) must be created here
  GameObjectFactory::getTheInstance()->registerType("MenuButton", new MenuButtonCreator());
  GameObjectFactory::getTheInstance()->registerType("Player", new PlayerCreator());

  stateHandler = new GameStateHandler();
  stateHandler->changeState(new MainMenuState());
  gameRunning = true;

  return true;
}

void Game::update(){

    stateHandler->update();

    float frameTime = SDL_GetTicks() - lastFrame;
    lastFrame += frameTime;
    deltaTime = frameTime / 1000.0;
}
void Game::render(){
    SDL_RenderClear(renderer);

    stateHandler->render();

    SDL_RenderPresent(renderer);
}
void Game::handleInput(){
    InputHandler::getTheInstance()->update();
}

void Game::quitGame(){
  SDL_DestroyWindow(gameWindow);
  delete stateHandler;
  delete gameWindow;
  delete renderer;
  gameRunning = false;
}
