//FallBox.cpp
#include "FailBox.h"

FailBox::FailBox(SDL_Renderer* renderer, int screenWidth, int screenHeight)
    : Item(renderer, screenWidth, screenHeight)
{
    // 아이템 이미지 로드
    SDL_Surface* surface = IMG_Load("C:/Users/JunHyeok/Desktop/Shooting_game/FailBox.png");
    if (!surface) {
        std::cerr << "Failed to load image: " << IMG_GetError() << std::endl;
    }
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    position = { disX(gen), 0, 118, 70 }; // x 좌표는 화면 절반의 오른쪽에서 랜덤으로 설정,y좌표는 화면 상단, 가로세로 크기는 임의로 설정

    moveSpeed = 20;
}


