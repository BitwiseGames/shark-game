#ifndef COLLISIONHANDLER_H
#define COLLISIONHANDLER_H


class CollisionHandler {
    public:

        static CollisionHandler* getTheInstance();

        void update();

    private:
        CollisionHandler(){};
        static CollisionHandler* theInstance;
};

#endif
