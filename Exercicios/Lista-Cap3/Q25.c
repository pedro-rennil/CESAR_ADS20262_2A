#include <stdio.h>

int main() {
    int n, divisores = 0;
    printf("Digite um numero inteiro positivo: ");
    scanf("%d", &n);

    if (n <= 1) {
    
        printf("O numero %d NAO eh primo.\n", n);
    }
    else {
        for (int i = 1; i <= n; i++) {
            if (n % i == 0) divisores++;
        }
        if (divisores == 2) {
            printf("O numero %d EH PRIMO! (Possui exatamente 2 divisores)\n", n);
        }
        else{
            printf("O numero %d NAO eh primo. (Possui %d divisores)\n", n, divisores);
        }
    }
    return 0;
}