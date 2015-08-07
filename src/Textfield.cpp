#include "Textfield.h"
#include "Game.h"
#include "TextureHandler.h"

Textfield::Textfield(int x, int y, string Text, string fontFile, int fontSize, float rot, SDL_Color textColor) {
    position.setX(x);
    position.setY(y);
    text = Text;
    font = TTF_OpenFont(fontFile.c_str(), fontSize);
    fontColor = textColor;
}

void Textfield::render(){
    TextureHandler::getTheInstance()->renderText(position.X(), position.Y(), font, text, fontColor, Game::getTheInstance()->getRenderer());
}
