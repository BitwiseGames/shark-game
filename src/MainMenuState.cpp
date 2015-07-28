#include "MainMenuState.h"
#include "PlayState.h"
#include "Game.h"

const string MainMenuState::menuID = "MENU";

void MainMenuState::update(){

  for (int i = 0; i < gameObjects.size(); i++){
    gameObjects[i]->update();
  }

}
void MainMenuState::render(){

  for (int i = 0; i < gameObjects.size(); i++){
    gameObjects[i]->render();
  }

}

bool MainMenuState::onEnter(){
  callbacks.push_back(0);
  callbacks.push_back(quitGame);
  callbacks.push_back(startGame);
  return true;
}
bool MainMenuState::onExit(){
  for (int i = 0; i < gameObjects.size(); i++){
    delete gameObjects[i];
  }
  gameObjects.clear();
  return true;
}

void MainMenuState::quitGame(){
  Game::getTheInstance()->quitGame();
}
void MainMenuState::startGame(){
  Game::getTheInstance()->getStateHandler()->changeState(new PlayState());
}
