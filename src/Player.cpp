#include "Player.h"
#include "Camera.h"
#include "InputHandler.h"
#include "BulletHandler.h"
#include "Tests.h"
#include <cmath>

#define pi 3.1415926535897932384626433832795

Player::Player(){
    speed = MIN_SPEED;
    spaceKeyDown = false;
    currentWeapon = "pistol";
    laserCharge = 0;
    shotCoolDown = 0;
    maxCoolDown = 15;
    Camera::getTheInstance()->setTarget(this);
    type = "Player";
}

void Player::update(){

    //update animation
    currentFrame = int(((SDL_GetTicks() / (1000 / animSpeed)) % numFrames));


    // changing speeds
    if (InputHandler::getTheInstance()->getKey(SDL_SCANCODE_SPACE)){
        if (!spaceKeyDown){
            spaceKeyDown = true;
            speed *= SPEED_CHANGER;
            if (speed > (MIN_SPEED * SPEED_CHANGER * MAX_SPEEDS)){
                speed = MIN_SPEED;
            }
        }
    }
    else {
        spaceKeyDown = false;
    }

    // switching weapons
    if (InputHandler::getTheInstance()->getKey(SDL_SCANCODE_1)){ // ordinary gun
        currentWeapon = "pistol";
        maxCoolDown = 15;
    }
    else if (InputHandler::getTheInstance()->getKey(SDL_SCANCODE_2)){ // machine gun
        currentWeapon = "machinegun";
        maxCoolDown = 5;
    }
    else if (InputHandler::getTheInstance()->getKey(SDL_SCANCODE_3)){
        currentWeapon = "energygun";
    }
    else if (InputHandler::getTheInstance()->getKey(SDL_SCANCODE_4)){
        currentWeapon = "rocketlauncher";
        maxCoolDown = 60;
    }

    // shooting bullets
    shotCoolDown--;
    if (currentWeapon == "machinegun" || currentWeapon == "pistol"){
        if (InputHandler::getTheInstance()->getMouseState(LEFT)){
            if (shotCoolDown <= 0){
                shotCoolDown = maxCoolDown;
                shoot("bullet");
            }
        }
    }
    // shooting the energy ball gun
    else if (currentWeapon == "energygun"){
        if (InputHandler::getTheInstance()->getMouseState(LEFT)){
            laserCharge++;
        }
        else {
            if (laserCharge > 0){ // we've charged, then let go, so shoot
                shoot("energyball");
                laserCharge = 0;
            }
        }
    }
    // shooting rockets
    else if (currentWeapon == "rocketlauncher"){
        if (InputHandler::getTheInstance()->getMouseState(LEFT)){
            if (shotCoolDown <= 0){
                shotCoolDown = maxCoolDown;
                shoot("rocket");
            }
        }
    }

    // moving
    if (InputHandler::getTheInstance()->getKey(SDL_SCANCODE_A) || InputHandler::getTheInstance()->getKey(SDL_SCANCODE_LEFT)){
        rotation = 180;
        flip = SDL_FLIP_VERTICAL;
    }
    else if (InputHandler::getTheInstance()->getKey(SDL_SCANCODE_D) || InputHandler::getTheInstance()->getKey(SDL_SCANCODE_RIGHT)){
        rotation = 0;
        flip = SDL_FLIP_NONE;
    }
    if (InputHandler::getTheInstance()->getKey(SDL_SCANCODE_S) || InputHandler::getTheInstance()->getKey(SDL_SCANCODE_DOWN)){
        rotation = 90;
    }
    else if (InputHandler::getTheInstance()->getKey(SDL_SCANCODE_W) || InputHandler::getTheInstance()->getKey(SDL_SCANCODE_UP)){
        rotation = -90;
    }

    float newX, newY;
    if (rotation == 180){
        newX = -1 * (Game::getTheInstance()->getDeltaTime() * speed);
        newY = 0;
        collisionWidth = 60;
        collisionHeight = 30;
    }
    else if (rotation == 0){
        newX = (Game::getTheInstance()->getDeltaTime() * speed);
        newY = 0;
        collisionWidth = 60;
        collisionHeight = 30;
    }
    else if (rotation == 90){
        newX = 0;
        newY = (Game::getTheInstance()->getDeltaTime() * speed);
        collisionWidth = 30;
        collisionHeight = 60;
    }
    else if (rotation == -90){
        newX = 0;
        newY = -1 * (Game::getTheInstance()->getDeltaTime() * speed);
        collisionWidth = 30;
        collisionHeight = 60;
    }

    Vector2D newPos = Vector2D(position.X() + newX, position.Y() + newY);
    if (!tileCollisions(newPos)){
        position.setX( position.X() + newX );
        position.setY( position.Y() + newY );
    }
}

void Player::shoot(string type){
    int mouseX = InputHandler::getTheInstance()->getMousePosition()->X();
    int mouseY = InputHandler::getTheInstance()->getMousePosition()->Y();
    float px = (position.X() - Game::getTheInstance()->getDeltaTime() * speed) - Camera::getTheInstance()->getPosition().X();
    float py = (position.Y() - Game::getTheInstance()->getDeltaTime() * speed) - Camera::getTheInstance()->getPosition().Y();

    float degrees = Tests::angleBetween(px,py,mouseX,mouseY);
    px += Camera::getTheInstance()->getPosition().X();
    py += Camera::getTheInstance()->getPosition().Y();

    BulletHandler::getTheInstance()->addPlayerBullet(px, py, degrees, type, laserCharge);
}
