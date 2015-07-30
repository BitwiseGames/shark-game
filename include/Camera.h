#ifndef CAMERA_H
#define CAMERA_H

#include "Vector2D.h"
#include "GameObject.h"
#include "Game.h"

class Camera {
  public:

    void update(Vector2D);

    static Camera* getTheInstance();

    Vector2D getPosition();

    void setTarget(GameObject* t){
      target = t;
    }

  private:
    Camera();
    static Camera* theInstance;
    Vector2D position;
    GameObject* target; // the object that the camera follows, usually the player
};

#endif
