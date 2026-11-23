#include <stdio.h>

int soma(int a, int b);

int soma(int a, int b) {
    return a + b;
}

int main(void) {
    int a, b;
    scanf("%d %d", &a, &b);
    printf("Soma = %d\n", soma(a, b));
    return 0;
}
