//base.h
#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <random>
class Base {
public:
    Base(SDL_Renderer* renderer, int screenWidth, int screenHeight);
    ~Base();

    void update(Uint32 deltaTime);
    void render(SDL_Renderer* renderer);
    void respawn();

    double moveSpeed;
    int onoff;

    SDL_Texture* texture; // 텍스쳐
    SDL_Rect position; // 위치값

    int screenWidth;
    int screenHeight;

    Uint32 respawnTime; // 리스폰 시간
    Uint32 lastSpawnTime;

    std::random_device rd;
    std::mt19937 gen;
    std::uniform_int_distribution<int> disX;//모름
};