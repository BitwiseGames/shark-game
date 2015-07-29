#include "PauseState.h"
#include "Game.h"
#include "StateParser.h"
#include "TextureHandler.h"
#include "MenuButton.h"
#include "InputHandler.h"

const string PauseState::pauseID = "PAUSE";


void PauseState::update(){
    for (int i = 0; i < gameObjects.size(); i++){
        gameObjects[i]->update();
    }
}
void PauseState::render(){

    for (int i = 0; i < gameObjects.size(); i++){
        gameObjects[i]->render();
    }

}

bool PauseState::onEnter(){
    cout << "Entering pause" << endl;
    StateParser stateParser;
    stateParser.parseState("game.xml", pauseID, &gameObjects, &textureIDList);

    SDL_SetRenderDrawColor(Game::getTheInstance()->getRenderer(), 255, 255, 255, 255); // white background

    callbacks.push_back(0);
    callbacks.push_back(quitGame);
    callbacks.push_back(resumeGame);
    setCallbacks();

    return true;
}
bool PauseState::onExit(){
    cout << "Exiting pause" << endl;
    for (int i = 0; i < gameObjects.size(); i++){
        delete gameObjects[i];
    }
    gameObjects.clear();
    for (int i = 0; i < textureIDList.size(); i++){
        TextureHandler::getTheInstance()->removeFromTextureMap(textureIDList[i]);
    }
    InputHandler::getTheInstance()->reset();
    return true;
}


void PauseState::setCallbacks(){
    for (int i = 0; i < gameObjects.size(); i++){
        if (dynamic_cast<MenuButton*> (gameObjects[i])){ // if the item we're looking at is a menubutton
            MenuButton* button = dynamic_cast<MenuButton*>(gameObjects[i]);
            button->setCallback(callbacks[button->getCallbackID()]);  // set the callback
        }
    }
}

void PauseState::quitGame(){
    Game::getTheInstance()->quitGame();
}

void PauseState::resumeGame(){
    Game::getTheInstance()->getStateHandler()->popState();
}
