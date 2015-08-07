#include "OptionsState.h"
#include "Game.h"
#include "MenuButton.h"
#include "StateParser.h"

const string OptionsState::optionsID = "OPTIONS";

void OptionsState::update(){
    for (int i = 0; i < gameObjects.size(); i++){
        gameObjects[i]->update();
    }
}

void OptionsState::render(){
    for (int i = 0; i < gameObjects.size(); i++){
        gameObjects[i]->render();
    }
}

bool OptionsState::onEnter(){
    cout << "entering options" << endl;
    StateParser stateParser;
    stateParser.parseState("game.xml", optionsID, &gameObjects, &textureIDList);

    SDL_SetRenderDrawColor(Game::getTheInstance()->getRenderer(), 255, 255, 255, 255); // white background

    callbacks.push_back(0);
    callbacks.push_back(closeOptions);
    setCallbacks();

    return true;
}

bool OptionsState::onExit(){
}

void OptionsState::setCallbacks(){
    for (int i = 0; i < gameObjects.size(); i++){
        if (dynamic_cast<MenuButton*> (gameObjects[i])){ // if the item we're looking at is a menubutton
            MenuButton* button = dynamic_cast<MenuButton*>(gameObjects[i]);
            button->setCallback(callbacks[button->getCallbackID()]);  // set the callback
        }
    }
}

void OptionsState::closeOptions(){
    Game::getTheInstance()->getStateHandler()->popState();
}
