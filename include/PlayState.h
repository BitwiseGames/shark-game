#ifndef PLAYSTATE_H
#define PLAYSTATE_H

#include <string>
#include <vector>
#include "GameState.h"

using namespace std;

class Level;
class GameObject;
class PlayState : public GameState {

  public:
    virtual ~PlayState(){ delete level; };

    virtual void update();
    virtual void render();

    virtual bool onEnter();
    virtual bool onExit();

    virtual string getStateID(){ return playID; };
  private:
    static const string playID;
    Level* level;
    vector<GameObject*> gameObjects;

};

#endif
