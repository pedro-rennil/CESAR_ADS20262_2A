#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
    int m[4][4], principal = 0, secundaria = 0, acima = 0;
    srand((unsigned)time(NULL));
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            m[i][j] = rand() % 20 + 1;
            printf("%4d", m[i][j]);
            if (i == j) principal += m[i][j];
            if (i + j == 3) secundaria += m[i][j];
            if (j > i) acima += m[i][j];
        }
        printf("\n");
    }
    printf("Diagonal principal: %d\nDiagonal secundaria: %d\nAcima: %d\n",
           principal, secundaria, acima);
    return 0;
}

