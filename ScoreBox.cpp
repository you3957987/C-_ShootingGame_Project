//ScoreBox.cpp
#include "ScoreBox.h"

ScoreBox::ScoreBox(SDL_Renderer* renderer, int screenWidth, int screenHeight)
    : Base(renderer, screenWidth, screenHeight)
{
    // ������ �̹��� �ε�
    SDL_Surface* surface = IMG_Load("C:/Users/JunHyeok/Desktop/Shooting_game/scorebox.png");
    if (!surface) {
        std::cerr << "Failed to load image: " << IMG_GetError() << std::endl;
    }
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    position = { disX(gen), 0, 118, 70 }; // x ��ǥ�� ȭ�� ������ �����ʿ��� �������� ����,y��ǥ�� ȭ�� ���, ���μ��� ũ��� ���Ƿ� ����

    moveSpeed = 15;
    respawnTime = 1000;

}

bool ScoreBox::checkBulletCollision(const SDL_Rect& otherRect) const {
    // 
    return SDL_HasIntersection(&position, &otherRect);
}

void ScoreBox::destroy() {
    // �������� �ؽ�ó�� �ı��Ͽ� ȭ�鿡 ǥ�õ��� �ʰ� ����ϴ�.
    position.y = screenHeight + 100; // ȭ�� �Ʒ��� ����������.
}



