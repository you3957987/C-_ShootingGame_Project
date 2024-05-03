// Game.cpp
#include "Game.h"
using namespace std;
constexpr Uint32 FRAME_DELAY = 16; // 프레임 고정

Game::Game() {
    // SDL 초기화
    SDL_Init(SDL_INIT_VIDEO);

    // 윈도우 생성
    window = SDL_CreateWindow("Shooting Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1440, 900, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        cerr << "Failed to create window: " << SDL_GetError() << endl;
        exit(1);
    }

    // 렌더러 생성
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        cerr << "Failed to create renderer: " << SDL_GetError() << endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(1);
    }

    // 배경화면 이미지 로드
    backgroundTexture = loadTexture("C:/Users/JunHyeok/Desktop/Shooting_game/background.png");//이미지 불러오는 파일 위치
    if (backgroundTexture == nullptr) {
        cerr << "Failed to load background texture" << endl;
        cleanup();
        exit(1);
    }

    // 캐릭터 이미지 로드
    characterTexture = loadTexture("C:/Users/JunHyeok/Desktop/Shooting_game/character.png");
    if (characterTexture == nullptr) {
        cerr << "Failed to load character texture" << endl;
        cleanup();
        exit(1);
    }

    // 메인메뉴 이미지 로드
    mainmenuTexture = loadTexture("C:/Users/JunHyeok/Desktop/Shooting_game/coupangmaster.png");
    if (mainmenuTexture == nullptr) {
        cerr << "Failed to load character texture" << endl;
        cleanup();
        exit(1);
    }

    helpmenuTexture = loadTexture("C:/Users/JunHyeok/Desktop/Shooting_game/helpmenu.png");
    if (helpmenuTexture == nullptr) {
        cerr << "Failed to load character texture" << endl;
        cleanup();
        exit(1);
    }

    startbuttonTexture = loadTexture("C:/Users/JunHyeok/Desktop/Shooting_game/startbutton.png");
    if (startbuttonTexture == nullptr) {
        cerr << "Failed to load character texture" << endl;
        cleanup();
        exit(1);
    }

    helpbuttonTexture = loadTexture("C:/Users/JunHyeok/Desktop/Shooting_game/helpbutton.png");
    if (helpbuttonTexture == nullptr) {
        cerr << "Failed to load character texture" << endl;
        cleanup();
        exit(1);
    }

    // 캐릭터의 초기 위치와 크기 설정 이미지 없는 그냥 사각형.
    characterRect = { 400, 300, 96, 80 };
    startButton = {619, 600, 202, 64};
    helpButton = { 619, 800, 202, 64 };

    // 앞으로 추가할 클래스의 객체 생성 장소
    base = new Base(renderer, 1440, 900);

    item = new Item(renderer, 1440, 900);

    nomalbox = new NomalBox(renderer, 1440, 900);
    
    failbox = new FailBox(renderer, 1440, 900);

    smoke = new Smoke(renderer, 1440, 900);

}

Game::~Game() {
    cleanup();
    delete base;
    delete item;
}

void Game::run() {
    bool quit = false;
    SDL_Event e;

    Uint32 prevFrameTime = SDL_GetTicks(); // 프레임 시간 측정을 위한 초기화

    while (!quit) {

        while (SDL_PollEvent(&e) != 0) {

            if (e.type == SDL_QUIT) {
                quit = true;
            }
            // 게임 상태에 따른 동작 수행
            switch (gameState) {

            case GameState::MainMenu:

                handleMainMenuInput(e);
                mainmenurender();

                break;
            case GameState::Help:

                handleMainMenuInput(e);
                helpmenurender();
                break;

            case GameState::FoodStage:

                while (!quit) {
                    Uint32 currentFrameTime = SDL_GetTicks();
                    Uint32 deltaTime = currentFrameTime - prevFrameTime;
                    prevFrameTime = currentFrameTime; // 모름 일단 60 프레임 고정용 코드

                    while (SDL_PollEvent(&e) != 0) {
                        if (e.type == SDL_QUIT) {
                            quit = true;
                        }
                    } // 종료 이벤트

                    handleInput(deltaTime); // 방향키 조작 이벤트

                    updateFoodStage(deltaTime); // 앞으로 추가할 업데이트

                    foodstagerender(); // 렌더링

                    Uint32 frameTime = SDL_GetTicks() - currentFrameTime;
                    if (frameTime < 16) {
                        SDL_Delay(16 - frameTime);
                    } // 60 프레임 유지장치.
                }

                break;

            }
               
        }
    }
}

