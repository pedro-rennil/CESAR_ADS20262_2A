#include "telas.h"
#include "tipos.h"
#include "config.h"
#include "render.h"
#include "audio.h"
#include "ajustes.h"
#include "plataforma.h"
#include <stdlib.h>

// ===================================================================
// Efeito "glitch" (tela cheia de blocos 2x2 aparecendo/piscando/
// sumindo aleatoriamente) - usado no boot, na tela de espera e como
// transicao entre telas. Transcricao direta do original.
// ===================================================================
// GLITCH_TILE_* e as 3 fases de duracao precisam ser macros (nao
// "static const"): elas alimentam outras constantes estaticas logo
// abaixo (GLITCH_TILES_X/Y, GLITCH_CICLO_MS), e C - ao contrario de
// C++ - nao aceita um objeto const em expressao usada pra inicializar
// outro objeto estatico. Macro e so substituicao de texto, entao
// continua sendo uma expressao constante de verdade.
#define GLITCH_TILE_W 2
#define GLITCH_TILE_H 2
#define GLITCH_FASE_LIGAR_MS 1000
#define GLITCH_FASE_SEGURAR_MS 1500
#define GLITCH_FASE_APAGAR_MS 1000
// Estas tambem precisam ser macros: dependem das de cima, e uma cadeia
// de "const depende de const" continua invalida em C em qualquer
// profundidade (soh literais/macros/enum sao expressao constante).
#define GLITCH_TILES_X (MATRIX_W / GLITCH_TILE_W)
#define GLITCH_TILES_Y (MATRIX_H / GLITCH_TILE_H)
#define GLITCH_N_TILES (GLITCH_TILES_X * GLITCH_TILES_Y)
static const uint16_t GLITCH_QUADRO_MS = 40;
static const uint16_t GLITCH_PAUSA_MS = 700;
static const uint32_t GLITCH_CICLO_MS = (uint32_t)GLITCH_FASE_LIGAR_MS + GLITCH_FASE_SEGURAR_MS + GLITCH_FASE_APAGAR_MS;
static const uint8_t GLITCH_NIVEL_BASE = 100;
static const uint8_t GLITCH_CLARAO_TICKS = 1;
static const uint8_t GLITCH_INTERVALO_MIN = 4, GLITCH_INTERVALO_VAR = 10;

static uint16_t glitchAcordaEm[32];
static uint16_t glitchApagaEm[32];
static bool glitchPiscando[32];
static uint8_t glitchContagem[32];
static bool glitchEmB[32];
static uint32_t glitchInicio = 0;
static uint32_t glitchProximoQuadro = 0;

static uint16_t glitch_proximo_intervalo(void) {
  if (rand() % 100 < 15) return GLITCH_QUADRO_MS * 3 + rand() % 150;
  return GLITCH_QUADRO_MS / 3 + rand() % GLITCH_QUADRO_MS;
}

static void glitch_sorteia(void) {
  for (uint8_t i = 0; i < GLITCH_N_TILES; i++) {
    glitchAcordaEm[i] = (uint16_t)(rand() % GLITCH_FASE_LIGAR_MS);
    glitchApagaEm[i] = (uint16_t)(rand() % GLITCH_FASE_APAGAR_MS);
    glitchPiscando[i] = false;
    glitchContagem[i] = (uint8_t)(GLITCH_INTERVALO_MIN + rand() % GLITCH_INTERVALO_VAR);
    glitchEmB[i] = rand() % 2;
  }
  glitchInicio = millis();
  glitchProximoQuadro = millis();
}

