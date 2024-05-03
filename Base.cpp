//base.cpp
#include "Base.h"
using namespace std;

Base::Base(SDL_Renderer* renderer, int screenWidth, int screenHeight)
    : screenWidth(screenWidth), screenHeight(screenHeight), lastSpawnTime(0), gen(rd()), disX( 50 , screenWidth-50 ) {

    // ���̽��� �̹��� �ε�
    SDL_Surface* surface = IMG_Load("C:/Users/JunHyeok/Desktop/Shooting_game/Base.png");
    if (!surface) {
        cerr << "Failed to load image: " << IMG_GetError() << endl;
    }
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    // ���̽��� �ʱ� ��ġ�� ũ�� ����
    position = { disX(gen), 0, 37, 80 }; // x ��ǥ�� ȭ�� ������ �����ʿ��� �������� ����, ���μ��� ũ��� ���Ƿ� ����
    moveSpeed = 8; // ĳ���Ϳ� ���� �ӵ��� ����
}

Base::~Base() {
    SDL_DestroyTexture(texture);
}

void Base::update(Uint32 deltaTime) {
    // ���� �̵� �ӵ��� ������ �ӵ��� ���� ����
    double frameRateFactor = static_cast<double>(deltaTime) / (1000.0 / 30.0); // ������ �ӵ��� 60���� ����. �ʹ� ������ �Ҷ� ���� ����.
    double distance = moveSpeed * frameRateFactor;

    // ���� ��ġ ������Ʈ
    position.y += static_cast<int>(distance); // baseƯ¡ : ������ �ӵ��� �Ʒ��� ��������.

    // ���� ȭ���� ����� �ٽ� ���� �̵�
    if (position.y > screenHeight) {
        position.y = 0;
        position.x = disX(gen);
    }

    lastSpawnTime += deltaTime; // �ð� ������Ʈ
}

void Base::render(SDL_Renderer* renderer) {
    // ���� ������
    SDL_RenderCopy(renderer, texture, NULL, &position);

}