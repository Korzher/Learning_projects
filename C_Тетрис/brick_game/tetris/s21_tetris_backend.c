#include "s21_tetris_backend.h"

static GameInfo_t current_game_state = {
    .field = NULL,
};

void s21_init_game_info() {
  s21_free_game_info();
  current_game_state.field = malloc(FIELD_HEIGHT * sizeof(int *));
  for (int i = 0; i < FIELD_HEIGHT; i++) {
    current_game_state.field[i] = malloc(FIELD_WIDTH * sizeof(int));
  }
  current_game_state.score = 0;
  current_game_state.level = 1;
  current_game_state.speed = 38;
  current_game_state.pause = 0;
  current_game_state.frames = 0;
  current_game_state.next_piece.type = -1;
};

void s21_free_game_info() {
  if (current_game_state.field != NULL) {
        for (int i = 0; i < FIELD_HEIGHT; i++) {
            if (current_game_state.field[i] != NULL) {
                free(current_game_state.field[i]);
                current_game_state.field[i] = NULL;
            }
        }
        free(current_game_state.field);
        current_game_state.field = NULL;
    }
}

void s21_set_name(char *username) {
  if (strlen(username) != 0) {
    strncpy(current_game_state.name, username, 11);
  } else {
    strncpy(current_game_state.name, "Anonim", 7);
  }
}

GameInfo_t s21_update_current_state() { return current_game_state; }

static Piece_t pieces[PIECE_COUNT][ROTATIONS] = {
    {{{{-1, 0}, {0, 0}, {1, 0}, {2, 0}}, R},
     {{{0, -1}, {0, 0}, {0, 1}, {0, 2}}, R},
     {{{-1, 0}, {0, 0}, {1, 0}, {2, 0}}, R},
     {{{0, -1}, {0, 0}, {0, 1}, {0, 2}}, R}},
    {{{{-1, 1}, {-1, 0}, {0, 0}, {1, 0}}, G},
     {{{-1, -1}, {0, -1}, {0, 0}, {0, 1}}, G},
     {{{-1, 0}, {0, 0}, {1, 0}, {1, -1}}, G},
     {{{0, -1}, {0, 0}, {1, 1}, {0, 1}}, G}},
    {{{{-1, 0}, {0, 0}, {1, 0}, {1, 1}}, U},
     {{{0, -1}, {0, 0}, {0, 1}, {-1, 1}}, U},
     {{{-1, 0}, {0, 0}, {1, 0}, {-1, -1}}, U},
     {{{0, -1}, {0, 0}, {0, 1}, {1, -1}}, U}},
    {{{{0, 0}, {1, 0}, {0, 1}, {1, 1}}, O},
     {{{0, 0}, {1, 0}, {0, 1}, {1, 1}}, O},
     {{{0, 0}, {1, 0}, {0, 1}, {1, 1}}, O},
     {{{0, 0}, {1, 0}, {0, 1}, {1, 1}}, O}},
    {{{{0, 0}, {1, 0}, {-1, 1}, {0, 1}}, C},
     {{{0, -1}, {0, 0}, {1, 0}, {1, 1}}, C},
     {{{0, 0}, {1, 0}, {-1, 1}, {0, 1}}, C},
     {{{0, -1}, {0, 0}, {1, 0}, {1, 1}}, C}},
    {{{{-1, 0}, {0, 0}, {1, 0}, {0, 1}}, M},
     {{{0, -1}, {0, 0}, {0, 1}, {1, 0}}, M},
     {{{-1, 0}, {0, 0}, {1, 0}, {0, -1}}, M},
     {{{0, -1}, {0, 0}, {0, 1}, {-1, 0}}, M}},
    {{{{-1, 0}, {0, 0}, {0, 1}, {1, 1}}, W},
     {{{1, -1}, {0, 0}, {1, 0}, {0, 1}}, W},
     {{{-1, 0}, {0, 0}, {0, 1}, {1, 1}}, W},
     {{{1, -1}, {0, 0}, {1, 0}, {0, 1}}, W}}};

Piece_t s21_get_piece(int type, int rotation) { return pieces[type][rotation]; }

void s21_init_game() {
  for (int y = 0; y < FIELD_HEIGHT; y++) {
    for (int x = 0; x < FIELD_WIDTH; x++) {
      current_game_state.field[y][x] = 0;
      if (x == 0 || x == FIELD_WIDTH - 1 || y == FIELD_HEIGHT - 1) {
        current_game_state.field[y][x] = -1;
      }
    }
  }
}

