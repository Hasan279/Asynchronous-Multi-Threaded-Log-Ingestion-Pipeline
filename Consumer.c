#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "buffer.h"
#include "logger.h"

void *consumer(void *arg) {
    int id = *(int *)arg;

    while (running) {
        int item = remove_item();
        log_consumed(id, item);

        sleep(rand() % 3 + 1);
    }

    return NULL;
}