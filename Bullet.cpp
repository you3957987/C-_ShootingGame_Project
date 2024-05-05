// Bullet.cpp
#include "Bullet.h"
using namespace std;

Bullet::Bullet(SDL_Renderer* renderer, int startX, int startY) {
    // 탄막 이미지 로드
    SDL_Surface* surface = IMG_Load("C:/Users/JunHyeok/Desktop/Shooting_game/bacode.png");
    if (!surface) {
        cerr << "Failed to load image: " << IMG_GetError() << endl;
    }
    bullettexture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    // 탄막의 초기 위치 설정
    bulletposition.x = startX;
    bulletposition.y = startY;
    bulletposition.w = 90; // 탄막의 너비
    bulletposition.h = 49; // 탄막의 높이
    bulletspeed = 25;
}

Bullet::~Bullet() {
    SDL_DestroyTexture(bullettexture);
}

void Bullet::update() {
    // 탄막을 위쪽으로 이동
    bulletposition.y -= bulletspeed;
}

void Bullet::render(SDL_Renderer* renderer) {
    SDL_RenderCopy(renderer, bullettexture, NULL, &bulletposition);
}

bool Bullet::isOutOfBounds() {
    // 탄막이 화면을 벗어났는지 여부를 확인
    return bulletposition.y + bulletposition.h < 0;
}

SDL_Rect Bullet::getBullet() {
    return bulletposition;
}
