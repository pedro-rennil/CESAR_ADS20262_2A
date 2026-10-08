#include <stdio.h>

int main() {
    const int SENHA_CORRETA = 2026;
    int senha_digitada, tentativas = 0, acesso = 0;
    
    while (tentativas < 3 && !acesso) {
        printf("Digite a senha (Tentativa %d de 3): ", tentativas + 1);
        scanf("%d", &senha_digitada);
        tentativas++;
        if (senha_digitada == SENHA_CORRETA) {
            acesso = 1;
        } else{
            printf("Senha incorreta!\n");
        }
    }
    if (acesso) {
        printf("\nAcesso Concedido! (Tentativas usadas: %d)\n", tentativas);
    } else{
        printf("\nConta Bloqueada por Seguranca!\n");
    }
    return 0;
}