static void glitch_desenha_quadro(uint32_t decorrido) {
  for (uint8_t i = 0; i < GLITCH_N_TILES; i++) {
    if (glitchContagem[i] > 0) {
      glitchContagem[i]--;
      continue;
    }
    glitchPiscando[i] = !glitchPiscando[i];
    glitchContagem[i] = glitchPiscando[i] ? GLITCH_CLARAO_TICKS : (uint8_t)(GLITCH_INTERVALO_MIN + rand() % GLITCH_INTERVALO_VAR);
  }

  for (uint8_t ty = 0; ty < GLITCH_TILES_Y; ty++) {
    for (uint8_t tx = 0; tx < GLITCH_TILES_X; tx++) {
      uint8_t idx = ty * GLITCH_TILES_X + tx;
      bool ligado;
      if (decorrido < GLITCH_FASE_LIGAR_MS) {
        ligado = decorrido >= glitchAcordaEm[idx];
      } else if (decorrido < (uint32_t)GLITCH_FASE_LIGAR_MS + GLITCH_FASE_SEGURAR_MS) {
        ligado = true;
      } else {
        uint32_t tApagar = decorrido - GLITCH_FASE_LIGAR_MS - GLITCH_FASE_SEGURAR_MS;
        ligado = tApagar < glitchApagaEm[idx];
      }
      Cor base = glitchEmB[idx] ? COR_GLITCH_B : COR_GLITCH_A;
      Cor outra = glitchEmB[idx] ? COR_GLITCH_A : COR_GLITCH_B;
      Cor cor = !ligado ? cor_rgb(0, 0, 0) : (glitchPiscando[idx] ? outra : escala(base, GLITCH_NIVEL_BASE));
      for (uint8_t dy = 0; dy < GLITCH_TILE_H; dy++)
        for (uint8_t dx = 0; dx < GLITCH_TILE_W; dx++)
          ponto((int8_t)(tx * GLITCH_TILE_W + dx), (int8_t)(ty * GLITCH_TILE_H + dy), cor);
    }
  }
  mostra();
}

void glitch_de_boot(void) {
  render_status("INICIANDO...", "", "", "", "");
  glitch_sorteia();
  while (millis() - glitchInicio < GLITCH_CICLO_MS) {
    if (millis() < glitchProximoQuadro) {
      delay(2);
      continue;
    }
    glitchProximoQuadro = millis() + glitch_proximo_intervalo();
    glitch_desenha_quadro(millis() - glitchInicio);
  }
  limpa_tela_led();
  mostra();
}

static void glitch_desenha_estatica(void) {
  for (uint8_t ty = 0; ty < GLITCH_TILES_Y; ty++) {
    for (uint8_t tx = 0; tx < GLITCH_TILES_X; tx++) {
      Cor cor = (rand() % 2) ? escala((rand() % 2) ? COR_GLITCH_A : COR_GLITCH_B, (uint8_t)(60 + rand() % 195))
                              : cor_rgb(0, 0, 0);
      for (uint8_t dy = 0; dy < GLITCH_TILE_H; dy++)
        for (uint8_t dx = 0; dx < GLITCH_TILE_W; dx++)
          ponto((int8_t)(tx * GLITCH_TILE_W + dx), (int8_t)(ty * GLITCH_TILE_H + dy), cor);
    }
  }
  mostra();
}

void rajada_glitch(uint16_t duracaoMs) {
  uint32_t inicio = millis();
  uint32_t proximoQuadro = millis();
  while (millis() - inicio < duracaoMs) {
    atualiza_sfx();
    if (millis() < proximoQuadro) {
      delay(2);
      continue;
    }
    uint16_t intervalo = glitch_proximo_intervalo();
    proximoQuadro = millis() + intervalo;
    glitch_desenha_estatica();
    uint16_t duracaoBlip = intervalo > 8 ? intervalo - 8 : 1;
    toca_sfx((uint16_t)(300 + rand() % 1400), duracaoBlip);
  }
  para_sfx();
}

