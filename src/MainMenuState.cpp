#include "MainMenuState.h"
#include "PlayState.h"
#include "StateParser.h"
#include "MenuButton.h"
#include "Game.h"
#include "InputHandler.h"

const string MainMenuState::menuID = "MENU";

void MainMenuState::update(){
    for (int i = 0; i < gameObjects.size(); i++){
        gameObjects[i]->update();
    }
}
void MainMenuState::render(){
    SDL_RenderClear(Game::getTheInstance()->getRenderer());

    for (int i = 0; i < gameObjects.size(); i++){
        gameObjects[i]->render();
    }

    SDL_RenderPresent(Game::getTheInstance()->getRenderer());

}

bool MainMenuState::onEnter(){
    exiting = false;
    StateParser stateParser;
    stateParser.parseState("game.xml", menuID, &gameObjects, &textureIDList);

    SDL_SetRenderDrawColor(Game::getTheInstance()->getRenderer(), 255, 255, 255, 255); // white background

    callbacks.push_back(0);
    callbacks.push_back(startGame);
    callbacks.push_back(quitGame);
    setCallbacks();

    return true;
}
bool MainMenuState::onExit(){
    exiting = true;
    for (int i = 0; i < gameObjects.size(); i++){
        delete gameObjects[i];
    }
    gameObjects.clear();
    InputHandler::getTheInstance()->reset();
    return true;
}

void MainMenuState::quitGame(){
    Game::getTheInstance()->quitGame();
}
void MainMenuState::startGame(){
    Game::getTheInstance()->getStateHandler()->changeState(new PlayState());
}

void MainMenuState::setCallbacks(){
    for (int i = 0; i < gameObjects.size(); i++){
        if (dynamic_cast<MenuButton*> (gameObjects[i])){ // if the item we're looking at is a menubutton
            MenuButton* button = dynamic_cast<MenuButton*>(gameObjects[i]);
            button->setCallback(callbacks[button->getCallbackID()]);  // set the callback
        }
    }
}














