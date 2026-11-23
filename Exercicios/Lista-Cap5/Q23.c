#include <stdio.h>

#define DOBRO(x) x * 2

int dobro(int x);

int dobro(int x) {
    return x * 2;
}

int main(void) {
    int resultadoMacro, resultadoFuncao, resultadoMacroCorrigida;
    resultadoMacro = DOBRO(2 + 3);
    resultadoFuncao = dobro(2 + 3);
#undef DOBRO
#define DOBRO(x) ((x) * 2)
    resultadoMacroCorrigida = DOBRO(2 + 3);
    printf("Macro sem protecao = %d\n", resultadoMacro);
    printf("Funcao = %d\n", resultadoFuncao);
    printf("Macro corrigida = %d\n", resultadoMacroCorrigida);
    /* Sem parenteses, DOBRO(2 + 3) vira 2 + 3 * 2 e resulta em 8. */
    return 0;
}
