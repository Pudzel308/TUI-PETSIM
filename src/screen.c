#include <pthread.h>

#include "screen.h"
#include "input.h"
#include "sprite.h"
#include "ui.h"
#include "game_util.h"

int code = 0;       //code 0: Title screen, code 1: Game screen, code 2: Pause screen, code 3: Shop screen

void loading(int code) {
    finished = false;

    pthread_create(&thread1, NULL, loading_anim, NULL);
    pthread_create(&thread2, NULL, loading_draw_pos, NULL);

    pthread_join(thread2, NULL);
    pthread_join(thread1, NULL);

    if (code == 0) {
        return;
    } else if (code == 1) {
        game_scr();
    }
    loading_cleanup();
}

void shop_scr() {
    cindex = 0;
    code = 1;
    while (1) {
        gen_refresh();
        getmaxyx(stdscr, y, x);
        shop_scr_draw();
        nsleep(10000);
        gen_refresh();
        shop_scr_key();
    }
}

void game_scr() {
    cindex = 0;
    code = 1;
    while (1) {
        gen_refresh();
        getmaxyx(stdscr, y, x);
        game_scr_draw();
        nsleep(10000);
        gen_refresh();
        game_scr_key();
    }
}

void confirmation() {
    cindex = 0;
    while(1) {
        gen_refresh();
        getmaxyx(stdscr, y, x);
        confirmation_draw();
        nsleep(10000);
        gen_refresh();
        confirmation_key();
    }
}

void exit_prompt() {
    cindex = 0;
    while(1) {
        gen_refresh();
        getmaxyx(stdscr, y, x);
        exit_prompt_draw();
        nsleep(10000);
        gen_refresh();
        exit_prompt_key();
    }
}

void settings() {
    cindex = 0;
    while (1) {
        gen_refresh();
        getmaxyx(stdscr, y, x);
        settings_draw();
        nsleep(10000);
        gen_refresh();
        settings_key();
    }
}

void title_scr() {
    cindex = 0;
    code = 0;
    while (1) {
        gen_refresh();
        getmaxyx(stdscr, y, x);
        title_scr_draw();
        nsleep(10000);
        gen_refresh();
        title_scr_key();
    }
}

void pause_scr() {
    cindex = 0;
    code = 1;
    while (1) {
        gen_refresh();
        getmaxyx(stdscr, y, x);
        pause_scr_draw();
        nsleep(10000);
        gen_refresh();
        pause_scr_key();
    }
}
