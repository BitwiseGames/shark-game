#include "MenuButton.h"
#include "InputHandler.h"
#include "TextureHandler.h"
#include "Game.h"

void MenuButton::update(){
    int mouseX = InputHandler::getTheInstance()->getMousePosition()->X();
    int mouseY = InputHandler::getTheInstance()->getMousePosition()->Y();

    if (mouseX > position.X() && mouseX < (position.X() + width) && mouseY > position.Y() && mouseY < (position.Y() + height)){
        if (InputHandler::getTheInstance()->getMouseState(LEFT) && !mouseButtonDown){ // pressing the left mouse button
            currentFrame = MOUSE_CLICKED;
            callback();
            mouseButtonDown = true;
        }
        else if (!InputHandler::getTheInstance()->getMouseState(LEFT)){
            mouseButtonDown = false;
            currentFrame = MOUSE_OVER;
        }
    }
    else {
        currentFrame = MOUSE_OUT;
    }
}

void MenuButton::render(){
    TextureHandler::getTheInstance()->renderFrame(textureID, position.X(), position.Y(), width, height, currentRow, currentFrame, Game::getTheInstance()->getRenderer());
}
