//FailWater.h
#pragma once
#include "Item.h"

class FailWater : public Item {
public:
    FailWater(SDL_Renderer* renderer, int screenWidth, int screenHeight);

    void failwater_decrease_health(int &currentHealth,bool& gameover);
};