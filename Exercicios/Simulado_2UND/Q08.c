#include <stdio.h>

int somaDigitos(int n);
long potencia(int base, int exp);

int somaDigitos(int n) {
    if (n < 0) n = -n;
    if (n < 10) return n;
    return n % 10 + somaDigitos(n / 10);
}

long potencia(int base, int exp) {
    if (exp == 0) return 1;
    return base * potencia(base, exp - 1);
}

int main(void) {
    int n, base, exp;
    scanf("%d%d%d", &n, &base, &exp);
    printf("Soma dos digitos: %d\n", somaDigitos(n));
    printf("Potencia: %ld\n", potencia(base, exp));
    return 0;
}
