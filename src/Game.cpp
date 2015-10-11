#include "Game.h"
#include "GameObjectFactory.h"
#include "MenuButton.h"
#include "BrokenBlock.h"
#include "Player.h"
#include "PufferFish.h"
#include "PistolShrimp.h"
#include "SardineSchool.h"
#include "ElectricEel.h"
#include "Jellyfish.h"
#include "Octopus.h"
#include "GoldenEgg.h"
#include "MainMenuState.h"
#include "PlayState.h"
#include "InputHandler.h"
#include "SoundHandler.h"

Game* Game::theInstance = nullptr;

Game* Game::getTheInstance(){
  if (theInstance == nullptr){
    theInstance = new Game();
  }
  return theInstance;
}

bool Game::startGame(){
  gameWindow = SDL_CreateWindow(gameTitle.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
  if (gameWindow == nullptr){
    cout << "Failed to create window." << endl;
    return false;
  }
  renderer = SDL_CreateRenderer(gameWindow, -1, SDL_RENDERER_ACCELERATED);
  if (renderer == nullptr){
    cout << "Failed to create renderer." << endl;
    return false;
  }
    SoundHandler::getTheInstance()->load("Assets/Audio/Sound Effects/gun shot 2.wav", "gunshot", SOUND_EFFECT);
    SoundHandler::getTheInstance()->load("Assets/Audio/Sound Effects/gun shot 1.wav", "energyball", SOUND_EFFECT);
    SoundHandler::getTheInstance()->load("Assets/Audio/Sound Effects/gun shot 3.wav", "cannonball", SOUND_EFFECT);
    SoundHandler::getTheInstance()->load("Assets/Audio/Sound Effects/missile 2.wav", "missile", SOUND_EFFECT);

  // anything that is not created at runtime (bullets, explosions, ect) must be created here
  GameObjectFactory::getTheInstance()->registerType("PistolShrimp", new PistolShrimpCreator());
  GameObjectFactory::getTheInstance()->registerType("ElectricEel", new ElectricEelCreator());
  GameObjectFactory::getTheInstance()->registerType("BrokenBlock", new BrokenBlockCreator());
  GameObjectFactory::getTheInstance()->registerType("MenuButton", new MenuButtonCreator());
  GameObjectFactory::getTheInstance()->registerType("PufferFish", new PufferFishCreator());
  GameObjectFactory::getTheInstance()->registerType("GoldenEgg", new GoldenEggCreator());
  GameObjectFactory::getTheInstance()->registerType("Jellyfish", new JellyfishCreator());
  GameObjectFactory::getTheInstance()->registerType("Octopus", new OctopusCreator());
  GameObjectFactory::getTheInstance()->registerType("Player", new PlayerCreator());

  stateHandler = new GameStateHandler();
  stateHandler->changeState(new MainMenuState());
  gameRunning = true;

  return true;
}

void Game::update(){

    stateHandler->update();

    float frameTime = SDL_GetTicks() - lastFrame;
    lastFrame += frameTime;
    deltaTime = frameTime / 1000.0;
}
void Game::render(){
    SDL_RenderClear(renderer);

    stateHandler->render();

    SDL_RenderPresent(renderer);
}
void Game::handleInput(){
    InputHandler::getTheInstance()->update();
}

void Game::setScreenWidth(int w){
    screenWidth = w;
    SDL_SetWindowSize(gameWindow, screenWidth, screenHeight);
}

void Game::setScreenHeight(int h){
    screenHeight = h;
    SDL_SetWindowSize(gameWindow, screenWidth, screenHeight);
}

void Game::toggleFullscreen(bool f){
    SDL_SetWindowFullscreen(gameWindow, f);
}

void Game::setCurrentLevel(int l){
    if (l > NUM_LEVELS || l < 1){
        cout << "Level " << l << " does not exist, returning first level." << endl;
        currentLevel = 1;
        return;
    }
    if (l == currentLevel){
        cout << "We're already on that level!" << endl;
        return;
    }
    currentLevel = l;
    stateHandler->changeState(new PlayState());
}

void Game::quitGame(){
  SDL_DestroyWindow(gameWindow);
  delete stateHandler;
  delete gameWindow;
  delete renderer;
  gameRunning = false;
}
