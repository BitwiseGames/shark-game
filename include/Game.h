#ifndef GAME_H
#define GAME_H

class Game {
  public:

    static Game* getTheInstance();

    void startGame();
    void update();
    void render();

    bool isGameRunning()
    { return gameRunning; };

    int getScreenWidth()
    { return screenWidth; };

    int getScreenHeight()
    { return screenHeight; };

    SDL_Renderer* getRenderer()
    { return renderer; };

    GameStateHandler* getStateHandler()
    { return stateHandler; };

  private:
    Game();
    static Game* theInstance;
    bool gameRunning;
    int screenHeight = 600;
    int screenWidth = 800;
    SDL_Renderer* renderer;
    SDL_Window* gameWindow;
    GameStateHandler* stateHandler;

};

#endif