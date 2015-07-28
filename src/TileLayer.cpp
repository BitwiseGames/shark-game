#include "TileLayer.h"
#include "Camera.h"

TileLayer::TileLayer(int ts, int mw, int mh, vector<Tileset>& Tilesets) : tileSize(ts), tilesets(Tilesets), position(0.0,0.0), velocity(0.0,0.0) {
  numColumns = mh;
  numRows = mw;
  mapWidth = mw;
}

void TileLayer::render(){
  int x1, y1, x2, y2 = 0;
  x1 = position.X() / tileSize;
  y1 = position.Y() / tileSize;
  x2 = int(position.X()) % tileSize;
  y2 = int(position.Y()) % tileSize;

  for (int i = 0; i < numRows; i++){
    for (int j = 0; j < numColumns; j++){
      int ID = tileIDs[i + y1][j + x1];
      if (ID == 0){
        continue;
      }
      // if any of these are true, do not draw the tile
      bool tooFarLeft = ((j * tileSize) - x2) - Camera::getTheInstance()->getPosition().X() < -tileSize;
      bool tooFarRight = ((j * tileSize) - x2) - Camera::getTheInstance()->getPosition().X() < Game::getTheInstance()->getScreenWidth();
      bool tooFarUp = ((i * tileSize) - y2) - Camera::getTheInstance()->getPosition().Y() < -tileSize;
      bool tooFarDown = ((i * tileSize) - y2) - Camera::getTheInstance()->getPosition().Y() < Game::getTheInstance()->getScreenHeight();

      if (tooFarLeft || tooFarRight || tooFarUp || tooFarDown){
        continue;
      }

      Tileset tileset = getTilesetByID(ID);
      ID--;

      //TextureHandler::getTheInstance()->drawTile();

    }
  }
}

Tileset TileLayer::getTilesetByID(int tileID){
  for (int i = 0; i < tilesets.size(); i++){
    if (i + 1 <= tilesets.size() - 1){
      if (tileID <= tilesets[i].firstGridID && tileID < tilesets[i + 1].firstGridID){
        return tilesets[i];
      }
    }
    else {
      return tilesets[i];
    }
  }
  cout << "Could not find tilset, returning blank tileset." << endl;
  Tileset tileset;
  return tileset;
}
