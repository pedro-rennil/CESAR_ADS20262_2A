#include <stdio.h> 
#include <stdlib.h> 
int main() { 
    int numero; 
    printf("Digite um numero inteiro: "); 
    scanf("%d", &numero); 
    printf("Decimal: %d | Hexadecimal: %x | Octal: %o | ASCII: %c\n", numero, numero, numero, (char)numero);
    return 0; }