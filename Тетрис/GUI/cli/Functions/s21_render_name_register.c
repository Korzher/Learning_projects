#include "s21_tetris_frontend.h"

void s21_render_name_register(settings_t *settings) {
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
    mvwprintw(settings->tetris, 35, 21, "%-10s", username);
    if (cursor_pos < 10) {
      mvwprintw(settings->tetris, 35, 21 + cursor_pos, "_");
    } else {
      mvwprintw(settings->tetris, 35, 31, " ");
    }
    wrefresh(settings->tetris);
  }

  if (strlen(username) != 0) {
    strncpy(settings->name, username, 11);
  } else {
    strncpy(settings->name, "Anonim", 7);
  }
}