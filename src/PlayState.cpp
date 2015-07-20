#include "PlayState.h"

void PlayState::update(){
  level->update();
}
void PlayState::render(){
  level->render();
}

bool PlayState::onEnter(){
  return true;
}
bool PlayState::onExit(){
  return true;
}