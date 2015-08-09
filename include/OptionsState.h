#ifndef OPTIONSSTATE_H
#define OPTIONSSTATE_H

#include <string>
#include <iostream>
#include "MenuState.h"
#include "GameObject.h"
#include "Textfield.h"

using namespace std;

class OptionsState : public MenuState {
    public:
        bool onEnter();
        bool onExit();

        void update();
        void render();

        virtual string getStateID() { return optionsID; };

    private:
        static const string optionsID;
        vector<GameObject*> gameObjects;
        void setCallbacks();

        static bool fullscreen;

        static const int NUM_RESOLUTIONS;
        static SDL_Point currentResolution;
        static SDL_Point resolutions[8];
        Textfield* curResolutionText;
        static int curResolutionIndex;

        static void closeOptions();
        static void increaseResolution();
        static void decreaseResolution();
        static void toggleFullscreen();
};

#endif
