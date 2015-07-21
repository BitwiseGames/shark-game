#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

class MainMenuState : public GameState {
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
  vector<GameObject*> gameObjects;
  static const string menuID;

};

#endif