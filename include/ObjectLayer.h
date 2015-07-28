#ifndef OBJECTLAYER_H
#define OBJECTLAYER_H

#include <vector>
#include <iostream>
#include "Layer.h"
#include "GameObject.h"

using namespace std;

class GameObject;

class ObjectLayer : public Layer {
  public:
    virtual ~ObjectLayer();
    virtual void update(Level*);
    virtual void render();
    vector<GameObject*>* getGameObjects(){ return &gameObjects; };
  private:
    vector<GameObject*> gameObjects;
};

#endif
