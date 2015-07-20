#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

class MainMenuState : public GameState {
  public:
   virtual ~MainMenuState(){};

   void update();
   void render();

   bool onEnter();
   bool onExit();

 private:
  quitGame();
  startGame();
  vector<GameObject*> gameObjects;

};

#endif