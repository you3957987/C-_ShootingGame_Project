//FailWater.cpp
#include "FailWater.h"

FailWater::FailWater(SDL_Renderer* renderer, int screenWidth, int screenHeight)
    : Item(renderer, screenWidth, screenHeight)
{
    // ������ �̹��� �ε�
    SDL_Surface* surface = IMG_Load("C:/Users/JunHyeok/Desktop/Shooting_game/FailWater.png");
    if (!surface) {
        std::cerr << "Failed to load image: " << IMG_GetError() << std::endl;
    }
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    position = { disX(gen), screenHeight + 100, 90, 124 }; // x ��ǥ�� ȭ�� ������ �����ʿ��� �������� ����,y��ǥ�� ȭ�� ���, ���μ��� ũ��� ���Ƿ� ����

    moveSpeed = 20;
    respawnTime = 1500;
}

void FailWater::failwater_decrease_health(int& currentHealth,bool& gameover) {
    currentHealth -= 1;
    if (currentHealth == 0) {
        gameover = true;
    }
}

