#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_t thread1; //For rendering/drawing interfaces
pthread_t thread2; //For logic processing
pthread_t thread3; //Other processing

WINDOW *load;
WINDOW *p1;
WINDOW *p2;
WINDOW *p3;
WINDOW *p4;

WINDOW *win;
WINDOW *co;

WINDOW *game;
WINDOW *menu;
WINDOW *pet;
WINDOW *items;
WINDOW *info;

bool finished = false;

int x, y;
int cindex = 0;
char c;
int code = 0;       //code 0: Title screen, code 1: Game screen, code 2: Pause screen, code 3: Shop screen

#define BUNNY 5 
#define CAT 16
#define DOG 14
#define HAMSTER 4

//====SETTINGS=====//

int slider = 0;

//=================//

int pos1 = 0;
int pos2 = 0;
int pos3 = 0;
int pos4 = 0;
int pos5 = 0;
int pos6 = 0;
int pos7 = 0;

//==========data=========//

struct Pet {
    int age;
    int ageCap;
    int happiness;
    int energy;
    char name;
};

struct Player {
    int energy;
    int money;
};

struct Inventory {
    int food;
    bool toy;
};

int day = 1;

struct Pet mpet;
struct Player you;
struct Inventory item;

//=======================//

void title_scr();

void settings();

void shop_scr();

void game_scr();

void pause_scr();

void loading(int code);

void init() {
    mpet.age = 0;
    mpet.ageCap = BUNNY;
    mpet.energy = 200;
    mpet.happiness = 100;

    you.money = 2000;
    you.energy = 100;

    item.food = 2;

    title_scr();
}

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

void loading_cleanup() {
    delwin(p1);
    delwin(p2);
    delwin(p3);
    delwin(p4);
    delwin(load);
}

void return_logic(int code) {
    switch (code) {
        case 0 : return title_scr(); break;
        case 1 : return game_scr(); break;
        case 2 : return pause_scr(); break;
        case 3 : return shop_scr(); break;
    }
}

void return_bridger(int from,int code, int to) {
    code = from;
    return_logic(code);
    code = to;
}

int info_code = 0;

void feed_info(int code) {
    switch (code) {
        case 0 : {
            mvwprintw(info, 1, 1, "+75 Energy\n-1 Food");
        }
    }
}

void feed(WINDOW *w) {
    if (item.food > 0 && mpet.energy < 200) {
        mpet.energy += 75;
        item.food--;
    } else {

    }

    if (mpet.energy > 200) {
        mpet.energy = 200;
    } else if (mpet.energy < 0) mpet.energy = 0;
}

void play() {
    if (item.toy == false && you.energy > 0 && mpet.energy > 0) {
        you.energy -= 25;
        mpet.energy -= 25;
        mpet.happiness += 30;
    } else if (item.toy == true && you.energy > 0 && mpet.energy > 0) {
        you.energy -= 15;
        mpet.energy -= 25;
        mpet.happiness += 35;
    } else {

    }

    if (you.energy < 0) {
        you.energy = 0;
    } else if (mpet.energy < 0) {
        mpet.energy = 0;
    }
}

void work() {
    if (you.energy > 0) {
        you.energy -= 25;
        you.money += 120;
        mpet.happiness -= 4;
    } else {

    }

    if (you.energy < 0) you.energy = 0;
}

void rest() {
    if (you.energy == 0) {
        you.energy = 100;
        day++;
        loading(0);
    } else {}
}

int pp1 = 6;
int pp2 = 7;
int pp3 = 8;
int pp4 = 5;

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

void *loading_draw_pos(void *arg) {
    win = newwin(0, 0, 0, 0);
    p1 = newwin(5, 9, 6, (x - 46) / 2);
    p2 = newwin(4, 9, 7, (x - 26) / 2);
    p3 = newwin(3, 8, 8, (x - 6) / 2);
    p4 = newwin(6, 11, 5, (x + 12) / 2);
    load = newwin(6, 41, 11, (x - 41) / 2);

    loading_refresh();
    while (finished == false) {
        usleep(10000);
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

void shop_scr() {
    cindex = 0;
    code = 1;
    while (1) {
        gen_refresh();
        getmaxyx(stdscr, y, x);
        shop_scr_draw();
        usleep(10000);
        gen_refresh();
        shop_scr_key();
    }
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

void game_scr_key() {
    c = getch();
    switch (c) {
        case '\x1b' : pause_scr(); break;
        case 'l' : {
            if (cindex == 0) {
                feed(game);
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

void game_scr() {
    cindex = 0;
    code = 1;
    while (1) {
        gen_refresh();
        getmaxyx(stdscr, y, x);
        game_scr_draw();
        usleep(10000);
        gen_refresh();
        game_scr_key();
    }
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

void confirmation() {
    cindex = 0;
    while(1) {
        gen_refresh();
        getmaxyx(stdscr, y, x);
        confirmation_draw();
        usleep(10000);
        gen_refresh();
        confirmation_key();
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

void exit_prompt() {
    cindex = 0;
    while(1) {
        gen_refresh();
        getmaxyx(stdscr, y, x);
        exit_prompt_draw();
        usleep(10000);
        gen_refresh();
        exit_prompt_key();
    }
}

//Work in progress
void new_pet() {

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

void settings_key() {
    c = getch();
    switch (c) {
        case 'h' : {
            if (cindex != 4) {
                cindex = 0;
                return title_scr();
            }
            if (cindex ==4 && slider > 0) slider--;
        } break;

        case 'l' : {
            if (cindex == 4 && slider < 10) slider++;
        } break;
    }
    keyProcessing(4, c);
}

void settings() {
    cindex = 0;
    while (1) {
        gen_refresh();
        getmaxyx(stdscr, y, x);
        settings_draw();
        usleep(10000);
        gen_refresh();
        settings_key();
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

void title_scr_key() {
    c = getch();
    if (c == 'l' && cindex == 0) loading(1);
    if (c == 'l' && cindex == 2) settings();
    if (c == 'l' && cindex == 3) exit_prompt();
    keyProcessing(4, c);
}

void title_scr() {
    cindex = 0;
    code = 0;
    while (1) {
        gen_refresh();
        getmaxyx(stdscr, y, x);
        title_scr_draw();
        usleep(10000);
        gen_refresh();
        title_scr_key();
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

void pause_scr() {
    cindex = 0;
    code = 1;
    while (1) {
        gen_refresh();
        getmaxyx(stdscr, y, x);
        pause_scr_draw();
        usleep(10000);
        gen_refresh();
        pause_scr_key();
    }
}

int main() {
    initscr();
    noecho();
    curs_set(0);

    init();

    delwin(win);
    delwin(co);
    endwin();

    return 0;
}
