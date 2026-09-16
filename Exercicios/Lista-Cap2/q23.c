#include <stdio.h>
#include <stdlib.h>

int main() {
    int h_inicio, m_inicio, s_inicio, duracao_segundos;

    printf("Digite o horario de inicio (Horas Minutos Segundos): ");
    scanf("%d %d %d", &h_inicio, &m_inicio, &s_inicio);

    printf("Digite a duracao do experimento em segundos: ");
    scanf("%d", &duracao_segundos);

    int inicio_total_seg = h_inicio * 3600 + m_inicio * 60 + s_inicio;
    int termino_total_seg = (inicio_total_seg + duracao_segundos) % 86400;

    int h_fim = termino_total_seg / 3600;
    int resto_seg = termino_total_seg % 3600;
    int m_fim = resto_seg / 60;
    int s_fim = resto_seg % 60;

    printf("Horario de termino: %02d:%02d:%02d\n", h_fim, m_fim, s_fim);

    return 0;
}