#ifndef PHIL_H
#define PHIL_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>
#define THINKERS 5
static sem_t chopsticks[THINKERS];

struct timespec eatingtime = {
	0,
	100000000
};

void* dine(void* arg);


#endif