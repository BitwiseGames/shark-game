#include "SoundHandler.h"

SoundHandler* SoundHandler::theInstance = nullptr;

SoundHandler* SoundHandler::getTheInstance(){
  if (theInstance == nullptr){
    theInstance = new SoundHandler();
  }
  return theInstance;
}

bool SoundHandler::load(string fileName, string ID, soundType type){
  if (type == SOUND_MUSIC){
    Mix_Music* musicFile = Mix_LoadMUS(fileName.c_str());
    if (musicFile == nullptr){
      cout << "Could not load music file: " << fileName << endl << Mix_GetError() << endl;
      return false;
    }

    music[ID] = musicFile;
    return true;

  }
  else if (type == SOUND_EFFECT){
    Mix_Chunk* effectFile = Mix_LoadWAV(fileName.c_str());
    if (effectFile == nullptr){
      cout << "Could not load sound effect file: " << fileName << endl << Mix_GetError() << endl;
      return false;
    }

    soundEffects[ID] = effectFile;
    return true;
  }
  return false;
}

void SoundHandler::playMusic(string ID, int loop){
  Mix_PlayMusic(music[ID], loop);
}

void SoundHandler::playSound(string ID, int loop){
  Mix_PlayChannel(-1, soundEffects[ID], loop);
}
