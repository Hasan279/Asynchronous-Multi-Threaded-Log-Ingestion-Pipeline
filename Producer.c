#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "Producer.h"
#include "logger.h"

void *producer(void *arg) {
    int id = *(int *)arg;

    while (running) {
        int item = rand() % 100;
        insert_item(item);
        log_produced(id, item);

        sleep(rand() % 2 + 1);
    }

    return NULL;
}