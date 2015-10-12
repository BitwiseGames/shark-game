#include "BulletHandler.h"
#include "SoundHandler.h"
#include "Flamethrower.h"

BulletHandler* BulletHandler::theInstance = nullptr;

BulletHandler* BulletHandler::getTheInstance(){
    if (theInstance == nullptr){
        theInstance = new BulletHandler();
    }
    return theInstance;
}

void BulletHandler::update(){
    updatePlayerBullets();
    updateEnemyBullets();
}
void BulletHandler::render(){
    renderPlayerBullets();
    renderEnemyBullets();
}

void BulletHandler::updatePlayerBullets(){
    for (vector<Bullet*>::iterator i = playerBullets.begin(); i != playerBullets.end();){
        if ((*i)->Dead()){
            delete *i;
            i = playerBullets.erase(i);
        }
        else {
            (*i)->update();
            i++;
        }
    }
}
void BulletHandler::renderPlayerBullets(){
    for (int i = 0; i < playerBullets.size(); i++){
        playerBullets[i]->render();
    }
}

void BulletHandler::updateEnemyBullets(){
    for (vector<Bullet*>::iterator i = enemyBullets.begin(); i != enemyBullets.end();){
        if ((*i)->Dead()){
            delete *i;
            i = enemyBullets.erase(i);
        }
        else {
            (*i)->update();
            i++;
        }
    }
}
void BulletHandler::renderEnemyBullets(){
    for (int i = 0; i < enemyBullets.size(); i++){
        enemyBullets[i]->render();
    }
}

void BulletHandler::addPlayerBullet(int x, int y, float rot, string type, int energyBallSize){
    Bullet* b = new Bullet();
    if (type == "pistol" || type == "machinegun"){
        SoundHandler::getTheInstance()->playSound("gunshot", 0);
        b->load(x, y, BULLET_SIZE, BULLET_SIZE, BULLET_SPEED, rot, "playerbullet");
    }
    else if (type == "energygun"){
        SoundHandler::getTheInstance()->playSound("energyball", 0);
        b->load(x, y, 64, 64, BULLET_SPEED, rot, "playerenergyball"); // width and height must always be 64, so that the energy ball is drawn properly
        b->setDrawWidth(energyBallSize);
        b->setDrawHeight(energyBallSize);
    }
    else if (type == "rocketlauncher"){
        SoundHandler::getTheInstance()->playSound("missile", 0);
        b->load(x, y, MISSILE_WIDTH, MISSILE_HEIGHT, MISSILE_SPEED, rot, "playerrocket");
    }
    else if (type == "cannon"){
        SoundHandler::getTheInstance()->playSound("cannonball", 0);
        b->load(x, y, CANNONBALL_SIZE, CANNONBALL_SIZE, CANNONBALL_SPEED, rot, "playercannonball");
    }
    else if (type == "fistgun"){
        b->load(x, y, FIST_SIZE, FIST_SIZE, FIST_SPEED, rot, "playerfist");
    }
    else if (type == "dragongun"){
        b->load(x, y, 256, 64, 500, rot, "playerdragon");
        b->setHealth(3); // dragons can hit multiple enemies without disappearing
    }

    b->setCollisionLayers(collisionLayers);
    playerBullets.push_back(b);
}

void BulletHandler::addEnemyBullet(int x, int y, float rot, string type){
    Bullet* b = new Bullet();
    if (type == "bullet"){
        SoundHandler::getTheInstance()->playSound("gunshot", 0);
        b->load(x, y, BULLET_SIZE, BULLET_SIZE, BULLET_SPEED, rot, "enemybullet");
        b->setCollisionLayers(collisionLayers);
        enemyBullets.push_back(b);
    }
    else if (type == "manta_ray_stinger"){
        b->load(x, y, 64, 32, BULLET_SPEED, rot, "manta_ray_stinger", 30);
        b->setCollisionLayers(collisionLayers);
        enemyBullets.push_back(b);
    }
}
