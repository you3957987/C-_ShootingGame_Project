// Score.cpp
#include <iostream>
#include <string>
#include "Score.h"

Score::Score(SDL_Renderer* renderer, int x, int y) : renderer(renderer), score(0), digitWidth(45), hundredDigit(0), tenDigit(0), oneDigit(0) {
    position.x = x;
    position.y = y;
    position.w = digitWidth * 4; // 4�ڸ� ���ڸ� ǥ���ϵ��� ����
    position.h = 60; // ���� �̹����� ����

    // ���� �ڵ� ����

    // 100 �ڸ�, 10 �ڸ�, 1 �ڸ��� ���� �ؽ�ó �迭 �ʱ�ȭ
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

    // �ʱ� �������� ���� �ڸ��� ������Ʈ
    updateDigits();
}

Score::~Score() {
    // �ؽ�ó ����
    for (int i = 0; i < 10; ++i) {
        SDL_DestroyTexture(scoreTextures[i]);
    }
}
void Score::increaseScore(int num) {
    score += num;
    // ���ھ 10000 �̻��� ��� 1000 ���� ���� ����
    if (score >= 1000) {
        thousandDigit = score / 1000;
        hundredDigit = (score % 1000) / 100;
        tenDigit = (score % 100) / 10;
        oneDigit = score % 10;
    }
    else {
        // 1000 ������ �ƴ� ��� �ڸ��� ������Ʈ
        updateDigits();
    }
}
void Score::decreaseScore(int num) {

    score -= num;
    if (score < 0) {
        score = 0;
    }
    // ���ھ 10000 �̻��� ��� 1000 ���� ���� ����
    if (score >= 1000) {
        thousandDigit = score / 1000;
        hundredDigit = (score % 1000) / 100;
        tenDigit = (score % 100) / 10;
        oneDigit = score % 10;
    }
    else {
        // 1000 ������ �ƴ� ��� �ڸ��� ������Ʈ
        updateDigits();
    }
}

void Score::updateDigits() {
    // 1000 ���� ������ ���ھ ���� ���� �ڸ��� ������Ʈ
    int tempScore = score;
    thousandDigit = tempScore / 1000;
    tempScore %= 1000;
    hundredDigit = tempScore / 100;
    tempScore %= 100;
    tenDigit = tempScore / 10;
    oneDigit = tempScore % 10;
}

void Score::render(SDL_Renderer* renderer) {
    // 1000 �ڸ� ���� ������
    SDL_Rect thousandDestRect = { position.x, position.y, digitWidth, position.h };
    SDL_RenderCopy(renderer, scoreTextures[thousandDigit], NULL, &thousandDestRect);

    // 100 �ڸ� ���� ������
    SDL_Rect hundredDestRect = { position.x + digitWidth, position.y, digitWidth, position.h };
    SDL_RenderCopy(renderer, scoreTextures[hundredDigit], NULL, &hundredDestRect);

    // 10 �ڸ� ���� ������
    SDL_Rect tenDestRect = { position.x + digitWidth * 2, position.y, digitWidth, position.h };
    SDL_RenderCopy(renderer, scoreTextures[tenDigit], NULL, &tenDestRect);

    // 1 �ڸ� ���� ������
    SDL_Rect oneDestRect = { position.x + digitWidth * 3, position.y, digitWidth, position.h };
    SDL_RenderCopy(renderer, scoreTextures[oneDigit], NULL, &oneDestRect);
}