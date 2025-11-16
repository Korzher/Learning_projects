#include "s21_tetris_frontend.h"

void s21_render_game_field(settings_t *settings) {
    werase(settings->game_field);
    box(settings->game_field, ACS_VLINE, ACS_HLINE);
    
    for (int y = 1; y < FIELD_HEIGHT - 1; y++) {
        for (int x = 1; x < FIELD_WIDTH - 1; x++) {
            if (settings->field[y][x] > 0) {
                int color_pair = settings->field[y][x];
                wattron(settings->game_field, COLOR_PAIR(color_pair));
                mvwaddch(settings->game_field, y, x, '#');
                wattroff(settings->game_field, COLOR_PAIR(color_pair));
            }
        }
    }
    
    int color = pieces[settings->current_piece.type][settings->current_piece.rotation].color;
    wattron(settings->game_field, COLOR_PAIR(color));
    
    for (int i = 0; i < BLOCKS; i++) {
        int x = settings->current_piece.x + settings->current_piece.blocks[i].x;
        int y = settings->current_piece.y + settings->current_piece.blocks[i].y;
        
        if (y >= 1 && y < FIELD_HEIGHT - 1 && x >= 1 && x < FIELD_WIDTH - 1) {
            mvwaddch(settings->game_field, y, x, '#');
        }
    }
    wattroff(settings->game_field, COLOR_PAIR(color));
}