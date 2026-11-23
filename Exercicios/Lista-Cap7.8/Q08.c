#include <stdio.h>

int main(void) {
    int m[3][4], t[4][3];
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 4; j++) {
            scanf("%d", &m[i][j]);
            t[j][i] = m[i][j];
        }
    printf("Original:\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) printf("%4d", m[i][j]);
        printf("\n");
    }
    printf("Transposta:\n");
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) printf("%4d", t[i][j]);
        printf("\n");
    }
    return 0;
}

