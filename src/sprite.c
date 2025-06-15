#include <ncurses.h>
#include <unistd.h>

#include "sprite.h"
#include "ui.h"
#include "game_util.h"

WINDOW *load;
WINDOW *p1;
WINDOW *p2;
WINDOW *p3;
WINDOW *p4;

bool finished = false;

void wload() {
    werase(load);
    mvwprintw(load, 0, 0, " _                 _ _                   ");
    mvwprintw(load, 1, 0, "| | ___   __ _  __| (_)_ __   __ _       ");
    mvwprintw(load, 2, 0, "| |/ _ \\ / _` |/ _` | | '_ \\ / _` |      ");
    mvwprintw(load, 3, 0, "| | (_) | (_| | (_| | | | | | (_| |_ _ _ ");
    mvwprintw(load, 4, 0, "|_|\\___/ \\__,_|\\__,_|_|_| |_|\\__, (_|_|_)");
    mvwprintw(load, 5, 0, "                             |___/       ");
}

void seg1() {
    werase(p1);
    mvwprintw(p1, 0, 0, " ( \\ / ) ");
    mvwprintw(p1, 1, 0, "  |/-\\|  ");
    mvwprintw(p1, 2, 0, " /. , .\\ ");
    mvwprintw(p1, 3, 0, "|  \\ /  | ");
    mvwprintw(p1, 4, 0, "( \\_ _/ )");
}

void seg2() {
    werase(p2);
    mvwprintw(p2, 0, 0, " |\\---/| ");
    mvwprintw(p2, 1, 0, "= - v - =");
    mvwprintw(p2, 2, 0, "| \\| |/ |");
    mvwprintw(p2, 3, 0, "( \\_ _/ )");
}

void seg3() {
    werase(p3);
    mvwprintw(p3, 0, 0, " (\\--/) ");
    mvwprintw(p3, 1, 0, "( * ,* )");
    mvwprintw(p3, 2, 0, "(7    7)");
}

void seg4() {
    werase(p4);
    mvwprintw(p4, 0, 0, "  /|---|\\  ");
    mvwprintw(p4, 1, 0, " | _   _ | ");
    mvwprintw(p4, 2, 0, " \\ ( T ) / ");
    mvwprintw(p4, 3, 0, " /   U   \\ ");
    mvwprintw(p4, 4, 0, "| \\ | | / |");
    mvwprintw(p4, 5, 0, "[ )     ( ]");
}

void title(WINDOW *w) {
    mvwprintw(w, 1, (x - 75) / 2, " ____      _   ____  _                 _       _                     _____");
    mvwprintw(w, 2, (x - 75) / 2, "|  _ \\ ___| |_/ ___|(_)_ __ ___  _   _| | __ _| |_ ___  _ __  __   _|___ /");
    mvwprintw(w, 3, (x - 75) / 2, "| |_) / _ \\ __\\___ \\| | '_ ` _ \\| | | | |/ _` | __/ _ \\| '__| \\ \\ / / |_ \\");
    mvwprintw(w, 4, (x - 75) / 2, "|  __/  __/ |_ ___) | | | | | | | |_| | | (_| | || (_) | |     \\ V / ___) |");
    mvwprintw(w, 5, (x - 75) / 2, "|_|   \\___|\\__|____/|_|_| |_| |_|\\__,_|_|\\__,_|\\__\\___/|_|      \\_/ |____/");
}

void shop_board(WINDOW *w) {
    mvwprintw(w, 1, (x - 23) / 2, "     _                 ");
    mvwprintw(w, 2, (x - 23) / 2, " ___| |__   ___  _ __  ");
    mvwprintw(w, 3, (x - 23) / 2, "/ __| '_ \\ / _ \\| '_ \\ ");
    mvwprintw(w, 4, (x - 23) / 2, "\\__ \\ | | | (_) | |_) |");
    mvwprintw(w, 5, (x - 23) / 2, "|___/_| |_|\\___/| .__/ ");
    mvwprintw(w, 6, (x - 23) / 2, "                |_|    ");
}

void pet_sprite(WINDOW *w) {
    mvwprintw(w, 0, 0, "    (\\(\\");
    mvwprintw(w, 1, 0, " ,~~~ \\ \\_");
    mvwprintw(w, 2, 0, "(       . \\");
    mvwprintw(w, 3, 0, " \\___(__--`");
}

int pp1 = 6;
int pp2 = 7;
int pp3 = 8;
int pp4 = 5;

void *loading_draw_pos(void *arg) {
    win = newwin(0, 0, 0, 0);
    p1 = newwin(5, 9, 6, (x - 46) / 2);
    p2 = newwin(4, 9, 7, (x - 26) / 2);
    p3 = newwin(3, 8, 8, (x - 6) / 2);
    p4 = newwin(6, 11, 5, (x + 12) / 2);
    load = newwin(6, 41, 11, (x - 41) / 2);

    loading_refresh();
    while (finished == false) {
        sleep(10000);
        loading_refresh();
        getmaxyx(win, y, x);
        mvwin(p1, pp1, (x - 46) / 2);
        mvwin(p2, pp2, (x - 26) / 2);
        mvwin(p3, pp3, (x - 6) / 2);
        mvwin(p4, pp4, (x + 12) / 2);
        mvwin(load, 11, (x - 42) / 2);
    }
    return NULL;
}

void *loading_anim(void *arg) {
    int limit = 0;
    while (limit < 2) {
        delay_output(300);

        pp1 = 5;

        delay_output(300);
        
        pp1 = 6;

        limit++;

        delay_output(300);

        pp2 = 6;

        delay_output(300);

        pp2 = 7;

        delay_output(300);

        pp3 = 7;

        delay_output(300);

        pp3 = 8;

        delay_output(300);

        pp4 = 4;

        delay_output(300);

        pp4 = 5;
    }
    finished = true;
    return NULL;
}
