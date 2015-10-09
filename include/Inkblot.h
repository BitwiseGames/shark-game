#ifndef INKBLOT_H
#define INKBLOT_H

#include "Explosion.h"
#include "TextureHandler.h"
#include "Game.h"
#include "Camera.h"

class Inkblot : public Explosion {
    public:
        Inkblot(){};
        void update(){
            timeRemaining--;
            if (timeRemaining <= 0){
                dead = true;
            }
        };

        void render(){
            SDL_Rect srcRect = {0, 0, width, height};
            SDL_Rect dstRect = {position.X() - Camera::getTheInstance()->getPosition().X(), position.Y() - Camera::getTheInstance()->getPosition().Y(), drawWidth, drawHeight};
            TextureHandler::getTheInstance()->renderScale(textureID, srcRect, dstRect, Game::getTheInstance()->getRenderer(), rotation);
        }

        void load(int x, int y, int w, int h, int time, string ID){
            position.setX(x);
            position.setY(y);
            width = w;
            height = h;
            textureID = ID;
            currentFrame = 1;
            currentRow = 1;
            drawWidth = width;
            drawHeight = height;
            timeRemaining = time;
            TextureHandler::getTheInstance()->load("Assets/Art/inkblot.png", textureID, Game::getTheInstance()->getRenderer());
        }

        void setDrawWidth(int dw)
        { drawWidth = dw; };
        void setDrawHeight(int dh)
        { drawHeight = dh; };

    private:
        int drawWidth; // these variables are necessary to resize the sprite
        int drawHeight;
        int timeRemaining;
};

#endif
