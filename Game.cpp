// Game.cpp
#include "Game.h"
#include <string>
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
        cerr << "Failed to load main texture" << endl;
        cleanup();
        exit(1);
    }

    helpmenuTexture = loadTexture("C:/Users/JunHyeok/Desktop/Shooting_game/helpmenu.png");
    if (helpmenuTexture == nullptr) {
        cerr << "Failed to load help texture" << endl;
        cleanup();
        exit(1);
    }

    startbuttonTexture = loadTexture("C:/Users/JunHyeok/Desktop/Shooting_game/startbutton.png");
    if (startbuttonTexture == nullptr) {
        cerr << "Failed to load startbutton texture" << endl;
        cleanup();
        exit(1);
    }

    helpbuttonTexture = loadTexture("C:/Users/JunHyeok/Desktop/Shooting_game/helpbutton.png");
    if (helpbuttonTexture == nullptr) {
        cerr << "Failed to load helpbutton texture" << endl;
        cleanup();
        exit(1);
    }
    clearfirstTexture = loadTexture("C:/Users/JunHyeok/Desktop/Shooting_game/clearfirst.png");
    if (clearfirstTexture == nullptr) {
        cerr << "Failed to load clearfirst texture" << endl;
        cleanup();
        exit(1);
    }
    clearlastTexture = loadTexture("C:/Users/JunHyeok/Desktop/Shooting_game/clearlast.png");
    if (clearlastTexture == nullptr) {
        cerr << "Failed to load clearlast texture" << endl;
        cleanup();
        exit(1);
    }
    gameoverTexture = loadTexture("C:/Users/JunHyeok/Desktop/Shooting_game/gameover.png");
    if (gameoverTexture == nullptr) {
        cerr << "Failed to load gameover texture" << endl;
        cleanup();
        exit(1);
    }
    nextbuttonTexture = loadTexture("C:/Users/JunHyeok/Desktop/Shooting_game/nextbutton.png");
    if (gameoverTexture == nullptr) {
        cerr << "Failed to load gameover texture" << endl;
        cleanup();
        exit(1);
    }
    gameoverButtonTexture = loadTexture("C:/Users/JunHyeok/Desktop/Shooting_game/gameoverbutton.png");
    if (gameoverTexture == nullptr) {
        cerr << "Failed to load gameover texture" << endl;
        cleanup();
        exit(1);
    }
    heartTexture = loadTexture("C:/Users/JunHyeok/Desktop/Shooting_game/Heart.png");
    if (heartTexture == nullptr) {
        cerr << "Failed to load heart texture" << endl;
        cleanup();
        exit(1);
    }

    maxHealth = 3;
    currentHealth = 2;
    bullet = nullptr; // 게임 시작 시에는 탄막이 없음

    moveSpeed = 0.5;
    spacePressed = true;
    gameover = false;

    characterRect = { 670, 750, 96, 80 };
    startButton = {619, 600, 202, 64};
    helpButton = { 619, 800, 202, 64 };
    nextButton = { 619, 700, 202, 64 };
    gameoverButton = { 619, 700, 202, 64 };

    // 앞으로 추가할 클래스의 객체 생성 장소
    item = new Item(renderer, 1440, 900);

    nomalbox = new NomalBox(renderer, 1440, 900);
    
    failbox = new FailBox(renderer, 1440, 900);

    smoke = new Smoke(renderer, 1440, 900);

    nomalwater = new NomalWater(renderer, 1440, 900);

    failwater = new FailWater(renderer, 1440, 900);

    soju = new Soju(renderer, 1440, 900);

    score = new Score(renderer, 1000, 50); // 스코어 객체 생성 및 위치 설정

    scorebox1 = new ScoreBox(renderer, 1440, 900);

    scorebox2 = new ScoreBox(renderer, 1440, 900);

    scorebox3 = new ScoreBox(renderer, 1440, 900);

    captain1 = new Captain(renderer, 1440, 900);

    captain2 = new Captain(renderer, 1440, 900);

}

