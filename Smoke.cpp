//Smoke.cpp
#include "Smoke.h"

Smoke::Smoke(SDL_Renderer* renderer, int screenWidth, int screenHeight)
    : Item(renderer, screenWidth, screenHeight)
{
    // ������ �̹��� �ε�
    SDL_Surface* surface = IMG_Load("C:/Users/JunHyeok/Desktop/Shooting_game/Smoke.png");
    if (!surface) {
        std::cerr << "Failed to load image: " << IMG_GetError() << std::endl;
    }
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    position = { disX(gen), screenHeight + 100, 74, 140 }; // x ��ǥ�� ȭ�� ������ �����ʿ��� �������� ����,y��ǥ�� ȭ�� ���, ���μ��� ũ��� ���Ƿ� ����

    moveSpeed = 8;
    respawnTime = 2000;
}
