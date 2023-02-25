#include "philosophers.h"

int main()
{
	unsigned args[THINKERS];
	pthread_t thinkers[THINKERS];

	// create the chopsticks
	for (size_t i = 0; i < THINKERS; i++) {
		if (sem_init(chopsticks + i, 0, 1) != 0) {
			perror("unable to initialize mutex");
			return 1;
		}
	}

	// launch threads
	for (size_t i = 0; i < THINKERS; i++) {
		args[i] = i;
		if (pthread_create(thinkers + i, NULL, dine, args + i) != 0) {
			perror("unable to create thread");
			return 1;
		}
	}
	// wait for threads to finish
	for (size_t i = 0; i < THINKERS; i++) {
		if (pthread_join(thinkers[i], NULL) != 0) {
			perror("unable to join thread");
			return 1;
		}
	}
	// remove the chopsticks
	for (size_t i = 0; i < THINKERS; i++) {
		if (sem_destroy(chopsticks + i) != 0) {
			perror("unable to destroy mutex");
			return 1;
		}
	}
	return 0;
}




void* dine(void* arg) {
	const unsigned id = *((unsigned *) arg);
	while (true) {
		if (id % 2 == 0){
			sem_wait(chopsticks + id);
			sem_wait(chopsticks + ((id + 1) % THINKERS));
		} else {
			sem_wait(chopsticks + ((id + 1) % THINKERS));
			sem_wait(chopsticks + id);
		}
		printf("Philosopher %u is eating\n", id);
		if (id % 2 == 0){
			sem_post(chopsticks + id);
			sem_post(chopsticks + ((id + 1) % THINKERS));
		} else {
			sem_post(chopsticks + ((id + 1) % THINKERS));
			sem_post(chopsticks + id);
		}

	}
	return NULL;
}