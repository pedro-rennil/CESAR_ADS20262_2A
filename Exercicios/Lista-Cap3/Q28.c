#include <stdio.h>

int main() {
    int opcao;
    float salario;

    do {
        printf("\n=== SISTEMA DE FOLHA DE PAGAMENTO ===\n");
        printf("1. Reajuste Salarial\n");
        printf("2. Retencao de Imposto de Renda\n");
        printf("3. Encerrar Programa\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        switch (opcao) {
            case 1:
                printf("Digite o salario atual: R$ ");
                scanf("%f", &salario);

                if (salario <= 2000.0f) salario *= 1.15f;

                else salario *= 1.10f;
                printf("Novo Salario Reajustado: R$ %.2f\n", salario);
                break;

            case 2:
                printf("Digite o salario bruto: R$ ");
                scanf("%f", &salario);
                float ir = (salario <= 3000.0f) ? (salario * 0.08f) : (salario * 0.15f);

                printf("Desconto de IR: R$ %.2f | Salario Liquido: R$ %.2f\n", ir, salario - ir);
                break;

            case 3:
                printf("Programa encerrado com sucesso!\n");
                break;

            default:
                printf("Opcao invalida! Tente novamente.\n");
                }
    } while (opcao != 3);
    
    return 0;
}