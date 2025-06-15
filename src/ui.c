#include <ncurses.h>

#include "ui.h"
#include "entity.h"
#include "input.h"
#include "sprite.h"

WINDOW *win;
WINDOW *co;

WINDOW *game;
WINDOW *menu;
WINDOW *pet;
WINDOW *items;
WINDOW *info;

int x, y;

int pos1 = 0;
int pos2 = 0;
int pos3 = 0;
int pos4 = 0;
int pos5 = 0;
int pos6 = 0;
int pos7 = 0;

void ground_gen(WINDOW *w) {
    for (int i = 0; i < x; i++) {
        mvwprintw(w, 15, i, "_");
        pos1++;
        pos2++;
        pos3++;
        pos4++;
        pos5++;
        pos6++;
        pos7++;
        if (pos2 == 37) {
            mvwprintw(w, 15, i, "o");
            pos2 = 0;
        }
        if (pos1 == 22) {
            mvwprintw(w, 15, i, "-");
            pos1 = 0;
        }
        if (pos3 == 19) {
            mvwprintw(w, 15, i, "^");
            pos3 = 0;
        }
        if (pos4 == 16) {
            mvwprintw(w, 15, i, "-");
            pos4 = 0;
        }
        if (pos5 == 8) {
            mvwprintw(w, 16, i, "-");
            pos5 = 0;
        }
        if (pos6 == 18) {
            mvwprintw(w, 16, i, "_");
            pos6 = 0;
        }
        if (pos7 == 58) {
            mvwprintw(w, 16, i, "O");
            pos7 = 0;
        }
    }
    pos1 = 0;
    pos2 = 0;
    pos3 = 0;
    pos4 = 0;
    pos5 = 0;
    pos6 = 0;
    pos7 = 0;
}

void hud(WINDOW *w) {
    getmaxyx(w, y, x);
    mvwprintw(w, 2, 2, "Happiness: %d", mpet.happiness);
    mvwprintw(w, 4, 2, "Energy: %d", mpet.energy);
    mvwprintw(w, 6, 2, "Age: %d", mpet.age);

    mvwprintw(w, 4, (x - 8) / 2, "Day: %d", day);

    mvwprintw(w, 25, 2, "Money: %dG", you.money);
    mvwprintw(w, 27, 2, "Your energy: %d", you.energy);
}

void inventory_contents(WINDOW *w) {
    mvwprintw(w, 0, 2, " Inventory ");
    mvwprintw(w, 5, 5, "Food: %d", item.food);
    mvwprintw(w, 7, 5, "Toys: %d", item.toy);
}

void game_scr_draw() {
    win = newwin(0, 0, 0, 0);
    items = newwin(13, 40, 33, x - 42);
    game = newwin(30, x - 4, 1, 2);
    pet = newwin(4, 12, 14, (x - 14) /2);
    info = newwin(7, 16, 23, x - 20);

    pet_sprite(pet);
    ground_gen(game);
    hud(game);

    for (int i = 0; i < 5; i++) {
        if (i == cindex) wattron(win, A_REVERSE | A_BLINK);
        if (i == 0) mvwprintw(win, 35, 4, " FEED\t");
        if (i == 1) mvwprintw(win, 37, 4, " PLAY\t");
        if (i == 2) mvwprintw(win, 40, 4, " WORK\t");
        if (i == 3) mvwprintw(win, 42, 4, " SLEEP\t");
        if (i == 4) mvwprintw(win, 45, 4, " SHOP\t");
        wattroff(win, A_REVERSE | A_BLINK);
    }

    box(win, 0, '=');
    box(items, 0, 0);
    box(game, 0, 0);
    box(info, 0, 0);

    inventory_contents(items);
}

void shop_scr_draw() {
    win = newwin(0, 0, 0, 0);
    items = newwin(13, 40, 11, x - 42);

    box(win, 0, '=');
    box(items, 0, 0);

    shop_board(win);
    inventory_contents(items);

    mvwprintw(win, 9, 4, "Money: %dG", you.money);

    for (int i = 0; i < 2; i++) {
        if (i == cindex) wattron(win, A_REVERSE | A_BLINK);
        if (i == 0) mvwprintw(win, 12, 4, " FOOD\t\t[200G] ");
        if (i == 1 && item.toy == false) {
            mvwprintw(win, 14, 4, " TOYS\t\t[600G] ");
        } else if (i == 1 && item.toy == true){
            mvwprintw(win, 14, 4, " TOYS\t\t[OWNED] ");
        }
        wattroff(win, A_REVERSE | A_BLINK);
    }
}

