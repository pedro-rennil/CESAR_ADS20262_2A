#include "ajustes.h"
#include "config.h"
#include "render.h"
#include "audio.h"
#include "telas.h"
#include "plataforma.h"
#include <stdio.h>
#include <string.h>

// ---- Paletas de cores (transcricao direta das 4 paletas do original) ----
// Precisam ser macros (nao "static const Cor"): a tabela PALETAS abaixo e
// estatica, e C - ao contrario de C++ - nao aceita um objeto const como
// inicializador de outro objeto estatico. Como macro, isso e so
// substituicao de texto, entao o literal "{0,255,255}" cai direto na
// tabela e continua sendo uma expressao constante de verdade.
#define PAL_CIANO {0, 255, 255}
#define PAL_AMBAR {255, 140, 0}
#define PAL_MAGENTA {255, 0, 255}
#define PAL_BRANCO {255, 255, 255}
#define PAL_AZUL_ELETRICO {0, 128, 255}
#define PAL_ROSA_NEON {255, 0, 128}
#define PAL_LARANJA_NEON {255, 72, 0}
#define PAL_LIMA {128, 255, 0}
#define PAL_ROXO {140, 0, 255}
#define PAL_VIOLETA {180, 0, 255}
#define PAL_AMARELO_NEON {255, 200, 0}

typedef struct {
  const char *nome;
  Cor caindo, grid, gameOver, destaque, glitchA, glitchB, assinatura, tituloA, tituloB, menu;
} Paleta;

static const Paleta PALETAS[] = {
    {"LARANJA", PAL_CIANO, PAL_AMBAR, PAL_MAGENTA, PAL_BRANCO, PAL_CIANO, PAL_MAGENTA, PAL_MAGENTA, PAL_MAGENTA,
     PAL_CIANO, PAL_MAGENTA},

    {"CIDADE", PAL_AZUL_ELETRICO, PAL_ROSA_NEON, PAL_LARANJA_NEON, PAL_BRANCO, PAL_AZUL_ELETRICO, PAL_ROSA_NEON,
     PAL_ROSA_NEON, PAL_ROSA_NEON, PAL_AZUL_ELETRICO, PAL_ROSA_NEON},

    {"ACIDO", PAL_LIMA, PAL_ROXO, PAL_MAGENTA, PAL_BRANCO, PAL_LIMA, PAL_ROXO, PAL_ROXO, PAL_ROXO, PAL_LIMA,
     PAL_ROXO},

    {"SYNTH", PAL_CIANO, PAL_VIOLETA, PAL_LARANJA_NEON, PAL_AMARELO_NEON, PAL_CIANO, PAL_VIOLETA, PAL_VIOLETA,
     PAL_VIOLETA, PAL_CIANO, PAL_VIOLETA},
};
static const uint8_t N_PALETAS = sizeof(PALETAS) / sizeof(PALETAS[0]);

uint8_t paletaAtual = 0;

Cor COR_CAINDO, COR_GRID, COR_GAME_OVER, COR_DESTAQUE, COR_GLITCH_A, COR_GLITCH_B, COR_ASSINATURA, COR_TITULO_A,
    COR_TITULO_B, COR_MENU;
Cor COR_PISO;

void aplica_paleta(uint8_t idx) {
  if (idx >= N_PALETAS) idx = 0;
  paletaAtual = idx;
  const Paleta *p = &PALETAS[idx];
  COR_CAINDO = p->caindo;
  COR_GRID = p->grid;
  COR_GAME_OVER = p->gameOver;
  COR_DESTAQUE = p->destaque;
  COR_GLITCH_A = p->glitchA;
  COR_GLITCH_B = p->glitchB;
  COR_ASSINATURA = p->assinatura;
  COR_TITULO_A = p->tituloA;
  COR_TITULO_B = p->tituloB;
  COR_MENU = p->menu;

  COR_PISO = escala(COR_MENU, 64);
}

// ---- Brilho e volumes ----
uint8_t brilhoAtual = MATRIX_BRIGHTNESS_PADRAO;
static const uint8_t BRILHO_STEP = 15;

uint8_t volumeSfx = 90;
uint8_t volumeMusica = 50;

// ---- Persistencia em arquivo (equivalente ao Preferences/flash do
// original - aqui e so um struct gravado em binario, igual ao
// savegame.dat do jogo Pokemon do mesmo repositorio) ----
#define ARQUIVO_AJUSTES "ajustes.dat"

typedef struct {
  uint8_t brilho, volMus, volSfx, paleta;
} AjustesSalvos;

