#include <stdio.h>

int somaVetor(int v[], int n);
int maiorValor(int v[], int n);
int buscaValor(int v[], int n, int x);

int somaVetor(int v[], int n) {
    int soma = 0;
    for (int i = 0; i < n; i++) soma += v[i];
    return soma;
}

int maiorValor(int v[], int n) {
    int maior = v[0];
    for (int i = 1; i < n; i++) if (v[i] > maior) maior = v[i];
    return maior;
}

int buscaValor(int v[], int n, int x) {
    for (int i = 0; i < n; i++) if (v[i] == x) return i;
    return -1;
}

int main(void) {
    int v[8], x;
    for (int i = 0; i < 8; i++) scanf("%d", &v[i]);
    scanf("%d", &x);
    printf("Soma: %d\nMaior: %d\nPosicao: %d\n",
           somaVetor(v, 8), maiorValor(v, 8), buscaValor(v, 8, x));
    return 0;
}

