#ifndef PAUSESTATE_H
#define PAUSESTATE_H

#include <string>
#include <vector>
#include <iostream>
#include "MenuState.h"
#include "MenuButton.h"
#include "GameObject.h"

using namespace std;

class GameObject;

class PauseState : public MenuState {
    public:
        virtual ~PauseState(){};
        void update();
        void render();

        bool onEnter();
        bool onExit();

        virtual string getStateID() { return pauseID; };

    private:
        void setCallbacks();
        vector<GameObject*> gameObjects;
        MenuButton* mainmenuButton;
        static const string pauseID;
        static void quitGame();
        static void resumeGame();
        static void gotoMainMenu();
};

#endif
