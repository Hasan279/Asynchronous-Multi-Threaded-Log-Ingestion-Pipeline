#include <stdio.h>
#include "buffer.h"

void *consumer(void *arg) {
    int id = *(int *)arg;

    while (running) {
        consume_item(id);
    }

    return NULL;
}