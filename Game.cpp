// Game.cpp
#include "Game.h"
#include <string>
using namespace std;
constexpr Uint32 FRAME_DELAY = 16; // ������ ����

Game::Game() {
    // SDL �ʱ�ȭ
    SDL_Init(SDL_INIT_VIDEO);

    // ������ ����
    window = SDL_CreateWindow("Shooting Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1440, 900, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        cerr << "Failed to create window: " << SDL_GetError() << endl;
        exit(1);
    }

    // ������ ����
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        cerr << "Failed to create renderer: " << SDL_GetError() << endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(1);
    }

    // ���ȭ�� �̹��� �ε�
    backgroundTexture = loadTexture("C:/Users/JunHyeok/Desktop/Shooting_game/background.png");//�̹��� �ҷ����� ���� ��ġ
    if (backgroundTexture == nullptr) {
        cerr << "Failed to load background texture" << endl;
        cleanup();
        exit(1);
    }

    // ĳ���� �̹��� �ε�
    characterTexture = loadTexture("C:/Users/JunHyeok/Desktop/Shooting_game/character.png");
    if (characterTexture == nullptr) {
        cerr << "Failed to load character texture" << endl;
        cleanup();
        exit(1);
    }

    // ���θ޴� �̹��� �ε�
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
    bullet = nullptr; // ���� ���� �ÿ��� ź���� ����

    moveSpeed = 0.5;
    spacePressed = true;

    characterRect = { 400, 300, 96, 80 };
    startButton = {619, 600, 202, 64};
    helpButton = { 619, 800, 202, 64 };
    nextButton = { 619, 700, 202, 64 };

    // ������ �߰��� Ŭ������ ��ü ���� ���
    item = new Item(renderer, 1440, 900);

    nomalbox = new NomalBox(renderer, 1440, 900);
    
    failbox = new FailBox(renderer, 1440, 900);

    smoke = new Smoke(renderer, 1440, 900);

    scorebox = new ScoreBox(renderer, 1440, 900);

    score = new Score(renderer, 1000, 50); // ���ھ� ��ü ���� �� ��ġ ����


}

Game::~Game() {
    cleanup();

    delete item;
    delete bullet;
    delete nomalbox;
    delete failbox;
    delete smoke;
    delete score;
}

void Game::run() {
    bool quit = false;
    SDL_Event e;

    Uint32 prevFrameTime = SDL_GetTicks(); // ������ �ð� ������ ���� �ʱ�ȭ

    while (!quit) {

        while (SDL_PollEvent(&e) != 0) {

            if (e.type == SDL_QUIT) {
                quit = true;
            }
            // ���� ���¿� ���� ���� ����
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
                clearlastrender();
                break;
            case GameState::FoodStage: // 1��������
                while (!quit) {
                    Uint32 currentFrameTime = SDL_GetTicks();
                    Uint32 deltaTime = currentFrameTime - prevFrameTime;
                    prevFrameTime = currentFrameTime; // �� �ϴ� 60 ������ ������ �ڵ�

                    while (SDL_PollEvent(&e) != 0) {
                        if (e.type == SDL_QUIT) {
                            quit = true;
                        }
                    } // ���� �̺�Ʈ
                    handleInput(deltaTime); // ����Ű ���� �̺�Ʈ

                    if (score->score > 400) {
                        gameState = GameState::ClearFirst;
                        break;
                    }
                    updateFoodStage(deltaTime); // ������ �߰��� ������Ʈ

                    foodstagerender(); // ������

                    Uint32 frameTime = SDL_GetTicks() - currentFrameTime;
                    if (frameTime < 16) {
                        SDL_Delay(16 - frameTime);
                    } // 60 ������ ������ġ.  
                }
                break;

            case GameState::ItemStage: // 2��������
                while (!quit) {
                    Uint32 currentFrameTime = SDL_GetTicks();
                    Uint32 deltaTime = currentFrameTime - prevFrameTime;
                    prevFrameTime = currentFrameTime; // �� �ϴ� 60 ������ ������ �ڵ�

                    while (SDL_PollEvent(&e) != 0) {
                        if (e.type == SDL_QUIT) {
                            quit = true;
                        }
                    } // ���� �̺�Ʈ

                    handleInput(deltaTime); // ����Ű ���� �̺�Ʈ

                    updateFoodStage(deltaTime); // ������ �߰��� ������Ʈ

                    foodstagerender(); // ������

                    Uint32 frameTime = SDL_GetTicks() - currentFrameTime;
                    if (frameTime < 16) {
                        SDL_Delay(16 - frameTime);
                    } // 60 ������ ������ġ.

                    if (score->score > 2000) {
                        gameState = GameState::ClearLast;
                        break;
                    }
                }
                break;

            }
              
        }
    }
}

