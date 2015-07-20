#include "GameObjectFactory.h"
GameObjectFactory::GameObjectFactory* theInstance = nullptr;

GameObjectFactory* GameObjectFactory::getTheInstance(){
  if (theInstance == nullptr){
    theInstance = new GameObjectFactory();
  }
  return theInstance;
}

bool GameObjectFactory::registerType(string typeID, BaseCreator* creator){
  map<string, BaseCreator*>::iterator i = creators.find(typeID);

  if (i == creators.end()){ // it already exists, don't need to do anything
    delete creator;
  }

  creators[typeID] = creator;
  return true;
}

GameObject* GameObjectFactory::create(string typeID){
  map<string, BaseCreator*>::iterator i = creators.find(typeID);
  if(i == creators.end()){
   cout << "could not find type: " << typeID << endl;
   return NULL;
  }  
  BaseCreator* creator = (*i).second;
  return creator->createGameObject();
}