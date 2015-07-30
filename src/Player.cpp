#include "Player.h"
#include "Camera.h"
#include "InputHandler.h"
#include <cmath>

#define pi 3.1415926535897932384626433832795

Player::Player(){
    speed = MIN_SPEED;
    spaceKeyDown = false;
    Camera::getTheInstance()->setTarget(this);
}

void Player::update(){

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
        }
        else if (rotation == 0){
            newX = (Game::getTheInstance()->getDeltaTime() * speed);
            newY = 0;
        }
        else if (rotation == 90){
            newX = 0;
            newY = (Game::getTheInstance()->getDeltaTime() * speed);
        }
        else if (rotation == -90){
            newX = 0;
            newY = -1 * (Game::getTheInstance()->getDeltaTime() * speed);
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



