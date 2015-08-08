#include "BulletHandler.h"
#include "SoundHandler.h"

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

void BulletHandler::addPlayerBullet(int x, int y, float rot){
    SoundHandler::getTheInstance()->playSound("gunshot", 0);
    Bullet* b = new Bullet();
    b->load(x, y, BULLET_SIZE, BULLET_SIZE, BULLET_SPEED, rot, "playerbullet");
    b->setCollisionLayers(collisionLayers);
    playerBullets.push_back(b);
}

void BulletHandler::addEnemyBullet(int x, int y, float rot){
    SoundHandler::getTheInstance()->playSound("gunshot", 0);
    Bullet* b = new Bullet();
    b->load(x, y, BULLET_SIZE, BULLET_SIZE, BULLET_SPEED, rot, "enemybullet");
    b->setCollisionLayers(collisionLayers);
    enemyBullets.push_back(b);
}
