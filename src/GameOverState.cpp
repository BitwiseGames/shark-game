#include "GameOverState.h"
#include "Textfield.h"
#include "Game.h"
#include "GameObject.h"
#include "StateParser.h"
#include "MainMenuState.h"

const string GameOverState::gameOverID = "GAMEOVER";

void GameOverState::update(){
    for (int i = 0; i < gameObjects.size(); i++){
        gameObjects[i]->update();
    }
    mainmenuButton->update();
}

void GameOverState::render(){
    for (int i = 0; i < gameObjects.size(); i++){
        gameObjects[i]->render();
    }
    mainmenuButton->render();
}

bool GameOverState::onEnter(){
    cout << "entering gameover" << endl;

    StateParser stateParser;
    stateParser.parseState("game.xml", gameOverID, &gameObjects, &textureIDList);

    GameObject* gameOverText = new Textfield(50,100, "GAME OVER", "Assets/Fonts/Arial.ttf", 72);
    gameObjects.push_back(gameOverText);

    callbacks.push_back(0);
    callbacks.push_back(quitGame);
    callbacks.push_back(gotoMainMenu);
    setCallbacks();
    return true;
}

bool GameOverState::onExit(){
    for (int i = 0; i < gameObjects.size(); i++){
        delete gameObjects[i];
    }
    return true;
}

void GameOverState::setCallbacks(){
    for (int i = 0; i < gameObjects.size(); i++){
        if (dynamic_cast<MenuButton*> (gameObjects[i])){ // if the item we're looking at is a menubutton
            MenuButton* button = dynamic_cast<MenuButton*>(gameObjects[i]);
            button->setCallback(callbacks[button->getCallbackID()]);  // set the callback
            if (button->getTextureID() == "mainmenubutton"){
                mainmenuButton = button;
                gameObjects.erase(gameObjects.begin() + i);
                i--;
            }
        }
    }
}


void GameOverState::gotoMainMenu(){
    Game::getTheInstance()->getStateHandler()->changeState(new MainMenuState());
}
void GameOverState::quitGame(){
    Game::getTheInstance()->quitGame();
}
