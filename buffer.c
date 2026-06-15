#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include "buffer.h"
#include "logger.h"

static pthread_mutex_t print_mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t operation_mutex = PTHREAD_MUTEX_INITIALIZER;

int buffer[BUFFER_SIZE];
int in = 0;
int out = 0;

pthread_mutex_t mutex;
sem_t empty_slots;
sem_t full_slots;

void init_buffer(void)
{
    for (int i = 0; i < BUFFER_SIZE; i++)
    {
        buffer[i] = BUFFER_EMPTY;
    }

    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty_slots, 0, BUFFER_SIZE);
    sem_init(&full_slots, 0, 0);
}


void produce_item(int producer_id)
{
    int item = rand() % 100;

    sem_wait(&empty_slots);
    if (!running) {
        sem_post(&empty_slots);
        return;
    }
    pthread_mutex_lock(&operation_mutex);
    pthread_mutex_lock(&mutex);

    buffer[in] = item;
    in = (in + 1) % BUFFER_SIZE;

    pthread_mutex_unlock(&mutex);
    sem_post(&full_slots);

    log_produced(producer_id, item);
    sleep(1);
    pthread_mutex_unlock(&operation_mutex);
}

void consume_item(int consumer_id)
{
    sem_wait(&full_slots);
    if (!running) {
        sem_post(&full_slots);
        return;
    }
    pthread_mutex_lock(&operation_mutex);
    pthread_mutex_lock(&mutex);

    int item = buffer[out];
    buffer[out] = BUFFER_EMPTY;
    out = (out + 1) % BUFFER_SIZE;

    pthread_mutex_unlock(&mutex);
    sem_post(&empty_slots);

    log_consumed(consumer_id, item);
    sleep(1);
    pthread_mutex_unlock(&operation_mutex);
}

void log_and_print(const char *msg)
{
    pthread_mutex_lock(&print_mutex);
    printf("%s", msg);
    printf("Buffer: [");
    for (int i = 0; i < BUFFER_SIZE; i++)
    {
        if (buffer[i] == BUFFER_EMPTY)
        {
            printf(" -");
        }
        else
        {
            printf("%2d", buffer[i]);
        }
        if (i < BUFFER_SIZE - 1)
        {
            printf(" |");
        }
    }
    printf(" ]\n");
    pthread_mutex_unlock(&print_mutex);
}