void settings_draw() {
    win = newwin(10, 0, 0, 0);
    co = newwin(y - 10, 0, 10, 0);

    box(win, 0, '=');

    switch (cindex) {
        case 0 : mvwprintw(win, 4, 4, "This is a setting, it acts as a setting"); break;
        case 1 : mvwprintw(win, 4, 4, "Another setting"); break;
        case 2 : mvwprintw(win, 4, 4, "sudo rm's your linux"); break;
        case 3 : mvwprintw(win, 4, 4, "Hello I am a sample setting, and i will fuck your system up"); break;
    }

    for (int i = 0; i < 5; i++) {
        if (i == cindex) wattron(co, A_REVERSE | A_BLINK);
        if (i == 0) mvwprintw(co, 2, (x - 16) / 2, " SAMPLE SETTING ");
        if (i == 1) mvwprintw(co, 4, (x - 16) / 2, " SAMPLE SETTING ");
        if (i == 2) mvwprintw(co, 6, (x - 16) / 2, " SAMPLE SETTING ");
        if (i == 3) mvwprintw(co, 8, (x - 16) / 2, " SAMPLE SETTING ");
        wattroff(co, A_REVERSE | A_BLINK);

    }
}

void title_scr_draw() {
    win = newwin(10, 0, 0, 0);
    co = newwin(y - 10, 0, 10, 0);

    title(win);

    box(win, 0, '=');

    for (int i = 0; i < 4; i++) {
        if (i == cindex) wattron(co, A_REVERSE | A_BLINK);
        if (i == 0) mvwprintw(co, 2, (x - 10) / 2, " NEW  PET ");
        if (i == 1) mvwprintw(co, 4, (x - 10) / 2, " LOAD PET ");
        if (i == 2) mvwprintw(co, 6, (x - 10) / 2, " SETTINGS ");
        if (i == 3) mvwprintw(co, 8, (x - 6) / 2, " EXIT ");
        wattroff(co, A_REVERSE | A_BLINK);

    }
}

void pause_scr_draw() {
    win = newwin(0, 0, 0, 0);

    mvwprintw(win, 11, (x - 8) / 2, "[Paused]");

    for (int i = 0; i < 3; i++) {
        if (i == cindex) wattron(win, A_REVERSE | A_BLINK);
        if (i == 0) mvwprintw(win, 14, (x - 8) / 2, " RESUME ");
        if (i == 1) mvwprintw(win, 16, (x - 14) / 2, " TITLE SCREEN ");
        if (i == 2) mvwprintw(win, 18, (x - 6) / 2, " EXIT ");
        wattroff(win, A_REVERSE | A_BLINK);
    }

    box(win, 0, '=');
}

void confirmation_draw() {
    win = newwin(10, 0, 0, 0);
    co = newwin(y - 10, 0, 10, 0);

    box(win, 0, '=');

    mvwprintw(win, 4, (x - 24) / 2, "Are you sure you want to");
    mvwprintw(win, 5, (x - 24) / 2, "go back to title screen?");

    for (int i = 0; i < 4; i++) {
        if (i == cindex) wattron(co, A_REVERSE | A_BLINK);
        if (i == 0) mvwprintw(co, 2, (x - 5) / 2, " YES ");
        if (i == 1) mvwprintw(co, 4, (x - 5) / 2, " NO! ");
        wattroff(co, A_REVERSE | A_BLINK);

    }
}

void exit_prompt_draw() {
    win = newwin(10, 0, 0, 0);
    co = newwin(y - 10, 0, 10, 0);

    box(win, 0, '=');

    mvwprintw(win, 4, (x - 12) / 2, "Confirm exit");

    for (int i = 0; i < 4; i++) {
        if (i == cindex) wattron(co, A_REVERSE | A_BLINK);
        if (i == 0) mvwprintw(co, 2, (x - 5) / 2, " YES ");
        if (i == 1) mvwprintw(co, 4, (x - 5) / 2, " NO! ");
        wattroff(co, A_REVERSE | A_BLINK);
    }
}
