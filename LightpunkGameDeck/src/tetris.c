#include "tetris.h"
#include "render.h"
#include "audio.h"
#include "ajustes.h"
#include "telas.h"
#include "plataforma.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// As 7 pecas classicas (I,O,S,Z,L,J,T), 4 rotacoes cada, em bitmask
// 4x4 - identico ao original.
const uint8_t PECAS[7][4][4] = {
    {{0b0000, 0b1111, 0b0000, 0b0000}, {0b0010, 0b0010, 0b0010, 0b0010},
     {0b0000, 0b0000, 0b1111, 0b0000}, {0b0100, 0b0100, 0b0100, 0b0100}},
    {{0b0110, 0b0110, 0b0000, 0b0000}, {0b0110, 0b0110, 0b0000, 0b0000},
     {0b0110, 0b0110, 0b0000, 0b0000}, {0b0110, 0b0110, 0b0000, 0b0000}},
    {{0b0100, 0b1110, 0b0000, 0b0000}, {0b0100, 0b0110, 0b0100, 0b0000},
     {0b0000, 0b1110, 0b0100, 0b0000}, {0b0100, 0b1100, 0b0100, 0b0000}},
    {{0b0110, 0b1100, 0b0000, 0b0000}, {0b0100, 0b0110, 0b0010, 0b0000},
     {0b0000, 0b0110, 0b1100, 0b0000}, {0b1000, 0b1100, 0b0100, 0b0000}},
    {{0b1100, 0b0110, 0b0000, 0b0000}, {0b0010, 0b0110, 0b0100, 0b0000},
     {0b0000, 0b1100, 0b0110, 0b0000}, {0b0100, 0b1100, 0b1000, 0b0000}},
    {{0b1000, 0b1110, 0b0000, 0b0000}, {0b0110, 0b0100, 0b0100, 0b0000},
     {0b0000, 0b1110, 0b0010, 0b0000}, {0b0100, 0b0100, 0b1100, 0b0000}},
    {{0b0010, 0b1110, 0b0000, 0b0000}, {0b0100, 0b0100, 0b0110, 0b0000},
     {0b0000, 0b1110, 0b1000, 0b0000}, {0b1100, 0b0100, 0b0100, 0b0000}},
};

static bool celulaDaPeca(const Peca *p, uint8_t r, uint8_t c) { return PECAS[p->tipo][p->rot][r] & (0b1000 >> c); }

uint8_t campo[MATRIX_H][MATRIX_W];
static Peca peca;
uint16_t linhas = 0, pontos = 0;
uint8_t nivel = 0;
static uint16_t intervaloQueda = 0;
static uint32_t ultimaQueda = 0;
static uint32_t repeteMs = 0;
static uint32_t inicioPartidaMs = 0;
static uint8_t nivelTempoVisto = 0;

static const uint16_t NIVEL_TEMPO_MS = 10000;
static const uint8_t LINHAS_POR_NIVEL = 10;
static const uint16_t INTERVALO_POR_NIVEL[] = {650, 600, 550, 500, 450, 400, 360, 320,
                                                280, 240, 200, 170, 140, 110, 85,  65};
const uint8_t N_NIVEIS = sizeof(INTERVALO_POR_NIVEL) / sizeof(INTERVALO_POR_NIVEL[0]);
static const uint16_t SOFT_DROP_MS = 55;
static const uint16_t DAS_MS = 170;
static const uint16_t ARR_MS = 70;
static const uint16_t HARD_DROP_MS_POR_LINHA = 8;
static const uint16_t ENCAIXE_MS = 90;

static uint8_t saco[7];
static uint8_t sacoPos = 7;

static uint8_t proximoTipo(void) {
  if (sacoPos >= 7) {
    for (uint8_t i = 0; i < 7; i++) saco[i] = i;
    for (uint8_t i = 6; i > 0; i--) {
      uint8_t j = rand() % (i + 1);
      uint8_t t = saco[i];
      saco[i] = saco[j];
      saco[j] = t;
    }
    sacoPos = 0;
  }
  return saco[sacoPos++];
}

static bool colide(uint8_t tipo, uint8_t rot, int8_t px, int8_t py) {
  for (uint8_t r = 0; r < 4; r++) {
    for (uint8_t c = 0; c < 4; c++) {
      if (!(PECAS[tipo][rot][r] & (0b1000 >> c))) continue;
      int8_t x = (int8_t)(px + c), y = (int8_t)(py + r);
      if (x < 0 || x >= MATRIX_W || y >= MATRIX_H) return true;
      if (y >= 0 && campo[y][x]) return true;
    }
  }
  return false;
}

static bool novaPeca(void) {
  peca.tipo = proximoTipo();
  peca.rot = 0;
  peca.x = 2;
  peca.y = 0;
  return !colide(peca.tipo, peca.rot, peca.x, peca.y);
}

