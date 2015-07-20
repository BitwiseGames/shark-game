#ifndef LAYER_H
#define LAYER_H

class Level;

class Layer {
  virtual ~Layer(){};

  virtual void update(Level* level)=0;
  virtual void render()=0;
};

#endif