#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>

#include "input.h"
#include "PetSim.h"
#include "entity.h"
#include "screen.h"
#include "ui.h"
#include "game_util.h"

int cindex = 0;
char c;

void keyProcessing(int size, char c) {
    switch (c) {
        case 'j' : {
            if (cindex < size - 1) {
                cindex++;
            } else if (cindex == size - 1) cindex = 0;
        }break;

        case 'k' : {
            if (c == 'k' && cindex > 0) {
                cindex--;
            } else if (c == 'k' && cindex == 0) cindex = size - 1;
        }break;
        case 'd' : {
            loading(0);
        }
    }
}

void title_scr_key() {
    c = getch();
    if (c == 'l' && cindex == 0) loading(1);
    if (c == 'l' && cindex == 2) settings();
    if (c == 'l' && cindex == 3) exit_prompt();
    keyProcessing(4, c);
}

void settings_key() {
    c = getch();
    switch (c) {
        case '\x1b' : {
            cindex = 0;
            return_logic(code);
        }break;
        case 'h' : {
            cindex = 0;
            return_logic(code);
        }
    }
    keyProcessing(4, c);
}

void pause_scr_key() {
    c = getch();
    switch (c) {
        case '\x1b' : {
            cindex = 0;
            return_logic(code);
        }break;
        case 'h' : {
            cindex = 0;
            return_logic(code);
        }break;
        case 'l' : {
            if (cindex == 0) {
                cindex = 0;
                return_logic(code);
            } else if (cindex == 1) {
                code = 2;
                confirmation();
            } else if (cindex == 2) {
                code = 2;
                exit_prompt();
            }
        }break;
    }
    keyProcessing(3, c);
}

void game_scr_key() {
    c = getch();
    switch (c) {
        case '\x1b' : pause_scr(); break;
        case 'l' : {
            if (cindex == 0) {
                feed();
            } else if (cindex == 1) {
                play();
            } else if (cindex == 2) {
                work();
            } else if (cindex == 3) {
                rest();
            } else if (cindex == 4) {
                shop_scr();
            }
        }break;
    }
    keyProcessing(5, c);
}

void shop_scr_key() {
    c = getch();
    switch (c) {
        case 'h' : {
            cindex = 0;
            return_logic(code);
        }break;
        case 'l' : {
            if (cindex == 0 && you.money >= 200) {
                item.food++;
                you.money -= 200;
            } else if (cindex == 1 && you.money >= 600 && item.toy == false) {
                item.toy = true;
                you.money -= 600;
            }
        }break;
        case '\x1b' : {
            code = 3;
            pause_scr();
            code = 1;
        }break;
    }
    keyProcessing(2, c);
}

void confirmation_key() {
    c = getch();
    switch (c) {
        case 'h' : {
            cindex = 0;
            return_logic(code);
            code = 1;
        }break;
        case 'l' : {
            if (cindex == 1) {
                cindex = 0;
                return_logic(code);
                code = 1;
            } else if (cindex == 0) {
                title_scr();
            }
        }break;
    }
    keyProcessing(2, c);
}

void exit_prompt_key() {
    c = getch();
    switch (c) {
        case 'h' : {
            cindex = 0;
            return_logic(code);
        }break;
        case 'l' : {
            if (cindex == 1) {
                cindex = 0;
                return_logic(code);
            } else if (cindex == 0) {
                endwin();
                delwin(win);
                delwin(co);
                exit(0);
            }
        }break;
    }
    keyProcessing(2, c);
}

