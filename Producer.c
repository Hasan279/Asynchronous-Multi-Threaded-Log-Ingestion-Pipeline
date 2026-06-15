#include <stdio.h>
#include "Producer.h"
#include "buffer.h"

void *producer(void *arg) {
    int id = *(int *)arg;

    while (running) {
        produce_item(id);
    }

    return NULL;
}