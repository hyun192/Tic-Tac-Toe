#include <algorithm>

#include "bot.h"
#include "game_state.h"
#include "logic.h"

using namespace std;

int evaluate(game_t *game) {
    if (playerWon(game, PLAYER_X)) return -10;
    else if (playerWon(game, PLAYER_O)) return +10;
    else return 0;
}

int minimax(game_t *game, int *board, int depth, bool isMax) {
    int score = evaluate(game);

    // If PLAYER_O_WON
    if (score == 10)
        return score - depth;

    // If PLAYER_X_WON
    if (score == -10)
        return score + depth;

    // If DRAW
    if (cellsCount(board, EMPTY) == 0)
        return 0;

    if (isMax) {
        int best = -1000;

        for (int i = 0; i < N * N; i++) {
            if (board[i] == EMPTY) {
                board[i] = PLAYER_O;
                best = max(best, minimax(game, board, depth + 1, false));
                board[i] = EMPTY;
            }
        }
        return best;
    }
    else {
        int best = 1000;

        for (int i = 0; i < N * N; i++) {
            if (board[i] == EMPTY) {
                board[i] = PLAYER_X;
                best = min(best, minimax(game, board, depth + 1, true));
                board[i] = EMPTY;
            }
        }
        return best;
    }
}

int findBestMove(game_t *game, int *board) {
    int bestVal = -1000;
    int bestMove = -1;

    for (int i = 0; i < N * N; i++) {
        if (board[i] == EMPTY) {
            board[i] = PLAYER_O;
            int moveVal = minimax(game, board, 0, false);
            board[i] = EMPTY;

            if (moveVal > bestVal) {
                bestMove = i;
                bestVal = moveVal;
            }
        }
    }
    return bestMove;
}
