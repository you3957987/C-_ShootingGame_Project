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
    SDL_Texture* scoreTextures[10]; // 0���� 9������ ���� �ؽ�ó �迭
    SDL_Rect position;
    SDL_Renderer* renderer;
    int digitWidth; // �� ������ ��

    int thousandDigit; // 1000 �ڸ�
    int hundredDigit;
    int tenDigit;
    int oneDigit;

    // �߰�: ���ھ ������ �� ���� �ڸ����� ������Ʈ�ϴ� �Լ�
    void updateDigits();
    int getscore();
};