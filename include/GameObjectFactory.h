#ifndef GAMEOBJECTFACTORY_H
#define GAMEOBJECTFACTORY_H

#include <string>
#include <map>
#include <iostream>
#include "GameObject.h"

using namespace std;

class BaseCreator {
  public:
    GameObject* createGameObject();
    virtual ~BaseCreator(){};
};

class GameObjectFactory {

  public:
    static GameObjectFactory* getTheInstance();
    bool registerType(string, BaseCreator*);
    GameObject* create(string);
  private:
    GameObjectFactory(){};
    ~GameObjectFactory(){};
    static GameObjectFactory* theInstance;
    map<string, BaseCreator*> creators;


};

#endif
