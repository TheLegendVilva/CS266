#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5

pthread_mutex_t mutex;
pthread_cond_t cond_vars[NUM_PHILOSOPHERS];
enum {THINKING, HUNGRY, EATING} states[NUM_PHILOSOPHERS];

void test(int philosopher_number) {
    if (states[philosopher_number] == HUNGRY && states[(philosopher_number + 1) % NUM_PHILOSOPHERS] != EATING && states[(philosopher_number + NUM_PHILOSOPHERS - 1) % NUM_PHILOSOPHERS] != EATING) {
        states[philosopher_number] = EATING;
        printf("Philosopher %d starts eating.\n", philosopher_number);
        pthread_cond_signal(&cond_vars[philosopher_number]);
    }
}

void pickup_forks(int philosopher_number) {
    pthread_mutex_lock(&mutex);
    states[philosopher_number] = HUNGRY;
    test(philosopher_number);
    while (states[philosopher_number] != EATING) {
        pthread_cond_wait(&cond_vars[philosopher_number], &mutex);
    }
    pthread_mutex_unlock(&mutex);
}

void return_forks(int philosopher_number) {
    pthread_mutex_lock(&mutex);
    states[philosopher_number] = THINKING;
    printf("Philosopher %d finishes eating.\n", philosopher_number);
    test((philosopher_number + NUM_PHILOSOPHERS - 1) % NUM_PHILOSOPHERS);
    test((philosopher_number + 1) % NUM_PHILOSOPHERS);
    pthread_mutex_unlock(&mutex);
}

void *philosopher(void *arg) {
    int philosopher_number = *(int *) arg;
    while (1) {
        printf("Philosopher %d is thinking.\n", philosopher_number);
        sleep(rand() % 3 + 1);  
        printf("Philosopher %d is hungry.\n", philosopher_number);
        pickup_forks(philosopher_number);
        sleep(rand() % 3 + 1); 
        return_forks(philosopher_number);
    }
    return NULL;
}

int main(void) {
    pthread_t philosophers[NUM_PHILOSOPHERS];
    int philosopher_numbers[NUM_PHILOSOPHERS];
    int i;
    pthread_mutex_init(&mutex, NULL);
    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_cond_init(&cond_vars[i], NULL);
        philosopher_numbers[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &philosopher_numbers[i]);
    }
    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(philosophers[i], NULL);
    }
    pthread_mutex_destroy(&mutex);
    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_cond_destroy(&cond_vars[i]);
    }
    return 0;
}