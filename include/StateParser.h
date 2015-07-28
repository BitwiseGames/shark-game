#ifndef STATEPARSER_H
#define STATEPARSER_H

#include "tinyxml.h"
#include <string>
#include <vector>
using namespace std;

class GameObject;
class StateParser{

  public:
    StateParser(){};
    ~StateParser(){};

    bool parseState(const char*, string, vector<GameObject*>*, vector<string>*);

  private:
    void parseObjects(TiXmlElement*, vector<GameObject*>*);
    void parseTextures(TiXmlElement*, vector<string>*);

};

#endif
