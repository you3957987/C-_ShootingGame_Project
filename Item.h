//item.h
#pragma once

#include "Base.h"

class Item : public Base {
public:
    Item(SDL_Renderer* renderer, int screenWidth, int screenHeight);

    // 아이템을 삭제하는 메서드
    void destroy();

    // 충돌 감지 함수
    bool checkCollision(const SDL_Rect& otherRect) const;


};