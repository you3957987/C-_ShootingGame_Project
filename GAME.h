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
        Help
    };
    GameState  gameState = GameState::MainMenu;;

    Base* base;
    Item* item;
    NomalBox* nomalbox;
    FailBox* failbox;
    Smoke* smoke;
    double moveSpeed = 0.5;

    void foodstagerender();
    void updateFoodStage(Uint32 deltaTime);
    void handleInput(Uint32 deltaTime);
    void handleMainMenuInput(SDL_Event& e);
    
    void helpmenurender();
    void mainmenurender();

    SDL_Texture* backgroundTexture;
    SDL_Texture* characterTexture;
    SDL_Texture* mainmenuTexture;
    SDL_Texture* startbuttonTexture;
    SDL_Texture* helpbuttonTexture;
    SDL_Texture* helpmenuTexture;

    SDL_Rect characterRect;
    SDL_Rect startButton;
    SDL_Rect helpButton;

    SDL_Window* window;
    SDL_Renderer* renderer;
    void cleanup();
    SDL_Texture* loadTexture(const std::string& filePath);
};


