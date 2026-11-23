#include <stdio.h>

typedef enum { INTEIRO, REAL, CARACTERE } Tipo;
typedef union { int i; float f; char c; } Valor;
typedef struct { Tipo tipo; Valor valor; } Registro;

int main(void) {
    Registro registros[3];
    for (int i = 0; i < 3; i++) {
        scanf("%d", (int *)&registros[i].tipo);
        if (registros[i].tipo == INTEIRO) scanf("%d", &registros[i].valor.i);
        else if (registros[i].tipo == REAL) scanf("%f", &registros[i].valor.f);
        else scanf(" %c", &registros[i].valor.c);
    }
    for (int i = 0; i < 3; i++) {
        if (registros[i].tipo == INTEIRO) printf("%d\n", registros[i].valor.i);
        else if (registros[i].tipo == REAL) printf("%.2f\n", registros[i].valor.f);
        else printf("%c\n", registros[i].valor.c);
    }
    /* A union ocupa o tamanho do maior membro, suficiente para qualquer valor. */
    printf("sizeof(Valor): %zu\n", sizeof(Valor));
    return 0;
}

