#include "render.h"
#include "config.h"
#include "plataforma.h"
#include "ajustes.h" // brilhoAtual
#include <stdio.h>
#include <string.h>

// O MinGW.org (toolchain de 2016) nao tem essa constante no
// <windows.h> dele; o valor e fixo pela API do Windows desde o
// Windows 10, entao e seguro definir na mao quando falta.
#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif

static Cor leds[MATRIX_N];

static char statusTitulo[64] = "";
static char statusLinha[4][64] = {"", "", "", ""};

static HANDLE consoleSaida;

static int dentroDaMatriz(int8_t x, int8_t y) { return x >= 0 && x < MATRIX_W && y >= 0 && y < MATRIX_H; }

void render_iniciar(void) {
  consoleSaida = GetStdHandle(STD_OUTPUT_HANDLE);

  DWORD modo = 0;
  GetConsoleMode(consoleSaida, &modo);
  SetConsoleMode(consoleSaida, modo | ENABLE_VIRTUAL_TERMINAL_PROCESSING);

  SetConsoleTitleA("Lightpunk GameDeck - Console Edition");
  fputs("\x1b[2J\x1b[?25l", stdout); // limpa a tela e esconde o cursor
  fflush(stdout);

  limpa_tela_led();
}

void render_encerrar(void) {
  fputs("\x1b[0m\x1b[?25h\x1b[2J\x1b[H", stdout); // reseta cor, mostra cursor, limpa
  fflush(stdout);
}

void ponto(int8_t x, int8_t y, Cor cor) {
  if (!dentroDaMatriz(x, y)) return;
  leds[(int)y * MATRIX_W + x] = cor;
}

void limpa_tela_led(void) { memset(leds, 0, sizeof(leds)); }

Cor cor_rgb(uint8_t r, uint8_t g, uint8_t b) {
  Cor c;
  c.r = r;
  c.g = g;
  c.b = b;
  return c;
}

Cor escala(Cor cor, uint8_t percentual255) {
  return cor_rgb((uint8_t)((uint16_t)cor.r * percentual255 / 255), (uint8_t)((uint16_t)cor.g * percentual255 / 255),
                 (uint8_t)((uint16_t)cor.b * percentual255 / 255));
}

Cor blend(Cor a, Cor b, uint8_t quantidade) {
  return cor_rgb((uint8_t)(a.r + ((int32_t)(b.r - a.r) * quantidade) / 255),
                 (uint8_t)(a.g + ((int32_t)(b.g - a.g) * quantidade) / 255),
                 (uint8_t)(a.b + ((int32_t)(b.b - a.b) * quantidade) / 255));
}

void esmaece(uint8_t quantidade) {
  uint8_t restante = (uint8_t)(255 - quantidade);
  for (uint16_t i = 0; i < MATRIX_N; i++) leds[i] = escala(leds[i], restante);
}

void desenha_glifo_painel(const uint8_t *glifo, uint8_t painel, Cor cor) {
  for (uint8_t row = 0; row < 8; row++)
    for (uint8_t col = 0; col < 8; col++)
      if ((glifo[row] >> (7 - col)) & 1) ponto(col, painel * (MATRIX_H / 2) + row, cor);
}

void desenha_glifo_painel_borda_letra(const uint8_t *glifo, uint8_t painel, Cor corBorda, Cor corLetra) {
  for (uint8_t row = 0; row < 8; row++)
    for (uint8_t col = 0; col < 8; col++)
      if ((glifo[row] >> (7 - col)) & 1) {
        bool borda = (row == 0 || row == 7 || col == 0 || col == 7);
        ponto(col, painel * (MATRIX_H / 2) + row, borda ? corBorda : corLetra);
      }
}

void desenha_tela_dupla_cor(const uint8_t *cima, const uint8_t *baixo, Cor cor) {
  limpa_tela_led();
  desenha_glifo_painel(cima, 0, cor);
  desenha_glifo_painel(baixo, 1, cor);
  mostra();
}

void fade_out_matriz(void) {
  const uint16_t DURACAO_MS = 600;
  const uint8_t PASSOS = 15;
  for (uint8_t p = 0; p < PASSOS; p++) {
    esmaece(255 / PASSOS);
    mostra();
    delay(DURACAO_MS / PASSOS);
  }
  limpa_tela_led();
  mostra();
}

void render_status(const char *titulo, const char *l1, const char *l2, const char *l3, const char *l4) {
  snprintf(statusTitulo, sizeof(statusTitulo), "%s", titulo ? titulo : "");
  snprintf(statusLinha[0], sizeof(statusLinha[0]), "%s", l1 ? l1 : "");
  snprintf(statusLinha[1], sizeof(statusLinha[1]), "%s", l2 ? l2 : "");
  snprintf(statusLinha[2], sizeof(statusLinha[2]), "%s", l3 ? l3 : "");
  snprintf(statusLinha[3], sizeof(statusLinha[3]), "%s", l4 ? l4 : "");
}

static char quadro[32768];

void mostra(void) {
  int n = 0;
  n += sprintf(quadro + n, "\x1b[H"); // cursor pro topo esquerdo, sem rolar a tela

  n += sprintf(quadro + n, "  LIGHTPUNK GAMEDECK \x1b[2mconsole edition\x1b[0m\x1b[K\n");
  n += sprintf(quadro + n, "  +");
  for (uint8_t x = 0; x < MATRIX_W; x++) n += sprintf(quadro + n, "--");
  n += sprintf(quadro + n, "+\x1b[K\n");

  for (uint8_t y = 0; y < MATRIX_H; y++) {
    n += sprintf(quadro + n, "  |");
    for (uint8_t x = 0; x < MATRIX_W; x++) {
      Cor c = escala(leds[(int)y * MATRIX_W + x], brilhoAtual);
      n += sprintf(quadro + n, "\x1b[48;2;%u;%u;%um  ", c.r, c.g, c.b);
    }
    n += sprintf(quadro + n, "\x1b[0m|\x1b[K\n");
  }

  n += sprintf(quadro + n, "  +");
  for (uint8_t x = 0; x < MATRIX_W; x++) n += sprintf(quadro + n, "--");
  n += sprintf(quadro + n, "+\x1b[K\n\x1b[K\n");

  n += sprintf(quadro + n, "  \x1b[1m%s\x1b[0m\x1b[K\n\x1b[K\n", statusTitulo);
  for (uint8_t i = 0; i < 4; i++) n += sprintf(quadro + n, "  %s\x1b[K\n", statusLinha[i]);
  n += sprintf(quadro + n, "\x1b[J");

  DWORD escritos;
  WriteFile(consoleSaida, quadro, (DWORD)n, &escritos, NULL);

  delay(20); // igual ao original: mostra() do FastLED tambem tinha esse delay(20) embutido
}
