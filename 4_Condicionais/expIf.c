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

    if (idade < 16) {
        printf("Você não pode votar.\n");
    }
    if (idade >= 16 && idade < 18) {
        printf("Você pode votar, mas não é obrigatório.\n");
    }
    if (idade >= 18 && idade < 70) {
        printf("Você pode votar e é obrigatório.\n");
    }
    if (idade >= 70) {
        printf("Você pode votar, mas não é obrigatório.\n");
    }

    system("PAUSE");
    return 0;
}