#include "ElectricEel.h"
#include "Game.h"
#include "CollisionHandler.h"
#include "Player.h"
#include "Tests.h"
#include <cmath>
#define pi 3.1415926535897932384626433832795


ElectricEel::ElectricEel() {
    speed = 50;
}

void ElectricEel::update(){
    int px = CollisionHandler::getTheInstance()->getPlayer()->Position()->X();
    int py = CollisionHandler::getTheInstance()->getPlayer()->Position()->Y();
    if (Tests::distanceBetween(px, py, position.X(), position.Y()) <= viewDistance){
        float angle = Tests::angleBetween(position.X(), position.Y(), px, py);
        rotation = angle;
        float newX = cos(rotation / 180 * pi) * speed * Game::getTheInstance()->getDeltaTime();
        float newY = sin(rotation / 180 * pi) * speed * Game::getTheInstance()->getDeltaTime();
        Vector2D newPos = Vector2D(position.X() + newX, position.Y() + newY);
        if (!tileCollisions(newPos)){
            position.setX( position.X() + newX);
            position.setY( position.Y() + newY);
        }
    }
}
