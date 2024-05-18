//Soju.cpp
#include "Soju.h"

Soju::Soju(SDL_Renderer* renderer, int screenWidth, int screenHeight)
    : Item(renderer, screenWidth, screenHeight)
{
    // ������ �̹��� �ε�
    SDL_Surface* surface = IMG_Load("C:/Users/JunHyeok/Desktop/Shooting_game/Soju.png");
    if (!surface) {
        std::cerr << "Failed to load image: " << IMG_GetError() << std::endl;
    }
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    position = { disX(gen), screenHeight + 100, 24, 80 }; // x ��ǥ�� ȭ�� ������ �����ʿ��� �������� ����,y��ǥ�� ȭ�� ���, ���μ��� ũ��� ���Ƿ� ����

    moveSpeed = 30;
    respawnTime = 2000;
}

void Soju::soju_decrease_speed(double& moveSpeed) {
    moveSpeed = 0.3; //����Ǹ� �ӵ� ����.
}