int s21_spawn_new_piece() {
  current_game_state.current_piece = current_game_state.next_piece;

  int type = rand() % PIECE_COUNT;
  current_game_state.next_piece.type = type;
  current_game_state.next_piece.rotation = 0;
  current_game_state.next_piece.x = FIELD_WIDTH / 2;
  current_game_state.next_piece.y = 1;

  for (int i = 0; i < BLOCKS; i++) {
    current_game_state.next_piece.blocks[i] = pieces[type][0].blocks[i];
  }

  return s21_is_not_collided(current_game_state.current_piece.x,
                             current_game_state.current_piece.y) == SUCCESS;
}

int s21_is_not_collided(int test_x, int test_y) {
  int not_collided = SUCCESS;
  for (int i = 0; i < BLOCKS && not_collided == SUCCESS; i++) {
    int new_x = test_x + current_game_state.current_piece.blocks[i].x;
    int new_y = test_y + current_game_state.current_piece.blocks[i].y;

    if (current_game_state.field[new_y][new_x] != 0) {
      not_collided = ERROR;
    }
  }

  return not_collided;
}

void s21_shift(int step) {
  int new_x = current_game_state.current_piece.x + step;

  if (s21_is_not_collided(new_x, current_game_state.current_piece.y) ==
      SUCCESS) {
    current_game_state.current_piece.x = new_x;
  }
}

void s21_rotate() {
  CurrentPiece_t original = current_game_state.current_piece;
  int new_rotation =
      (current_game_state.current_piece.rotation + 1) % ROTATIONS;
  Piece_t new_piece =
      pieces[current_game_state.current_piece.type][new_rotation];

  for (int i = 0; i < BLOCKS; i++) {
    current_game_state.current_piece.blocks[i] = new_piece.blocks[i];
  }

  current_game_state.current_piece.rotation = new_rotation;

  if (!(s21_is_not_collided(current_game_state.current_piece.x,
                            current_game_state.current_piece.y) == SUCCESS)) {
    current_game_state.current_piece = original;
  }
}

int s21_move() {
  int state = MOVING;
  int new_y = current_game_state.current_piece.y + 1;

  if (s21_is_not_collided(current_game_state.current_piece.x, new_y) ==
      SUCCESS) {
    current_game_state.current_piece.y = new_y;
  } else {
    state = ATTACH;
  }

  return state;
}

void s21_attach() {
  for (int i = 0; i < BLOCKS; i++) {
    int field_x = current_game_state.current_piece.x +
                  current_game_state.current_piece.blocks[i].x;
    int field_y = current_game_state.current_piece.y +
                  current_game_state.current_piece.blocks[i].y;
    int color = pieces[current_game_state.current_piece.type]
                      [current_game_state.current_piece.rotation]
                          .color;
    current_game_state.field[field_y][field_x] = color;
  }
  s21_destroy_rows();
}

void s21_destroy_rows() {
  int full_rows = 0;

  for (int y = FIELD_HEIGHT - 2; y >= 1; y--) {
    int row_full = 1;

    for (int x = 1; x < FIELD_WIDTH - 1; x++) {
      if (current_game_state.field[y][x] == 0) {
        row_full = 0;
        break;
      }
    }

    if (row_full) {
      full_rows++;
      for (int ny = y; ny > 0; ny--) {
        for (int x = 1; x < FIELD_WIDTH - 1; x++) {
          current_game_state.field[ny][x] = current_game_state.field[ny - 1][x];
        }
      }
      for (int x = 1; x < FIELD_WIDTH - 1; x++) {
        current_game_state.field[1][x] = 0;
      }

      y++;
    }
  }

  if (full_rows > 0) {
    s21_count_points(full_rows);
  }
}

void s21_count_points(int full_rows) {
  int score = 0;
  switch (full_rows) {
    case 1:
      score = 100;
      break;
    case 2:
      score = 300;
      break;
    case 3:
      score = 700;
      break;
    case 4:
      score = 1500;
      break;
  }

  current_game_state.score += score;
  s21_calculate_level();
  s21_calculate_speed();
  s21_update_leaderboard();
}

void s21_calculate_level() {
  current_game_state.level = current_game_state.score / 600 + 1;
  if (current_game_state.level > 10) {
    current_game_state.level = 10;
  }
}

void s21_calculate_speed() {
  current_game_state.speed = 38 - (current_game_state.level * 2);
}

void s21_load_leaderboard() {
  FILE *scores_file = fopen(FILENAME, "r");
  if (scores_file == NULL) {
    printf("Error opening leaderboard file.\n");
    return;
  }
  int lines = 0;
  while (lines < MAX_LB_LINES &&
         fscanf(scores_file, "%s %d",
                current_game_state.leaderboard[lines].name,
                &current_game_state.leaderboard[lines].score) == 2) {
    lines++;
  }
  fclose(scores_file);
  strncpy(current_game_state.leaderboard[lines].name, current_game_state.name,
          11);
  current_game_state.leaderboard[lines].score = current_game_state.score;
  current_game_state.leaderboard_pos = lines;
  lines++;
  current_game_state.leaderboard_size = lines;
}

