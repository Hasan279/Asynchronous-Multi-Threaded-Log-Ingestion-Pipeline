#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include "buffer.h"
#include "Producer.h"
#include "Consumer.h"
#include "logger.h"

// #define NUM_PRODUCERS 3
// #define NUM_CONSUMERS 3
#define SIM_DURATION 15

volatile int running = 1;

int main()
{
    srand((unsigned int)time(NULL));

    printf("simulations\n");

    // 2 prods
    printf("2 prods\n");
    total_produced = 0;
    total_consumed = 0;
    running = 1;
    init_buffer();

    pthread_t prod_threads_case1[2];
    int prod_ids_case1[2] = {1, 2};

    for (int i = 0; i < 2; i++)
    {
        pthread_create(&prod_threads_case1[i], NULL, producer, &prod_ids_case1[i]);
    }

    sleep(SIM_DURATION);
    running = 0;

    for (int i = 0; i < 2 + BUFFER_SIZE; i++)
    {
        sem_post(&empty_slots);
    }
    for (int i = 0; i < BUFFER_SIZE; i++)
    {
        sem_post(&full_slots);
    }

    for (int i = 0; i < 2; i++)
    {
        pthread_join(prod_threads_case1[i], NULL);
    }

    print_stats();
    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty_slots);
    sem_destroy(&full_slots);

    // one prod one cons
    printf("one producer one cons\n");
    // total_produced = 0;
    // total_consumed = 0;
    // running = 1;
    // init_buffer();
    //
    // pthread_t prod_threads_case2[1];
    // pthread_t cons_threads_case2[1];
    // int prod_ids_case2[1] = {1};
    // int cons_ids_case2[1] = {1};
    //
    // pthread_create(&prod_threads_case2[0], NULL, producer, &prod_ids_case2[0]);
    // pthread_create(&cons_threads_case2[0], NULL, consumer, &cons_ids_case2[0]);
    //
    // sleep(SIM_DURATION);
    // running = 0;
    //
    // for (int i = 0; i < 1 + BUFFER_SIZE; i++)
    // {
    //     sem_post(&empty_slots);
    // }
    // for (int i = 0; i < 1 + BUFFER_SIZE; i++)
    // {
    //     sem_post(&full_slots);
    // }
    //
    // pthread_join(prod_threads_case2[0], NULL);
    // pthread_join(cons_threads_case2[0], NULL);
    //
    // print_stats();
    // pthread_mutex_destroy(&mutex);
    // sem_destroy(&empty_slots);
    // sem_destroy(&full_slots);

    // printf("2 cons");
    // total_produced = 0;
    // total_consumed = 0;
    // running = 1;
    // init_buffer();
    //
    // pthread_t cons_threads_case3[2];
    // int cons_ids_case3[2] = {1, 2};
    //
    // for (int i = 0; i < 2; i++)
    // {
    //     pthread_create(&cons_threads_case3[i], NULL, consumer, &cons_ids_case3[i]);
    // }
    //
    // sleep(SIM_DURATION);
    // running = 0;
    //
    // for (int i = 0; i < BUFFER_SIZE; i++)
    // {
    //     sem_post(&empty_slots);
    // }
    // for (int i = 0; i < 2 + BUFFER_SIZE; i++)
    // {
    //     sem_post(&full_slots);
    // }
    //
    // for (int i = 0; i < 2; i++)
    // {
    //     pthread_join(cons_threads_case3[i], NULL);
    // }
    //
    // print_stats();
    // pthread_mutex_destroy(&mutex);
    // sem_destroy(&empty_slots);
    // sem_destroy(&full_slots);

    return 0;
}