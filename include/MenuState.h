#ifndef MENUSTATE_H
#define MENUSTATE_H

#include <vector>
#include "Callback.h"
#include "GameState.h"

class MenuState : public GameState {

  public:
    virtual ~MenuState(){};
  protected:
    typedef void(*Callback)();
    std::vector <Callback> callbacks;
};

#endif
