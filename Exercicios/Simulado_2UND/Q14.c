#include <stdio.h>
#include <string.h>

int main(void) {
    char mensagem[500];
    int k;

    fgets(mensagem, sizeof(mensagem), stdin);
    mensagem[strcspn(mensagem, "\n")] = '\0';
    scanf("%d", &k);
    k %= 26;
    if (k < 0) k += 26;

    for (int i = 0; mensagem[i] != '\0'; i++) {
        if (mensagem[i] >= 'A' && mensagem[i] <= 'Z') {
            mensagem[i] = (char)('A' + (mensagem[i] - 'A' + k) % 26);
        }
    }
    puts(mensagem);
    return 0;
}
