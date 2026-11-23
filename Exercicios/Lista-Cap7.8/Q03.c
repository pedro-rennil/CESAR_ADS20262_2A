#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
    int valores[30], frequencia[6] = {0};
    srand((unsigned)time(NULL));
    for (int i = 0; i < 30; i++) {
        valores[i] = rand() % 6 + 1;
        frequencia[valores[i] - 1]++;
    }
    for (int i = 0; i < 6; i++)
        printf("Face %d: %d vezes\n", i + 1, frequencia[i]);
    return 0;
}

