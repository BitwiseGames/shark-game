#ifndef MENUBUTTON_H
#define MENUBUTTON_H

#include "GameObject.h"
#include "GameObjectFactory.h"

class MenuButton : public GameObject {

  public:
    MenuButton(){ mouseButtonDown = false;};
    ~MenuButton(){};
    void update();
    void render();
    void setCallback(void(*callBack)()) { callback = callBack;};
    int getCallbackID() { return callbackID; };
  private:
    void (*callback)();
    bool mouseButtonDown;
    enum button_state{
        MOUSE_OUT = 0,
        MOUSE_OVER = 1,
        MOUSE_CLICKED = 2
    };

};

class MenuButtonCreator : public BaseCreator {
  GameObject* createGameObject() const {
    return new MenuButton();
  }
};

#endif
