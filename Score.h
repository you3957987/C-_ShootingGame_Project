// Score.h
#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>

class Score {
public:
    Score(SDL_Renderer* renderer, int x, int y);
    ~Score();
    void increaseScore(int num);
    void decreaseScore(int num);
    void render(SDL_Renderer* renderer);


    int score;
    SDL_Texture* scoreTextures[10]; // 0부터 9까지의 숫자 텍스처 배열
    SDL_Rect position;
    SDL_Renderer* renderer;
    int digitWidth; // 각 숫자의 폭

    int thousandDigit; // 1000 자리
    int hundredDigit;
    int tenDigit;
    int oneDigit;

    // 추가: 스코어를 갱신할 때 숫자 자릿수를 업데이트하는 함수
    void updateDigits();
    int getscore();
};