// ===================================================================
// Assinatura de boot (as iniciais dos dois criadores do jogo original)
// ===================================================================
static const uint8_t ASSINATURA_CIMA[3][8] = {
    {0b11111111, 0b10000001, 0b10111101, 0b10100001, 0b10100001, 0b10111101, 0b10000001, 0b11111111},
    {0b11111111, 0b10000001, 0b10100001, 0b10100001, 0b10100001, 0b10111001, 0b10000001, 0b11111111},
    {0b11111111, 0b10000001, 0b10111001, 0b10100101, 0b10100101, 0b10111001, 0b10000001, 0b11111111},
};
static const uint8_t ASSINATURA_BAIXO[3][8] = {
    {0b11111111, 0b10000001, 0b10100001, 0b10111101, 0b10100101, 0b10111001, 0b10000001, 0b11111111},
    {0b11111111, 0b10000001, 0b10100101, 0b10110101, 0b10101101, 0b10100101, 0b10000001, 0b11111111},
    {0b11111111, 0b10000001, 0b10111001, 0b10100101, 0b10111001, 0b10100101, 0b10000001, 0b11111111},
};
static const uint16_t ASSINATURA_DISPLAY_MS = 1000;
static const uint16_t ASSINATURA_GLITCH_MS = 500;

static void desenha_assinatura_quadro(uint8_t tela) {
  desenha_tela_dupla_cor(ASSINATURA_CIMA[tela], ASSINATURA_BAIXO[tela], COR_ASSINATURA);
}

void assinatura_de_boot(void) {
  render_status("LIGHTPUNK GAMEDECK", "porte para C (console) do jogo", "original em C++ p/ ESP32", "by @cebolander & @lixofuturista", "");
  desenha_assinatura_quadro(0);
  delay(ASSINATURA_DISPLAY_MS);
  for (uint8_t tela = 1; tela < 3; tela++) {
    rajada_glitch(ASSINATURA_GLITCH_MS);
    desenha_assinatura_quadro(tela);
    delay(ASSINATURA_DISPLAY_MS);
  }
}

// ===================================================================
// Tela de espera (titulo piscando -> estatica -> glitch -> pausa, em
// ciclo continuo ate o jogador apertar alguma tecla).
// ===================================================================
static const uint8_t TITULO_CIMA[3][8] = {
    {0b11111111, 0b10000001, 0b10111101, 0b10011001, 0b10011001, 0b10011001, 0b10000001, 0b11111111},
    {0b11111111, 0b10000001, 0b10111101, 0b10011001, 0b10011001, 0b10011001, 0b10000001, 0b11111111},
    {0b11111111, 0b10000001, 0b10011001, 0b10011001, 0b10011001, 0b10011001, 0b10000001, 0b11111111},
};
static const uint8_t TITULO_BAIXO[3][8] = {
    {0b11111111, 0b10000001, 0b10111101, 0b10111101, 0b10100001, 0b10111101, 0b10000001, 0b11111111},
    {0b11111111, 0b10000001, 0b10111101, 0b10100101, 0b10111001, 0b10100101, 0b10000001, 0b11111111},
    {0b11111111, 0b10000001, 0b10111101, 0b10110001, 0b10001101, 0b10111101, 0b10000001, 0b11111111},
};
static const uint8_t TITULO_TELAS = 3;
static const uint16_t IDLE_TITULO_MS = 1400;
static const uint16_t IDLE_ESTATICA_MS = 450;

static IdleFase idleFase = IDLE_TITULO;
static uint8_t idleTela = 0;
static uint32_t idleFaseInicioMs = 0;

static uint8_t idleTituloFase = 0;
static uint32_t idleTituloPiscaMs = 0;
static const uint16_t IDLE_TITULO_PISCA_MS = 350;

static void status_tela_espera(void) {
  render_status("LIGHTPUNK GAMEDECK", "seta: comeca o Tetris", "ENTER 2x: Tetris Invader", "segure ENTER: ajustes", "ESC: sair");
}

static void desenha_titulo(void) {
  Cor a = idleTituloFase ? COR_TITULO_B : COR_TITULO_A;
  Cor b = idleTituloFase ? COR_TITULO_A : COR_TITULO_B;
  limpa_tela_led();
  desenha_glifo_painel_borda_letra(TITULO_CIMA[idleTela], 0, a, b);
  desenha_glifo_painel_borda_letra(TITULO_BAIXO[idleTela], 1, b, a);
  status_tela_espera();
  mostra();
}

