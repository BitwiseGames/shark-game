#include "PlayState.h"
#include "Level.h"
#include "LevelParser.h"

const string PlayState::playID = "PLAY";

void PlayState::update(){
    level->update();
}
void PlayState::render(){
    level->render();
}

bool PlayState::onEnter(){
    LevelParser levelParser;
    levelParser.parseLevel("level_1.tmx");
cout << "finished parsing level" << endl;
    return true;
}
bool PlayState::onExit(){
    return true;
}