void carrega_ajustes(void) {
  AjustesSalvos a;
  FILE *f = fopen(ARQUIVO_AJUSTES, "rb");
  if (f && fread(&a, sizeof(a), 1, f) == 1) {
    brilhoAtual = a.brilho;
    volumeMusica = a.volMus;
    volumeSfx = a.volSfx;
    paletaAtual = a.paleta;
  }
  if (f) fclose(f);

  if (paletaAtual >= N_PALETAS) paletaAtual = 0;
  if (brilhoAtual < MATRIX_BRIGHTNESS_MIN) brilhoAtual = MATRIX_BRIGHTNESS_MIN;
  // (brilhoAtual > MATRIX_BRIGHTNESS_MAX) nao precisa de checagem: MATRIX_BRIGHTNESS_MAX e 255,
  // o maior valor que um uint8_t consegue representar.
  if (volumeMusica > VOLUME_MAX) volumeMusica = VOLUME_MAX;
  if (volumeSfx > VOLUME_MAX) volumeSfx = VOLUME_MAX;
}

void salva_ajustes(void) {
  AjustesSalvos a;
  a.brilho = brilhoAtual;
  a.volMus = volumeMusica;
  a.volSfx = volumeSfx;
  a.paleta = paletaAtual;
  FILE *f = fopen(ARQUIVO_AJUSTES, "wb");
  if (!f) return;
  fwrite(&a, sizeof(a), 1, f);
  fclose(f);
}

// ---- Menu de ajustes ----
static uint8_t ajusteAtual = AJUSTE_BRILHO;

static const uint8_t AJUSTE_GLIFO_B[8] = {0b11111111, 0b10000001, 0b10100001, 0b10111101,
                                           0b10100101, 0b10111001, 0b10000001, 0b11111111};
static const uint8_t AJUSTE_GLIFO_M[8] = {0b11111111, 0b10000001, 0b10100101, 0b10111101,
                                           0b10100101, 0b10100101, 0b10000001, 0b11111111};
static const uint8_t AJUSTE_GLIFO_F[8] = {0b11111111, 0b10000001, 0b10111101, 0b10100001,
                                           0b10111001, 0b10100001, 0b10000001, 0b11111111};
static const uint8_t AJUSTE_GLIFO_P[8] = {0b11111111, 0b10000001, 0b10111101, 0b10100101,
                                           0b10111101, 0b10100001, 0b10000001, 0b11111111};
static const uint8_t *const AJUSTE_GLIFOS[N_AJUSTES] = {AJUSTE_GLIFO_B, AJUSTE_GLIFO_M, AJUSTE_GLIFO_F,
                                                          AJUSTE_GLIFO_P};
static const char *const AJUSTE_NOMES[N_AJUSTES] = {"BRILHO", "MUSICA", "EFEITOS (FX)", "PALETA"};

static float ajuste_posicao_barra(uint8_t valor, uint8_t minV, uint8_t maxV) {
  if (maxV <= minV) return 0.0f;
  return 8.0f * (float)(valor - minV) / (float)(maxV - minV);
}

static float posicao_do_ajuste_atual(void) {
  if (ajusteAtual == AJUSTE_BRILHO) return ajuste_posicao_barra(brilhoAtual, MATRIX_BRIGHTNESS_MIN, MATRIX_BRIGHTNESS_MAX);
  if (ajusteAtual == AJUSTE_MUSICA) return ajuste_posicao_barra(volumeMusica, VOLUME_MIN, VOLUME_MAX);
  return ajuste_posicao_barra(volumeSfx, VOLUME_MIN, VOLUME_MAX);
}

static void atualiza_status_ajustes(void) {
  char l1[64], l2[64];
  if (ajusteAtual == AJUSTE_PALETA) {
    snprintf(l1, sizeof(l1), "< %s >", PALETAS[paletaAtual].nome);
    render_status("AJUSTES", "ESQ/DIR: troca o ajuste", l1, "CIMA/BAIXO: troca a paleta", "segure ENTER: salvar e sair");
    return;
  }
  uint8_t valor = (ajusteAtual == AJUSTE_BRILHO) ? brilhoAtual : (ajusteAtual == AJUSTE_MUSICA) ? volumeMusica : volumeSfx;
  uint8_t maxV = (ajusteAtual == AJUSTE_BRILHO) ? MATRIX_BRIGHTNESS_MAX : VOLUME_MAX;
  snprintf(l1, sizeof(l1), "%s: %u / %u", AJUSTE_NOMES[ajusteAtual], valor, maxV);
  snprintf(l2, sizeof(l2), "%s", (ajusteAtual == AJUSTE_MUSICA || ajusteAtual == AJUSTE_FX) && valor == 0 ? "(mudo)" : "");
  render_status("AJUSTES", l1, l2, "CIMA/BAIXO: ajusta o valor", "segure ENTER: salvar e sair");
}

