#include <stdio.h>
#include <string.h>

int main(void) {
    char nome[60], sobrenome[60], completo[125];
    scanf("%59s%59s", nome, sobrenome);
    strcpy(completo, sobrenome);
    strcat(completo, ", ");
    strcat(completo, nome);
    puts(completo);
    printf("Caracteres: %zu\n", strlen(completo));
    return 0;
}

