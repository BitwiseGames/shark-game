#ifndef LEVELPARSER_H
#define LEVELPARSER_H

#include <iostream>
#include <vector>
#include "tinyxml.h"

class Level;
class TileLayer;
class Layer;
struct Tileset;

using namespace std;

class LevelParser {
    public:
        Level* parseLevel(const char*);

    private:
        void parseTextures(TiXmlElement*);
        void parseTilesets(TiXmlElement*, vector<Tileset>*);
        void parseObjectLayer(TiXmlElement*, vector<Layer*>*, Level*);
        void parseTileLayer  (TiXmlElement*, vector<Layer*>*, vector<Tileset>*, vector<TileLayer*>*);

        int tileSize;
        int width;
        int height;
};

#endif
