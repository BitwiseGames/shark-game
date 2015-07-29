#include "Player.h"
#include "Camera.h"

Player::Player(){
    Camera::getTheInstance()->setTarget(this);
}

void Player::update(){

}
