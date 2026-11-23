#include <stdio.h>

int mdc(int a, int b);
void simplifica(int num, int den);

int mdc(int a, int b) {
    if (b == 0) {
        return a;
    }
    return mdc(b, a % b);
}

void simplifica(int num, int den) {
    int divisor = mdc(num, den);
    printf("Fracao simplificada = %d/%d\n", num / divisor, den / divisor);
}

int main(void) {
    int a, b;
    scanf("%d %d", &a, &b);
    if (a <= 0 || b <= 0) {
        printf("Os numeros devem ser positivos.\n");
        return 0;
    }
    printf("MDC = %d\n", mdc(a, b));
    simplifica(a, b);
    return 0;
}