void s21_save_leaderboard() {
  FILE *leaderboard = fopen(FILENAME, "w");
  int lines = current_game_state.leaderboard_size > MAX_LB_LINES
                  ? MAX_LB_LINES
                  : current_game_state.leaderboard_size;
  for (int i = 0; i < lines; i++) {
    fprintf(leaderboard, "%s %.6d\n", current_game_state.leaderboard[i].name,
            current_game_state.leaderboard[i].score);
  }
  fclose(leaderboard);
}

void s21_update_leaderboard() {
  int pos = current_game_state.leaderboard_pos;
  current_game_state.leaderboard[pos].score = current_game_state.score;

  while (pos > 0 && current_game_state.leaderboard[pos].score >
                        current_game_state.leaderboard[pos - 1].score) {
    HighScore_t temp = current_game_state.leaderboard[pos];
    current_game_state.leaderboard[pos] =
        current_game_state.leaderboard[pos - 1];
    current_game_state.leaderboard[pos - 1] = temp;
    pos--;
  }
  current_game_state.leaderboard_pos = pos;
}

void s21_do_game_start(UserAction_t action, GameState *state) {
  if (action == Start) {
    s21_user_input(action);
    *state = NAME_INSERT;
  }
}

void s21_do_name_insert(GameState *state) {
  s21_init_game();
  s21_load_leaderboard();
  *state = SPAWN;
}

void s21_do_spawn(GameState *state) {
  if (current_game_state.next_piece.type == -1) {
    s21_spawn_new_piece();
  }
  if (s21_spawn_new_piece()) {
    *state = MOVING;
  } else {
    *state = GAME_OVER;
  }
}

void s21_do_moving(UserAction_t action, GameState *state) {
  s21_user_input(action);
  if (action == Left || action == Right || action == Action) {
    *state = SHIFT;
  } else if (action == Down) {
    *state = ATTACH;
  } else if (action == Pause) {
    *state = PAUSE;
  } else if (action == Terminate) {
    *state = GAME_OVER;
  }

  if (*state != PAUSE) {
    current_game_state.frames++;
    if (current_game_state.frames == current_game_state.speed ||
        current_game_state.frames > current_game_state.speed) {
      *state = s21_move();
      current_game_state.frames = 0;
    }
  }
}

void s21_do_pause(GameState *state) {
while (1) {
	UserAction_t action = s21_get_user_input(getch());
	if (action == Pause) {
		*state = MOVING;
		break;
	}
	if (action == Terminate) {
		*state = GAME_OVER;
		break;
	}
}
}

void s21_user_input(UserAction_t action) {
  switch (action) {
    case Start:
      break;
    case Pause:
      break;
    case Terminate:
      break;
    case Left:
      s21_shift(-1);
      break;
    case Right:
      s21_shift(1);
      break;
    case Up:
      break;
    case Down:
      while (s21_move() != ATTACH) {
      };
      break;
    case Action:
      s21_rotate();
      break;
    default:
      break;
  }
  return;
}

UserAction_t s21_get_user_input(int signal) {
  UserAction_t action = NO_INPUT;

  if (signal == ENTER_KEY)
    action = Start;
  else if (signal == 'w' || signal == 'W')
    action = Up;
  else if (signal == 's' || signal == 'S')
    action = Down;
  else if (signal == 'a' || signal == 'A')
    action = Left;
  else if (signal == 'd' || signal == 'D')
    action = Right;
  else if (signal == ' ')
    action = Action;
  else if (signal == 'q' || signal == 'Q')
    action = Terminate;
  else if (signal == 'p' || signal == 'P')
    action = Pause;

  return action;
}

void s21_do_attach(GameState *state) {
  s21_attach();
  *state = SPAWN;
}

void s21_do_game_over(UserAction_t action, GameState *state) {
  s21_save_leaderboard();
  s21_free_game_info();
  if (action == Start) {
    s21_init_game_info();
    *state = NAME_INSERT;
  } else if (action == Terminate) {
    *state = END_GAME;
  }
}

GameInfo_t* s21_test_get_game_state_ptr() {
    return &current_game_state;
}

void s21_test_reset_game() {
  s21_free_game_info();
  current_game_state.score = 0;
  current_game_state.level = 1;
  current_game_state.speed = 38;
  current_game_state.pause = 0;
  current_game_state.frames = 0;
  current_game_state.next_piece.type = -1;
}
