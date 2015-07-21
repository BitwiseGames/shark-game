#ifndef SOUNDHANDLER_H
#define SOUNDHANDLER_H

#include <string>
using namespace std;

enum soundType{
  SOUND_MUSIC = 0,
  SOUND_EFFECT = 1
}

class SoundHandler{

  public:

    static SoundHandler* getTheInstance();
    bool load(string, string, soundType);
    void playSound(string, int);
    void playMusic(string, int);

  private:
    SoundHandler();
    ~SoundHandler(){ Mix_Close_Audio(); };
    static SoundHandler* theInstance;
    map<string, Mix_Chunk*> soundEffects;
    map<string, Mix_Chunk*> music;
  
};

#endif