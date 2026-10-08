#include <stdio.h>
void contagem_for() {
    for (int i = 0; i <= 100; i++) printf("%d \n", i);
}
void contagem_while() {
    int i = 0;
    while (i <= 100) { printf("%d \n", i); i++; }
}
void contagem_dowhile() {
    int i = 0;
    do { printf("%d ", i); i++; } while (i <= 100);
}
/* A estrutura 'for' é a mais adequada pois o número de iterações
é fixo e conhecido antecipadamente (0 a 100). */

int main (){
    contagem_for();
    contagem_while();
    contagem_dowhile();

    return 0;
}