#include <iostream>

#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

#include "game_state.h"
#include "game_rendering.h"
#include "logic.h"

using namespace std;

int SDL_main(int argc, char *argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        cerr << "Could not initialize SDL2: " << SDL_GetError() << endl;
        return EXIT_FAILURE;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) != 0) {
        cerr << "Could not initialize SDL2_mixer: " << Mix_GetError() << endl;
        return EXIT_FAILURE;
    }

    if (TTF_Init() != 0) {
        cerr << "Could not initialize SDL2_ttf: " << TTF_GetError() << std::endl;
        return EXIT_FAILURE;
    }

    SDL_Window *window = SDL_CreateWindow("tictactoe",
                                          100, 100,
                                          SCREEN_WIDTH, SCREEN_HEIGHT,
                                          SDL_WINDOW_SHOWN);
    if (window == NULL) {
        cerr << "SDL_CreateWindow Error" << SDL_GetError << endl;
        return EXIT_FAILURE;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1,
                                                SDL_RENDERER_ACCELERATED |
                                                SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) {
        SDL_DestroyWindow(window);
        cerr << "SDL_CreateRenderer Error" << SDL_GetError << endl;
        return EXIT_FAILURE;
    }

    Mix_Chunk *click_sound = Mix_LoadWAV("tbt_soundeffect.wav");
    if (click_sound == NULL) {
        cerr << "Failed to load click sound: " << Mix_GetError() << endl;
        return EXIT_FAILURE;
    }

    game_t game = {
        .board = {EMPTY, EMPTY, EMPTY,
                EMPTY, EMPTY, EMPTY,
                EMPTY, EMPTY, EMPTY},
        .player = PLAYER_X,
        .state = RUNNING_STATE
    };

    //Game Loop
    SDL_Event e;
    int quit = 0;
    while(game.state != QUIT) {
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
            case SDL_QUIT:
                game.state = QUIT;
                break;

            case SDL_MOUSEBUTTONDOWN:
                clickOnCell(&game,
                            e.button.y / CELL_HEIGHT,
                            e.button.x / CELL_WIDTH,
                            click_sound);
                break;
            default: {}
            }
        }
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);
        gameStateRendering(renderer, &game);
        SDL_RenderPresent(renderer);
    }

    Mix_FreeChunk(click_sound);
    Mix_CloseAudio();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}
