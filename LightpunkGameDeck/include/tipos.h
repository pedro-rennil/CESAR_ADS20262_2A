#ifndef TIPOS_H
#define TIPOS_H
#include <stdint.h>
#include <stdbool.h>

// Todos os tipos abaixo sao a transcricao direta das structs/enums do
// jogo original em C++. La eram PODs simples (sem metodos, sem
// heranca), entao a conversao pra C e literal.

typedef struct {
  uint8_t r, g, b;
} Cor;

typedef struct {
  uint8_t tipo, rot;
  int8_t x, y;
} Peca;

typedef struct {
  int8_t x, y;
} Nave;

typedef struct {
  int8_t x, y;
  bool ativo;
} Tiro;

typedef struct {
  int8_t x, y, dx, dy;
  bool ativo;
  bool quicou;
} Estilhaco;

typedef struct {
  bool ativo;
  bool entrando;
  int8_t x, y;
  int8_t dxForm;
  int8_t yAlvo;
  uint8_t hp;
  bool escudo;
  uint8_t escudoFase;
  uint32_t proximoPassoMs, proximoTiroMs, proximoEscudoMs;
} Inimigo;

typedef struct {
  int8_t dx, dy;
} Slot;

typedef struct {
  int8_t grau;
  uint8_t acento;
  uint8_t lead;
} PassoMusica;

typedef enum { PARADA, JOGANDO, INVADER, AJUSTES } Estado;

typedef enum { ESQUERDA, CIMA, BAIXO, DIREITA, SELECT, NADA } Tecla;

typedef enum { IDLE_TITULO, IDLE_ESTATICA, IDLE_GLITCH, IDLE_PAUSA } IdleFase;

typedef enum { AJUSTE_BRILHO = 0, AJUSTE_MUSICA, AJUSTE_FX, AJUSTE_PALETA, N_AJUSTES } Ajuste;

typedef enum { ONDA_LATERAL, ONDA_CENTRAL } OndaTipo;

typedef enum { FASE_PECAS, FASE_LIMPANDO, FASE_ALERTA, FASE_CHEFE } InvFase;

// Estado global compartilhado entre os modulos (dono: main.c). No
// original era uma unica variavel estatica do arquivo; aqui vira
// extern porque varios modulos (ajustes, tetris, invader, telas)
// precisam lê-la e escrever nela.
extern Estado estado;

#endif
