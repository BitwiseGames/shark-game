#include "ObjectLayer.h"

ObjectLayer::~ObjectLayer(){
  for (vector<GameObject*>::iterator i = gameObjects.begin(); i != gameObjects.end(); i++){
    delete (*i);
  }
  gameObjects.clear();
}

void ObjectLayer::update(Level* level){
  if (!gameObjects.empty()){
    for (vector<GameObject*>::iterator i = gameObjects.begin(); i != gameObjects.end();){
      (*i)->update();
      if ((*i)->Dead()){
        delete *i;
        i = gameObjects.erase(i);
      }
      else {
        i++;
      }
    }
  }
}

void ObjectLayer::render(){
  for (int i = 0; i < gameObjects.size(); i++){
    gameObjects[i]->render();
  }
}
