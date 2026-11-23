#include <stdio.h>

long potencia(int base, int expoente);

long potencia(int base, int expoente) {
    if (expoente == 0) { /* Caso base. */
        return 1;
    }
    return base * potencia(base, expoente - 1); /* Passo recursivo. */
}

int main(void) {
    int base, expoente;
    scanf("%d %d", &base, &expoente);
    if (expoente < 0) {
        printf("O expoente deve ser nao negativo.\n");
        return 0;
    }
    printf("Resultado = %ld\n", potencia(base, expoente));
    return 0;
}
