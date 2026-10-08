#include <stdio.h>

int main() {
    int l;
    printf("Digite o tamanho do lado L (3 a 20): ");
    scanf("%d", &l);

    for (int i = 1; i <= l; i++) {
        for (int j = 1; j <= l; j++) {
            if (i == 1 || i == l || j == 1 || j == l) {
                printf("X");
                }
                else{
                    printf(" ");
            }
        }
        printf("\n");
    }
    return 0;
}