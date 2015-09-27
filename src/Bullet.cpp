#include "Bullet.h"
#include "Game.h"
#include "TextureHandler.h"
#include "ExplosionHandler.h"
#include "Camera.h"
#include "TileLayer.h"
#include <cmath>

#define pi 3.1415926535897932384626433832795

void Bullet::update(){
    float newX = cos(rotation / 180 * pi) * speed * Game::getTheInstance()->getDeltaTime();
    float newY = sin(rotation / 180 * pi) * speed * Game::getTheInstance()->getDeltaTime();
    position.setX( position.X() + newX);
    position.setY( position.Y() + newY);
    if (tileCollisions(position)){
        dead = true;
        if (textureID == "playerrocket"){
            ExplosionHandler::getTheInstance()->addExplosion(position.X(), position.Y(), 50, 50, 14, "explosion");
        }
    }
}

void Bullet::render(){
    SDL_Rect srcRect = {0, 0, width, height};
    SDL_Rect dstRect = {position.X() - Camera::getTheInstance()->getPosition().X(), position.Y() - Camera::getTheInstance()->getPosition().Y(), drawWidth, drawHeight};
    TextureHandler::getTheInstance()->renderScale(textureID, srcRect, dstRect, Game::getTheInstance()->getRenderer(), rotation);
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
    drawWidth = width;
    drawHeight = height;
    collisionWidth = width;
    collisionHeight = height;                           // textureID should be "playerbullet" or "enemybullet", ect so they load the right files
    TextureHandler::getTheInstance()->load("Assets/Art/" + textureID + ".png", textureID, Game::getTheInstance()->getRenderer());
}

bool Bullet::tileCollisions(Vector2D pos){
    for(vector<TileLayer*>::iterator i = collisionLayers->begin(); i != collisionLayers->end(); i++){
        TileLayer* tileLayer = (*i);
        vector<vector<int>> tiles = tileLayer->getTileIDs();

        Vector2D layerPos = tileLayer->getPosition();

        int x, y, tileColumn, tileRow, tileid = 0;

        x = layerPos.X() / tileLayer->getTileSize();
        y = layerPos.Y() / tileLayer->getTileSize();

        Vector2D startPos = pos;
        startPos.setX( startPos.X() + 3);
        startPos.setY( startPos.Y() + 4);
        Vector2D endPos(pos.X() + collisionWidth, pos.Y() + collisionHeight);

        for(int i = startPos.X(); i < endPos.X(); i++) {
            for(int j = startPos.Y(); j < endPos.Y(); j++) {
                tileColumn = i / tileLayer->getTileSize();
                tileRow = j / tileLayer->getTileSize();

                tileid = tiles[tileRow + y][tileColumn + x];

                if(tileid != 0) {
                    return true;
                }
            }
        }
    }
    return false;
}

