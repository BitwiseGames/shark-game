#include <string>
#include "LevelParser.h"
#include "Game.h"
#include "TextureHandler.h"
#include "ObjectLayer.h"
#include "TileLayer.h"
#include "GameObjectFactory.h"
#include "zlib.h"
#include "base64.h"
#include "Level.h"

Level* LevelParser::parseLevel(const char* levelFile){

    // create a tixml document and load the map file
    TiXmlDocument levelDoc;
    levelDoc.LoadFile(levelFile);

    Level* level = new Level();

    TiXmlElement* root = levelDoc.RootElement();

    root->Attribute("tileSize", &tileSize);
    root->Attribute("width", &width);
    root->Attribute("height", &height);

    TiXmlElement* properties = root->FirstChildElement();

    // parse the textures needed for this level
    for(TiXmlElement* e = properties->FirstChildElement(); e != NULL; e = e->NextSiblingElement()){
        if(e->Value() == string("property")){
            parseTextures(e);
        }
    }

    // parse the tilesets
    for(TiXmlElement* e = root->FirstChildElement(); e != NULL; e = e->NextSiblingElement()){
        if(e->Value() == string("tileset")){
            parseTilesets(e, level->getTilesets());
        }
    }

    // parse any object layers
    for(TiXmlElement* e = root->FirstChildElement(); e != NULL; e = e->NextSiblingElement()){
        if(e->Value() == string("objectgroup") || e->Value() == string("layer")){
            if(e->FirstChildElement()->Value() == string("object")){
                parseObjectLayer(e, level->getLayers(), level);
            }
            else if(e->FirstChildElement()->Value() == string("data") || (e->FirstChildElement()->NextSiblingElement() != 0 && e->FirstChildElement()->NextSiblingElement()->Value() == string("data"))){
                parseTileLayer(e, level->getLayers(), level->getTilesets(), level->getCollisionLayers());
            }
        }
    }

    return level;
}


void LevelParser::parseTextures(TiXmlElement* textureRoot){
    TextureHandler::getTheInstance()->load(textureRoot->Attribute("value"), textureRoot->Attribute("name"), Game::getTheInstance()->getRenderer());
}

void LevelParser::parseTilesets(TiXmlElement* tilesetRoot, vector<Tileset>* tilesets){

    TextureHandler::getTheInstance()->load(tilesetRoot->FirstChildElement()->Attribute("source"), tilesetRoot->Attribute("name"), Game::getTheInstance()->getRenderer());

    // create a tileset object
    Tileset tileset;
    tilesetRoot->FirstChildElement()->Attribute("width", &tileset.width);
    tilesetRoot->FirstChildElement()->Attribute("height", &tileset.height);
    tilesetRoot->Attribute("firstgid", &tileset.firstGridID);
    tilesetRoot->Attribute("tilewidth", &tileset.tileWidth);
    tilesetRoot->Attribute("tileheight", &tileset.tileHeight);
    tilesetRoot->Attribute("spacing", &tileset.spacing);
    tilesetRoot->Attribute("margin", &tileset.margin);
    tileset.name = tilesetRoot->Attribute("name");

    tileset.numColumns = tileset.width / (tileset.tileWidth + tileset.spacing);

    tilesets->push_back(tileset);
}

void LevelParser::parseObjectLayer(TiXmlElement* objectElement, vector<Layer*> *layers, Level* level) {

    ObjectLayer* objectLayer = new ObjectLayer();

    for(TiXmlElement* e = objectElement->FirstChildElement(); e != NULL; e = e->NextSiblingElement()){
        if(e->Value() == string("object")) {
            int x, y, width, height, numFrames, health, callbackID = 0, animSpeed = 0;
            string textureID;
            string type;

            // get the initial node values type, x and y
            e->Attribute("x", &x);
            e->Attribute("y", &y);

            type = e->Attribute("type");
            GameObject* gameObject = GameObjectFactory::getTheInstance()->create(type);

            // get the property values
            for(TiXmlElement* properties = e->FirstChildElement(); properties != NULL; properties = properties->NextSiblingElement()) {
                if(properties->Value() == string("properties")){
                    for(TiXmlElement* property = properties->FirstChildElement(); property != NULL; property = property->NextSiblingElement()){
                        if(property->Value() == string("property")){
                            if(property->Attribute("name") == string("numFrames")){
                                property->Attribute("value", &numFrames);
                            }
                            else if(property->Attribute("name") == string("health")){
                                property->Attribute("value", &health);
                            }
                            else if(property->Attribute("name") == string("height")){
                                property->Attribute("value", &height);
                            }
                            else if(property->Attribute("name") == string("textureID")){
                                textureID = property->Attribute("value");
                            }
                            else if(property->Attribute("name") == string("width")){
                                property->Attribute("value", &width);
                            }
                            else if(property->Attribute("name") == string("callbackID")){
                                property->Attribute("value", &callbackID);
                            }
                            else if(e->Attribute("name") == string("animSpeed")){
                                property->Attribute("value", &animSpeed);
                            }
                        }
                    }
                }
            }
            // load the object
            gameObject->load(x, y, width, height, numFrames, callbackID, health, animSpeed, textureID);
            // set the collision layers
            //gameObject->setCollisionLayers(level->getCollisionLayers());

            if(type == "Player"){
               level->setPlayer(dynamic_cast<Player*>(gameObject));
            }

            objectLayer->getGameObjects()->push_back(gameObject);
        }
    }

    layers->push_back(objectLayer);
}


void LevelParser::parseTileLayer(TiXmlElement* tileElement, vector<Layer*>* layers, vector<Tileset>* tilesets, vector<TileLayer*>* collisionLayers) {
    TileLayer* tileLayer = new TileLayer(tileSize, width, height, *tilesets);

    bool collidable = false;

    // tile data
    vector<vector<int>> data;

    string decodedIDs;
    TiXmlElement* dataNode;

    for(TiXmlElement* e = tileElement->FirstChildElement(); e != NULL; e = e->NextSiblingElement()){
        if(e->Value() == string("properties")){
            for(TiXmlElement* property = e->FirstChildElement(); property != NULL; property = property->NextSiblingElement()){
                if(property->Value() == string("property")){
                    if(property->Attribute("name") == string("collidable")){
                        collidable = true;
                    }
                }
            }
        }

        if(e->Value() == string("data")){
            dataNode = e;
        }
    }

    for(TiXmlNode* e = dataNode->FirstChild(); e != NULL; e = e->NextSibling()){
        TiXmlText* text = e->ToText();
        string t = text->Value();
        decodedIDs = base64_decode(t);
    }

    // uncompress zlib compression
    uLongf sizeOfIDs = width * height * sizeof(int);
    vector<int> ids(width * height);
    uncompress((Bytef*)&ids[0], &sizeOfIDs,(const Bytef*)decodedIDs.c_str(), decodedIDs.size());

    vector<int> layerRow(width);

    for(int i = 0; i < height; i++){
        data.push_back(layerRow);
    }

    for(int rows = 0; rows < height; rows++){
        for(int cols = 0; cols < width; cols++){
            data[rows][cols] = ids[rows * width + cols];
        }
    }

    tileLayer->setTileIDs(data);

    if(collidable) {
        collisionLayers->push_back(tileLayer);
    }

    layers->push_back(tileLayer);
}
