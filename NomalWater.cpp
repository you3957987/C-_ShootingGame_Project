//NomalWater.cpp
#include "NomalWater.h"

NomalWater::NomalWater(SDL_Renderer* renderer, int screenWidth, int screenHeight)
    : Item(renderer, screenWidth, screenHeight)
{
    // 아이템 이미지 로드
    SDL_Surface* surface = IMG_Load("C:/Users/JunHyeok/Desktop/Shooting_game/NomalWater.png");
    if (!surface) {
        std::cerr << "Failed to load image: " << IMG_GetError() << std::endl;
    }
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    position = { disX(gen), screenHeight + 100, 37, 80 }; // x 좌표는 화면 절반의 오른쪽에서 랜덤으로 설정,y좌표는 화면 상단, 가로세로 크기는 임의로 설정

    moveSpeed = 20;
    respawnTime = 3000;
}

void NomalWater::nomalwater_increase_health(int& currentHealth) {
    currentHealth += 1;
    if (currentHealth >= 3) {
        currentHealth = 3; // 최대 체력은 3
    }
}