#include "Tests.h"
#include <cmath>

#define pi 3.1415926535897932384626433832795

float Tests::distanceBetween(int x1, int y1, int x2, int y2){
    int dx = x2 - x1;
    int dy = y2 - y1;
    return sqrt( (dx*dx) + (dy*dy));
}

float Tests::angleBetween(int x1, int y1, int x2, int y2){
    int dx = x2 - x1;
    int dy = y2 - y1;
    float angle = atan2(dy, dx);
    return 360 * (angle/(2*pi));
}

bool Tests::AABB(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2){
    if ((x1 <= x2 + w2) && (x1 + w1 >= x2)) {
        if ((y1 <= y2 + h2) && (y1 + h1 >= y2)) {
          return true;
        }
    }
    return false;
}
