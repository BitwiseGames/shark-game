#include "Bullet.h"
#include "Game.h"
#include "TextureHandler.h"
#include <cmath>

#define pi 3.1415926535897932384626433832795

Bullet::Bullet(string ID, int x, int y, int w, int h, float s, float rot){
    textureID = ID;
    position.setX(x);
    position.setY(y);
    width = w;
    height = h;
    speed = s;
    rotation = rot;
    currentFrame = 0;
    currentRow = 0;
    TextureHandler::getTheInstance()->load("Art/player_bullet.png", ID, Game::getTheInstance()->getRenderer());
}

void Bullet::update(){
    float newX = cos(rotation * 180 / pi) * speed * Game::getTheInstance()->getDeltaTime();
    float newY = sin(rotation * 180 / pi) * speed * Game::getTheInstance()->getDeltaTime();
    position.setX( position.X() + newX);
    position.setY( position.Y() + newY);
}
