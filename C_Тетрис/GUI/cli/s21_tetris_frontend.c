#include "s21_tetris_frontend.h"

void s21_create_game_state(Windows_t *windows) {
  windows->tetris = newwin(42, 60, 0, 0);
  windows->game_field = newwin(FIELD_HEIGHT, FIELD_WIDTH, 7, 13);
  windows->next_piece_field = newwin(5, 7, 7, 31);
  windows->leaderboard_field = newwin(9, 20, 20, 31);
  box(windows->tetris, ACS_VLINE, ACS_HLINE);
  wrefresh(windows->tetris);
}

void s21_delete_game_state(Windows_t *windows) {
  delwin(windows->tetris);
  delwin(windows->game_field);
  delwin(windows->next_piece_field);
  delwin(windows->leaderboard_field);
}

void s21_render_start(Windows_t *windows) {
  s21_render_logo(windows);
  mvwprintw(windows->tetris, 35, 15, "Press Enter to start the game");
  wrefresh(windows->tetris);
}

void s21_render_logo(Windows_t *windows) {
  s21_render_t(windows, 10, 4);
  s21_render_e(windows, 10, 13);
  s21_render_t(windows, 10, 22);
  s21_render_r(windows, 10, 31);
  s21_render_i(windows, 10, 40);
  s21_render_s(windows, 10, 49);
}

void s21_render_t(Windows_t *windows, int y, int x) {
  int color_map[7][7] = {{G, G, W, W, W, W, W}, {G, G, W, W, W, W, W},
                         {A, A, W, W, W, A, A}, {A, A, W, W, W, A, A},
                         {A, A, W, W, W, A, A}, {A, A, W, G, G, A, A},
                         {A, A, W, G, G, A, A}};

  for (int i = 0; i < 7; i++) {
    for (int j = 0; j < 7; j++) {
      int color = color_map[i][j];
      wattron(windows->tetris, COLOR_PAIR(color));
      mvwaddch(windows->tetris, y + i, x + j, '#');
      wattroff(windows->tetris, COLOR_PAIR(color));
    }
  }
}

void s21_render_e(Windows_t *windows, int y, int x) {
  int color_map[7][7] = {{W, O, O, O, W, W, W}, {W, O, A, A, A, A, A},
                         {W, W, A, A, A, A, A}, {W, W, W, W, W, W, W},
                         {W, W, A, A, A, A, A}, {M, M, A, A, A, A, A},
                         {W, M, M, W, W, W, W}};

  for (int i = 0; i < 7; i++) {
    for (int j = 0; j < 7; j++) {
      int color = color_map[i][j];
      wattron(windows->tetris, COLOR_PAIR(color));
      mvwaddch(windows->tetris, y + i, x + j, '#');
      wattroff(windows->tetris, COLOR_PAIR(color));
    }
  }
}

void s21_render_r(Windows_t *windows, int y, int x) {
  int color_map[7][7] = {{W, W, W, W, W, W, A}, {W, A, A, A, A, A, W},
                         {U, A, A, A, A, A, W}, {U, U, W, W, W, W, A},
                         {U, A, A, W, A, A, A}, {W, A, A, A, W, A, A},
                         {W, A, A, A, A, W, A}};

  for (int i = 0; i < 7; i++) {
    for (int j = 0; j < 7; j++) {
      int color = color_map[i][j];
      wattron(windows->tetris, COLOR_PAIR(color));
      mvwaddch(windows->tetris, y + i, x + j, '#');
      wattroff(windows->tetris, COLOR_PAIR(color));
    }
  }
}

void s21_render_i(Windows_t *windows, int y, int x) {
  int color_map[7][7] = {{W, W, W, W, W, W, W}, {A, A, A, W, A, A, A},
                         {A, A, A, W, A, A, A}, {A, A, A, W, A, A, A},
                         {A, A, A, C, A, A, A}, {A, A, A, C, A, A, A},
                         {W, W, C, C, W, W, W}};

  for (int i = 0; i < 7; i++) {
    for (int j = 0; j < 7; j++) {
      int color = color_map[i][j];
      wattron(windows->tetris, COLOR_PAIR(color));
      mvwaddch(windows->tetris, y + i, x + j, '#');
      wattroff(windows->tetris, COLOR_PAIR(color));
    }
  }
}

