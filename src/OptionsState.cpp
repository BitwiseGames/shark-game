#include "OptionsState.h"
#include "Game.h"
#include "MenuButton.h"
#include "TextureHandler.h"
#include "Textfield.h"
#include "InputHandler.h"
#include "StateParser.h"
#include <sstream>

const string OptionsState::optionsID = "OPTIONS";
bool OptionsState::fullscreen = false;
SDL_Point OptionsState::currentResolution = {800,600};
int OptionsState::curResolutionIndex = 0;
const int OptionsState::NUM_RESOLUTIONS = 8;
SDL_Point OptionsState::resolutions[] = {{800,600}, {1024,768}, {1280,720}, {1366,768}, {1440,900}, {1600,900}, {1600,1200}, {1920,1080}};

void OptionsState::update(){
    for (int i = 0; i < gameObjects.size(); i++){
        gameObjects[i]->update();
    }
    int curResW = Game::getTheInstance()->getScreenWidth();
    int curResH = Game::getTheInstance()->getScreenHeight();
    string newText;
    stringstream s;
    s << curResW << "," << curResH;
    newText = s.str();
    curResolutionText->changeText(newText);
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

    GameObject* resolutionText = new Textfield(100, 100, "RESOLUTION: ", "Assets/Fonts/arial.ttf", 48);
    curResolutionText = new Textfield(525, 100, "res", "Assets/Fonts/arial.ttf", 48);
    gameObjects.push_back(resolutionText);
    gameObjects.push_back(curResolutionText);

    callbacks.push_back(0);
    callbacks.push_back(closeOptions);
    callbacks.push_back(decreaseResolution);
    callbacks.push_back(increaseResolution);
    callbacks.push_back(toggleFullscreen);
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

void OptionsState::increaseResolution(){
    curResolutionIndex++;
    if (curResolutionIndex > NUM_RESOLUTIONS - 1){ // we're at the last option
        curResolutionIndex = 0;
    }
    currentResolution.x = resolutions[curResolutionIndex].x;
    currentResolution.y = resolutions[curResolutionIndex].y;
    Game::getTheInstance()->setScreenWidth(currentResolution.x);
    Game::getTheInstance()->setScreenHeight(currentResolution.y);
}

void OptionsState::decreaseResolution(){
    curResolutionIndex--;
    if (curResolutionIndex < 0){ // we're at the first option
        curResolutionIndex = NUM_RESOLUTIONS - 1;
    }
    currentResolution.x = resolutions[curResolutionIndex].x;
    currentResolution.y = resolutions[curResolutionIndex].y;
    Game::getTheInstance()->setScreenWidth(currentResolution.x);
    Game::getTheInstance()->setScreenHeight(currentResolution.y);
}

void OptionsState::toggleFullscreen(){
    fullscreen = !fullscreen;
    Game::getTheInstance()->toggleFullscreen(fullscreen);
}
