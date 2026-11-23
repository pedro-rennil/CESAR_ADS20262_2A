#include <stdio.h>

int ehPar(int n);

int ehPar(int n) {
    return n % 2 == 0;
}

int main(void) {
    int n;
    scanf("%d", &n);
    printf("%d %s par.\n", n, ehPar(n) ? "e" : "nao e");
    return 0;
}
