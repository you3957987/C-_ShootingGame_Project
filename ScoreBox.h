//ScoreBox.h
#pragma once

#include "Base.h"

class ScoreBox : public Base {
public:

    ScoreBox(SDL_Renderer* renderer, int screenWidth, int screenHeight);

    bool checkBulletCollision(const SDL_Rect& otherRect) const;

    void destroy();

};