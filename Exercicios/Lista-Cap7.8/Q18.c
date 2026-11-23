#include <stdio.h>
#include <string.h>

int main(void) {
    char nomes[3][80], aux[80];
    for (int i = 0; i < 3; i++) scanf("%79s", nomes[i]);
    for (int i = 0; i < 2; i++)
        for (int j = i + 1; j < 3; j++)
            if (strcmp(nomes[i], nomes[j]) > 0) {
                strcpy(aux, nomes[i]); strcpy(nomes[i], nomes[j]); strcpy(nomes[j], aux);
            }
    for (int i = 0; i < 3; i++) puts(nomes[i]);
    return 0;
}

