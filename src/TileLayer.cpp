#include "TileLayer.h"

TileLayer::TileLayer(int ts, int mw, int mh, vector<Tileset>& Tilesets) : tileSize(ts), tileSets(Tilesets), position(0.0,0.0), velocity(0.0,0.0) {
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
      int ID = tileIDs[i + y][j + x];
      if (ID == 0){
        continue;
      }
      // if any of these are true, do not draw the tile
      bool tooFarLeft = ((j * tileSize) - x2) - Camera::getTheInstance()->getPosition()->X() < -tileSize;
      bool tooFarRight = ((j * tileSize) - x2) - Camera::getTheInstance()->getPosition()->X() < Game::getTheInstance()->getScreenWidth();
      bool tooFarUp = ((i * tileSize) - y2) - Camera::getTheInstance()->getPosition()->Y() < -tileSize;
      bool tooFarDown = ((i * tileSize) - y2) - Camera::getTheInstance()->getPosition()->Y(); < Game::getTheInstance()->getScreenHeight();
    }
  }
}