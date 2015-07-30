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
    shotCoolDown = 0;
    maxCoolDown = 15;
    Camera::getTheInstance()->setTarget(this);
}

void Player::update(){

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

    // shooting bullets
    shotCoolDown--;
    if (InputHandler::getTheInstance()->getMouseState(LEFT)){
        if (shotCoolDown <= 0){
            shotCoolDown = maxCoolDown;
            int mouseX = InputHandler::getTheInstance()->getMousePosition()->X();
            int mouseY = InputHandler::getTheInstance()->getMousePosition()->Y();
            int px = position.X() + (collisionWidth / 2) - Camera::getTheInstance()->getPosition().X();
            int py = position.Y() + (collisionHeight / 2) - Camera::getTheInstance()->getPosition().Y();

            float degrees = Tests::angleBetween(px,py,mouseX,mouseY);

            BulletHandler::getTheInstance()->addPlayerBullet(position.X(), position.Y(),degrees);
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
            collisionWidth = 64;
            collisionHeight = 32;
        }
        else if (rotation == 0){
            newX = (Game::getTheInstance()->getDeltaTime() * speed);
            newY = 0;
            collisionWidth = 64;
            collisionHeight = 32;
        }
        else if (rotation == 90){
            newX = 0;
            newY = (Game::getTheInstance()->getDeltaTime() * speed);
            collisionWidth = 32;
            collisionHeight = 64;
        }
        else if (rotation == -90){
            newX = 0;
            newY = -1 * (Game::getTheInstance()->getDeltaTime() * speed);
            collisionWidth = 32;
            collisionHeight = 64;
        }

    Vector2D newPos = Vector2D(position.X() + newX, position.Y() + newY);
    if (!tileCollisions(newPos)){
        position.setX( position.X() + newX );
        position.setY( position.Y() + newY );
    }
}

/*void Player::render(){

    int drawX, drawY;
    drawX = (position.X() - Camera::getTheInstance()->getPosition().X());
    drawY = (position.Y() - Camera::getTheInstance()->getPosition().Y());
    SDL_Rect srcRect = {0, 0, width, height};
    SDL_Rect dstRect = {0, 0, 64, 32};
    TextureHandler::getTheInstance()->renderScale(textureID, srcRect, dstRect, Game::getTheInstance()->getRenderer(), rotation, alpha, flip);

}*/



