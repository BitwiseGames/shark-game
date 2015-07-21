#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

class GameObject {
  public:
    virtual void update();
    virtual void render();

    virtual void load(int x, int y, int w, int h, int frames, int cID, int health, string tID){
        position.setX(x);
        position.setY(y);
        width = w;
        height = h;
        numFrames = frames;
        callbackID = cID;
        textureID = tID;
    }

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
    Vector2D& Position()
    { return position; };

    virtual void setHealth(int newHealth){
      health = newHealth;
      if (health <= 0){
        dying = true;
      }
    }

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
};

#endif