#ifndef AUDIO_H
#define AUDIO_H
#include <stdint.h>

// ===================================================================
// No original, dois buzzers piezo eram tocados via PWM (LEDC) sem
// bloquear o loop principal - podiam tocar por baixo enquanto o
// resto do jogo continuava rodando. O Windows so oferece Beep(),
// que e SINCRONO (trava a thread que chamou pela duracao inteira).
// Pra nao travar o jogo a cada nota, este modulo roda uma thread
// dedicada so pra tocar som; o resto do jogo apenas "pede" uma nota
// (toca_sfx/musica_nota) e continua imediatamente.
//
// Simplificacao assumida: o alto-falante do PC so consegue tocar UM
// tom por vez (era literalmente assim tambem no hardware original -
// dois canais, mas aqui vira um so). Efeito sonoro (SFX) sempre tem
// prioridade sobre a musica de fundo, do mesmo jeito que o original
// ja "abaixava" (duck) a musica quando um SFX tocava.
//
// Volume tambem nao existe de verdade no Beep() do Windows (e so
// liga/desliga o alto-falante na frequencia pedida); volumeSfx e
// volumeMusica continuam existindo como ajustes (0 = mudo, >0 =
// toca), mas nao controlam intensidade sonora como no original.
// ===================================================================

// Notas usadas nos efeitos e na musica (mesmos valores em Hz do
// original - viram #define porque sao so constantes numericas
// reaproveitadas em varios modulos, sem custo de linkagem).
#define LA5 880
#define B5 988
#define C6 1047
#define D6 1175
#define E6 1319
#define F6 1397
#define G6 1568
#define LA6 1760

extern const uint16_t PENTA[10];
extern const uint16_t ESCALA_MENU[8];

void audio_iniciar(void);
void audio_encerrar(void);

// SFX (efeitos de curta duracao - movimento, rotacao, tiro etc).
void toca_sfx(uint16_t hz, uint16_t ms);
void toca_sfx_tique(uint16_t hz, uint16_t ms);
void toca_sfx_suave(uint16_t hz, uint16_t ms);
void para_sfx(void);
void atualiza_sfx(void);

// Musica de fundo (groove procedural).
void inicia_musica(void);
void para_musica(void);
void atualiza_musica(void);
void motivo_tetris(void); // jingle de "tetris" (limpou 4 linhas de uma vez)
void musica_nota(uint16_t hz); // usado pelo menu de ajustes p/ tocar uma nota curta
void reforca_silencio(void);

uint16_t penta_do_nivel(uint8_t nivel);

// Espera ms milissegundos, mantendo musica/SFX atualizados (igual ao
// esperaMs() do original, que fazia a mesma coisa durante animacoes).
void espera_ms(uint32_t ms);

#endif
