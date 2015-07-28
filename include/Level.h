#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include <vector>
#include "Layer.h"
#include "Player.h"
#include "LevelParser.h"

using namespace std;

class TileLayer;

struct Tileset{
  int firstGridID;
  int numColumns;
  int tileHeight;
  int tileWidth;
  int spacing;
  int margin;
  int height;
  int width;
  string name;
};

class Level {
  public:
    ~Level();

    void update();
    void render();

    vector<Layer*>* getLayers()
    { return &layers; };
    vector<TileLayer*>* getCollisionLayers()
    { return &collisionLayers; };
    vector<Tileset>* getTilesets()
    { return &tilesets; };
    Player* getPlayer()
    { return player; };
    void setPlayer(Player* p)
    { player = p; };

  private:
    friend class LevelParser;
    Level(){};
    Player* player;
    vector<Layer*> layers;
    vector<Tileset> tilesets;
    vector<TileLayer*> collisionLayers;
};

#endif
