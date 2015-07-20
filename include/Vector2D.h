#ifndef VECTOR2D
#define VECTOR2D

class Vector2D{
  public:
    Vector2D(float X, float Y){
      x = X;
      y = Y;
    }

    void setX(float newX)
    { x = newX; };
    void setY(float newY)
    { x = newY; };

    float X()
    { return x; };
    float Y()
    { return y; };

  private:
    float x;
    float y;

};

#endif