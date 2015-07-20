#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

class GameObject {
  public:
    virtual void update();
    virtual void render();

    int Width()
    { return width; };
    int Height()
    { return height; };
    int Health()
    { return health; };
    bool Dying()
    { return dying; };
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
    int health;
    bool dying;
    Vector2D position = Vector2D(0,0);
};

#endif