// Bullet.cpp
#include "Bullet.h"
using namespace std;

Bullet::Bullet(SDL_Renderer* renderer, int startX, int startY) {
    // ź�� �̹��� �ε�
    SDL_Surface* surface = IMG_Load("C:/Users/JunHyeok/Desktop/Shooting_game/bacode.png");
    if (!surface) {
        cerr << "Failed to load image: " << IMG_GetError() << endl;
    }
    bullettexture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    // ź���� �ʱ� ��ġ ����
    bulletposition.x = startX;
    bulletposition.y = startY;
    bulletposition.w = 90; // ź���� �ʺ�
    bulletposition.h = 49; // ź���� ����
    bulletspeed = 25;
}

Bullet::~Bullet() {
    SDL_DestroyTexture(bullettexture);
}

void Bullet::update() {
    // ź���� �������� �̵�
    bulletposition.y -= bulletspeed;
}

void Bullet::render(SDL_Renderer* renderer) {
    SDL_RenderCopy(renderer, bullettexture, NULL, &bulletposition);
}

bool Bullet::isOutOfBounds() {
    // ź���� ȭ���� ������� ���θ� Ȯ��
    return bulletposition.y + bulletposition.h < 0;
}

SDL_Rect Bullet::getBullet() {
    return bulletposition;
}