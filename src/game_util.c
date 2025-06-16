#define _POSIX_C_SOURCE 199309L

#include <pthread.h>
#include <ncurses.h>
#include <time.h>

#include "game_util.h"
#include "screen.h"
#include "ui.h"
#include "sprite.h"

pthread_t thread1; //For rendering/drawing interfaces
pthread_t thread2; //For logic processing
pthread_t thread3; //Other processing

void nsleep(unsigned int usec) {
    struct timespec ts;
    ts.tv_sec = usec / 1000000;
    ts.tv_nsec = (usec % 1000000) * 1000;
    nanosleep(&ts, NULL);
}

void gen_refresh() {
    refresh();
    wnoutrefresh(win);      //level 1
    wnoutrefresh(co);       //level 2
    wnoutrefresh(items);    //level 3
    wnoutrefresh(game);     //level 4
    wnoutrefresh(pet);      //level 5
    wnoutrefresh(info);     //level 6
    doupdate();
}
void loading_refresh() {
    werase(win);
    seg1();
    seg2();
    seg3();
    seg4();
    wload();

    wnoutrefresh(win);
    wnoutrefresh(p1);
    wnoutrefresh(p2);
    wnoutrefresh(p3);
    wnoutrefresh(p4);
    wnoutrefresh(load);
    doupdate();
}

void loading_cleanup() {
    delwin(p1);
    delwin(p2);
    delwin(p3);
    delwin(p4);
    delwin(load);
}

void return_logic(int code) {
    switch (code) {
        case 0 : title_scr(); break;
        case 1 : game_scr(); break;
        case 2 : pause_scr(); break;
        case 3 : shop_scr(); break;
    }
}

void return_bridger(int from,int code, int to) {
    code = from;
    return_logic(code);
    code = to;
}
