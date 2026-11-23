#include <stdio.h>

int main(void) {
    int ocup[3][2][4], geral = 0;
    for (int b = 0; b < 3; b++)
        for (int a = 0; a < 2; a++)
            for (int p = 0; p < 4; p++) scanf("%d", &ocup[b][a][p]);
    for (int b = 0; b < 3; b++) {
        int total = 0;
        for (int a = 0; a < 2; a++)
            for (int p = 0; p < 4; p++) total += ocup[b][a][p];
        printf("Bloco %d: %d moradores\n", b + 1, total);
        geral += total;
    }
    printf("Total geral: %d moradores\n", geral);
    return 0;
}

