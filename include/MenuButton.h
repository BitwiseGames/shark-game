#ifndef MENUBUTTON_H
#define MENUBUTTON_H

#include "GameObject.h"
#include "GameObjectFactory.h"

class MenuButton : public GameObject {

  public:
    MenuButton(){};
    ~MenuButton(){};
    void update();
    void render();
  private:
    void (*callback)();

};

class MenuButtonCreator : public BaseCreator {
  GameObject* createGameObject() const {
    return new MenuButton();
  }
};

#endif
