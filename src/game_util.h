#ifndef GAME_UTIL_H
#define GAME_UTIL_H

#include <pthread.h>

extern pthread_t thread1; //For rendering/drawing interfaces
extern pthread_t thread2; //For logic processing
extern pthread_t thread3; //Other processing

void gen_refresh();
void loading_refresh();
void loading_cleanup();
void return_logic(int code);
void return_bridger(int from,int code, int to);

#endif
