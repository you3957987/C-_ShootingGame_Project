//NomalBox.h
#pragma once
#include "Item.h"
#include "Score.h"

class NomalBox : public Item {
public:
    NomalBox(SDL_Renderer* renderer, int screenWidth, int screenHeight);

    void nomalbox_increse_score(Score* score);
};
