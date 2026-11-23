#include <stdio.h>

typedef struct {
    char nome[80];
    int codigo;
    float salario;
} Funcionario;

int main(void) {
    Funcionario funcionarios[4];
    float soma = 0.0f, media;
    int maior = 0;

    for (int i = 0; i < 4; i++) {
        scanf(" %79[^\n]", funcionarios[i].nome);
        scanf("%d%f", &funcionarios[i].codigo, &funcionarios[i].salario);
        soma += funcionarios[i].salario;
        if (funcionarios[i].salario > funcionarios[maior].salario) maior = i;
    }
    media = soma / 4.0f;

    printf("Maior salario: %s (R$ %.2f)\n",
           funcionarios[maior].nome, funcionarios[maior].salario);
    printf("Media salarial: R$ %.2f\n", media);
    for (int i = 0; i < 4; i++) {
        if (funcionarios[i].salario < media) {
            printf("%s apos reajuste: R$ %.2f\n",
                   funcionarios[i].nome, funcionarios[i].salario * 1.10f);
        }
    }
    return 0;
}
