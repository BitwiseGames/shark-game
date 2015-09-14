#include "Flamethrower.h"
#include "InputHandler.h"
#include "CollisionHandler.h"
#include "Camera.h"
#include "Tests.h"
#include "Player.h"

void Flamethrower::load(int x, int y, int w, int h, int t, float rot, string ID){
    cout << "creating flamethrower" << endl;
    position.setX(x);
    position.setY(y);
    width = w;
    height = h;
    time = t;
    rotation = rot;
    textureID = ID;
    TextureHandler::getTheInstance()->load("Assets/Art/" + textureID + ".png", textureID, Game::getTheInstance()->getRenderer());

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
