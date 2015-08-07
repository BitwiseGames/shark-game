#ifndef TEXTFIELD_H
#define TEXTFIELD_H

#include "GameObject.h"
#include "SDL_ttf.h"

class Textfield : public GameObject{
    public:
        Textfield(int, int, string, string, int = 12, float = 0.0, SDL_Color={0,0,0,255});
        void render();

    private:
        string text;
        TTF_Font* font;
        SDL_Color fontColor;
};

#endif
