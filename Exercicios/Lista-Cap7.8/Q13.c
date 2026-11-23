#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(void) {
    char frase[200];
    int vogais = 0, consoantes = 0, espacos = 0;
    printf("Frase: ");
    fgets(frase, sizeof frase, stdin);
    for (size_t i = 0; i < strlen(frase); i++) {
        char c = (char)tolower((unsigned char)frase[i]);
        if (strchr("aeiou", c)) vogais++;
        else if (isalpha((unsigned char)c)) consoantes++;
        else if (c == ' ') espacos++;
    }
    printf("Vogais: %d\nConsoantes: %d\nEspacos: %d\n", vogais, consoantes, espacos);
    return 0;
}

