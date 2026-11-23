#include <stdio.h>
#include <string.h>

int main(void) {
    const char correta[] = "c@esar2026";
    char senha[100];
    int tentativas = 0, acesso = 0;
    while (tentativas < 3 && !acesso) {
        printf("Senha: ");
        scanf("%99s", senha);
        if (strlen(senha) < 6) {
            printf("A senha deve ter pelo menos 6 caracteres.\n");
            continue;
        }
        tentativas++;
        acesso = strcmp(senha, correta) == 0;
        if (!acesso) printf("Senha incorreta.\n");
    }
    printf("%s\n", acesso ? "Acesso liberado" : "Acesso bloqueado");
    return 0;
}

