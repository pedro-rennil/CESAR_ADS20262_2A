#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand((unsigned int)time(NULL));

    int dado1 = (rand() % 6) + 1;
    int dado2 = (rand() % 6) + 1;
    int dado3 = (rand() % 6) + 1;

    printf("Valores sorteados nos dados:\n");
    printf("Dado 1: %d | Dado 2: %d | Dado 3: %d\n", dado1, dado2, dado3);

    return 0;
}