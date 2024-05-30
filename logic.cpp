#include "game_state.h"
#include "logic.h"
#include "bot.h"

void switchPlayer (game_t *game) {
    if (game->player == PLAYER_X) game->player = PLAYER_O;
    else if (game->player == PLAYER_O) game->player = PLAYER_X;
}

int playerWon (game_t *game, int player) {
    int row_count = 0, column_count = 0;
    int diag1_count = 0, diag2_count = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (game->board[i * N + j] == player) row_count++;
            if (game->board[j * N + i] == player) column_count++;
        }
        if (row_count >= N || column_count >= N) return 1;
        row_count = 0;
        column_count = 0;
        if (game->board[i * N + i] == player) diag1_count++;
        if (game->board[i * N + N - i - 1] == player) diag2_count++;
    }
    return diag1_count >= N || diag2_count >= N;
}

int cellsCount (const int *board, int cell) {
    int count = 0;
    for (int i = 0; i < N * N; i++) {
        if (board[i] == cell) count++;
    }
    return count;
}

void gameOverCondition(game_t *game) {
    if (playerWon(game, PLAYER_X)) game->state = PLAYER_X_WON;
    else if (playerWon(game, PLAYER_O)) game->state = PLAYER_O_WON;
    else if (cellsCount(game->board, EMPTY) == 0) game->state = DRAW;
}

void playerTurn(game_t *game, int row, int column, Mix_Chunk *click_sound) {
    if (game->board[row * N + column] == EMPTY) {
        game->board[row * N + column] = game->player;
        Mix_PlayChannel(-1, click_sound, 0);
        gameOverCondition(game);
        switchPlayer(game);
        if (game->state == RUNNING_STATE && game->player == PLAYER_O) {
            int bestMove = findBestMove(game->board);
            game->board[bestMove] = game->player;
            Mix_PlayChannel(-1, click_sound, 0);
            gameOverCondition(game);
            switchPlayer(game);
        }
    }
}

void resetGame(game_t *game) {
    game->player = PLAYER_X;
    game->state = RUNNING_STATE;
    for (int i = 0; i < N*N; i++) {
        game->board[i] = EMPTY;
    }
}

void clickOnCell(game_t *game, int row, int column, Mix_Chunk *click_sound){
    if (game->state == RUNNING_STATE) {
        playerTurn(game, row, column, click_sound);
    }
    else resetGame(game);
}
