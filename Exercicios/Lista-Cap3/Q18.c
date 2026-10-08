#include <stdio.h>

int main() {
    int num, invertido = 0, digito;
    printf("Digite um numero inteiro positivo: ");
    scanf("%d", &num);
    int temp = num;
    
    while (temp > 0) {
        digito = temp % 10; // Extrai o ultimo digito
        invertido = (invertido * 10) + digito; // Desloca e adiciona
        temp /= 10; // Remove o ultimo digito
    }

    printf("Numero original: %d | Invertido: %d\n", num, invertido);
    return 0;
}