#include <stdio.h>

typedef enum { VISITANTE = 1, USUARIO, ADMIN } Nivel;

typedef struct {
    char nome[80];
    Nivel nivel;
} Usuario;

int main(void) {
    Usuario usuario;
    int nivel;

    scanf(" %79[^\n]", usuario.nome);
    scanf("%d", &nivel);
    usuario.nivel = (Nivel)nivel;
    printf("Usuario: %s\n", usuario.nome);
    switch (usuario.nivel) {
        case VISITANTE:
            printf("Permissoes: apenas leitura.\n");
            break;
        case USUARIO:
            printf("Permissoes: leitura e escrita.\n");
            break;
        case ADMIN:
            printf("Permissoes: leitura, escrita e gerenciamento de usuarios.\n");
            break;
        default:
            printf("Nivel invalido.\n");
    }
    return 0;
}
