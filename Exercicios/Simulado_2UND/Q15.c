#include <stdio.h>
#include <string.h>

int main(void) {
    char convidados[5][30], nome[30];
    int encontrado = 0;

    for (int i = 0; i < 5; i++) {
        fgets(convidados[i], sizeof(convidados[i]), stdin);
        convidados[i][strcspn(convidados[i], "\n")] = '\0';
    }
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';

    for (int i = 0; i < 5; i++) {
        if (strcmp(nome, convidados[i]) == 0) {
            printf("Nome encontrado na posicao %d.\n", i + 1);
            encontrado = 1;
            break;
        }
    }
    if (!encontrado) printf("Nome nao encontrado.\n");
    return 0;
}
