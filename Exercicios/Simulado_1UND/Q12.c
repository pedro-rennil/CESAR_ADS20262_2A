#include <stdio.h>

int main(){
    float nota = 0.0;
    do{
        printf("Digite uma nota valida: ");
        scanf("%f",&nota);
        if (nota < 0.0 || nota > 10.0)
        {
            printf("\nVoce digitou uma nota invalida, digite novamente\n");
        }
        
    }while (nota < 0.0 || nota > 10.0);

    return 0;
}