#include <stdio.h>

void contagem(int n);
void contagemCrescente(int n);

void contagem(int n) {
    if (n == 0) {
        printf("Fogo!\n");
        return;
    }
    printf("%d\n", n);
    contagem(n - 1);
}

void contagemCrescente(int n) {
    if (n == 0) {
        return;
    }
    contagemCrescente(n - 1);
    printf("%d\n", n);
    /* Aqui o printf fica depois da chamada, na fase de desempilhamento. */
}

int main(void) {
    int n;
    scanf("%d", &n);
    if (n <= 0) {
        printf("O numero deve ser positivo.\n");
        return 0;
    }
    contagem(n);
    printf("Contagem crescente:\n");
    contagemCrescente(n);
    return 0;
}
