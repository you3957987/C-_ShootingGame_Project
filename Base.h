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

    SDL_Texture* texture; // �ؽ���
    SDL_Rect position; // ��ġ��

    int screenWidth;
    int screenHeight;

    Uint32 respawnTime; // ������ �ð�
    Uint32 lastSpawnTime;

    std::random_device rd;
    std::mt19937 gen;
    std::uniform_int_distribution<int> disX;//��
};