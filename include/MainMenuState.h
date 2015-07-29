#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include <string>
#include <vector>
#include "MenuState.h"
#include "GameObject.h"

using namespace std;

class GameObject;

class MainMenuState : public MenuState {
  public:
   virtual ~MainMenuState(){};

   void update();
   void render();

   bool onEnter();
   bool onExit();

   virtual string getStateID() { return menuID; };

 private:
  static void quitGame(); // button callbacks
  static void startGame();
  void setCallbacks();
  vector<GameObject*> gameObjects;
  static const string menuID;

};

#endif
