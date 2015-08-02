#include "PlayState.h"
#include "Level.h"
#include "StateParser.h"
#include "Game.h"
#include "InputHandler.h"
#include "LevelParser.h"
#include "BulletHandler.h"
#include "PauseState.h"

const string PlayState::playID = "PLAY";

void PlayState::update(){
    level->update();
    if (InputHandler::getTheInstance()->getKey(SDL_SCANCODE_ESCAPE)){
        pauseGame();
    }
    BulletHandler::getTheInstance()->update();
}
void PlayState::render(){
    level->render();
    BulletHandler::getTheInstance()->render();
}

bool PlayState::onEnter(){
    /**BE ABSOLUTELY SURE THAT MARGIN AND SPACING IN THE LEVEL FILE ARE NOT ZERO**/
    LevelParser levelParser;
    level = levelParser.parseLevel("level_1.tmx");
    /**YOU WILL GET A DIVISION BY ZERO AND THE PROGRAM WILL NOT LAUNCH**/

    BulletHandler::getTheInstance()->setCollisionLayers(level->getCollisionLayers());
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
