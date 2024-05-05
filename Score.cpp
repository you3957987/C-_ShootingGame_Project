// Score.cpp
#include <iostream>
#include <string>
#include "Score.h"

Score::Score(SDL_Renderer* renderer, int x, int y) : renderer(renderer), score(0), digitWidth(45), hundredDigit(0), tenDigit(0), oneDigit(0) {
    position.x = x;
    position.y = y;
    position.w = digitWidth * 4; // 4자리 숫자를 표시하도록 변경
    position.h = 60; // 숫자 이미지의 높이

    // 기존 코드 유지

    // 100 자리, 10 자리, 1 자리의 숫자 텍스처 배열 초기화
    for (int i = 0; i < 10; ++i) {
        std::string filename = "C:/Users/JunHyeok/Desktop/Shooting_game/score" + std::to_string(i) + ".png";
        SDL_Surface* surface = IMG_Load(filename.c_str());
        if (!surface) {
            std::cerr << "Failed to load image: " << IMG_GetError() << std::endl;
            exit(1);
        }
        scoreTextures[i] = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
    }

    // 초기 렌더링을 위해 자릿수 업데이트
    updateDigits();
}

Score::~Score() {
    // 텍스처 해제
    for (int i = 0; i < 10; ++i) {
        SDL_DestroyTexture(scoreTextures[i]);
    }
}
void Score::increaseScore(int num) {
    score += num;
    // 스코어가 10000 이상일 경우 1000 단위 숫자 갱신
    if (score >= 1000) {
        thousandDigit = score / 1000;
        hundredDigit = (score % 1000) / 100;
        tenDigit = (score % 100) / 10;
        oneDigit = score % 10;
    }
    else {
        // 1000 단위가 아닐 경우 자릿수 업데이트
        updateDigits();
    }
}
void Score::decreaseScore(int num) {

    score -= num;
    if (score < 0) {
        score = 0;
    }
    // 스코어가 10000 이상일 경우 1000 단위 숫자 갱신
    if (score >= 1000) {
        thousandDigit = score / 1000;
        hundredDigit = (score % 1000) / 100;
        tenDigit = (score % 100) / 10;
        oneDigit = score % 10;
    }
    else {
        // 1000 단위가 아닐 경우 자릿수 업데이트
        updateDigits();
    }
}

void Score::updateDigits() {
    // 1000 단위 이하의 스코어에 대한 숫자 자릿수 업데이트
    int tempScore = score;
    thousandDigit = tempScore / 1000;
    tempScore %= 1000;
    hundredDigit = tempScore / 100;
    tempScore %= 100;
    tenDigit = tempScore / 10;
    oneDigit = tempScore % 10;
}

void Score::render(SDL_Renderer* renderer) {
    // 1000 자리 숫자 렌더링
    SDL_Rect thousandDestRect = { position.x, position.y, digitWidth, position.h };
    SDL_RenderCopy(renderer, scoreTextures[thousandDigit], NULL, &thousandDestRect);

    // 100 자리 숫자 렌더링
    SDL_Rect hundredDestRect = { position.x + digitWidth, position.y, digitWidth, position.h };
    SDL_RenderCopy(renderer, scoreTextures[hundredDigit], NULL, &hundredDestRect);

    // 10 자리 숫자 렌더링
    SDL_Rect tenDestRect = { position.x + digitWidth * 2, position.y, digitWidth, position.h };
    SDL_RenderCopy(renderer, scoreTextures[tenDigit], NULL, &tenDestRect);

    // 1 자리 숫자 렌더링
    SDL_Rect oneDestRect = { position.x + digitWidth * 3, position.y, digitWidth, position.h };
    SDL_RenderCopy(renderer, scoreTextures[oneDigit], NULL, &oneDestRect);
}