#include "InputHandler.h"
#include "Game.h"

InputHandler* InputHandler::theInstance = nullptr;

InputHandler* InputHandler::getTheInstance(){

    if (theInstance == nullptr){
        theInstance = new InputHandler();
    }
    return theInstance;
}

InputHandler::InputHandler() : keyStates(0) {
    mousePosition = new Vector2D(0.0, 0.0);
    for (int i = 0; i < NUM_MOUSE_BUTTONS; i++){
        mouseButtonStates.push_back(false);
    }
}

InputHandler::~InputHandler(){
    delete keyStates;
    delete mousePosition;
    mouseButtonStates.clear();
}

void InputHandler::reset(){
    for (int i = 0; i < NUM_MOUSE_BUTTONS; i++){
        mouseButtonStates[i] = false;
    }
}

void InputHandler::update(){
    // reset the value every frame
    scrollDirection = 0;
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type){
    case SDL_QUIT:
        Game::getTheInstance()->getStateHandler()->popState();
        Game::getTheInstance()->quitGame();
        break;
    case SDL_MOUSEBUTTONDOWN:
        if (event.button.button == SDL_BUTTON_LEFT){
            mouseButtonStates[LEFT] = true;
            break;
        }
        else if (event.button.button == SDL_BUTTON_RIGHT){
            mouseButtonStates[RIGHT] = true;
            break;
        }
        else if (event.button.button == SDL_BUTTON_MIDDLE){
            mouseButtonStates[MIDDLE] = true;
            break;
        }
    case SDL_MOUSEBUTTONUP:
        if (event.button.button == SDL_BUTTON_LEFT){
            mouseButtonStates[LEFT] = false;
            break;
        }
        else if (event.button.button == SDL_BUTTON_RIGHT){
            mouseButtonStates[RIGHT] = false;
            break;
        }
        else if (event.button.button == SDL_BUTTON_MIDDLE){
            mouseButtonStates[MIDDLE] = false;
            break;
        }
    case SDL_MOUSEWHEEL:
        scrollDirection = event.wheel.y;
        break;
    case SDL_MOUSEMOTION:
        mousePosition->setX(event.motion.x);
        mousePosition->setY(event.motion.y);
        break;
    case SDL_KEYDOWN:
        keyStates = SDL_GetKeyboardState(NULL);
        break;
    case SDL_KEYUP:
        keyStates = SDL_GetKeyboardState(NULL);
        break;
    }
}

bool InputHandler::getKey(SDL_Scancode key){
    if (keyStates != nullptr){
        if (keyStates[key] == 1){
            return true;
        }
    }
    return false;
}

bool InputHandler::getMouseState(int mouseButton){
    return (mouseButtonStates[mouseButton] == true);
}

int InputHandler::scrolling(){
    return scrollDirection;
}

Vector2D* InputHandler::getMousePosition(){
    return mousePosition;
}

