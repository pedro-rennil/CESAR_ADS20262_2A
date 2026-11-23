#include <stdio.h>

#define N 3

void ler(int m[N][N]);
void exibir(int m[N][N]);

void ler(int m[N][N]) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) scanf("%d", &m[i][j]);
}

void exibir(int m[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) printf("%4d", m[i][j]);
        printf("\n");
    }
}

int main(void) {
    int a[N][N], b[N][N], soma[N][N];
    ler(a); ler(b);
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) soma[i][j] = a[i][j] + b[i][j];
    printf("Matriz A:\n"); exibir(a);
    printf("Matriz B:\n"); exibir(b);
    printf("Soma:\n"); exibir(soma);
    return 0;
}

