#include "OptionsState.h"
#include "Game.h"
#include "MenuButton.h"
#include "TextureHandler.h"
#include "Textfield.h"
#include "InputHandler.h"
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

    GameObject* textField = new Textfield(100,100,"TEST","Fonts/arial.ttf");
    gameObjects.push_back(textField);

    callbacks.push_back(0);
    callbacks.push_back(closeOptions);
    setCallbacks();

    return true;
}

bool OptionsState::onExit(){
    for (int i = 0; i < gameObjects.size(); i++){
        delete gameObjects[i];
    }
    gameObjects.clear();
    for (int i = 0; i < textureIDList.size(); i++){
        TextureHandler::getTheInstance()->removeFromTextureMap(textureIDList[i]);
    }
    InputHandler::getTheInstance()->reset();
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
