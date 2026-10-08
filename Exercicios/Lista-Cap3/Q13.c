#include <stdio.h>
int main() {
    int n;
    printf("Digite um numero inteiro nao-negativo: ");
    scanf("%d", &n);
    if (n < 0) {
        printf("Erro: Nao existe fatorial de numero negativo!\n");
    }
    else{
        long long int fat = 1;

        for (int i = 1; i <= n; i++) {
            fat *= i;
        }
        printf("%d! = %lld\n", n, fat);
    }
    return 0;
}