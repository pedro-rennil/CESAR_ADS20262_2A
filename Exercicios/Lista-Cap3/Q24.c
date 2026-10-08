#include <stdio.h>

int main() {
    int n;
    printf("Digite uma dimensao impar N (3 a 19): ");
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (j == i || j == (n - i + 1)) {
                printf("*");
                }
                else {
                    printf(" ");
            }
        }
        printf("\n");
    }
    return 0;
}