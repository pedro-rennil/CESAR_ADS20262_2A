#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int tempoSegundos;
    int horas, minutos, segundos;

    printf("Digite o intervalo de tempo em segundos: ");
    if (scanf("%d", &tempoSegundos) != 1) {
        printf("Erro na leitura do valor.\n");
        return 1;
    }

    horas = tempoSegundos / 3600;              
    minutos = (tempoSegundos % 3600) / 60;        
    segundos = tempoSegundos % 60;

    printf("%d segundos correspondem a:\n", tempoSegundos);
    printf("%d hora(s), %d minuto(s) e %d segundo(s).\n", horas, minutos, segundos);

    system("PAUSE");
    return 0;
}