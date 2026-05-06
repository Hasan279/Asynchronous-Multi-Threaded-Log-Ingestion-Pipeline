#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "buffer.h"
#include "Producer.h"
#include "Consumer.h"
#include "logger.h"

#define NUM_PRODUCERS 3
#define NUM_CONSUMERS 3
#define SIM_DURATION 15

int running = 1;

int main() {
    printf("=== Producer-Consumer Simulation ===\n\n");

    init_buffer();

    pthread_t prod_threads[NUM_PRODUCERS];
    pthread_t cons_threads[NUM_CONSUMERS];

    int prod_ids[NUM_PRODUCERS];
    int cons_ids[NUM_CONSUMERS];

    for (int i = 0; i < NUM_PRODUCERS; i++) {
        prod_ids[i] = i + 1;
        pthread_create(&prod_threads[i], NULL, producer, &prod_ids[i]);
    }

    for (int i = 0; i < NUM_CONSUMERS; i++) {
        cons_ids[i] = i + 1;
        pthread_create(&cons_threads[i], NULL, consumer, &cons_ids[i]);
    }

    sleep(SIM_DURATION);

    running = 0;

    for (int i = 0; i < NUM_PRODUCERS + BUFFER_SIZE; i++) {
        sem_post(&empty_slots);
    }
    for (int i = 0; i < NUM_CONSUMERS + BUFFER_SIZE; i++) {
        sem_post(&full_slots);
    }

    for (int i = 0; i < NUM_PRODUCERS; i++) {
        pthread_join(prod_threads[i], NULL);
    }
    for (int i = 0; i < NUM_CONSUMERS; i++) {
        pthread_join(cons_threads[i], NULL);
    }

    print_stats();

    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty_slots);
    sem_destroy(&full_slots);

    return 0;
}