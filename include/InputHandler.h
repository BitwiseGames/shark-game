#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include "SDL.h"
#include <string>
#include <vector>
#include "Vector2D.h"

using namespace std;

enum button_states{
    LEFT = 0,
    MIDDLE = 1,
    RIGHT = 2
};

class InputHandler {
    public:
        ~InputHandler();
        static InputHandler* getTheInstance();

        void reset();
        void update();
        bool getKey(SDL_Scancode);
        bool getMouseState(int);
        int scrolling();
        Vector2D* getMousePosition();

    private:
        InputHandler();
        static InputHandler* theInstance;

        const Uint8* keyStates;
        vector<bool> mouseButtonStates;
        Vector2D* mousePosition;
        bool scrollDown = false;
        bool scrollUp = false;

        const int NUM_MOUSE_BUTTONS = 3; // SDL supports up to 255 mouse buttons


};

#endif
