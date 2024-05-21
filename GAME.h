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
#include "Captain.h"
#include "NomalWater.h"
#include "FailWater.h"
#include "Soju.h"

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
        HelpOne,
        HelpTwo,
        GameOver,
        ClearFirst,
        ClearLast,
        StoryStartOne,
        StroyStartTwo,
        StoryNextOne,
        StoryNextTwo,
        StoryEndOne,
        StoryEndTwo
    }; // 게임 상태 표시용
    GameState  gameState = GameState::MainMenu;;

    Bullet* bullet;
    void updateBullet(); // 탄막 업데이트 함수 추가
    void renderBullet(); // 탄막 렌더 함수 추가

    Score* score;
    Item* item;
    NomalBox* nomalbox;
    FailBox* failbox;
    Smoke* smoke;
    NomalWater* nomalwater;
    FailWater* failwater;
    Soju* soju; // 객체들!!!!!!!!

    ScoreBox* scorebox1;//스코어 박스 복사 == 점수 내는 박스
    ScoreBox* scorebox2;
    ScoreBox* scorebox3;

    Captain* captain1;// 캡틴 복사 == 게임 오버 아이템
    Captain* captain2;

    double moveSpeed; // 캐릭터 이동속도
    bool spacePressed; // 총알 스페이스 땠을때 나가게 만드는용 변수
    bool gameover; // 게임오버 변수

    int maxHealth;
    int currentHealth;
    SDL_Texture* heartTexture; // 캐릭터 체력. max = 3

    void foodstagerender();
    void itemstagerender();
    void updateFoodStage(Uint32 deltaTime);
    void updateItemStage(Uint32 deltaTime);
    void handleInput(Uint32 deltaTime);
    void handleMainMenuInput(SDL_Event& e);
    
    void helpmenu_one_render();
    void helpmenu_two_render();
    void mainmenurender();
    void clearfirstrender();
    void clearlastrender();
    void gameoverrender();

    void story_start_one_render();
    void story_start_two_render();
    void story_next_one_render();
    void story_next_two_render();
    void story_end_one_render();
    void story_end_two_render();
    SDL_Texture* story_start_one_Texture;
    SDL_Texture* story_start_two_Texture;
    SDL_Texture* story_next_one_Texture;
    SDL_Texture* story_next_two_Texture;
    SDL_Texture* story_end_one_Texture;
    SDL_Texture* story_end_two_Texture;
    SDL_Texture* helpmenu_one_Texture;
    SDL_Texture* helpmenu_two_Texture;
    SDL_Texture* backgroundTexture;
    SDL_Texture* characterTexture;
    SDL_Texture* mainmenuTexture;
    SDL_Texture* startbuttonTexture;
    SDL_Texture* helpbuttonTexture;
    SDL_Texture* clearfirstTexture;
    SDL_Texture* clearlastTexture;
    SDL_Texture* gameoverTexture;
    SDL_Texture* nextbuttonTexture;
    SDL_Texture* gameoverButtonTexture;

    SDL_Rect characterRect;
    SDL_Rect startButton;
    SDL_Rect helpButton;
    SDL_Rect nextButton;
    SDL_Rect gameoverButton;

    SDL_Window* window;
    SDL_Renderer* renderer;
    void cleanup();
    SDL_Texture* loadTexture(const std::string& filePath);
};