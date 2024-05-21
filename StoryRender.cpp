#include "Game.h"

void Game::story_start_one_render() {

    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);

    SDL_RenderCopy(renderer, story_start_one_Texture, NULL, NULL);
    SDL_RenderCopy(renderer, nextbuttonTexture, NULL, &nextButton);

    SDL_RenderPresent(renderer);

}
void Game::story_start_two_render() {

    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);

    SDL_RenderCopy(renderer, story_start_two_Texture, NULL, NULL);
    SDL_RenderCopy(renderer, nextbuttonTexture, NULL, &nextButton);

    SDL_RenderPresent(renderer);

}
void Game::story_next_one_render() {

    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);

    SDL_RenderCopy(renderer, story_next_one_Texture, NULL, NULL);
    SDL_RenderCopy(renderer, nextbuttonTexture, NULL, &nextButton);

    SDL_RenderPresent(renderer);

}
void Game::story_next_two_render() {

    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);

    SDL_RenderCopy(renderer, story_next_two_Texture, NULL, NULL);
    SDL_RenderCopy(renderer, nextbuttonTexture, NULL, &nextButton);

    SDL_RenderPresent(renderer);

}
void Game::story_end_one_render() {

    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);

    SDL_RenderCopy(renderer, story_end_one_Texture, NULL, NULL);
    SDL_RenderCopy(renderer, nextbuttonTexture, NULL, &nextButton);

    SDL_RenderPresent(renderer);

}
void Game::story_end_two_render() {

    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);

    SDL_RenderCopy(renderer, story_end_two_Texture, NULL, NULL);
    SDL_RenderCopy(renderer, nextbuttonTexture, NULL, &nextButton);

    SDL_RenderPresent(renderer);

}