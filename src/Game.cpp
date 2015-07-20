#include "Game.h"

Game::Game* theInstance = nullptr;

Game* Game::getTheInstance(){
  if (theInstance == nullptr){
    theInstance = new Game();
  }
  return theInstance;
}

void Game::startGame(){
  // init renderer and game window
  stateHandler = new GameStateHandler;
  stateHandler->changeState(new MainMenuState);
  gameRunning = true;
}

void Game::update(){
  stateHandler->update();
}
void Game::render(){
  stateHandler->render();
}