void desenha_ajustes(void) {
  limpa_tela_led();
  desenha_glifo_painel(AJUSTE_GLIFOS[ajusteAtual], 0, COR_MENU);

  if (ajusteAtual == AJUSTE_PALETA) {
    const Cor *faixas[4] = {&COR_CAINDO, &COR_GRID, &COR_GAME_OVER, &COR_DESTAQUE};
    for (uint8_t f = 0; f < 4; f++)
      for (uint8_t r = 0; r < 2; r++)
        for (uint8_t col = 0; col < MATRIX_W; col++) ponto(col, MATRIX_H / 2 + f * 2 + r, *faixas[f]);
    atualiza_status_ajustes();
    mostra();
    return;
  }

  float posicao = posicao_do_ajuste_atual();
  int linhasCheias = (int)posicao;
  float fracionaria = posicao - linhasCheias;

  for (uint8_t r = 0; r < 8; r++) {
    uint8_t row = MATRIX_H - 1 - r;
    Cor cor;
    if (posicao <= 0.0f) cor = cor_rgb(0, 0, 0);
    else if ((int)r < linhasCheias) cor = COR_MENU;
    else if ((int)r == linhasCheias) cor = blend(COR_PISO, COR_MENU, (uint8_t)(fracionaria * 255));
    else cor = cor_rgb(0, 0, 0);
    for (uint8_t col = 0; col < MATRIX_W; col++) ponto(col, row, cor);
  }
  atualiza_status_ajustes();
  mostra();
}

static void toca_blip_ajuste(float posicao) {
  if (posicao <= 0.0f) return;
  int grau = (int)(posicao + 0.5f);
  if (grau > 7) grau = 7;
  toca_sfx(ESCALA_MENU[grau], 40);
}

static void toca_blip_ajuste_musica(float posicao) {
  if (posicao <= 0.0f) return;
  int grau = (int)(posicao + 0.5f);
  if (grau > 7) grau = 7;
  musica_nota(ESCALA_MENU[grau]);
  delay(50);
  musica_nota(0);
}

static void ajusta_valor(int8_t direcao) {
  if (ajusteAtual == AJUSTE_PALETA) {
    aplica_paleta((uint8_t)((paletaAtual + N_PALETAS + direcao) % N_PALETAS));
    toca_blip_ajuste(1.0f + 7.0f * paletaAtual / (N_PALETAS > 1 ? N_PALETAS - 1 : 1));
    return;
  }
  if (ajusteAtual == AJUSTE_BRILHO) {
    int v = (int)brilhoAtual + direcao * BRILHO_STEP;
    if (v < MATRIX_BRIGHTNESS_MIN) v = MATRIX_BRIGHTNESS_MIN;
    if (v > MATRIX_BRIGHTNESS_MAX) v = MATRIX_BRIGHTNESS_MAX;
    brilhoAtual = (uint8_t)v;
    toca_blip_ajuste(posicao_do_ajuste_atual());
  } else if (ajusteAtual == AJUSTE_MUSICA) {
    int v = (int)volumeMusica + direcao * VOLUME_STEP;
    if (v < VOLUME_MIN) v = VOLUME_MIN;
    if (v > VOLUME_MAX) v = VOLUME_MAX;
    volumeMusica = (uint8_t)v;
    toca_blip_ajuste_musica(posicao_do_ajuste_atual());
  } else {
    int v = (int)volumeSfx + direcao * VOLUME_STEP;
    if (v < VOLUME_MIN) v = VOLUME_MIN;
    if (v > VOLUME_MAX) v = VOLUME_MAX;
    volumeSfx = (uint8_t)v;
    toca_blip_ajuste(posicao_do_ajuste_atual());
  }
}

void comando_ajustes(Tecla t) {
  switch (t) {
    case ESQUERDA:
      ajusteAtual = (ajusteAtual + N_AJUSTES - 1) % N_AJUSTES;
      toca_sfx(ESCALA_MENU[0], 25);
      break;
    case DIREITA:
      ajusteAtual = (ajusteAtual + 1) % N_AJUSTES;
      toca_sfx(ESCALA_MENU[1], 25);
      break;
    case CIMA: ajusta_valor(+1); break;
    case BAIXO: ajusta_valor(-1); break;
    default: return;
  }
  desenha_ajustes();
}

void entra_nos_ajustes(void) {
  toca_sfx(ESCALA_MENU[0], 45);
  espera_ms(45);
  toca_sfx(ESCALA_MENU[4], 45);
  espera_ms(45);
  estado = AJUSTES;
  ajusteAtual = AJUSTE_BRILHO;
  desenha_ajustes();
}

void sai_dos_ajustes(void) {
  toca_sfx(ESCALA_MENU[4], 45);
  espera_ms(45);
  toca_sfx(ESCALA_MENU[0], 45);
  espera_ms(45);
  salva_ajustes();
  inicia_idle();
}
