#ifndef CAMERA_H
#define CAMERA_H

class Camera {
  public:

    void update();

    Camera* getTheInstance();

    Vector2D getPosition();

    void setTarget(GameObject* t){
      target = t;
    }

  private:
    Camera();
    static Camera* theInstance;
    Vector2D position = Vector2D(0,0);
    GameObject* target; // the object that the camera follows, usually the player
};

#endif