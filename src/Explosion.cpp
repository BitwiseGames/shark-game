#include "Explosion.h"
#include "Camera.h"
#include "Game.h"
#include "TextureHandler.h"

void Explosion::update(){
    // update the animation
    currentFrame++;
    if (currentFrame == numFrames-1){ // we're at the end of the animation
        dead = true;
    }
}

void Explosion::render(){
    SDL_Rect srcRect = {width * currentFrame, height * currentRow, width, height};
    SDL_Rect dstRect = {position.X() - Camera::getTheInstance()->getPosition().X(), position.Y() - Camera::getTheInstance()->getPosition().Y(), drawWidth, drawHeight};
    TextureHandler::getTheInstance()->renderScale(textureID, srcRect, dstRect, Game::getTheInstance()->getRenderer(), rotation);
}

void Explosion::load(int x, int y, int w, int h, int time, string ID){
    position.setX(x);
    position.setY(y);
    width = w;
    height = h;
    textureID = ID;
    currentFrame = 0;
    currentRow = 0;
    numFrames = 7;
    animSpeed = 24;
    collisionWidth = width;
    collisionHeight = height;
    drawWidth = width;
    drawHeight = height;
    TextureHandler::getTheInstance()->load("Assets/Art/explosion.png", textureID, Game::getTheInstance()->getRenderer());
}
