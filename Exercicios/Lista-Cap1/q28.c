#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int n1, n2, n3;
    double media;
    printf("Insira tres numeros inteiros separados por espaco: ");
    
    if (scanf("%d %d %d", &n1, &n2, &n3) != 3) {
        printf("Entrada invalida. Insira tres inteiros.\n");
        return 1;
    }

    media = (double)(n1 + n2 + n3) / 3.0;
    printf("A media aritmetica simples e: %.2f\n", media);
    system("PAUSE");
    return 0;
}