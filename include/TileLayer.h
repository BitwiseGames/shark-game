#ifndef TILELAYER_H
#define TILELAYER_H

#include <vector>
#include "Layer.h"
#include "Level.h"
#include "Vector2D.h"

using namespace std;

class TileLayer : public Layer {

  public:
    TileLayer(int, int, int, vector<Tileset>&);
    virtual ~TileLayer(){}
    virtual void update(Level*){};
    virtual void render();
    Tileset getTilesetByID(int);
    void setTileIDs(const vector<vector<int>>& IDs)
    { tileIDs = IDs; };
    void setTileSize(int ts)
    { tileSize = ts;};
    void setMapWidth(int mw)
    { mapWidth = mw; };
    void setPosition( Vector2D newPos )
    { position = newPos; };
    const Vector2D getPosition()
    { return position; };
    vector<vector<int>>& getTileIDs()
    { return tileIDs; };

  private:
    int numColumns;
    int numRows;
    int tileSize;
    int mapWidth;
    float diff;
    Vector2D position;
    Vector2D velocity;
    Vector2D acceleration;
    const vector<Tileset>& tilesets;
    const vector<vector<int>> tileIDs;

};

#endif