void Game::updateBullet() {
    // ź�� ������Ʈ
    if (bullet) {
        bullet->update();
        // ź���� ȭ���� ����� ����
        if (bullet->isOutOfBounds()) {
            delete bullet;
            bullet = nullptr;
        }
    }
}

void Game::renderBullet() {
    // ź�� ����
    if (bullet) {
        bullet->render(renderer);
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

    if (currentKeyStates[SDL_SCANCODE_SPACE] && !spacePressed) { // �����̽��ٰ� ���Ȱ�, ������ �����̽��ٰ� ������ ���� ������ ��
        spacePressed = true; // �����̽��ٰ� �������� ǥ��

        // ������ ź���� ���ų� ������ ź���� ȭ���� ����� ���� ���ο� ź���� ����
        if (bullet == nullptr || bullet->isOutOfBounds()) {
            bullet = new Bullet(renderer, characterRect.x + (characterRect.w / 2) - 8, characterRect.y);
        }
    }
    else if (!currentKeyStates[SDL_SCANCODE_SPACE]) { // �����̽��ٰ� ������ ���� ������ ��
        spacePressed = false; // �����̽��ٰ� ������ �ʾ����� ǥ��
    }
}

void Game::updateFoodStage(Uint32 deltaTime) {

    updateBullet();// ź�� ������Ʈ
    // ���⿡ ���� ���� ������Ʈ �ڵ� �߰�
    item->update(deltaTime); // Item ������Ʈ ȣ��
    nomalbox->update(deltaTime);
    failbox->update(deltaTime);
    smoke->update(deltaTime);
    scorebox->update(deltaTime);

 
    // ĳ���Ϳ� �������� �浹 ����
    if (item->checkCollision(characterRect)) {
        // �浹 �� ������ �����ϰ� ���ο� ������ ����
        item->destroy();
    }
    if (nomalbox->checkCollision(characterRect)) {
        // �浹 �� ������ �����ϰ� ���ο� ������ ����
        score->increaseScore(50); // 1�� ���ھ� ����
        nomalbox->destroy();  
    }
    if (failbox->checkCollision(characterRect)) {
        // �浹 �� ������ �����ϰ� ���ο� ������ ����
        score->decreaseScore(50); // 1�� ���ھ� ����
        failbox->destroy();
    }
    if (smoke->checkCollision(characterRect)) {
        // �浹 �� ������ �����ϰ� ���ο� ������ ����
        moveSpeed = 0.8; //����Ǹ� �ӵ� ����.
        smoke->destroy();
    }
    if (bullet) {
        SDL_Rect bulletPosition = bullet->getBullet();

        // ������ ��ġ�� ����Ͽ� ScoreBox���� �浹 ����
        if (scorebox->checkBulletCollision(bulletPosition)) {
            
            score->increaseScore(200); // 1�� ���ھ� ����

            scorebox->destroy();
            delete bullet;
            bullet = nullptr;
        }
    }
}

void Game::updateItemStage(Uint32 deltaTime) {

    updateBullet();// ź�� ������Ʈ
    // ���⿡ ���� ���� ������Ʈ �ڵ� �߰�
    item->update(deltaTime); // Item ������Ʈ ȣ��
    nomalbox->update(deltaTime);
    failbox->update(deltaTime);
    smoke->update(deltaTime);
    scorebox->update(deltaTime);


    // ĳ���Ϳ� �������� �浹 ����
    if (item->checkCollision(characterRect)) {
        // �浹 �� ������ �����ϰ� ���ο� ������ ����
        item->destroy();
    }
    if (nomalbox->checkCollision(characterRect)) {
        // �浹 �� ������ �����ϰ� ���ο� ������ ����
        score->increaseScore(50); // 1�� ���ھ� ����
        nomalbox->destroy();
    }
    if (failbox->checkCollision(characterRect)) {
        // �浹 �� ������ �����ϰ� ���ο� ������ ����
        score->decreaseScore(50); // 1�� ���ھ� ����
        failbox->destroy();
    }
    if (smoke->checkCollision(characterRect)) {
        // �浹 �� ������ �����ϰ� ���ο� ������ ����
        moveSpeed = 0.8; //����Ǹ� �ӵ� ����.
        smoke->destroy();
    }
    if (bullet) {
        SDL_Rect bulletPosition = bullet->getBullet();

        // ������ ��ġ�� ����Ͽ� ScoreBox���� �浹 ����
        if (scorebox->checkBulletCollision(bulletPosition)) {

            score->increaseScore(200); // 1�� ���ھ� ����

            scorebox->destroy();
            delete bullet;
            bullet = nullptr;
        }
    }
}

void Game::foodstagerender() { // ������ �߰��� Ŭ������ ���� �߰� ���

    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);

    SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL); // ���ȭ�� �ؽ��� ������
    SDL_RenderCopy(renderer, characterTexture, NULL, &characterRect); // ĳ���Ϳ� �̹��� ���̱�

    renderBullet();// ź�� ������
    score->render(renderer); // ���ھ� ������
    item->render(renderer); // Item ���� ȣ��
    nomalbox->render(renderer);
    failbox->render(renderer);
    smoke->render(renderer);
    scorebox->render(renderer);

    SDL_RenderPresent(renderer);
}


