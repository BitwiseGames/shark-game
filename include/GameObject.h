#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <string>
#include <vector>
#include "Vector2D.h"

using namespace std;

class Camera;
class TextureHandler;
class TileLayer;
class GameObject {
  public:

    virtual void update(){}; // this gets overridden
    virtual void render();   // this gets overridden, but only sometimes

    virtual void load(int, int, int, int, int, int, int, int, string);

    virtual void setHealth(int newHealth){
      health = newHealth;
      if (health <= 0){
        dying = true;
      }
    }

    void setCollisionLayers(vector<TileLayer*>* cLayers)
    { collisionLayers = cLayers; };

    int Width()
    { return width; };
    int Height()
    { return height; };
    int Health()
    { return health; };
    bool Dying()
    { return dying; };
    bool Dead()
    { return dead; };
    Vector2D* Position()
    { return &position; };

  protected:
    int width;
    int height;
    int numFrames;
    int animSpeed;
    int callbackID;
    int health;
    string textureID;
    bool dying = false;
    bool dead = false;
    Vector2D position = Vector2D(0,0);
    vector<TileLayer*>* collisionLayers;
};

#endif
