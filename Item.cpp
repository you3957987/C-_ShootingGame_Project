//item.cpp
#include "Item.h"

Item::Item(SDL_Renderer* renderer, int screenWidth, int screenHeight)
    : Base(renderer, screenWidth, screenHeight)
{
    // 아이템 이미지 로드
    SDL_Surface* surface = IMG_Load("C:/Users/JunHyeok/Desktop/Shooting_game/Item.png");
    if (!surface) {
        std::cerr << "Failed to load image: " << IMG_GetError() << std::endl;
    }
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    position = { disX(gen), screenHeight + 100, 118, 70 }; // x 좌표는 화면 절반의 오른쪽에서 랜덤으로 설정,y좌표는 화면 상단, 가로세로 크기는 임의로 설정

    moveSpeed = 10;
    respawnTime = 6000;
}

bool Item::checkCollision(const SDL_Rect& otherRect) const {
    // 
    return SDL_HasIntersection(&position, &otherRect);
}

void Item::destroy() {
    // 아이템의 텍스처를 파괴하여 화면에 표시되지 않게 만듭니다.
    position.y = screenHeight + 100; // 화면 아래로 내려버리기.
}
// Item.cpp


