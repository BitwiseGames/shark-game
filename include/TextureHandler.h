#ifndef TEXTUREHANDLER_H
#define TEXTUREHANDLER_H

#include <iostream>
#include <string>
#include <map>
#include "SDL.h"

using namespace std;

class TextureHandler {

    public:
        static TextureHandler* getTheInstance();
        bool load(string, string, SDL_Renderer*);
        void clearTextureMap();
        void removeFromTextureMap(string);
        void renderTexture(string, int, int, int, int, SDL_Renderer*, SDL_RendererFlip = SDL_FLIP_NONE);
        void renderScale(string, SDL_Rect, SDL_Rect, SDL_Renderer*, double, int, SDL_RendererFlip = SDL_FLIP_NONE);
        void renderFrame(string, int, int, int, int, int, int, SDL_Renderer*, double = 0.0, int = 255, SDL_RendererFlip = SDL_FLIP_NONE);
        void renderTile(string, int, int, int, int, int, int, int, int, SDL_Renderer*);

    private:
        TextureHandler(){};
        ~TextureHandler(){};

        map<string, SDL_Texture*> textureMap;

        static TextureHandler* theInstance;
};

#endif
