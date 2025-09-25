#include "s21_tetris_frontend.h"

void s21_render_next_piece(settings_t *settings) {
    werase(settings->next_piece_field);
    box(settings->next_piece_field, ACS_VLINE, ACS_HLINE);
    
    int center_x = 3;
    int center_y = 1;
    
    int color = pieces[settings->next_piece.type][settings->next_piece.rotation].color;
    wattron(settings->next_piece_field, COLOR_PAIR(color));
    
    for (int i = 0; i < BLOCKS; i++) {
        int x = center_x + settings->next_piece.blocks[i].x;
        int y = center_y + settings->next_piece.blocks[i].y;
        
        if (y >= 1 && y < 4 && x >= 1 && x < 6) {
            mvwaddch(settings->next_piece_field, y, x, '#');
        }
    }
    wattroff(settings->next_piece_field, COLOR_PAIR(color));
}