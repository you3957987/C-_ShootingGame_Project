//FallBox.h
#pragma once
#include "Item.h"
#include "Score.h"

class FailBox : public Item {
public:
    FailBox(SDL_Renderer* renderer, int screenWidth, int screenHeight);

    void failbox_decrease_score(Score* score);

};