Game::~Game() {
    cleanup();

    delete item;
    delete bullet;
    delete nomalbox;
    delete failbox;
    delete smoke;
    delete score;
    delete scorebox1;
    delete scorebox2;
    delete scorebox3;
    delete captain1;
    delete captain2;
    delete nomalwater;
    delete failwater;
    delete soju;
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
            case GameState:: ClearFirst:
                handleMainMenuInput(e);
                clearfirstrender();
                break;
            case GameState::ClearLast:
                score->score = 0;
                handleMainMenuInput(e);
                clearlastrender();
                break;
            case GameState::FoodStage: // 1스테이지
                while (!quit) {
                    Uint32 currentFrameTime = SDL_GetTicks();
                    Uint32 deltaTime = currentFrameTime - prevFrameTime;
                    prevFrameTime = currentFrameTime; // 모름 일단 60 프레임 고정용 코드

                    while (SDL_PollEvent(&e) != 0) {
                        if (e.type == SDL_QUIT) {
                            quit = true;
                        }
                    } // 종료 이벤트
                    score->increaseScore(0);

                    handleInput(deltaTime); // 방향키 조작 이벤트

                    updateFoodStage(deltaTime); // 앞으로 추가할 업데이트

                    foodstagerender(); // 렌더링

                    if (score->score > 2000) {
                        score->score = 0;
                        gameState = GameState::ClearFirst;
                        break;
                    }
                    if (gameover == true) {
                        gameState = GameState::GameOver;
                        break;
                    }
         
                    Uint32 frameTime = SDL_GetTicks() - currentFrameTime;
                    if (frameTime < 16) {
                        SDL_Delay(16 - frameTime);
                    } // 60 프레임 유지장치.  
                }
                break;

            case GameState::ItemStage: // 2스테이지
                while (!quit) {
                    Uint32 currentFrameTime = SDL_GetTicks();
                    Uint32 deltaTime = currentFrameTime - prevFrameTime;
                    prevFrameTime = currentFrameTime; // 모름 일단 60 프레임 고정용 코드

                    while (SDL_PollEvent(&e) != 0) {
                        if (e.type == SDL_QUIT) {
                            quit = true;
                        }
                    } // 종료 이벤트
                    score->increaseScore(0);

                    handleInput(deltaTime); // 방향키 조작 이벤트

                    updateItemStage(deltaTime); // 앞으로 추가할 업데이트

                    itemstagerender(); // 렌더링

                    if (score->score > 3000) {
                        gameState = GameState::ClearLast;
                        break;
                    }
                    if (gameover == true) {
                        gameState = GameState::GameOver;
                        break;
                    }

                    Uint32 frameTime = SDL_GetTicks() - currentFrameTime;
                    if (frameTime < 16) {
                        SDL_Delay(16 - frameTime);
                    } // 60 프레임 유지장치.

                }
                break;

            case GameState::GameOver:
                score->score = 0;
                handleMainMenuInput(e);
                gameoverrender();
                break;
            }
              
        }
    }
}

void Game::updateBullet() {
    // 탄막 업데이트
    if (bullet) {
        bullet->update();
        // 탄막이 화면을 벗어나면 삭제
        if (bullet->isOutOfBounds()) {
            delete bullet;
            bullet = nullptr;
        }
    }
    if (bullet) {
        SDL_Rect bulletPosition = bullet->getBullet();

        // 가져온 위치를 사용하여 ScoreBox와의 충돌 감지
        if (scorebox1->checkBulletCollision(bulletPosition)) {

            score->increaseScore(200); // 1씩 스코어 증가

            scorebox1->destroy();
            delete bullet;
            bullet = nullptr;
        }
        if (scorebox2->checkBulletCollision(bulletPosition)) {

            score->increaseScore(200); // 1씩 스코어 증가

            scorebox2->destroy();
            delete bullet;
            bullet = nullptr;
        }
        if (scorebox3->checkBulletCollision(bulletPosition)) {

            score->increaseScore(200); // 1씩 스코어 증가

            scorebox3->destroy();
            delete bullet;
            bullet = nullptr;
        }
    }
}

void Game::renderBullet() {
    // 탄막 렌더
    if (bullet) {
        bullet->render(renderer);
    }
}

void Game::handleInput(Uint32 deltaTime) {

    const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

    if (currentKeyStates[SDL_SCANCODE_LEFT]) {
        characterRect.x -= static_cast<int>(moveSpeed * deltaTime);
        if (characterRect.x < 0) {
            characterRect.x = 0;
        }
    }
    if (currentKeyStates[SDL_SCANCODE_RIGHT]) {
        characterRect.x += static_cast<int>(moveSpeed * deltaTime);
        if (characterRect.x > 1440 - characterRect.w) {  // 1440은 윈도우의 너비
            characterRect.x = 1440 - characterRect.w;
        }
    }
    if (currentKeyStates[SDL_SCANCODE_UP]) {
        characterRect.y -= static_cast<int>(moveSpeed * deltaTime);
        if (characterRect.y < 0) {
            characterRect.y = 0;
        }
    }
    if (currentKeyStates[SDL_SCANCODE_DOWN]) {
        characterRect.y += static_cast<int>(moveSpeed * deltaTime);
        if (characterRect.y > 900 - characterRect.h) {  // 900은 윈도우의 높이
            characterRect.y = 900 - characterRect.h;
        }
    }

    if (currentKeyStates[SDL_SCANCODE_SPACE] && !spacePressed) { // 스페이스바가 눌렸고, 이전에 스페이스바가 눌리지 않은 상태일 때
        spacePressed = true; // 스페이스바가 눌렸음을 표시

        // 기존의 탄막이 없거나 기존의 탄막이 화면을 벗어났을 때만 새로운 탄막을 생성
        if (bullet == nullptr || bullet->isOutOfBounds()) {
            bullet = new Bullet(renderer, characterRect.x + (characterRect.w / 2) - 8, characterRect.y);
        }
    }
    else if (!currentKeyStates[SDL_SCANCODE_SPACE]) { // 스페이스바가 눌리지 않은 상태일 때
        spacePressed = false; // 스페이스바가 눌리지 않았음을 표시
    }
}

