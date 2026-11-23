#include <stdio.h>

int ehBissexto(int ano);

int ehBissexto(int ano) {
    return ano % 400 == 0 || (ano % 4 == 0 && ano % 100 != 0);
}

int main(void) {
    int ano;
    scanf("%d", &ano);
    printf("%d %s bissexto.\n", ano, ehBissexto(ano) ? "e" : "nao e");
    return 0;
}
