#include <algorithm>

#include "bot.h"
#include "game_state.h"
#include "logic.h"

using namespace std;

int evaluate(const int *board) {
    for (int row = 0; row < N; row++) {
        if (board[row * N] == board[row * N + 1] && board[row * N + 1] == board[row * N + 2]) {
            if (board[row * N] == PLAYER_X) return -10;
            else if (board[row * N] == PLAYER_O) return +10;
        }
    }

    for (int col = 0; col < N; col++) {
        if (board[col] == board[N + col] && board[N + col] == board[2 * N + col]) {
            if (board[col] == PLAYER_X) return -10;
            else if (board[col] == PLAYER_O) return +10;
        }
    }

    if (board[0] == board[N + 1] && board[N + 1] == board[2 * N + 2]) {
        if (board[0] == PLAYER_X) return -10;
        else if (board[0] == PLAYER_O) return +10;
    }

    if (board[N - 1] == board[N + 1] && board[N + 1] == board[2 * N - 1]) {
        if (board[N - 1] == PLAYER_X) return -10;
        else if (board[N - 1] == PLAYER_O) return +10;
    }

    return 0;
}

int minimax(int *board, int depth, bool isMax) {
    int score = evaluate(board);

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
                best = max(best, minimax(board, depth + 1, false));
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
                best = min(best, minimax(board, depth + 1, true));
                board[i] = EMPTY;
            }
        }
        return best;
    }
}

int findBestMove(int *board) {
    int bestVal = -1000;
    int bestMove = -1;

    for (int i = 0; i < N * N; i++) {
        if (board[i] == EMPTY) {
            board[i] = PLAYER_O;
            int moveVal = minimax(board, 0, false);
            board[i] = EMPTY;

            if (moveVal > bestVal) {
                bestMove = i;
                bestVal = moveVal;
            }
        }
    }
    return bestMove;
}
