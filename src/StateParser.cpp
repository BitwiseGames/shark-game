#include "StateParser.h"
#include "Game.h"
#include "GameObject.h"
#include "TextureHandler.h"
#include "GameObjectFactory.h"

bool StateParser::parseState(const char* stateFile, string stateID, vector<GameObject*>* gameObjects, vector<string>* textureIDs){
  TiXmlDocument xmlDoc;
  if (!xmlDoc.LoadFile(stateFile)){
    cout << xmlDoc.ErrorDesc() << endl;
    return false;
  }
  TiXmlElement* root = xmlDoc.RootElement();
  TiXmlElement* stateRoot = nullptr;
  for (TiXmlElement* e = stateRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement()){
    if(e->Value() == stateID){
      stateRoot = e;
      break;
    }
  }

  TiXmlElement* textureRoot = nullptr;

  for(TiXmlElement* e = stateRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement()){
   if(e->Value() == string("TEXTURES")){
    textureRoot = e;
    break;
    }
  }

  parseTextures(textureRoot, textureIDs);

  TiXmlElement* objectRoot = nullptr;

  for(TiXmlElement* e = stateRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement()){
    if(e->Value() == string("OBJECTS")){
      objectRoot = e;
      break;
    }
  }

  parseObjects(objectRoot, gameObjects);
  return true;

}

void StateParser::parseTextures(TiXmlElement* stateRoot, vector<string>* textureIDs){
  for(TiXmlElement* e = stateRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement()){
      string filename = e->Attribute("filename");
      string ID = e->Attribute("ID");

      textureIDs->push_back(ID);

      TextureHandler::getTheInstance()->load(filename, ID, Game::getTheInstance()->getRenderer());
  }
}

void StateParser::parseObjects(TiXmlElement* stateRoot, vector<GameObject*>* gameObjects){
    for(TiXmlElement* e = stateRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement()){
        int x, y, width, height, numFrames, callbackID, health, animSpeed;
        string textureID;

        e->Attribute("x", &x);
        e->Attribute("y", &y);
        e->Attribute("width",&width);
        e->Attribute("height", &height);
        e->Attribute("numFrames", &numFrames);
        e->Attribute("callbackID", &callbackID);
        e->Attribute("health", &health);
        e->Attribute("animSpeed", &animSpeed);
        textureID = e->Attribute("textureID");

        GameObject* gameObject = GameObjectFactory::getTheInstance()->create(e->Attribute("type"));
        gameObject->load(x, y, width, height, numFrames, callbackID, health, animSpeed, textureID);
        gameObjects->push_back(gameObject);
    }
}
