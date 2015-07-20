#include "Camera.h"

Camera::Camera* theInstance = nullptr;

Camera* Camera::getTheInstance(){
  if (theInstance == nullptr){
    theInstance = new Camera();
  }
  return theInstance;
}

void Camera::update(){
  
}

Vector2D Camera::getPosition(){
  if (target != nullptr){
    int x = target->Position()->X() - (Game::getTheInstance()->getScreenWidth() / 2);
    int y = target->Position()->Y() - (Game::getTheInstance()->getScreenHeight() / 2);
    if (x < 0){
      x = 0;
    }
    if (y < 0){
      y = 0;
    }
    Vector2D pos = (x,y);
    return pos;
  }
  return position;
}