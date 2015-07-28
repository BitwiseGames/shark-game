#include "Game.h"
#include "GameObjectFactory.h"
#include "MenuButton.h"
#include "MainMenuState.h"
#include "InputHandler.h"

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


  // anything that is not created at runtime (bullets, explosions, ect) must be created here
  GameObjectFactory::getTheInstance()->registerType("MenuButton", new MenuButtonCreator());

  stateHandler = new GameStateHandler();
  stateHandler->changeState(new MainMenuState());
  gameRunning = true;

  return true;
}

void Game::update(){
  stateHandler->update();
}
void Game::render(){
  stateHandler->render();
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
