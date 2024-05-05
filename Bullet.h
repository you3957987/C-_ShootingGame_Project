//Bullet.h
#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

class Bullet {
public:
    Bullet(SDL_Renderer* renderer, int startX, int startY);
    ~Bullet();

    void update();
    void render(SDL_Renderer* renderer);

    bool isOutOfBounds();

    SDL_Rect getBullet();

    SDL_Texture* bullettexture;
    SDL_Rect bulletposition;
    int bulletspeed; // Åº¸·ÀÇ ¼Óµµ
};
