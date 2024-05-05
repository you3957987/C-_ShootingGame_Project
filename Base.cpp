//base.cpp
#include "Base.h"
using namespace std;

Base::Base(SDL_Renderer* renderer, int screenWidth, int screenHeight)
    : screenWidth(screenWidth), screenHeight(screenHeight), lastSpawnTime(0), gen(rd()), disX( 50 , screenWidth-50 ) {//리스폰 시간 조절

    // 베이스의 이미지 로드
    SDL_Surface* surface = IMG_Load("C:/Users/JunHyeok/Desktop/Shooting_game/Base.png");
    if (!surface) {
        cerr << "Failed to load image: " << IMG_GetError() << endl;
    }
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    // 베이스의 초기 위치와 크기 설정
    position = { disX(gen), 0, 37, 80 }; // x 좌표는 화면 절반의 오른쪽에서 랜덤으로 설정, 가로세로 크기는 임의로 설정
    moveSpeed = 8; // 캐릭터와 같은 속도로 설정
    respawnTime = 10000;// 리스폰 시간
}

Base::~Base() {
    SDL_DestroyTexture(texture);
}

void Base::update(Uint32 deltaTime) {
    // 적의 이동 속도를 프레임 속도에 맞춰 조절
    double frameRateFactor = static_cast<double>(deltaTime) / (1000.0 / 30.0);
    double distance = moveSpeed * frameRateFactor;

    // 적의 위치 업데이트
    position.y += static_cast<int>(distance);

    // 적이 화면을 벗어나면 삭제
    if (position.y > screenHeight) {
        respawn();
    }

  
}

void Base ::respawn() {

    Uint32 currentTime = SDL_GetTicks();
    if (currentTime - lastSpawnTime > respawnTime) {
        position.y = 0;
        position.x = disX(gen);
        lastSpawnTime = currentTime; // 마지막 생성 시간 업데이트
    }
}

void Base::render(SDL_Renderer* renderer) {
    // 적을 렌더링
    SDL_RenderCopy(renderer, texture, NULL, &position);

}