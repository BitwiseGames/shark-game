#include "PistolShrimp.h"
#include "CollisionHandler.h"
#include "BulletHandler.h"
#include "Player.h"
#include "Tests.h"
#include "Camera.h"

PistolShrimp::PistolShrimp(){
    shotCoolDown = 0;
    maxCoolDown = 15;
}

void PistolShrimp::update(){
    shotCoolDown--;
    int px = CollisionHandler::getTheInstance()->getPlayer()->Position()->X();
    int py = CollisionHandler::getTheInstance()->getPlayer()->Position()->Y();
    if (Tests::distanceBetween(px, py, position.X(), position.Y()) <= viewDistance){
        if (shotCoolDown <= 0){
            shotCoolDown = maxCoolDown;
            float angle = Tests::angleBetween(position.X(), position.Y(), px, py);
            BulletHandler::getTheInstance()->addEnemyBullet(position.X(), position.Y(), angle);
        }
    }
}
