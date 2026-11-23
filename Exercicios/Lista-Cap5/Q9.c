#include <stdio.h>

int maior(int a, int b);

int maior(int a, int b) {
    return a > b ? a : b;
}

int main(void) {
    int a, b;
    scanf("%d %d", &a, &b);
    printf("Maior = %d\n", maior(a, b));
    return 0;
}
