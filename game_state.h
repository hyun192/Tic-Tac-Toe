#ifndef GAME_STATE_H_
#define GAME_STATE_H_

#define N 3
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define CELL_WIDTH (SCREEN_WIDTH / N)
#define CELL_HEIGHT (SCREEN_HEIGHT / N)

#define EMPTY 0
#define PLAYER_X 1
#define PLAYER_O 2

#define RUNNING_STATE 0
#define PLAYER_X_WON 1
#define PLAYER_O_WON 2
#define DRAW 3
#define QUIT 4

//Game Setup
typedef struct game_t {
    int board[N*N];
    int player;
    int state;
}game_t;

#endif // GAME_STATE_H_
