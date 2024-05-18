//NomalWater.h
#pragma once
#include "Item.h"

class NomalWater : public Item {
public:
    NomalWater(SDL_Renderer* renderer, int screenWidth, int screenHeight);

    void nomalwater_increase_health(int & currentHealth);
};
