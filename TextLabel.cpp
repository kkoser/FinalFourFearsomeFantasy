//
//  TextLabel.cpp
//  FinalFourFearsomeFantasy
//
//  Created by Kyle Koser on 4/22/14.
//  Copyright (c) 2014 Kyle Koser. All rights reserved.
//

#include "TextLabel.h"

TextLabel::TextLabel(int cx, int cy, string str, string fontName, int size, SDL_Renderer *ren) {
    x = cx;
    y = cy;
    text = str;
    renderer = ren;
    
    font = TTF_OpenFont(fontName.c_str(), size);
    if(font == NULL) printf("font fail: %s\n", TTF_GetError());
    textColor = {0,0,0};
}

TextLabel::~TextLabel() {
    texture.free();
    //TTF_CloseFont(font);
}

void TextLabel::draw(SDL_Renderer *ren) {
    //texture.loadFromRenderedText(text, textColor, ren, font);
    renderer = ren;
    draw();

}

void TextLabel::draw() {
    if (texture.getHeight() <= 0) {
        texture.loadFromRenderedText(text, textColor, renderer, font);
    }
    texture.render(renderer, x, y);
    
}

string TextLabel::getText() {
    return text;
}

void TextLabel::setText(string str) {
    text = str;
    texture.loadFromRenderedText(text, textColor, renderer, font);
}

int TextLabel::getX() {
    return x;
}

int TextLabel::getY() {
    return y;
}

void TextLabel::setX(int cx) {
    x = cx;
}

void TextLabel::setY(int cy) {
    y = cy;
}

SDL_Color TextLabel::getColor() {
    return textColor;
}

void TextLabel::setColor(SDL_Color col) {
    textColor = col;
    texture.loadFromRenderedText(text, textColor, renderer, font);
}

void TextLabel::setColor(Uint8 r, Uint8 g, Uint8 b) {
    setColor({r,g,b});
}