static bool move(int8_t dx, int8_t dy) {
  if (colide(peca.tipo, peca.rot, (int8_t)(peca.x + dx), (int8_t)(peca.y + dy))) return false;
  peca.x = (int8_t)(peca.x + dx);
  peca.y = (int8_t)(peca.y + dy);
  return true;
}

static void colunasDaPeca(uint8_t tipo, uint8_t rot, int8_t px, int8_t *minX, int8_t *maxX) {
  *minX = 127;
  *maxX = -128;
  for (uint8_t r = 0; r < 4; r++)
    for (uint8_t c = 0; c < 4; c++)
      if ((PECAS[tipo][rot][r] >> (3 - c)) & 1) {
        int8_t x = (int8_t)(px + c);
        if (x < *minX) *minX = x;
        if (x > *maxX) *maxX = x;
      }
}

static bool rotaciona(void) {
  static const int8_t CHUTES[5] = {0, -1, 1, -2, 2};
  int8_t minAntes, maxAntes;
  colunasDaPeca(peca.tipo, peca.rot, peca.x, &minAntes, &maxAntes);
  bool encostadaEsq = (minAntes == 0);
  bool encostadaDir = (maxAntes == MATRIX_W - 1);

  uint8_t nova = (peca.rot + 1) & 3;
  bool girou = false;
  for (uint8_t k = 0; k < 5 && !girou; k++) {
    if (!colide(peca.tipo, nova, (int8_t)(peca.x + CHUTES[k]), peca.y)) {
      peca.rot = nova;
      peca.x = (int8_t)(peca.x + CHUTES[k]);
      girou = true;
    }
  }
  if (!girou) return false;

  int8_t minDepois, maxDepois;
  colunasDaPeca(peca.tipo, peca.rot, peca.x, &minDepois, &maxDepois);
  int8_t ajuste = 0;
  if (encostadaEsq && minDepois > 0) ajuste = (int8_t)(-minDepois);
  else if (encostadaDir && maxDepois < MATRIX_W - 1) ajuste = (int8_t)((MATRIX_W - 1) - maxDepois);
  if (ajuste != 0 && !colide(peca.tipo, peca.rot, (int8_t)(peca.x + ajuste), peca.y)) peca.x = (int8_t)(peca.x + ajuste);
  return true;
}

static void fixaPeca(void) {
  for (uint8_t r = 0; r < 4; r++)
    for (uint8_t c = 0; c < 4; c++)
      if (celulaDaPeca(&peca, r, c)) {
        int8_t x = (int8_t)(peca.x + c), y = (int8_t)(peca.y + r);
        if (y >= 0) campo[y][x] = 1;
      }
}

static uint8_t linhasCompletas(uint8_t *quais) {
  uint8_t n = 0;
  for (uint8_t y = 0; y < MATRIX_H; y++) {
    bool cheia = true;
    for (uint8_t x = 0; x < MATRIX_W && cheia; x++) cheia = campo[y][x] != 0;
    if (cheia) quais[n++] = y;
  }
  return n;
}

static void removeLinha(uint8_t y) {
  for (int8_t r = (int8_t)y; r > 0; r--) memcpy(campo[r], campo[r - 1], MATRIX_W);
  memset(campo[0], 0, MATRIX_W);
}

static void desenhaCampo(bool comPeca) {
  limpa_tela_led();
  for (uint8_t y = 0; y < MATRIX_H; y++)
    for (uint8_t x = 0; x < MATRIX_W; x++)
      if (campo[y][x]) ponto((int8_t)x, (int8_t)y, COR_GRID);
  if (comPeca)
    for (uint8_t r = 0; r < 4; r++)
      for (uint8_t c = 0; c < 4; c++)
        if (celulaDaPeca(&peca, r, c)) ponto((int8_t)(peca.x + c), (int8_t)(peca.y + r), COR_CAINDO);

  char l1[64], l2[64], l3[64];
  snprintf(l1, sizeof(l1), "pontos: %u", pontos);
  snprintf(l2, sizeof(l2), "linhas: %u   nivel: %u", linhas, nivel);
  snprintf(l3, sizeof(l3), "seta esq/dir move, baixo acelera");
  render_status("TETRIS", l1, l2, l3, "cima = hard drop | ENTER = girar");
  mostra();
}

bool pilha_alta(void) {
  for (uint8_t y = 0; y < 6; y++)
    for (uint8_t x = 0; x < MATRIX_W; x++)
      if (campo[y][x]) return true;
  return false;
}

static uint8_t nivelPorTempo(uint32_t inicioMs) {
  uint32_t t = (millis() - inicioMs) / NIVEL_TEMPO_MS;
  return (t >= N_NIVEIS) ? N_NIVEIS - 1 : (uint8_t)t;
}

static void recalculaVelocidade(void) {
  uint8_t porTempo = nivelPorTempo(inicioPartidaMs);
  uint8_t novo = (uint8_t)(porTempo + linhas / LINHAS_POR_NIVEL);
  if (novo >= N_NIVEIS) novo = N_NIVEIS - 1;
  if (novo > nivel) {
    nivel = novo;
    toca_sfx(penta_do_nivel(nivel), 35);
  }
  intervaloQueda = INTERVALO_POR_NIVEL[nivel];
}

