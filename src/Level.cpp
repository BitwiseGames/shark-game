#include "Level.h"
#include "Camera.h"

Level::Level(){};

Level::~Level(){
  for (int i = 0; i < layers.size(); i++){
    delete layers[i];
  }
  layers.clear();
}

void Level::render(){
    // loop backwards so that tiles get drawn first
    for (int i = layers.size() - 1; i >= 0; i--){
        layers[i]->render();
    }
}

void Level::update(){
  for (int i = 0; i < layers.size(); i++){
    layers[i]->update(this);
  }
  Camera::getTheInstance()->update(*player->Position());
}