static void idle_entra(IdleFase fase) {
  idleFase = fase;
  idleFaseInicioMs = millis();
  glitchProximoQuadro = millis();
  switch (fase) {
    case IDLE_TITULO:
      idleTituloFase = 0;
      idleTituloPiscaMs = millis();
      desenha_titulo();
      break;
    case IDLE_GLITCH:
      glitch_sorteia();
      break;
    case IDLE_PAUSA:
      limpa_tela_led();
      status_tela_espera();
      mostra();
      break;
    default:
      break;
  }
}

void inicia_idle(void) {
  estado = PARADA;
  idleTela = 0;
  idle_entra(IDLE_TITULO);
}

void inicia_idle_pelo_glitch(void) {
  estado = PARADA;
  idleTela = 0;
  idle_entra(IDLE_GLITCH);
}

void atualiza_idle(void) {
  uint32_t t = millis() - idleFaseInicioMs;
  switch (idleFase) {
    case IDLE_TITULO:
      if (t >= IDLE_TITULO_MS) {
        idle_entra(IDLE_ESTATICA);
      } else if (millis() - idleTituloPiscaMs >= IDLE_TITULO_PISCA_MS) {
        idleTituloPiscaMs = millis();
        idleTituloFase ^= 1;
        desenha_titulo();
      }
      break;

    case IDLE_ESTATICA:
      if (t >= IDLE_ESTATICA_MS) {
        idleTela++;
        if (idleTela >= TITULO_TELAS) {
          idleTela = 0;
          idle_entra(IDLE_GLITCH);
        } else {
          idle_entra(IDLE_TITULO);
        }
      } else if (millis() >= glitchProximoQuadro) {
        glitchProximoQuadro = millis() + glitch_proximo_intervalo();
        glitch_desenha_estatica();
      }
      break;

    case IDLE_GLITCH:
      if (millis() - glitchInicio >= GLITCH_CICLO_MS) {
        idle_entra(IDLE_PAUSA);
      } else if (millis() >= glitchProximoQuadro) {
        glitchProximoQuadro = millis() + glitch_proximo_intervalo();
        glitch_desenha_quadro(millis() - glitchInicio);
      }
      break;

    case IDLE_PAUSA:
      if (t >= GLITCH_PAUSA_MS) idle_entra(IDLE_TITULO);
      break;
  }
}

// ===================================================================
// Contagem regressiva antes de cada partida (Tetris ou Invader)
// ===================================================================
static const uint8_t CONTAGEM_CIMA[4][8] = {
    {0b11111111, 0b10000001, 0b10111101, 0b10011101, 0b10000101, 0b10111101, 0b10000001, 0b11111111},
    {0b11111111, 0b10000001, 0b10111101, 0b10001101, 0b10110001, 0b10111101, 0b10000001, 0b11111111},
    {0b11111111, 0b10000001, 0b10011001, 0b10001001, 0b10001001, 0b10001001, 0b10000001, 0b11111111},
    {0b11111111, 0b10000001, 0b10111101, 0b10100001, 0b10101101, 0b10111101, 0b10000001, 0b11111111},
};
static const uint8_t CONTAGEM_BAIXO[4][8] = {
    {0b11111111, 0b10000001, 0b10111101, 0b10011101, 0b10000101, 0b10111101, 0b10000001, 0b11111111},
    {0b11111111, 0b10000001, 0b10111101, 0b10001101, 0b10110001, 0b10111101, 0b10000001, 0b11111111},
    {0b11111111, 0b10000001, 0b10011001, 0b10001001, 0b10001001, 0b10001001, 0b10000001, 0b11111111},
    {0b11111111, 0b10000001, 0b10011001, 0b10100101, 0b10100101, 0b10011001, 0b10000001, 0b11111111},
};
static const uint16_t CONTAGEM_PISCA_MS = 150;

