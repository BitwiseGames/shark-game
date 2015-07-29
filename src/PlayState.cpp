#include "PlayState.h"
#include "Level.h"
#include "Game.h"
#include "InputHandler.h"
#include "LevelParser.h"
#include "PauseState.h"

const string PlayState::playID = "PLAY";

void PlayState::update(){
    level->update();
    if (InputHandler::getTheInstance()->getKey(SDL_SCANCODE_ESCAPE)){
        pauseGame();
    }
}
void PlayState::render(){
    level->render();
}

bool PlayState::onEnter(){
    LevelParser levelParser;
    level = levelParser.parseLevel("level_1.tmx");
    cout << "Entering playstate" << endl;
    return true;
}
bool PlayState::onExit(){
    InputHandler::getTheInstance()->reset();
    return true;
}

void PlayState::pauseGame(){
    Game::getTheInstance()->getStateHandler()->pushState(new PauseState());
}
