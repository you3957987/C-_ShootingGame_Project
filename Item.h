//item.h
#pragma once

#include "Base.h"

class Item : public Base {
public:
    Item(SDL_Renderer* renderer, int screenWidth, int screenHeight);

    // �������� �����ϴ� �޼���
    void destroy();

    // �浹 ���� �Լ�
    bool checkCollision(const SDL_Rect& otherRect) const;


};