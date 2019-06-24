#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <signal.h>
#include <stdlib.h>
#include <time.h>

#define TOTAL 8192

const char toto[] = "doo doo doo doo do do doo doo doooooooo\n";
const int toto_len = sizeof(toto);
const char rains[] = "I BLESS THE RAINS DOWN IN AFFFFFFFRICA\n";
const int rains_len = sizeof(rains);
static bool keepRunning = true;
static struct sigaction act;
int count = 0;

void intHandler(int null) {
    keepRunning = false;
}

int main(int argc, char *argv[]) {
    clock_t begin = clock(); // Start the clock!
    act.sa_handler = intHandler;
    sigaction(SIGINT, &act, NULL);

    // Toto buffer
    char *toto_buf = malloc(TOTAL);
    int toto_bufused = 0;
    int x;
    while (toto_bufused < TOTAL) {
        memcpy(toto_buf+toto_bufused, toto, toto_len);
        toto_bufused += toto_len;
    }

    // Rains buffer
    char *rains_buf = malloc(TOTAL);
    int rains_bufused = 0;
    int y;
    while (rains_bufused < TOTAL) {
        memcpy(rains_buf+rains_bufused, rains, rains_len);
        rains_bufused += rains_len;
    }
    
    // toto'ing happens here
    while (keepRunning) {
        int r = rand() % 10;
        if(r <= 2) {
            write(1, rains_buf, TOTAL);
        } else {
            write(1, toto_buf, TOTAL);
        }
        ++count;
    }

    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("\n");
    printf("You toto'd %d times in %f seconds\n", count * (TOTAL /strlen(toto)), time_spent);
    return 0;
}