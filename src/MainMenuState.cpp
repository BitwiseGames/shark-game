#include "MainMenuState.h"

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
  return true;
}
bool MainMenuState::onExit(){
  return true;
}