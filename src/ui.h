#ifndef UI_H
#define UI_H

#include <ncurses.h>

extern WINDOW *win;
extern WINDOW *co;

extern WINDOW *game;
extern WINDOW *menu;
extern WINDOW *pet;
extern WINDOW *items;
extern WINDOW *info;

extern int x, y;

void title_scr_draw();
void settings_draw();
void shop_scr_draw();
void game_scr_draw();
void pause_scr_draw();
void confirmation_draw();
void exit_prompt_draw();

#endif
