#include <stdio.h>
#include <string.h>

typedef struct { char nome[60]; float peso; int calorias; } Dieta;

int main(void) {
    Dieta d[5]; int mais = 0, total = 0;
    for (int i = 0; i < 5; i++) {
        scanf(" %59[^\n]", d[i].nome);
        scanf("%f%d", &d[i].peso, &d[i].calorias);
        total += d[i].calorias;
        if (d[i].calorias > d[mais].calorias) mais = i;
    }
    for (int i = 0; i < 5; i++) printf("%s - %.1fg - %d kcal\n", d[i].nome, d[i].peso, d[i].calorias);
    printf("Total: %d kcal\nMais calorico: %s\n", total, d[mais].nome);
    return 0;
}

