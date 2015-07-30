#include "CollisionHandler.h"

CollisionHandler* CollisionHandler::theInstance = nullptr;

CollisionHandler* CollisionHandler::getTheInstance(){
    if (theInstance == nullptr){
        theInstance = new CollisionHandler();
    }
    return theInstance;
}
