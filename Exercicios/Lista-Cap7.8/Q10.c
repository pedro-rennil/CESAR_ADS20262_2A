#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define JOGOS 5

int repetido(int jogo[], int n, int valor);

int repetido(int jogo[], int n, int valor) {
    for (int i = 0; i < n; i++) if (jogo[i] == valor) return 1;
    return 0;
}

int main(void) {
    int jogos[JOGOS][6];
    srand((unsigned)time(NULL));
    for (int i = 0; i < JOGOS; i++) {
        for (int j = 0; j < 6; j++) {
            do jogos[i][j] = rand() % 60 + 1;
            while (repetido(jogos[i], j, jogos[i][j]));
            printf("%2d ", jogos[i][j]);
        }
        printf("\n");
    }
    return 0;
}

