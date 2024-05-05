// game.h

#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "Base.h"
#include "Item.h"
#include "NomalBox.h"
#include "FailBox.h"
#include "Smoke.h"
#include "Bullet.h"
#include "ScoreBox.h"
#include "Score.h"

class Game {
public:
    Game();
    ~Game();

    void run();

protected:
    enum class GameState {
        MainMenu,
        FoodStage,
        ItemStage,
        Help,
        GameOver,
        ClearFirst,
        ClearLast
    };
    GameState  gameState = GameState::MainMenu;;

    Bullet* bullet;
    void updateBullet(); // 탄막 업데이트 함수 추가
    void renderBullet(); // 탄막 렌더 함수 추가
    Score* score;
    Item* item;
    NomalBox* nomalbox;
    FailBox* failbox;
    Smoke* smoke;
    ScoreBox* scorebox;
    double moveSpeed;
    bool spacePressed;

    void foodstagerender();
    void itemstagerender();
    void updateFoodStage(Uint32 deltaTime);
    void updateItemStage(Uint32 deltaTime);
    void handleInput(Uint32 deltaTime);
    void handleMainMenuInput(SDL_Event& e);
    
    void helpmenurender();
    void mainmenurender();
    void clearfirstrender();
    void clearlastrender();
    void gameoverrender();

    SDL_Texture* backgroundTexture;
    SDL_Texture* characterTexture;
    SDL_Texture* mainmenuTexture;
    SDL_Texture* startbuttonTexture;
    SDL_Texture* helpbuttonTexture;
    SDL_Texture* helpmenuTexture;
    SDL_Texture* clearfirstTexture;
    SDL_Texture* clearlastTexture;
    SDL_Texture* gameoverTexture;
    SDL_Texture* nextbuttonTexture;

    SDL_Rect characterRect;
    SDL_Rect startButton;
    SDL_Rect helpButton;
    SDL_Rect nextButton;

    SDL_Window* window;
    SDL_Renderer* renderer;
    void cleanup();
    SDL_Texture* loadTexture(const std::string& filePath);
};


