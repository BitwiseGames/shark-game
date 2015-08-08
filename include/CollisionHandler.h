#ifndef COLLISIONHANDLER_H
#define COLLISIONHANDLER_H

#include <vector>

using namespace std;

class Player;
class GameObject;

class CollisionHandler {
    public:

        static CollisionHandler* getTheInstance();

        void update(Player*, vector<GameObject*>);
        void setPlayer(Player* p){ player = p;};
        Player* getPlayer(){ return player; };

    private:
        CollisionHandler(){};
        static CollisionHandler* theInstance;

        void PlayerBulletEnemyCollisions(vector<GameObject*>);
        void playerEnemyCollisions(Player*, vector<GameObject*>);

        Player* player;
};

#endif
