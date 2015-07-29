#include "Player.h"
#include "Camera.h"
#include "TextureHandler.h"

Player::Player(){
    Camera::getTheInstance()->setTarget(this);
}

void Player::update(){

}