void Game::itemstagerender() { // ������ �߰��� Ŭ������ ���� �߰� ���

    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);

    SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL); // ���ȭ�� �ؽ��� ������
    SDL_RenderCopy(renderer, characterTexture, NULL, &characterRect); // ĳ���Ϳ� �̹��� ���̱�

    renderBullet();// ź�� ������
    score->render(renderer); // ���ھ� ������
    item->render(renderer); // Item ���� ȣ��
    nomalbox->render(renderer);
    failbox->render(renderer);
    smoke->render(renderer);
    scorebox->render(renderer);

    SDL_RenderPresent(renderer);
}

void Game::mainmenurender() {

    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);

    SDL_RenderCopy(renderer, mainmenuTexture, NULL, NULL); // ���ȭ�� �ؽ��� ������
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

    SDL_RenderPresent(renderer);

}
void Game::gameoverrender() {

    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);

    SDL_RenderCopy(renderer, gameoverTexture, NULL, NULL); 

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

SDL_Texture* Game::loadTexture(const std::string& filePath) { // �̹��� �ҷ����� �Լ�
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
    // ���콺 Ŭ�� �̺�Ʈ ó��
    if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
        int mouseX = e.button.x;
        int mouseY = e.button.y;

        // ��ŸƮ ��ư ������ Ŭ���� �߻��ϸ� ���� ���¸� FoodStage�� ����
        if (mouseX >= 619 && mouseX <= 619 + 202 &&
            mouseY >= 600 && mouseY <= 600 + 64 &&
            gameState == GameState::MainMenu) {
            gameState = GameState::FoodStage;
        }
        else if (mouseX >= 619 && mouseX <= 619 + 202 &&
            mouseY >= 800 && mouseY <= 800 + 64 ) {

            if(gameState == GameState :: MainMenu) gameState = GameState::Help;
            else if(gameState == GameState :: Help) gameState = GameState::MainMenu;
        }
        else if (mouseX >= 619 && mouseX <= 619 + 202 &&
            mouseY >= 700 && mouseY <= 700 + 64 &&
            gameState == GameState::ClearFirst) {
            gameState = GameState::ItemStage;
        }
    }
}
