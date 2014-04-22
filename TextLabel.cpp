//
//  TextLabel.cpp
//  FinalFourFearsomeFantasy
//
//  Created by Kyle Koser on 4/22/14.
//  Copyright (c) 2014 Kyle Koser. All rights reserved.
//

#include "TextLabel.h"

TextLabel::TextLabel(int cx, int cy, string str, string fontName, int size) {
    x = cx;
    y = cy;
    text = str;
    
    font = TTF_OpenFont( fontName.c_str(), size );
    textColor = {0,0,0};
}

TextLabel::TextLabel() {
    x = 0;
    y = 0;
    text = "";
    
    font = NULL;
    textColor = {0,0,0};
}

void TextLabel::draw(SDL_Renderer *ren) {
    texture.loadFromRenderedText(text, textColor, ren, font);
    texture.render(ren, 10, 10);

}

string TextLabel::getText() {
    return text;
}

void TextLabel::setText(string str) {
    text = str;
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

