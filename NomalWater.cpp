//NomalWater.cpp
#include "NomalWater.h"

NomalWater::NomalWater(SDL_Renderer* renderer, int screenWidth, int screenHeight)
    : Item(renderer, screenWidth, screenHeight)
{
    // ������ �̹��� �ε�
    SDL_Surface* surface = IMG_Load("C:/Users/JunHyeok/Desktop/Shooting_game/NomalWater.png");
    if (!surface) {
        std::cerr << "Failed to load image: " << IMG_GetError() << std::endl;
    }
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    position = { disX(gen), screenHeight + 100, 37, 80 }; // x ��ǥ�� ȭ�� ������ �����ʿ��� �������� ����,y��ǥ�� ȭ�� ���, ���μ��� ũ��� ���Ƿ� ����

    moveSpeed = 20;
    respawnTime = 3000;
}

void NomalWater::nomalwater_increase_health(int& currentHealth) {
    currentHealth += 1;
    if (currentHealth >= 3) {
        currentHealth = 3; // �ִ� ü���� 3
    }
}