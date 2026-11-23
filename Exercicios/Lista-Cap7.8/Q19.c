#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(void) {
    char nomes[5][30], letra;
    int maior = 0, menor = 0, iguais = 0;
    for (int i = 0; i < 5; i++) {
        fgets(nomes[i], sizeof nomes[i], stdin);
        nomes[i][strcspn(nomes[i], "\n")] = '\0';
    }
    letra = (char)tolower((unsigned char)nomes[0][0]);
    for (int i = 0; i < 5; i++) {
        if (strlen(nomes[i]) > strlen(nomes[maior])) maior = i;
        if (strlen(nomes[i]) < strlen(nomes[menor])) menor = i;
        if ((char)tolower((unsigned char)nomes[i][0]) == letra) iguais++;
    }
    printf("Mais longo: %s\nMais curto: %s\nMesma inicial: %d\n",
           nomes[maior], nomes[menor], iguais);
    return 0;
}

