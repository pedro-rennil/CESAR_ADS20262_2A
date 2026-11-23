#include <stdio.h>

typedef struct {
    char nome[80];
    int matricula;
    float notas[2];
} Aluno;

int main(void) {
    Aluno a;
    scanf(" %79[^\n]", a.nome);
    scanf("%d%f%f", &a.matricula, &a.notas[0], &a.notas[1]);
    float media = (a.notas[0] + a.notas[1]) / 2;
    printf("%s - %d\nMedia: %.2f\n%s\n", a.nome, a.matricula, media,
           media >= 7 ? "Aprovado" : media >= 4 ? "Final" : "Reprovado");
    return 0;
}