void inicia_jogo(void) {
  memset(campo, 0, sizeof(campo));
  linhas = 0;
  pontos = 0;
  nivel = 0;
  nivelTempoVisto = 0;
  inicioPartidaMs = millis();
  sacoPos = 7;
  recalculaVelocidade();
  novaPeca();
  estado = JOGANDO;

  contagem_regressiva();

  motivo_tetris();
  toca_sfx(G6, 60);
  inicia_musica();
  inicioPartidaMs = millis();
  ultimaQueda = millis();
  repeteMs = millis() + DAS_MS;
  desenhaCampo(true);
}

static void animaLinhas(const uint8_t *quais, uint8_t n) {
  static const uint16_t ARPEJO[3] = {C6, E6, G6};
  for (uint8_t i = 0; i < 3; i++) {
    for (uint8_t k = 0; k < n; k++)
      for (uint8_t x = 0; x < MATRIX_W; x++) ponto((int8_t)x, (int8_t)quais[k], COR_DESTAQUE);
    mostra();
    toca_sfx(ARPEJO[(i < n) ? i : n - 1], 60);
    espera_ms(90);
    for (uint8_t k = 0; k < n; k++)
      for (uint8_t x = 0; x < MATRIX_W; x++) ponto((int8_t)x, (int8_t)quais[k], cor_rgb(0, 0, 0));
    mostra();
    espera_ms(60);
  }
  if (n == 4) {
    para_musica();
    motivo_tetris();
    inicia_musica();
  }
}

static void fixaEProssegue(bool foiHardDrop) {
  fixaPeca();
  uint8_t quais[4];
  uint8_t n = linhasCompletas(quais);
  if (n) {
    desenhaCampo(false);
    espera_ms(ENCAIXE_MS);
    animaLinhas(quais, n);
    for (uint8_t k = 0; k < n; k++) removeLinha(quais[k]);
    static const uint16_t PONTOS_POR_LINHAS[5] = {0, 10, 30, 50, 80};
    linhas = (uint16_t)(linhas + n);
    pontos = (uint16_t)(pontos + PONTOS_POR_LINHAS[n] * (nivel + 1));
    recalculaVelocidade();
  } else if (!foiHardDrop) {
    toca_sfx(PENTA[0], 30);
  }
  if (!novaPeca()) {
    desenhaCampo(false);
    espera_ms(500);
    animacao_game_over();
    return;
  }
  ultimaQueda = millis();
  desenhaCampo(true);
}

void jogo(Tecla segurada, Tecla nova) {
  bool mudou = false;

  uint8_t porTempo = nivelPorTempo(inicioPartidaMs);
  if (porTempo != nivelTempoVisto) {
    nivelTempoVisto = porTempo;
    recalculaVelocidade();
  }

  if (nova == ESQUERDA || nova == DIREITA) {
    if (move(nova == ESQUERDA ? -1 : 1, 0)) {
      toca_sfx_tique(PENTA[4], 14);
      mudou = true;
    }
    repeteMs = millis() + DAS_MS;
  } else if ((segurada == ESQUERDA || segurada == DIREITA) && millis() >= repeteMs) {
    if (move(segurada == ESQUERDA ? -1 : 1, 0)) {
      toca_sfx_tique(PENTA[4], 10);
      mudou = true;
    }
    repeteMs = millis() + ARR_MS;
  }

  if (nova == SELECT && rotaciona()) {
    toca_sfx_tique(PENTA[6], 20);
    mudou = true;
  }

  if (nova == CIMA) {
    uint16_t hz = 2000;
    while (move(0, 1)) {
      pontos = (uint16_t)(pontos + 2);
      toca_sfx_tique(hz, 6);
      if (hz > 700) hz = (uint16_t)(hz - 80);
      desenhaCampo(true);
      espera_ms(HARD_DROP_MS_POR_LINHA);
    }

    for (uint8_t k = 0; k < 8; k++) {
      toca_sfx((uint16_t)(1600 - k * 140), 12);
      espera_ms(11);
    }
    fixaEProssegue(true);
    return;
  }

  uint16_t intervalo = (segurada == BAIXO) ? SOFT_DROP_MS : intervaloQueda;
  if (millis() - ultimaQueda >= intervalo) {
    ultimaQueda = millis();
    if (move(0, 1)) {
      if (segurada == BAIXO) {
        pontos = (uint16_t)(pontos + 1);
        toca_sfx_tique(PENTA[2], 8);
      } else if (intervaloQueda >= 150) {
        toca_sfx_suave(PENTA[0], 6);
      }
      mudou = true;
    } else {
      fixaEProssegue(false);
      return;
    }
  }

  if (mudou) desenhaCampo(true);
}
