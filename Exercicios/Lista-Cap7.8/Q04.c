#include <stdio.h>

int main(void) {
    int dmes[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
    int dia, mes, passados = 0, total = 365;
    printf("Dia e mes: ");
    scanf("%d%d", &dia, &mes);
    for (int i = 0; i < mes - 1; i++) passados += dmes[i];
    passados += dia - 1;
    printf("Dias desde 1 de janeiro: %d\n", passados);
    printf("Dias que faltam para o fim do ano: %d\n", total - passados - 1);
    return 0;
}

