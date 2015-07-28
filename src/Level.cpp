#include "Level.h"

Level::~Level(){
  for (int i = 0; i < layers.size(); i++){
    delete layers[i];
  }
  layers.clear();
}

void Level::render(){
    cout << "LEVEL RENDER" << endl;
    cout << layers.size() << endl;
  for (int i = 0; i < layers.size(); i++){
    layers[i]->render();
  }
}

void Level::update(){
  for (int i = 0; i < layers.size(); i++){
    layers[i]->update(this);
  }
}
