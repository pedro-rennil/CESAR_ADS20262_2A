#include <stdio.h>
int main() {
    int num, achou = 0;
    printf("Digite o valor limite NUM: ");
    scanf("%d", &num);
    printf("Multiplos de 3 e 5 ate %d:\n", num);
    for (int i = 1; i <= num; i++) {
        if (i % 3 == 0 && i % 5 == 0) {
            printf("%d ", i);
            achou = 1;
        }
    }
    if (!achou) printf("Nenhum multiplo encontrado.");
    printf("\n");
    
    return 0;
}