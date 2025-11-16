#ifndef OBJECTS_H
#define OBJECTS_H

#include <ncurses.h>
#include "s21_defines.h"

typedef struct {
    char name[11];
    int score;
} HighScore_t;

//Кнопки игрока

typedef enum {
  Start,
  Pause,
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Action
} UserAction_t;

//Игровые состояния

typedef enum {
    GAME_START,
    NAME_INSERT,
    SPAWN,
    MOVING,
    SHIFT,
    ATTACH,
    PAUSE,
    GAME_OVER,
    END_GAME,
} GameState;

typedef struct {
    int x;
    int y;
} Point_t;

typedef struct {
    Point_t blocks[BLOCKS];
    int color;
} Piece_t;

typedef struct {
    int type;
    int rotation;
    int x;
    int y;
    Point_t blocks[BLOCKS];
} CurrentPiece_t;

typedef struct {
  char name[11];
  int **field;
  int score;
  HighScore_t leaderboard[10];
  int level;
  int speed;
  int pause;
  int frames;
  CurrentPiece_t current_piece;
  CurrentPiece_t next_piece;
  int leaderboard_size;
  int leaderboard_pos;
} GameInfo_t;

typedef struct {
  WINDOW* tetris;
  WINDOW* game_field;
  WINDOW* next_piece_field;
  WINDOW* leaderboard_field;
} Windows_t;

#endif
