#include "PlayState.h"
#include "Level.h"

const string PlayState::playID = "PLAY";

void PlayState::update(){
    level->update();
}
void PlayState::render(){
    level->render();
}

bool PlayState::onEnter(){
    cout << "Entering play." << endl;
    return true;
}
bool PlayState::onExit(){
    return true;
}
