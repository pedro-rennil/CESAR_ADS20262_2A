#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    int idade;
    printf("Digite sua idade: ");
    scanf("%d", &idade);

    if (idade < 16 && idade >= 0) {
        printf("Você não pode votar.\n");
    } else
    if (idade >= 16 && idade < 18) {
        printf("Você pode votar, mas não é obrigatório.\n");
    } else
    if (idade >= 18 && idade < 70) {
        printf("Você pode votar e é obrigatório.\n");
    } else
    if (idade >= 70 && idade <= 120) {
        printf("Você pode votar, mas não é obrigatório.\n");
    } else {
        printf("Idade inválida.\n");
    }

    system("PAUSE");
    return 0;
}