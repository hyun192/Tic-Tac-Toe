#include <SDL.h>

#include "game_state.h"
#include "game_rendering.h"

const SDL_Color GRID_COLOR = { .r = 0, .g = 0, .b = 0 };
const SDL_Color PLAYER_X_COLOR = { .r = 255, .g = 50, .b = 50 };
const SDL_Color PLAYER_O_COLOR = { .r = 50, .g = 100, .b = 255 };
const SDL_Color DRAW_COLOR =  {.r = 0, .g = 0, .b = 0 };

void render_grid(SDL_Renderer *renderer, const SDL_Color *color) {
    SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, 255);
    for (int i=1; i<N; i++) {
        SDL_RenderDrawLine(renderer,
                           i * CELL_WIDTH, 0,
                           i * CELL_WIDTH, SCREEN_HEIGHT);
        SDL_RenderDrawLine(renderer,
                           0,            i*CELL_HEIGHT,
                           SCREEN_WIDTH, i*CELL_HEIGHT);
    }
}

void render_x(SDL_Renderer *renderer, int row, int collumn, const SDL_Color *color) {
    const int half_box_side = CELL_HEIGHT * 0.25;
    const float center_x = CELL_WIDTH * 0.5 + collumn * CELL_WIDTH;
    const float center_y = CELL_HEIGHT * 0.5 + row * CELL_HEIGHT;

    SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, 255);

    SDL_RenderDrawLine (renderer,
                        center_x - half_box_side,
                        center_y - half_box_side,
                        center_x + half_box_side,
                        center_y + half_box_side);
    SDL_RenderDrawLine (renderer,
                        center_x + half_box_side,
                        center_y - half_box_side,
                        center_x - half_box_side,
                        center_y + half_box_side);
}

void render_o(SDL_Renderer* renderer, int row, int collumn, const SDL_Color *color) {
    const int radius = CELL_HEIGHT * 0.25;
    const float center_x = CELL_WIDTH * 0.5 + collumn * CELL_WIDTH;
    const float center_y = CELL_HEIGHT * 0.5 + row * CELL_HEIGHT;

    int x = radius - 1;
    int y = 0;
    int dx = 1;
    int dy = 1;
    int err = dx - (radius << 1);

    SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, 255);

    while (x >= y) {
        SDL_RenderDrawPoint(renderer, center_x + x, center_y + y);
        SDL_RenderDrawPoint(renderer, center_x + y, center_y + x);
        SDL_RenderDrawPoint(renderer, center_x - y, center_y + x);
        SDL_RenderDrawPoint(renderer, center_x - x, center_y + y);
        SDL_RenderDrawPoint(renderer, center_x - x, center_y - y);
        SDL_RenderDrawPoint(renderer, center_x - y, center_y - x);
        SDL_RenderDrawPoint(renderer, center_x + y, center_y - x);
        SDL_RenderDrawPoint(renderer, center_x + x, center_y - y);

        if (err <= 0) {
            y++;
            err += dy;
            dy += 2;
        }
        if (err > 0) {
            x--;
            dx += 2;
            err += dx - (radius << 1);
        }
    }
}

void render_board(SDL_Renderer *renderer, const int *board, const SDL_Color *player_x_color, const SDL_Color *player_o_color) {
    for (int i=0; i<N; i++) {
        for (int j=0; j<N; j++) {
            switch (board[i * N + j]) {
            case PLAYER_X:
                render_x(renderer, i, j, player_x_color);
                break;
            case PLAYER_O:
                render_o(renderer, i, j, player_o_color);
                break;
            }
        }
    }
}

void render_running_state(SDL_Renderer *renderer, const game_t *game) {
    render_grid(renderer, &GRID_COLOR);
    render_board(renderer,
                 game->board,
                 &PLAYER_X_COLOR,
                 &PLAYER_O_COLOR);
}

void render_gameover_state(SDL_Renderer *renderer, const game_t *game, const SDL_Color *color) {
    render_grid(renderer, color);
    render_board(renderer, game->board, color, color);
}

void gameStateRendering(SDL_Renderer *renderer, const game_t *game) {
    switch (game->state) {
    case RUNNING_STATE:
        render_running_state(renderer, game);
        break;
    case PLAYER_X_WON:
        render_gameover_state(renderer, game, &PLAYER_X_COLOR);
        break;
    case PLAYER_O_WON:
        render_gameover_state(renderer, game, &PLAYER_O_COLOR);
        break;
    case DRAW:
        render_gameover_state(renderer, game, &DRAW_COLOR);
        break;
    }
}
