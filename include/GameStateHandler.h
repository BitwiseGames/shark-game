#ifndef GAMESTATEHANDLER_H
#define GAMESTATEHANDLER_H

#include <vector>

using namespace std;

class GameStateHandler {
  
  public:
    GameStateHandler(){};
    ~GameStateHandler(){};

    void pushState(GameState*);
    void changeState(GameState*);
    void popState();
    
    void update();
    void render();
  private:
    vector<GameState*> states;

};

#endif