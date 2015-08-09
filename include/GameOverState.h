#ifndef GAMEOVERSTATE_H
#define GAMEOVERSTATE_H

#include <string>
#include <vector>
#include <iostream>
#include "MenuState.h"
#include "MenuButton.h"

using namespace std;

class GameObject;
class GameOverState : public MenuState {

  public:

    virtual void update();
    virtual void render();

    virtual bool onEnter();
    virtual bool onExit();

    virtual string getStateID(){ return gameOverID; };
  private:
    static const string gameOverID;
    vector<GameObject*> gameObjects;

    void setCallbacks();

    MenuButton* mainmenuButton;

    static void gotoMainMenu();
    static void quitGame();

};

#endif
