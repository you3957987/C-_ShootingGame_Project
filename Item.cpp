//item.cpp
#include "Item.h"

Item::Item(SDL_Renderer* renderer, int screenWidth, int screenHeight)
    : Base(renderer, screenWidth, screenHeight)
{
    // ������ �̹��� �ε�
    SDL_Surface* surface = IMG_Load("C:/Users/JunHyeok/Desktop/Shooting_game/Item.png");
    if (!surface) {
        std::cerr << "Failed to load image: " << IMG_GetError() << std::endl;
    }
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    position = { disX(gen), screenHeight + 100, 118, 70 }; // x ��ǥ�� ȭ�� ������ �����ʿ��� �������� ����,y��ǥ�� ȭ�� ���, ���μ��� ũ��� ���Ƿ� ����

    moveSpeed = 10;
    respawnTime = 6000;
}

bool Item::checkCollision(const SDL_Rect& otherRect) const {
    // 
    return SDL_HasIntersection(&position, &otherRect);
}

void Item::destroy() {
    // �������� �ؽ�ó�� �ı��Ͽ� ȭ�鿡 ǥ�õ��� �ʰ� ����ϴ�.
    position.y = screenHeight + 100; // ȭ�� �Ʒ��� ����������.
}
// Item.cpp


