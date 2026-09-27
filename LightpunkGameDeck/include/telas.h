#ifndef TELAS_H
#define TELAS_H
#include <stdint.h>

// Telas/efeitos compartilhados por todos os modos: a tela de espera
// (titulo piscando + estatica + glitch, ciclando sozinha), a
// sequencia de boot, a contagem regressiva antes de cada partida e a
// tela de "game over". No original tudo isso ficava junto no mesmo
// arquivo; aqui vira um modulo proprio porque tanto o Tetris quanto
// o Tetris Invader chamam essas mesmas telas.

void inicia_idle(void);
void inicia_idle_pelo_glitch(void);
void atualiza_idle(void);

void glitch_de_boot(void);
void assinatura_de_boot(void);
void rajada_glitch(uint16_t duracaoMs);

void contagem_regressiva(void);
void animacao_game_over(void);

// Sai do jogo atual e volta pra tela de espera (chamado quando o
// jogador segura ENTER durante uma partida de Tetris).
void volta_ao_menu(void);

#endif
