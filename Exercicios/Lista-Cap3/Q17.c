#include <stdio.h>

int main() {
    float nota, soma = 0, maior = -1, menor = 11;
    int qtd = 0;
    printf("Digite as notas dos alunos (-1.0 para encerrar):\n");
    while (1) {
        printf("Nota do aluno %d: ", qtd + 1);
        scanf("%f", &nota);
        if (nota == -1.0f) break;

        if (nota >= 0.0f && nota <= 10.0f) {
            soma += nota;
            qtd++;
            if (nota > maior) maior = nota;

            if (nota < menor) menor = nota;
        }
        else {
            printf("Nota invalida! Digite entre 0.0 e 10.0.\n");
        }
    }

    if (qtd > 0) {
        printf("\n--- ESTATISTICAS DA TURMA ---\n");
        printf("Total de Alunos : %d\n", qtd);
        printf("Maior Nota : %.2f\n", maior);
        printf("Menor Nota : %.2f\n", menor);
        printf("Media Geral : %.2f\n", soma / qtd);
    }
    else {
        printf("Nenhum dado registrado.\n");
    }
    return 0;
}