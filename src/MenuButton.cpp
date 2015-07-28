#include "MenuButton.h"
#include "InputHandler.h"
#include "TextureHandler.h"
#include "Game.h"

void MenuButton::update(){
    int mouseX = InputHandler::getTheInstance()->getMousePosition()->X();
    int mouseY = InputHandler::getTheInstance()->getMousePosition()->Y();

    if (mouseX > position.X() && mouseX < position.X() + width){
        if (mouseY > position.Y() && mouseY < position.Y() + height){
            currentRow = MOUSE_OVER;
            if (InputHandler::getTheInstance()->getMouseState(LEFT)){ // pressing the left mouse button
                currentRow = MOUSE_CLICKED;
                mouseButtonDown = true;
            }
        }
    }
    else {
        currentRow = MOUSE_OUT;
    }
}

void MenuButton::render(){
    TextureHandler::getTheInstance()->renderTexture(textureID, position.X(), position.Y(), width, height, Game::getTheInstance()->getRenderer());
    //TextureHandler::getTheInstance()->renderFrame(textureID, position.X(), position.Y(), width, height, currentRow, currentFrame, Game::getTheInstance()->getRenderer());
}
