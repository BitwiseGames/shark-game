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
    weapons[0] = "pistol";
    weapons[1] = "machinegun";
    weapons[2] = "energygun";
    weapons[3] = "rocketlauncher";
    weapons[4] = "fistgun";
    weapons[5] = "cannon";
    weapons[6] = "dragongun";
    weaponCooldowns[0] = 15;
    weaponCooldowns[1] = 5;
    weaponCooldowns[2] = 0;
    weaponCooldowns[3] = 60;
    weaponCooldowns[4] = 30;
    weaponCooldowns[5] = 90;
    weaponCooldowns[6] = 120;
    currentWeapon = weapons[weaponIndex];
    maxCoolDown = weaponCooldowns[weaponIndex];
    shotCoolDown = 0;
    laserCharge = 0;
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
    else if (InputHandler::getTheInstance()->getKey(SDL_SCANCODE_5)){
        currentWeapon = "fistgun";
        maxCoolDown = 30;
    }
    else if (InputHandler::getTheInstance()->getKey(SDL_SCANCODE_6)){
        currentWeapon = "cannon";
        maxCoolDown = 90;
    }
    else if (InputHandler::getTheInstance()->getKey(SDL_SCANCODE_7)){
        currentWeapon = "dragongun";
        maxCoolDown = 120;
    }

    /*if (InputHandler::getTheInstance()->scrolling() == "down"){
        weaponIndex--;
        if (weaponIndex < 0){
            weaponIndex = 6;
        }
        currentWeapon = weapons[weaponIndex];
        maxCoolDown = weaponCooldowns[weaponIndex];
    }
    else if (InputHandler::getTheInstance()->scrolling() == "up"){
        weaponIndex++;
        if (weaponIndex > 6){
            weaponIndex = 0;
        }
        currentWeapon = weapons[weaponIndex];
        maxCoolDown = weaponCooldowns[weaponIndex];
    }
*/

    shotCoolDown--;                                                             // energy gun has to be checked separately
    if (InputHandler::getTheInstance()->getMouseState(LEFT) && currentWeapon != "energygun"){
        if (shotCoolDown <= 0){
            shotCoolDown = maxCoolDown;
            shoot();
        }
    }

    // shooting the energy ball gun, this has to be checked separately
    if (currentWeapon == "energygun"){
        if (InputHandler::getTheInstance()->getMouseState(LEFT)){
            laserCharge++;
        }
        else {
            if (laserCharge > 0){ // we've charged, then let go, so shoot
                shoot();
                laserCharge = 0;
            }
        }
    }

    // moving
    if (InputHandler::getTheInstance()->getKey(SDL_SCANCODE_A) || InputHandler::getTheInstance()->getKey(SDL_SCANCODE_LEFT)){
        rotation = 180;
        flip = SDL_FLIP_VERTICAL;
        collisionWidth = 32;
        collisionHeight = 32;
    }
    else if (InputHandler::getTheInstance()->getKey(SDL_SCANCODE_D) || InputHandler::getTheInstance()->getKey(SDL_SCANCODE_RIGHT)){
        rotation = 0;
        flip = SDL_FLIP_NONE;
        collisionWidth = 32;
        collisionHeight = 32;
    }
    if (InputHandler::getTheInstance()->getKey(SDL_SCANCODE_S) || InputHandler::getTheInstance()->getKey(SDL_SCANCODE_DOWN)){
        rotation = 90;
        collisionWidth = 32;
        collisionHeight = 32;
    }
    else if (InputHandler::getTheInstance()->getKey(SDL_SCANCODE_W) || InputHandler::getTheInstance()->getKey(SDL_SCANCODE_UP)){
        rotation = -90;
        collisionWidth = 32;
        collisionHeight = 32;
    }


    float newX = cos(rotation / 180 * pi) * speed * Game::getTheInstance()->getDeltaTime();
    float newY = sin(rotation / 180 * pi) * speed * Game::getTheInstance()->getDeltaTime();

    Vector2D newPos = Vector2D(position.X() + newX, position.Y() + newY);
    if (!tileCollisions(newPos)){
        position.setX( position.X() + newX );
        position.setY( position.Y() + newY );
    }
}

void Player::shoot(){
    int mouseX = InputHandler::getTheInstance()->getMousePosition()->X();
    int mouseY = InputHandler::getTheInstance()->getMousePosition()->Y();
    float px = (position.X() - Game::getTheInstance()->getDeltaTime() * speed) - Camera::getTheInstance()->getPosition().X();
    float py = (position.Y() - Game::getTheInstance()->getDeltaTime() * speed) - Camera::getTheInstance()->getPosition().Y();

    float degrees = Tests::angleBetween(px,py,mouseX,mouseY);
    px += Camera::getTheInstance()->getPosition().X();
    py += Camera::getTheInstance()->getPosition().Y();

    BulletHandler::getTheInstance()->addPlayerBullet(px, py, degrees, currentWeapon, laserCharge);
}