void contagem_regressiva(void) {
  static const uint16_t BLIP[4] = {C6, D6, E6, LA6};
  render_status("PREPARA...", "", "", "", "");
  for (uint8_t passo = 0; passo < 4; passo++) {
    bool ehGo = (passo == 3);
    toca_sfx(BLIP[passo], ehGo ? 160 : 70);
    uint8_t piscas = ehGo ? 4 : 2;
    for (uint8_t f = 0; f < piscas; f++) {
      Cor a = (f & 1) ? COR_TITULO_B : COR_TITULO_A;
      Cor b = (f & 1) ? COR_TITULO_A : COR_TITULO_B;
      limpa_tela_led();
      desenha_glifo_painel_borda_letra(CONTAGEM_CIMA[passo], 0, a, b);
      desenha_glifo_painel_borda_letra(CONTAGEM_BAIXO[passo], 1, b, a);
      mostra();
      espera_ms(CONTAGEM_PISCA_MS);
    }
  }
  limpa_tela_led();
  mostra();
  espera_ms(150);
}

// ===================================================================
// Fim de jogo (compartilhado pelo Tetris e pelo Tetris Invader)
// ===================================================================
static const uint8_t GAMEOVER_CIMA[4][8] = {
    {0b11111111, 0b10000001, 0b10111101, 0b10100001, 0b10101101, 0b10111101, 0b10000001, 0b11111111},
    {0b11111111, 0b10000001, 0b10100101, 0b10111101, 0b10100101, 0b10100101, 0b10000001, 0b11111111},
    {0b11111111, 0b10000001, 0b10011001, 0b10100101, 0b10100101, 0b10011001, 0b10000001, 0b11111111},
    {0b11111111, 0b10000001, 0b10111101, 0b10111101, 0b10100001, 0b10111101, 0b10000001, 0b11111111},
};
static const uint8_t GAMEOVER_BAIXO[4][8] = {
    {0b11111111, 0b10000001, 0b10111101, 0b10100101, 0b10111101, 0b10100101, 0b10000001, 0b11111111},
    {0b11111111, 0b10000001, 0b10111101, 0b10111101, 0b10100001, 0b10111101, 0b10000001, 0b11111111},
    {0b11111111, 0b10000001, 0b10100101, 0b10100101, 0b10100101, 0b10011001, 0b10000001, 0b11111111},
    {0b11111111, 0b10000001, 0b10111101, 0b10100101, 0b10111001, 0b10100101, 0b10000001, 0b11111111},
};
static const uint8_t GAMEOVER_TELAS = 4;
static const uint16_t GAMEOVER_TELA_MS = 800;
static const uint16_t GAMEOVER_ESTATICA_MS = 300;

static void telas_de_game_over(void) {
  for (uint8_t tela = 0; tela < GAMEOVER_TELAS; tela++) {
    if (tela) rajada_glitch(GAMEOVER_ESTATICA_MS);
    desenha_tela_dupla_cor(GAMEOVER_CIMA[tela], GAMEOVER_BAIXO[tela], COR_GAME_OVER);
    espera_ms(GAMEOVER_TELA_MS);
  }
  fade_out_matriz();
}

void animacao_game_over(void) {
  para_musica();
  render_status("FIM DE JOGO", "", "", "", "");

  for (int8_t y = MATRIX_H - 1; y >= 0; y--) {
    for (uint8_t x = 0; x < MATRIX_W; x++) ponto((int8_t)x, y, COR_GAME_OVER);
    mostra();
    toca_sfx((uint16_t)(1000 - (MATRIX_H - 1 - y) * 45), 50);
    espera_ms(55);
  }
  espera_ms(400);
  for (uint8_t y = 0; y < MATRIX_H; y++) {
    for (uint8_t x = 0; x < MATRIX_W; x++) ponto((int8_t)x, (int8_t)y, cor_rgb(0, 0, 0));
    mostra();
    espera_ms(30);
  }

  espera_ms(300);
  telas_de_game_over();
  espera_ms(300);
  inicia_idle();
}

void volta_ao_menu(void) {
  para_musica();
  para_sfx();
  inicia_idle();
}
