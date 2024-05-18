//Soju.h
#pragma once
#include "Item.h"

class Soju : public Item {
public:
    Soju(SDL_Renderer* renderer, int screenWidth, int screenHeight);

    void soju_decrease_speed(double& moveSpeed);
};