void Game::updateFoodStage(Uint32 deltaTime) {

    updateBullet();// 탄막 업데이트
    // 여기에 게임 로직 업데이트 코드 추가
    item->update(deltaTime); // Item 업데이트 호출
    nomalbox->update(deltaTime);
    failbox->update(deltaTime);
    smoke->update(deltaTime);
    scorebox1->update(deltaTime);
    scorebox2->update(deltaTime);
    scorebox3->update(deltaTime);
    nomalwater->update(deltaTime);
    failwater->update(deltaTime);
    soju->update(deltaTime);
 
    // 캐릭터와 아이템의 충돌 감지
    if (item->checkCollision(characterRect)) {
        // 충돌 시 아이템 삭제하고 새로운 아이템 생성
        item->destroy();
    }
    if (nomalbox->checkCollision(characterRect)) {
        // 충돌 시 아이템 삭제하고 새로운 아이템 생성
        nomalbox->nomalbox_increse_score(score);
        nomalbox->destroy();  
    }
    if (failbox->checkCollision(characterRect)) {
        // 충돌 시 아이템 삭제하고 새로운 아이템 생성
        failbox->failbox_decrease_score(score);
        failbox->destroy();
    }
    if (smoke->checkCollision(characterRect)) {
        // 충돌 시 아이템 삭제하고 새로운 아이템 생성
        smoke->smoke_increase_speed(moveSpeed);
        smoke->destroy();
    }
    if (soju->checkCollision(characterRect)) {
        soju->soju_decrease_speed(moveSpeed);
        soju->destroy();
    }
    if (nomalwater->checkCollision(characterRect)) {
        // 피해 입음
        nomalwater->nomalwater_increase_health(currentHealth);
        nomalwater->destroy();
    }
    if (failwater->checkCollision(characterRect)) {
        // 피해 입음
        failwater->failwater_decrease_health(currentHealth, gameover);
        failwater->destroy();
    }
    
}

void Game::updateItemStage(Uint32 deltaTime) {

    updateBullet();// 탄막 업데이트
    // 여기에 게임 로직 업데이트 코드 추가
    item->update(deltaTime); // Item 업데이트 호출
    nomalbox->update(deltaTime);
    failbox->update(deltaTime);
    smoke->update(deltaTime);
    scorebox1->update(deltaTime);
    scorebox2->update(deltaTime);
    scorebox3->update(deltaTime);
    nomalwater->update(deltaTime);
    failwater->update(deltaTime);
    captain1->update(deltaTime);
    captain2->update(deltaTime);
    soju->update(deltaTime);

    // 캐릭터와 아이템의 충돌 감지
    if (item->checkCollision(characterRect)) {
        // 충돌 시 아이템 삭제하고 새로운 아이템 생성
        item->destroy();
    }
    if (nomalbox->checkCollision(characterRect)) {
        // 충돌 시 아이템 삭제하고 새로운 아이템 생성
        nomalbox->nomalbox_increse_score(score);

        nomalbox->destroy();
    }
    if (failbox->checkCollision(characterRect)) {
        // 충돌 시 아이템 삭제하고 새로운 아이템 생성
        failbox->failbox_decrease_score(score);
 
        failbox->destroy();
    }
    if (smoke->checkCollision(characterRect)) {
        // 충돌 시 아이템 삭제하고 새로운 아이템 생성
        smoke->smoke_increase_speed(moveSpeed);
        smoke->destroy();
    }
    if (soju->checkCollision(characterRect)) {
        soju->soju_decrease_speed(moveSpeed);
        soju->destroy();
    }
    if (nomalwater->checkCollision(characterRect)) {
        // 피해 입음
        nomalwater->nomalwater_increase_health(currentHealth);
        nomalwater->destroy();
    }
    if (failwater->checkCollision(characterRect)) {
        // 피해 입음
        failwater->failwater_decrease_health(currentHealth, gameover);
        failwater->destroy();
    }
    if (captain1->checkCollision(characterRect)) {
        // 충돌 시 아이템 삭제하고 새로운 아이템 생성
        captain1->captain_gameover(gameover);
        captain1->destroy();
    }
    if (captain2->checkCollision(characterRect)) {
        // 충돌 시 아이템 삭제하고 새로운 아이템 생성
        captain2->captain_gameover(gameover);
        captain2->destroy();
    }
}

