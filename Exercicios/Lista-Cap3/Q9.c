#include <stdio.h>
int main() {
    int num;
    
    printf("Digite um numero para ver sua tabuada: ");
    scanf("%d", &num);
    printf("\n--- TABUADA DO %d ---\n", num);

        for (int i = 1; i <= 10; i++) {
            printf("%2d x %2d = %4d\n", num, i, num * i);
        }

    return 0;
}