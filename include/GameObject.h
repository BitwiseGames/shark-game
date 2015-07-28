#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <string>
#include <vector>
#include "Vector2D.h"

using namespace std;

class GameObject {
  public:
    virtual void update();
    virtual void render();

    virtual void load(int x, int y, int w, int h, int frames, int cID, int _health, int speed, string tID){
        position.setX(x);
        position.setY(y);
        width = w;
        height = h;
        numFrames = frames;
        callbackID = cID;
        health = _health;
        animSpeed = speed;
        textureID = tID;
    }

    virtual void setHealth(int newHealth){
      health = newHealth;
      if (health <= 0){
        dying = true;
      }
    }

    void setCollisionLayers(vector<Tilelayer*>* cLayers)
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
