#ifndef OBJECTLAYER_H
#define OBJECTLAYER_H

#include "Layer.h"

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