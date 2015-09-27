#include "GameObject.h"
#include "Camera.h"
#include "TileLayer.h"
#include "TextureHandler.h"

void GameObject::render(){
    int drawX, drawY;
    drawX = (position.X() - Camera::getTheInstance()->getPosition().X());
    drawY = (position.Y() - Camera::getTheInstance()->getPosition().Y());
    TextureHandler::getTheInstance()->renderFrame(textureID, drawX, drawY, width, height, currentRow, currentFrame, Game::getTheInstance()->getRenderer(), rotation, alpha, flip);
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
    collisionWidth = width;
    collisionHeight = height;
}

bool GameObject::tileCollisions(Vector2D pos){
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
        Vector2D endPos(pos.X() + collisionWidth, pos.Y() + collisionHeight - 8);

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