void s21_render_s(Windows_t *windows, int y, int x) {
  int color_map[7][7] = {{A, R, R, R, R, W, A}, {W, A, A, A, A, A, A},
                         {W, A, A, A, A, A, A}, {A, W, R, R, R, R, A},
                         {A, A, A, A, A, A, W}, {A, A, A, A, A, A, W},
                         {A, R, R, R, R, W, A}};

  for (int i = 0; i < 7; i++) {
    for (int j = 0; j < 7; j++) {
      int color = color_map[i][j];
      wattron(windows->tetris, COLOR_PAIR(color));
      mvwaddch(windows->tetris, y + i, x + j, '#');
      wattroff(windows->tetris, COLOR_PAIR(color));
    }
  }
}

void s21_render_name(Windows_t *windows) {
  werase(windows->tetris);
  box(windows->tetris, ACS_VLINE, ACS_HLINE);

  s21_render_logo(windows);
  s21_render_name_placeholder(windows);
  wrefresh(windows->tetris);
  s21_render_name_register(windows);
}

void s21_render_name_placeholder(Windows_t *windows) {
  mvwprintw(windows->tetris, 32, 19, "ENTER YOUR NAME");
  mvwprintw(windows->tetris, 34, 20, "+-----------+");
  mvwprintw(windows->tetris, 35, 20, "|           |");
  mvwprintw(windows->tetris, 36, 20, "+-----------+");
  mvwprintw(windows->tetris, 38, 14, "Press ENTER to start the game");
}

void s21_render_name_register(Windows_t *windows) {
  char username[11] = {0};
  int cursor_pos = 0;
  int ch;
  while ((ch = getch()) != '\n') {
    if (ch == 127 || ch == KEY_BACKSPACE) {
      if (cursor_pos > 0) {
        cursor_pos--;
        username[cursor_pos] = '\0';
      }
    } else if ((ch > 10 && ch < 127) && cursor_pos < 10) {
      username[cursor_pos] = ch;
      cursor_pos++;
    }
    mvwprintw(windows->tetris, 35, 21, "%-10s", username);
    if (cursor_pos < 10) {
      mvwprintw(windows->tetris, 35, 21 + cursor_pos, "_");
    } else {
      mvwprintw(windows->tetris, 35, 31, " ");
    }
    wrefresh(windows->tetris);
  }
  s21_set_name(username);
}

void s21_render_field(Windows_t *windows) {
  werase(windows->tetris);
  mvwprintw(windows->tetris, 4, 26, "TETRIS");
  box(windows->tetris, ACS_VLINE, ACS_HLINE);
  box(windows->game_field, ACS_VLINE, ACS_HLINE);
  box(windows->leaderboard_field, ACS_VLINE, ACS_HLINE);
  box(windows->next_piece_field, ACS_VLINE, ACS_HLINE);

  GameInfo_t game_info = s21_update_current_state();
  s21_render_ui(windows, game_info);
  s21_render_next_piece(windows, game_info);
  s21_render_game_field(windows, game_info);
  s21_render_leaderboard(windows, game_info);

  wrefresh(windows->tetris);
  wrefresh(windows->game_field);
  wrefresh(windows->leaderboard_field);
  wrefresh(windows->next_piece_field);
}

void s21_render_ui(Windows_t *windows, GameInfo_t game_info) {
  mvwprintw(windows->tetris, 6, 31, "NEXT PIECE:");
  mvwprintw(windows->tetris, 14, 31, "Name:");
  mvwprintw(windows->tetris, 15, 31, "%s", game_info.name);
  mvwprintw(windows->tetris, 17, 31, "Score:");
  mvwprintw(windows->tetris, 18, 31, "%d", game_info.score);
  mvwprintw(windows->tetris, 19, 35, "Leaderboard:");
  mvwprintw(windows->tetris, 29, 15, "Level: %d", game_info.level);
  mvwprintw(windows->tetris, 31, 13, "Controls");
  mvwprintw(windows->tetris, 32, 13, "A - Shift left");
  mvwprintw(windows->tetris, 33, 13, "D - Shift right");
  mvwprintw(windows->tetris, 34, 13, "S - Drop tetramino");
  mvwprintw(windows->tetris, 35, 13, "Space - Rotate tetramino");
  mvwprintw(windows->tetris, 36, 13, "P - Pause");
  mvwprintw(windows->tetris, 37, 13, "Q - Quit");
}

