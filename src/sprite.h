#ifndef SPRITE_H
#define SPRITE_H

#include <ncurses.h>

extern bool finished;

extern WINDOW *load;
extern WINDOW *p1;
extern WINDOW *p2;
extern WINDOW *p3;
extern WINDOW *p4;

extern int pp1;
extern int pp2;
extern int pp3;
extern int pp4;

void wload();
void seg1();
void seg2();
void seg3();
void seg4();

void title(WINDOW *w);
void shop_board(WINDOW *w);
void pet_sprite(WINDOW *w);

void *loading_draw_pos(void *arg);
void *loading_anim(void *arg);

#endif
