#include <stdio.h>

int somaAteN(int n);

int somaAteN(int n) {
    int soma = 0;
    int i;
    for (i = 1; i <= n; i++) {
        soma += i;
#ifdef DEBUG
        printf("Parcial apos %d = %d\n", i, soma);
#endif
    }
    return soma;
}

int main(void) {
    int n;
    scanf("%d", &n);
    if (n < 0) {
        printf("O numero deve ser nao negativo.\n");
        return 0;
    }
    /*
     * Sem DEBUG, somente o resultado final e exibido.
     * Com DEBUG, tambem sao exibidos os valores parciais dentro do laco.
     * Exemplo de compilacao: gcc Q24.c -DDEBUG -o Q24_debug
     */
    printf("Soma = %d\n", somaAteN(n));
    return 0;
}