void s21_render_next_piece(Windows_t *windows, GameInfo_t game_info) {
  werase(windows->next_piece_field);
  box(windows->next_piece_field, ACS_VLINE, ACS_HLINE);

  int center_x = 3;
  int center_y = 1;

  Piece_t next_piece =
      s21_get_piece(game_info.next_piece.type, game_info.next_piece.rotation);
  int color = next_piece.color;
  wattron(windows->next_piece_field, COLOR_PAIR(color));

  for (int i = 0; i < BLOCKS; i++) {
    int x = center_x + game_info.next_piece.blocks[i].x;
    int y = center_y + game_info.next_piece.blocks[i].y;

    if (y >= 1 && y < 4 && x >= 1 && x < 6) {
      mvwaddch(windows->next_piece_field, y, x, '#');
    }
  }
  wattroff(windows->next_piece_field, COLOR_PAIR(color));
}

void s21_render_game_field(Windows_t *windows, GameInfo_t game_info) {
  werase(windows->game_field);
  box(windows->game_field, ACS_VLINE, ACS_HLINE);

  for (int y = 1; y < FIELD_HEIGHT - 1; y++) {
    for (int x = 1; x < FIELD_WIDTH - 1; x++) {
      if (game_info.field[y][x] > 0) {
        int color_pair = game_info.field[y][x];
        wattron(windows->game_field, COLOR_PAIR(color_pair));
        mvwaddch(windows->game_field, y, x, '#');
        wattroff(windows->game_field, COLOR_PAIR(color_pair));
      }
    }
  }
  Piece_t current_piece =
      s21_get_piece(game_info.current_piece.type, game_info.current_piece.rotation);
  int color = current_piece.color;
  wattron(windows->game_field, COLOR_PAIR(color));

  for (int i = 0; i < BLOCKS; i++) {
    int x = game_info.current_piece.x + game_info.current_piece.blocks[i].x;
    int y = game_info.current_piece.y + game_info.current_piece.blocks[i].y;

    if (y >= 1 && y < FIELD_HEIGHT - 1 && x >= 1 && x < FIELD_WIDTH - 1) {
      mvwaddch(windows->game_field, y, x, '#');
    }
  }
  wattroff(windows->game_field, COLOR_PAIR(color));
}

void s21_render_leaderboard(Windows_t *windows, GameInfo_t game_info) {
  int lines = game_info.leaderboard_size > MAX_LB_LINES
                  ? MAX_LB_LINES
                  : game_info.leaderboard_size;
  for (int i = 0; i < lines; i++) {
    mvwprintw(windows->leaderboard_field, i + 1, 1, "%-10s: %.6d",
              game_info.leaderboard[i].name, game_info.leaderboard[i].score);
  }
}

void s21_render_end_game(Windows_t *windows) {
  werase(windows->tetris);
  box(windows->tetris, ACS_VLINE, ACS_HLINE);

  s21_render_logo(windows);
  s21_render_final_score(windows);
  wrefresh(windows->tetris);
  getch();
}

void s21_render_final_score(Windows_t *windows) {
  GameInfo_t game_info = s21_update_current_state();
  mvwprintw(windows->tetris, 31, 24, "GAME OVER");
  mvwprintw(windows->tetris, 32, 20, "Your final score");
  mvwprintw(windows->tetris, 34, 16, "+--------------------+");
  mvwprintw(windows->tetris, 35, 16, "|(%-10s: %.6d)|", game_info.name,
            game_info.score);
  mvwprintw(windows->tetris, 36, 16, "+--------------------+");
  mvwprintw(windows->tetris, 38, 8,
            "Press ENTER to restart or Q to finish the game");
}

void s21_render_pause(Windows_t *windows) {
  werase(windows->tetris);
  werase(windows->game_field);
  werase(windows->leaderboard_field);
  werase(windows->next_piece_field);
  box(windows->tetris, ACS_VLINE, ACS_HLINE);
  mvwprintw(windows->tetris, 4, 26, "TETRIS");

  mvwprintw(windows->tetris, 15, 1,
            "__________________________________________________________");
  mvwprintw(windows->tetris, 18, 26, "PAUSE");
  mvwprintw(windows->tetris, 21, 1,
            "__________________________________________________________");

  wrefresh(windows->tetris);
}