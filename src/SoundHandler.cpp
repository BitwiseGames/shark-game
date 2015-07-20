#include "SoundHandler.h"

SoundHandler::SoundHandler* theInstance = nullptr;

SoundHandler* SoundHandler::getTheInstance(){
  if (theInstance == nullptr){
    theInstance = new SoundHandler();
  }
  return theInstance;
}

bool SoundHandler::load(string fileName, string ID, soundType type){
  if (type == SOUND_MUSIC){

  }
  else if (type == SOUND_EFFECT){

  }
  return false;
}

void SoundHandler::playMusic(){

}

void SoundHandler::playSound(){

}