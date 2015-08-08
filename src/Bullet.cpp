#include "Bullet.h"
#include "Game.h"
#include "TextureHandler.h"
#include <cmath>

#define pi 3.1415926535897932384626433832795

void Bullet::update(){
    float newX = cos(rotation / 180 * pi) * speed * Game::getTheInstance()->getDeltaTime();
    float newY = sin(rotation / 180 * pi) * speed * Game::getTheInstance()->getDeltaTime();
    position.setX( position.X() + newX);
    position.setY( position.Y() + newY);
    if (tileCollisions(position)){
        dead = true;
    }
}

void Bullet::load(int x, int y, int w, int h, float s, float rot, string ID){
    position.setX(x);
    position.setY(y);
    width = w;
    height = h;
    speed = s;
    textureID = ID;
    rotation = rot;
    currentFrame = 0;
    currentRow = 0;
    collisionWidth = width;
    collisionHeight = height;                           // textureID should be "playerbullet" or "enemybullet", ect so they load the right files
    TextureHandler::getTheInstance()->load("Assets/Art/" + textureID + ".png", textureID, Game::getTheInstance()->getRenderer());
}
