#include <stdio.h>

typedef struct { int hora, minuto; } Hora;
typedef struct { char placa[20]; Hora entrada, saida; } Veiculo;

int tempoPermanencia(Veiculo v);

int tempoPermanencia(Veiculo v) {
    int inicio = v.entrada.hora * 60 + v.entrada.minuto;
    int fim = v.saida.hora * 60 + v.saida.minuto;
    int minutos = fim - inicio;
    return (minutos + 59) / 60;
}

int main(void) {
    Veiculo v;
    scanf("%19s%d%d%d%d", v.placa, &v.entrada.hora, &v.entrada.minuto,
          &v.saida.hora, &v.saida.minuto);
    printf("Tempo: %d hora(s)\nValor: R$ %.2f\n",
           tempoPermanencia(v), tempoPermanencia(v) * 5.0);
    return 0;
}

