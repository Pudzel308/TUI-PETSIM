#include <ncurses.h>
#include <unistd.h>

#include "PetSim.h"
#include "entity.h"
#include "ui.h"
#include "screen.h"

void feed() {
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
