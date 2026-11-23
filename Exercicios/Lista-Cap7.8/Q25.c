#include <stdio.h>

enum Mes { Jan = 1, Fev, Mar, Abr, Mai, Jun, Jul, Ago, Set, Out, Nov, Dez };

int main(void) {
    const char *nomes[] = {"", "Janeiro", "Fevereiro", "Marco", "Abril", "Maio",
                           "Junho", "Julho", "Agosto", "Setembro", "Outubro", "Novembro", "Dezembro"};
    int dmes[] = {0,31,28,31,30,31,30,31,31,30,31,30,31}, mes;
    scanf("%d", &mes);
    if (mes >= Jan && mes <= Dez) printf("%s\n", nomes[mes]);
    else printf("Mes invalido\n");
    for (int i = Jan; i <= Dez; i++) printf("%d - %d dias\n", i, dmes[i]);
    return 0;
}

