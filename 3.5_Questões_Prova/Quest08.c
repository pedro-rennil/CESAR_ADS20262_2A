#include <stdio.h>
int main()
{
    int total_segundos;
    do
    {
        printf("Digite o intervalo de tempo em segundos (maior que 0): ");
        scanf("%d", &total_segundos);
        if (total_segundos <= 0)
        {
            printf("Valor invalido! Tente novamente.\n");
        }
    } while (total_segundos <= 0);
    
    int dias = total_segundos / 86400;
    int resto = total_segundos % 86400;
    int horas = resto / 3600;
    resto %= 3600;
    int minutos = resto / 60;
    int segundos = resto % 60;
    printf("Resultado: %d segundos -> %d dia(s), %d hora(s), %d minuto(s) e %d segundo(s).\n ",
           total_segundos,
           dias, horas, minutos, segundos);
    return 0;
}