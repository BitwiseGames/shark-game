#ifndef OPTIONSSTATE_H
#define OPTIONSSTATE_H

#include <string>
#include <iostream>
#include "MenuState.h"
#include "GameObject.h"

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
        static void closeOptions();
};

#endif
