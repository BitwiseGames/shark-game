#ifndef SARDINESCHOOL_H
#define SARDINESCHOOL_H

#include "Enemy.h"
#include "GameObjectFactory.h"

class SardineSchool : public Enemy {
    public:
        SardineSchool(){};

};

class SardineSchoolCreator : public BaseCreator {
    GameObject* createGameObject() const {
        return new SardineSchool();
    }
};
#endif
