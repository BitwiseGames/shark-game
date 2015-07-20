#include "Level.h"

Level::~Level(){
  for (int i = 0; i < layers.size(); i++){
    delete layers[i];
  }
  layers.clear();
}

void Level::render(){
  for (int i = 0; i < layers.size(); i++){
    layers[i]->render();
  }
}

void Level::update(){
  for (int i = 0; i < layers.size(); i++){
    layers[i]->update();
  }
}