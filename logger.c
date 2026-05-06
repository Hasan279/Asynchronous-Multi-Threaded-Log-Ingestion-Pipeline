#include <stdio.h>
#include <time.h>
#include "logger.h"
#include "buffer.h"

int total_produced = 0;
int total_consumed = 0;

static double get_time() {
    static time_t start = 0;
    if (start == 0)
    {
        start = time(NULL);
    }
    return difftime(time(NULL), start);
}

void log_produced(int producer_id, int item) {
    total_produced++;
    char msg[64];
    snprintf(msg, sizeof(msg), "[%.0fs] Producer-%d inserted: %2d\n", get_time(), producer_id, item);
    log_and_print(msg);
}

void log_consumed(int consumer_id, int item) {
    total_consumed++;
    char msg[64];
    snprintf(msg, sizeof(msg), "[%.0fs] Consumer-%d removed:  %2d\n", get_time(), consumer_id, item);
    log_and_print(msg);
}

void print_stats() {
    printf("\n=============================\n");
    printf("     Simulation Complete\n");
    printf("=============================\n");
    printf(" Total Produced : %d\n", total_produced);
    printf(" Total Consumed : %d\n", total_consumed);
    printf("=============================\n");
}