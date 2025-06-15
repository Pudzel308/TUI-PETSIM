#ifndef ENTITY_H
#define ENTITY_H

extern int bunny;
extern int cat;
extern int dog;
extern int hamster;

extern int day;

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

extern struct Pet mpet;
extern struct Player you;
extern struct Inventory item;

void init();

#endif
