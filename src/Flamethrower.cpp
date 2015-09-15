#include "Flamethrower.h"
#include "InputHandler.h"
#include "CollisionHandler.h"
#include "Camera.h"
#include "Tests.h"
#include "Player.h"

void Flamethrower::load(int x, int y, int w, int h, int t, float rot, string ID){
    position.setX(x);
    position.setY(y);
    width = w;
    height = h;
    time = t;
    rotation = rot;
    textureID = ID;
    TextureHandler::getTheInstance()->load("Assets/Art/" + textureID + ".png", textureID, Game::getTheInstance()->getRenderer());
}

void Flamethrower::render(){
    int drawX, drawY;
    drawX = (position.X() - Camera::getTheInstance()->getPosition().X());
    drawY = (position.Y() - Camera::getTheInstance()->getPosition().Y());                                                                    // rotation point
    TextureHandler::getTheInstance()->renderTexture(textureID, drawX, drawY, width, height, Game::getTheInstance()->getRenderer(), rotation, {0, height/2});
}

void Flamethrower::update(){
    //moves with the player
    int newX = CollisionHandler::getTheInstance()->getPlayer()->Position()->X();
    int newY = CollisionHandler::getTheInstance()->getPlayer()->Position()->Y();
    position.setX(newX);
    position.setY(newY);

    // rotate to face the mouse
    int mouseX = InputHandler::getTheInstance()->getMousePosition()->X();
    int mouseY = InputHandler::getTheInstance()->getMousePosition()->Y();
    float px = (newX - Game::getTheInstance()->getDeltaTime()) - Camera::getTheInstance()->getPosition().X();
    float py = (newY - Game::getTheInstance()->getDeltaTime()) - Camera::getTheInstance()->getPosition().Y();

    float degrees = Tests::angleBetween(px,py,mouseX,mouseY);
    rotation = degrees;
}