void Game::foodstagerender() { // 앞으로 추가할 클래스의 렌더 추가 장소

    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);

    SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL); // 배경화면 텍스쳐 입히기
    SDL_RenderCopy(renderer, characterTexture, NULL, &characterRect); // 캐릭터에 이미지 붙이기

    renderBullet();// 탄막 렌더러
    score->render(renderer); // 스코어 렌더링
    item->render(renderer); // Item 렌더 호출
    nomalbox->render(renderer);
    failbox->render(renderer);
    smoke->render(renderer);
    scorebox1->render(renderer);
    scorebox2->render(renderer);
    scorebox3->render(renderer);
    nomalwater->render(renderer);
    failwater->render(renderer);
    soju->render(renderer);
    for (int i = 0; i < currentHealth; ++i) {
        SDL_Rect heartRect = { 70 + i * 70, 50, 70, 61 }; // 하트의 위치와 크기 조절
        SDL_RenderCopy(renderer, heartTexture, NULL, &heartRect);
    }

    SDL_RenderPresent(renderer);
}


void Game::itemstagerender() { // 앞으로 추가할 클래스의 렌더 추가 장소

    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);

    SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL); // 배경화면 텍스쳐 입히기
    SDL_RenderCopy(renderer, characterTexture, NULL, &characterRect); // 캐릭터에 이미지 붙이기

    renderBullet();// 탄막 렌더러
    score->render(renderer); // 스코어 렌더링
    item->render(renderer); // Item 렌더 호출
    nomalbox->render(renderer);
    failbox->render(renderer);
    smoke->render(renderer);
    scorebox1->render(renderer);
    scorebox2->render(renderer);
    scorebox3->render(renderer);
    nomalwater->render(renderer);
    failwater->render(renderer);
    captain1->render(renderer);
    captain2->render(renderer);
    soju->render(renderer);
    for (int i = 0; i < currentHealth; ++i) {
        SDL_Rect heartRect = { 70 + i * 70, 50, 70, 61 }; // 하트의 위치와 크기 조절
        SDL_RenderCopy(renderer, heartTexture, NULL, &heartRect);
    }

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

    SDL_RenderCopy(renderer, helpmenuTexture, NULL, NULL); 
    SDL_RenderCopy(renderer, helpbuttonTexture, NULL, &helpButton);

    SDL_RenderPresent(renderer);

}
void Game::clearfirstrender() {

    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);

    SDL_RenderCopy(renderer, clearfirstTexture, NULL, NULL); 
    SDL_RenderCopy(renderer, nextbuttonTexture, NULL, &nextButton);
    SDL_RenderPresent(renderer);

}
void Game::clearlastrender() {

    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);

    SDL_RenderCopy(renderer, clearlastTexture, NULL, NULL);
    SDL_RenderCopy(renderer, gameoverButtonTexture, NULL, &gameoverButton);
    SDL_RenderPresent(renderer);

}
void Game::gameoverrender() {

    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);

    SDL_RenderCopy(renderer, gameoverTexture, NULL, NULL);
    SDL_RenderCopy(renderer, gameoverButtonTexture, NULL, &gameoverButton);

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
        else if (mouseX >= 619 && mouseX <= 619 + 202 && // 도움말
            mouseY >= 800 && mouseY <= 800 + 64 ) {
            if(gameState == GameState :: MainMenu) gameState = GameState::Help;
            else if(gameState == GameState :: Help) gameState = GameState::MainMenu;
        }
        else if (mouseX >= 619 && mouseX <= 619 + 202 && // 다음 스테이지
            mouseY >= 700 && mouseY <= 700 + 64 &&
            gameState == GameState::ClearFirst) {
            gameState = GameState::ItemStage;
        }
        else if (mouseX >= 619 && mouseX <= 619 + 202 && // 게임 오버시;
            mouseY >= 700 && mouseY <= 700 + 64 &&
            gameState == GameState::GameOver) {
            gameover = false;
            gameState = GameState::MainMenu;
        }
        else if (mouseX >= 619 && mouseX <= 619 + 202 && // 게임 클리어시
            mouseY >= 700 && mouseY <= 700 + 64 &&
            gameState == GameState::ClearLast) {
            gameState = GameState::MainMenu;
        }
    }
}
