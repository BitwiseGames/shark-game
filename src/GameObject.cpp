#include "GameObject.h"
#include "Camera.h"
#include "TextureHandler.h"

void GameObject::render(){
    int drawX, drawY;
    drawX = (position.X() - Camera::getTheInstance()->getPosition().X());
    drawY = (position.Y() - Camera::getTheInstance()->getPosition().Y());
    TextureHandler::getTheInstance()->renderTexture(textureID, drawX, drawY, width, height, Game::getTheInstance()->getRenderer());
}

void GameObject::load(int x, int y, int w, int h, int frames, int cID, int _health, int speed, string tID){
    position.setX(x);
    position.setY(y);
    width = w;
    height = h;
    numFrames = frames;
    callbackID = cID;
    health = _health;
    animSpeed = speed;
    textureID = tID;
    currentFrame = 0;
    currentRow = 0;
}
