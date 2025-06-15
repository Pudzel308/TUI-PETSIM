#include <stdbool.h>

#include "entity.h"
#include "screen.h"

int bunny = 5;
int cat = 16;
int dog = 14;
int hamster = 4;

int day = 1;

struct Pet mpet;
struct Player you;
struct Inventory item;

void init() {
    mpet.age = 0;
    mpet.ageCap = bunny;
    mpet.energy = 200;
    mpet.happiness = 100;

    you.money = 2000;
    you.energy = 100;

    item.food = 2;

    title_scr();
}


