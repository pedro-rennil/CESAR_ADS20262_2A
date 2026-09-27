#ifndef ENTRADA_H
#define ENTRADA_H
#include "tipos.h"

// Equivalente a leitura do keypad analogico do original. La, o
// keypad era lido por ADC e classificado por faixa de tensao; aqui
// lemos o teclado de verdade (setas + ENTER/ESPACO) e classificamos
// diretamente. O filtro de estabilidade (mesma janela de tempo,
// KEY_ESTAVEL_MS) foi mantido pra preservar o "feel" original.
Tecla le_tecla_estavel(void);
Tecla ressincroniza_teclado(void);

// Verdadeiro se o jogador pediu pra sair (tecla ESC).
bool deve_sair(void);

#endif