void Game::handleInput(Uint32 deltaTime) {

    const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

    if (currentKeyStates[SDL_SCANCODE_LEFT]) {
        characterRect.x -= static_cast<int>(moveSpeed * deltaTime);
    }
    if (currentKeyStates[SDL_SCANCODE_RIGHT]) {
        characterRect.x += static_cast<int>(moveSpeed * deltaTime);
    }
    if (currentKeyStates[SDL_SCANCODE_UP]) {
        characterRect.y -= static_cast<int>(moveSpeed * deltaTime);
    }
    if (currentKeyStates[SDL_SCANCODE_DOWN]) {
        characterRect.y += static_cast<int>(moveSpeed * deltaTime);
    }
}

void Game::updateFoodStage(Uint32 deltaTime) {
    // 여기에 게임 로직 업데이트 코드 추가
    base->update(deltaTime); // Base 업데이트 호출

    item->update(deltaTime); // Item 업데이트 호출
    nomalbox->update(deltaTime);
    failbox->update(deltaTime);
    smoke->update(deltaTime);

    // 캐릭터와 아이템의 충돌 감지
    if (item->checkCollision(characterRect)) {
        // 충돌 시 아이템 삭제하고 새로운 아이템 생성
        item->destroy();
        // 새로운 아이템 생성
        item = new Item(renderer, 1440, 900);
    }
    if (nomalbox->checkCollision(characterRect)) {
        // 충돌 시 아이템 삭제하고 새로운 아이템 생성
        nomalbox->destroy();
        // 새로운 아이템 생성
        nomalbox = new NomalBox(renderer, 1440, 900);
    }
    if (failbox->checkCollision(characterRect)) {
        // 충돌 시 아이템 삭제하고 새로운 아이템 생성
        failbox->destroy();
        // 새로운 아이템 생성
        failbox = new FailBox(renderer, 1440, 900);
    }
    if (smoke->checkCollision(characterRect)) {
        // 충돌 시 아이템 삭제하고 새로운 아이템 생성
        moveSpeed = 0.8; //담배피면 속도 증가.
        smoke->destroy();
        // 새로운 아이템 생성
        smoke = new Smoke(renderer, 1440, 900);

    }



}

void Game::foodstagerender() { // 앞으로 추가할 클래스의 렌더 추가 장소

    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);

    SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL); // 배경화면 텍스쳐 입히기
    SDL_RenderCopy(renderer, characterTexture, NULL, &characterRect); // 캐릭터에 이미지 붙이기

    base->render(renderer); // Base 렌더 호출
    item->render(renderer); // Item 렌더 호출
    nomalbox->render(renderer);
    failbox->render(renderer);
    smoke->render(renderer);

    SDL_RenderPresent(renderer);
}

void Game::mainmenurender() {

    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);

    SDL_RenderCopy(renderer, mainmenuTexture, NULL, NULL); // 배경화면 텍스쳐 입히기
    SDL_RenderCopy(renderer, startbuttonTexture, NULL, &startButton); 
    SDL_RenderCopy(renderer, helpbuttonTexture, NULL, &helpButton);

    SDL_RenderPresent(renderer);

}

void Game::helpmenurender() {

    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);

    SDL_RenderCopy(renderer, helpmenuTexture, NULL, NULL); // 배경화면 텍스쳐 입히기
    SDL_RenderCopy(renderer, helpbuttonTexture, NULL, &helpButton);

    SDL_RenderPresent(renderer);

}

void Game::cleanup() {
    if (renderer != nullptr) {
        SDL_DestroyRenderer(renderer);
    }
    if (window != nullptr) {
        SDL_DestroyWindow(window);
    }
    SDL_Quit();
}

SDL_Texture* Game::loadTexture(const std::string& filePath) { // 이미지 불러오는 함수
    SDL_Surface* surface = IMG_Load(filePath.c_str());
    if (!surface) {
        std::cerr << "Failed to load image: " << IMG_GetError() << std::endl;
        return nullptr;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    return texture;
}

void Game::handleMainMenuInput(SDL_Event& e) {
    // 마우스 클릭 이벤트 처리
    if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
        int mouseX = e.button.x;
        int mouseY = e.button.y;

        // 스타트 버튼 영역에 클릭이 발생하면 게임 상태를 FoodStage로 변경
        if (mouseX >= 619 && mouseX <= 619 + 202 &&
            mouseY >= 600 && mouseY <= 600 + 64 &&
            gameState == GameState::MainMenu) {
            gameState = GameState::FoodStage;
        }
        else if (mouseX >= 619 && mouseX <= 619 + 202 &&
            mouseY >= 800 && mouseY <= 800 + 64 ) {

            if(gameState == GameState :: MainMenu) gameState = GameState::Help;
            else gameState = GameState::MainMenu;
        }
    }
}
