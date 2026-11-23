#include <stdio.h>

void exibeMenu(void);

void exibeMenu(void) {
    printf("1 - Cadastrar\n");
    printf("2 - Listar\n");
    printf("3 - Remover\n");
    printf("0 - Sair\n");
}

int main(void) {
    int opcao;
    exibeMenu();
    scanf("%d", &opcao);
    switch (opcao) {
        case 1: printf("Opcao Cadastrar\n"); break;
        case 2: printf("Opcao Listar\n"); break;
        case 3: printf("Opcao Remover\n"); break;
        case 0: printf("Saindo\n"); break;
        default: printf("Opcao invalida\n");
    }
    return 0;
}
