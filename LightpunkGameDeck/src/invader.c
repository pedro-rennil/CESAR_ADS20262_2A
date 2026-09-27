#include "invader.h"
#include "tetris.h" // PECAS, campo, nivel
#include "render.h"
#include "audio.h"
#include "ajustes.h"
#include "telas.h"
#include "plataforma.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static uint8_t mundo[MATRIX_H][MATRIX_W];

static const uint8_t PECA_HP_MAX = 4;
static uint8_t pecaHp[16];
static uint8_t proximoIdPeca = 1;

static const uint8_t NIVEL_DERIVA = 4;
static const uint16_t PECA_DERIVA_MS = 260;
static uint8_t pecaColMin[16], pecaColMax[16];
static int8_t pecaDx[16] = {0};
static uint32_t pecaProximaDerivaMs[16];
static uint8_t pecaMovendoId = 0;

// Mesmas constantes de tempo do Tetris, usadas aqui tambem (no
// original eram as mesmas variaveis estaticas do arquivo; como agora
// sao arquivos .c separados, cada um tem a sua copia).
static const uint16_t NIVEL_TEMPO_MS = 10000;
static const uint16_t DAS_MS = 170;
static const uint16_t ARR_MS = 70;

static uint8_t chanceDeMovimento(uint8_t nivelInvader) {
  if (nivelInvader < NIVEL_DERIVA) return 0;
  uint16_t c = (uint16_t)(15 + (uint16_t)(nivelInvader - NIVEL_DERIVA) * 40 / (8 - NIVEL_DERIVA));
  return (uint8_t)(c > 55 ? 55 : c);
}

static const uint8_t N_FAIXAS = 2;
static const uint8_t FAIXA_COL_MIN[2] = {0, MATRIX_W / 2 + 1};
static const uint8_t FAIXA_COL_MAX[2] = {MATRIX_W / 2 - 1, MATRIX_W - 1};
static uint8_t filaId[2] = {0, 0};

static const uint8_t CHANCE_ONDA_CENTRAL = 15;
static const uint8_t CENTRAL_COL_MIN = 2, CENTRAL_COL_MAX = 5;
static OndaTipo ondaAtual = ONDA_LATERAL;
static uint16_t vaoOndaRestante = 3;
static uint8_t filaLinhasC[4];
static uint8_t filaNC = 0, filaPosC = 0;
static uint8_t filaIdC = 0;

static const uint16_t PISCA_PECA_MS[5] = {60, 120, 250, 400, 0};

static Nave nave;
#define NAVE_HP_MAX_BASE 6 // precisa ser macro, nao "static const": C (ao contrario de C++) nao aceita
                            // um objeto const como inicializador de outra variavel estatica
static uint8_t naveHpMax = NAVE_HP_MAX_BASE;
static uint8_t naveHp = NAVE_HP_MAX_BASE;
static uint32_t naveInvulneravelAteMs = 0;
static const uint16_t INV_INVULNERAVEL_MS = 1000;
static const int8_t NAVE_W = 3;
static const int8_t NAVE_Y_MIN = 0, NAVE_Y_MAX = 14;
static const uint8_t NAVE_FORMA[2] = {0b010, 0b111};
static const uint8_t INIMIGO_FORMA[2] = {0b111, 0b010};

static const uint8_t MAX_TIROS = 4;
static Tiro tiros[4];
static const uint8_t MAX_TIROS_INIMIGOS = 6;
static Tiro tirosInimigos[6];

static const uint8_t MAX_ESTILHACOS = 12;
static Estilhaco estilhacos[12];
static const uint16_t ESTILHACO_PASSO_MS = 90;
static const int8_t DIST_EXPLOSAO = 1;
static uint32_t invUltimoPassoEstilhacoMs = 0;

static const uint8_t MAX_INIMIGOS = 3;
static Inimigo inimigos[3];
static const uint8_t INIMIGO_HP_MAX = 4;

static const Slot FORMACAO_1[1] = {{0, 0}};
static const Slot FORMACAO_2[2] = {{0, 0}, {3, 3}};
static const Slot FORMACAO_2_ESCUDO[2] = {{0, 0}, {0, 4}};
static const Slot FORMACAO_3[3] = {{0, 0}, {3, 3}, {0, 6}};
static const int8_t FORMACAO_Y = 1;
static int8_t formX = 0, formDx = 1, formXMin = 0, formXMax = 5;
static uint32_t formProximoZigMs = 0;
static uint32_t invSireneMs = 0;
static bool invSireneAlta = false;

static const uint8_t INV_NIVEIS = 8;
static const uint16_t INV_SCROLL_MS[9] = {0, 360, 330, 305, 280, 260, 240, 220, 200};
static const uint8_t INV_VAO_MIN[9] = {0, 4, 4, 4, 4, 3, 3, 3, 3};
static const uint8_t INV_VAO_VAR[9] = {0, 2, 2, 2, 2, 2, 2, 2, 2};
static const uint8_t CHEFE_QTD[9] = {0, 0, 1, 2, 3, 1, 1, 2, 3};
static const uint8_t CHEFE_ESCUDO[9] = {0, 0, 0, 0, 0, 1, 1, 0, 0};
static const uint16_t CHEFE_TIRO_MS[9] = {0, 0, 1400, 1300, 1200, 1200, 1150, 1100, 950};

static InvFase invFase = FASE_PECAS;
static uint8_t invNivel = 1;
static bool invGerando = true;
static uint32_t invFaseInicioMs = 0;
static uint32_t invInicioMs = 0, invUltimoScrollMs = 0, invUltimoTiroMs = 0;
static uint32_t invUltimoPassoTiroMs = 0, invUltimoPassoTiroInimigoMs = 0;
static uint16_t invBlocos = 0, invNaves = 0;
static uint32_t repeteMs = 0;

static uint8_t filaLinhas[2][4];
static uint8_t filaN[2] = {0, 0}, filaPos[2] = {0, 0};

static const uint16_t INV_TIRO_PASSO_MS = 45;
static const uint16_t INV_TIRO_INIMIGO_PASSO_MS = 90;
static const uint16_t INV_CADENCIA_MS = 220;
static const uint16_t INV_ENTRADA_PASSO_MS = 60;
static const uint16_t INV_INIMIGO_ZIG_MS = 260;
static const uint16_t INV_ESCUDO_PASSO_MS = 120;
static const uint16_t INV_ALERTA_MS = 900;
static const uint16_t INV_ALERTA_PISCA_MS = 150;

static bool celulaDaForma(const uint8_t *forma, int8_t fx, int8_t fy, int8_t px, int8_t py) {
  int8_t r = (int8_t)(py - fy), c = (int8_t)(px - fx);
  if (r < 0 || r > 1 || c < 0 || c >= NAVE_W) return false;
  return (forma[r] >> (NAVE_W - 1 - c)) & 1;
}

static void celulaDoAnel(const Inimigo *e, uint8_t k, int8_t *cx, int8_t *cy) {
  k %= 14;
  if (k < 5) { *cx = (int8_t)(e->x - 1 + k); *cy = (int8_t)(e->y - 1); }
  else if (k < 8) { *cx = (int8_t)(e->x + 3); *cy = (int8_t)(e->y + (k - 5)); }
  else if (k < 12) { *cx = (int8_t)(e->x + 2 - (k - 8)); *cy = (int8_t)(e->y + 2); }
  else { *cx = (int8_t)(e->x - 1); *cy = (int8_t)(e->y + 1 - (k - 12)); }
}

static bool escudoCobre(const Inimigo *e, int8_t px, int8_t py) {
  if (!e->escudo) return false;
  int8_t cx, cy;
  for (uint8_t i = 0; i < 2; i++) {
    celulaDoAnel(e, (uint8_t)(e->escudoFase + i * 7), &cx, &cy);
    if (cx == px && cy == py) return true;
  }
  return false;
}

static bool naveColideBloco(void) {
  for (uint8_t r = 0; r < 2; r++)
    for (uint8_t c = 0; c < (uint8_t)NAVE_W; c++)
      if (((NAVE_FORMA[r] >> (NAVE_W - 1 - c)) & 1) && mundo[nave.y + r][nave.x + c]) return true;
  return false;
}

static Inimigo *inimigoEncostadoNaNave(void) {
  for (uint8_t i = 0; i < MAX_INIMIGOS; i++) {
    Inimigo *e = &inimigos[i];
    if (!e->ativo) continue;
    for (uint8_t r = 0; r < 2; r++)
      for (uint8_t c = 0; c < (uint8_t)NAVE_W; c++)
        if (((NAVE_FORMA[r] >> (NAVE_W - 1 - c)) & 1) &&
            celulaDaForma(INIMIGO_FORMA, e->x, e->y, (int8_t)(nave.x + c), (int8_t)(nave.y + r)))
          return e;
  }
  return NULL;
}

static bool algumInimigoAtivo(void) {
  for (uint8_t i = 0; i < MAX_INIMIGOS; i++)
    if (inimigos[i].ativo) return true;
  return false;
}

static bool mundoVazio(void) {
  for (uint8_t y = 0; y < MATRIX_H; y++)
    for (uint8_t x = 0; x < MATRIX_W; x++)
      if (mundo[y][x]) return false;
  return true;
}

static bool naveSofreDano(void) {
  if ((int32_t)(millis() - naveInvulneravelAteMs) < 0) return false;
  naveHp--;
  naveInvulneravelAteMs = millis() + INV_INVULNERAVEL_MS;
  toca_sfx(naveHp ? 880 : 659, 120);
  return naveHp == 0;
}

static void removePeca(uint8_t id) {
  for (uint8_t y = 0; y < MATRIX_H; y++)
    for (uint8_t x = 0; x < MATRIX_W; x++)
      if (mundo[y][x] == id) mundo[y][x] = 0;
  pecaHp[id] = 0;
  for (uint8_t faixa = 0; faixa < N_FAIXAS; faixa++)
    if (id == filaId[faixa]) filaPos[faixa] = filaN[faixa];
  if (id == filaIdC) filaPosC = filaNC;
}

static int8_t distanciaAteNave(int8_t x, int8_t y) {
  int8_t melhor = 127;
  for (uint8_t r = 0; r < 2; r++)
    for (uint8_t c = 0; c < (uint8_t)NAVE_W; c++) {
      int8_t dx = (int8_t)(x - (nave.x + c)), dy = (int8_t)(y - (nave.y + r));
      if (dx < 0) dx = (int8_t)-dx;
      if (dy < 0) dy = (int8_t)-dy;
      int8_t d = (dx > dy) ? dx : dy;
      if (d < melhor) melhor = d;
    }
  return melhor;
}

static void explodePeca(uint8_t id) {
  int8_t cy[4], cx[4];
  uint8_t n = 0;
  for (uint8_t y = 0; y < MATRIX_H && n < 4; y++)
    for (uint8_t x = 0; x < MATRIX_W && n < 4; x++)
      if (mundo[y][x] == id) {
        cy[n] = (int8_t)y;
        cx[n] = (int8_t)x;
        n++;
      }
  removePeca(id);
  if (pecaMovendoId == id) pecaMovendoId = 0;
  if (n == 0) return;
  int16_t somaX = 0, somaY = 0;
  for (uint8_t i = 0; i < n; i++) {
    somaX = (int16_t)(somaX + cx[i]);
    somaY = (int16_t)(somaY + cy[i]);
  }
  int8_t centroX = (int8_t)(somaX / n), centroY = (int8_t)(somaY / n);
  static const int8_t DIAGONAL[4][2] = {{-1, -1}, {1, -1}, {-1, 1}, {1, 1}};
  for (uint8_t i = 0; i < n; i++) {
    int8_t dx = (cx[i] > centroX) ? 1 : (cx[i] < centroX) ? -1 : 0;
    int8_t dy = (cy[i] > centroY) ? 1 : (cy[i] < centroY) ? -1 : 0;
    if (dx == 0 && dy == 0) {
      dx = DIAGONAL[i % 4][0];
      dy = DIAGONAL[i % 4][1];
    }
    for (uint8_t k = 0; k < MAX_ESTILHACOS; k++) {
      if (estilhacos[k].ativo) continue;
      estilhacos[k].x = cx[i];
      estilhacos[k].y = cy[i];
      estilhacos[k].dx = dx;
      estilhacos[k].dy = dy;
      estilhacos[k].ativo = true;
      estilhacos[k].quicou = false;
      break;
    }
  }
  toca_sfx(300, 60);
}

static void verificaExplosaoPecas(bool *mudou) {
  for (uint8_t id = 1; id <= 15; id++) {
    if (!pecaHp[id]) continue;
    bool perto = false;
    for (uint8_t y = 0; y < MATRIX_H && !perto; y++)
      for (uint8_t x = 0; x < MATRIX_W && !perto; x++)
        if (mundo[y][x] == id && distanciaAteNave((int8_t)x, (int8_t)y) <= DIST_EXPLOSAO) perto = true;
    if (perto) {
      explodePeca(id);
      *mudou = true;
    }
  }
}

static void danificaPeca(uint8_t id) {
  if (pecaHp[id] > 1) {
    pecaHp[id]--;
    toca_sfx_tique(PENTA[0], 15);
    return;
  }
  removePeca(id);
  invBlocos++;
  toca_sfx(784, 60);
}

static void inimigosLevamTiros(void) {
  for (uint8_t i = 0; i < MAX_TIROS; i++) {
    Tiro *t = &tiros[i];
    if (!t->ativo) continue;
    for (uint8_t k = 0; k < MAX_INIMIGOS && t->ativo; k++) {
      Inimigo *e = &inimigos[k];
      if (!e->ativo || e->entrando) continue;
      if (escudoCobre(e, t->x, t->y)) {
        t->ativo = false;
        toca_sfx_suave(PENTA[0], 12);
      } else if (celulaDaForma(INIMIGO_FORMA, e->x, e->y, t->x, t->y)) {
        t->ativo = false;
        if (e->hp > 1) {
          e->hp--;
          toca_sfx(PENTA[2], 25);
        } else {
          e->ativo = false;
          invNaves++;
          toca_sfx(PENTA[3], 90);
        }
      }
    }
  }
}

static bool naveAtingidaPorTiro(void) {
  for (uint8_t i = 0; i < MAX_TIROS_INIMIGOS; i++) {
    Tiro *t = &tirosInimigos[i];
    if (!t->ativo || !celulaDaForma(NAVE_FORMA, nave.x, nave.y, t->x, t->y)) continue;
    t->ativo = false;
    if (naveSofreDano()) return true;
  }
  return false;
}

static bool naveCabe(int8_t nx, int8_t ny) {
  if (nx < 0 || nx + NAVE_W > MATRIX_W || ny < NAVE_Y_MIN || ny > NAVE_Y_MAX) return false;
  for (uint8_t r = 0; r < 2; r++)
    for (uint8_t c = 0; c < (uint8_t)NAVE_W; c++)
      if (((NAVE_FORMA[r] >> (NAVE_W - 1 - c)) & 1) && mundo[ny + r][nx + c]) return false;
  return true;
}

static void moveNave(int8_t dx, int8_t dy) {
  if (!naveCabe((int8_t)(nave.x + dx), (int8_t)(nave.y + dy))) return;
  nave.x = (int8_t)(nave.x + dx);
  nave.y = (int8_t)(nave.y + dy);
  if (invFase != FASE_ALERTA) toca_sfx_suave(PENTA[3], 6);
}

static uint8_t chanceDeMira(uint8_t nivelInvader) {
  uint16_t c = (uint16_t)(50 + (uint16_t)(nivelInvader - 1) * 30 / (INV_NIVEIS - 1));
  return (uint8_t)(c > 80 ? 80 : c);
}

static void enfileiraPeca(uint8_t faixa) {
  uint8_t faixaIni = FAIXA_COL_MIN[faixa], faixaFim = FAIXA_COL_MAX[faixa];
  uint8_t largura = (uint8_t)(faixaFim - faixaIni + 1);
  uint8_t tipo, rot, cmin, cmax, w;
  do {
    tipo = rand() % 7;
    rot = rand() % 4;
    cmin = 4;
    cmax = 0;
    for (uint8_t r = 0; r < 4; r++)
      for (uint8_t c = 0; c < 4; c++)
        if ((PECAS[tipo][rot][r] >> (3 - c)) & 1) {
          if (c < cmin) cmin = c;
          if (c > cmax) cmax = c;
        }
    w = (uint8_t)(cmax - cmin + 1);
  } while (w > largura);
  int8_t maxX0 = (int8_t)(faixaFim - faixaIni + 1 - w);
  bool outraEmMovimento = pecaMovendoId && pecaHp[pecaMovendoId] && pecaDx[pecaMovendoId];
  bool emMovimento = !outraEmMovimento && rand() % 100 < chanceDeMovimento(invNivel);
  uint8_t x0;
  if (emMovimento) {
    x0 = (faixa == 0) ? 0 : (uint8_t)(MATRIX_W - w);
  } else {
    bool naveNaFaixa = (nave.x + NAVE_W - 1 >= faixaIni) && (nave.x <= faixaFim);
    if (naveNaFaixa && rand() % 100 < chanceDeMira(invNivel)) {
      int8_t alvo = (int8_t)((nave.x - faixaIni) + NAVE_W / 2 - w / 2 + (int8_t)(rand() % 3) - 1);
      if (alvo < 0) alvo = 0;
      if (alvo > maxX0) alvo = maxX0;
      x0 = (uint8_t)(faixaIni + (uint8_t)alvo);
    } else {
      x0 = (uint8_t)(faixaIni + rand() % (maxX0 + 1));
    }

    if (w == 1 && x0 == 0) x0 = 1;
    if (w == 1 && x0 == MATRIX_W - 1) x0 = MATRIX_W - 2;
  }
  filaN[faixa] = 0;
  for (uint8_t r = 0; r < 4; r++) {
    uint8_t bits = PECAS[tipo][rot][r];
    if (!bits) continue;
    uint8_t linha = 0;
    for (uint8_t c = cmin; c <= cmax; c++)
      if ((bits >> (3 - c)) & 1) linha = (uint8_t)(linha | (1 << (7 - (x0 + c - cmin))));
    filaLinhas[faixa][filaN[faixa]++] = linha;
  }
  filaPos[faixa] = 0;
  filaId[faixa] = proximoIdPeca;
  proximoIdPeca = (uint8_t)(proximoIdPeca % 15 + 1);
  pecaHp[filaId[faixa]] = PECA_HP_MAX;
  if (emMovimento) {
    pecaColMin[filaId[faixa]] = 0;
    pecaColMax[filaId[faixa]] = MATRIX_W - 1;
    pecaDx[filaId[faixa]] = (faixa == 0) ? 1 : -1;
    pecaMovendoId = filaId[faixa];
  } else {
    pecaColMin[filaId[faixa]] = faixaIni;
    pecaColMax[filaId[faixa]] = faixaFim;
    pecaDx[filaId[faixa]] = 0;
  }
  pecaProximaDerivaMs[filaId[faixa]] = millis() + PECA_DERIVA_MS;
}

static void enfileiraPecaCentral(void) {
  uint8_t tipo = rand() % 7, rot = rand() % 4;
  uint8_t cmin = 4, cmax = 0;
  for (uint8_t r = 0; r < 4; r++)
    for (uint8_t c = 0; c < 4; c++)
      if ((PECAS[tipo][rot][r] >> (3 - c)) & 1) {
        if (c < cmin) cmin = c;
        if (c > cmax) cmax = c;
      }
  uint8_t w = (uint8_t)(cmax - cmin + 1);
  int8_t maxX0 = (int8_t)(CENTRAL_COL_MAX - CENTRAL_COL_MIN + 1 - w);
  bool naveNoCentro = (nave.x + NAVE_W - 1 >= CENTRAL_COL_MIN) && (nave.x <= CENTRAL_COL_MAX);
  uint8_t x0;
  if (naveNoCentro && rand() % 100 < chanceDeMira(invNivel)) {
    int8_t alvo = (int8_t)((nave.x - CENTRAL_COL_MIN) + NAVE_W / 2 - w / 2 + (int8_t)(rand() % 3) - 1);
    if (alvo < 0) alvo = 0;
    if (alvo > maxX0) alvo = maxX0;
    x0 = (uint8_t)(CENTRAL_COL_MIN + (uint8_t)alvo);
  } else {
    x0 = (uint8_t)(CENTRAL_COL_MIN + rand() % (maxX0 + 1));
  }
  filaNC = 0;
  for (uint8_t r = 0; r < 4; r++) {
    uint8_t bits = PECAS[tipo][rot][r];
    if (!bits) continue;
    uint8_t linha = 0;
    for (uint8_t c = cmin; c <= cmax; c++)
      if ((bits >> (3 - c)) & 1) linha = (uint8_t)(linha | (1 << (7 - (x0 + c - cmin))));
    filaLinhasC[filaNC++] = linha;
  }
  filaPosC = 0;
  filaIdC = proximoIdPeca;
  proximoIdPeca = (uint8_t)(proximoIdPeca % 15 + 1);
  pecaHp[filaIdC] = PECA_HP_MAX;
  pecaColMin[filaIdC] = CENTRAL_COL_MIN;
  pecaColMax[filaIdC] = CENTRAL_COL_MAX;
  pecaDx[filaIdC] = 0;
}

static void atualizaDerivaPecas(bool *mudou) {
  uint32_t agora = millis();
  for (uint8_t id = 1; id <= 15; id++) {
    if (pecaDx[id] == 0 || pecaHp[id] == 0) continue;
    bool aindaEntrando = false;
    for (uint8_t faixa = 0; faixa < N_FAIXAS; faixa++)
      if (filaId[faixa] == id && filaPos[faixa] < filaN[faixa]) aindaEntrando = true;
    if (aindaEntrando) continue;
    if ((int32_t)(agora - pecaProximaDerivaMs[id]) < 0) continue;
    pecaProximaDerivaMs[id] = agora + PECA_DERIVA_MS;
    int8_t dx = pecaDx[id];
    int8_t cy[4], cx[4];
    uint8_t n = 0;
    for (uint8_t y = 0; y < MATRIX_H && n < 4; y++)
      for (uint8_t x = 0; x < MATRIX_W && n < 4; x++)
        if (mundo[y][x] == id) {
          cy[n] = (int8_t)y;
          cx[n] = (int8_t)x;
          n++;
        }
    bool cabe = true;
    for (uint8_t i = 0; i < n; i++) {
      int8_t nx = (int8_t)(cx[i] + dx);
      if (nx < pecaColMin[id] || nx > pecaColMax[id] || (mundo[cy[i]][nx] && mundo[cy[i]][nx] != id)) {
        cabe = false;
        break;
      }
    }
    if (!cabe) {
      pecaDx[id] = 0;
      continue;
    }
    for (uint8_t i = 0; i < n; i++) mundo[cy[i]][cx[i]] = 0;
    for (uint8_t i = 0; i < n; i++) mundo[cy[i]][cx[i] + dx] = id;
    *mudou = true;
  }
}

static const uint8_t ATRASO_ENTRE_FAIXAS = 2;
static uint8_t atrasoEntrada[2] = {0, 0};

static uint8_t chanceAlinhada(uint8_t nivelInvader) { return (uint8_t)((uint16_t)(nivelInvader - 1) * 75 / (INV_NIVEIS - 1)); }

static uint8_t proximaLinhaDoMundo(uint8_t faixa) {
  if (ondaAtual != ONDA_LATERAL || filaPos[faixa] >= filaN[faixa]) return 0;
  if (atrasoEntrada[faixa] > 0) {
    atrasoEntrada[faixa]--;
    return 0;
  }
  return filaLinhas[faixa][filaPos[faixa]++];
}

static uint8_t proximaLinhaDoMundoC(void) {
  if (ondaAtual != ONDA_CENTRAL || filaPosC >= filaNC) return 0;
  return filaLinhasC[filaPosC++];
}

static void avancaOnda(void) {
  bool ativa = (ondaAtual == ONDA_LATERAL) ? (filaPos[0] < filaN[0] || filaPos[1] < filaN[1]) : (filaPosC < filaNC);
  if (ativa || !invGerando) return;
  if (vaoOndaRestante > 0) {
    vaoOndaRestante--;
    return;
  }
  ondaAtual = (rand() % 100 < CHANCE_ONDA_CENTRAL) ? ONDA_CENTRAL : ONDA_LATERAL;
  if (ondaAtual == ONDA_LATERAL) {
    enfileiraPeca(0);
    enfileiraPeca(1);
    atrasoEntrada[0] = 0;
    bool alinhada = rand() % 100 < chanceAlinhada(invNivel);
    atrasoEntrada[1] = alinhada ? 0 : ATRASO_ENTRE_FAIXAS;
  } else {
    enfileiraPecaCentral();
  }
  vaoOndaRestante = (uint16_t)(INV_VAO_MIN[invNivel] + rand() % (INV_VAO_VAR[invNivel] + 1));
}

static void invaderScroll(void) {
  for (uint8_t x = 0; x < MATRIX_W; x++) {
    uint8_t id = mundo[MATRIX_H - 1][x];
    if (id) explodePeca(id);
  }
  for (int8_t y = MATRIX_H - 1; y > 0; y--) memcpy(mundo[y], mundo[y - 1], MATRIX_W);
  avancaOnda();
  uint8_t nova[MATRIX_W];
  memset(nova, 0, sizeof(nova));
  for (uint8_t faixa = 0; faixa < N_FAIXAS; faixa++) {
    uint8_t linha = proximaLinhaDoMundo(faixa);
    for (uint8_t x = FAIXA_COL_MIN[faixa]; x <= FAIXA_COL_MAX[faixa]; x++)
      if ((linha >> (7 - x)) & 1) nova[x] = filaId[faixa];
  }
  uint8_t linhaC = proximaLinhaDoMundoC();
  for (uint8_t x = CENTRAL_COL_MIN; x <= CENTRAL_COL_MAX; x++)
    if ((linhaC >> (7 - x)) & 1) nova[x] = filaIdC;
  memcpy(mundo[0], nova, MATRIX_W);
}

static void atira(void) {
  for (uint8_t i = 0; i < MAX_TIROS; i++) {
    if (tiros[i].ativo) continue;
    Tiro *t = &tiros[i];
    t->x = (int8_t)(nave.x + 1);
    t->y = (int8_t)(nave.y - 1);
    t->ativo = true;
    invUltimoTiroMs = millis();
    if (invFase != FASE_ALERTA) toca_sfx_tique(PENTA[5], 14);
    if (t->y >= 0 && mundo[t->y][t->x]) {
      danificaPeca(mundo[t->y][t->x]);
      t->ativo = false;
      return;
    }
    inimigosLevamTiros();
    return;
  }
}

static void chefesEntram(uint8_t qtd, bool escudo) {
  const Slot *form = (qtd >= 3) ? FORMACAO_3 : (qtd == 2) ? (escudo ? FORMACAO_2_ESCUDO : FORMACAO_2) : FORMACAO_1;
  int8_t maxDx = 0;
  for (uint8_t i = 0; i < qtd; i++)
    if (form[i].dx > maxDx) maxDx = form[i].dx;
  int8_t margem = escudo ? 1 : 0;
  formXMin = margem;
  formXMax = (int8_t)(MATRIX_W - NAVE_W - maxDx - margem);
  formX = (int8_t)((formXMin + formXMax) / 2);
  formDx = (rand() % 2) ? 1 : -1;
  uint32_t agora = millis();
  formProximoZigMs = agora + INV_INIMIGO_ZIG_MS;
  for (uint8_t i = 0; i < MAX_INIMIGOS; i++) {
    Inimigo *e = &inimigos[i];
    e->ativo = (i < qtd);
    if (!e->ativo) continue;
    e->dxForm = form[i].dx;
    e->yAlvo = (int8_t)(FORMACAO_Y + form[i].dy);
    e->x = (int8_t)(formX + e->dxForm);
    e->y = (int8_t)(e->yAlvo - 10);
    e->entrando = true;
    e->hp = INIMIGO_HP_MAX;
    e->escudo = escudo;
    e->escudoFase = (uint8_t)(i * 5);
    e->proximoPassoMs = agora;
    e->proximoTiroMs = agora;
    e->proximoEscudoMs = agora + INV_ESCUDO_PASSO_MS;
  }
  toca_sfx(PENTA[1], 80);
}

static bool celulaTemOutroInimigo(const Inimigo *quem, int8_t x, int8_t y) {
  for (uint8_t k = 0; k < MAX_INIMIGOS; k++) {
    const Inimigo *o = &inimigos[k];
    if (o == quem || !o->ativo || o->entrando) continue;
    if (celulaDaForma(INIMIGO_FORMA, o->x, o->y, x, y) || escudoCobre(o, x, y)) return true;
  }
  return false;
}

static bool inimigoAtira(const Inimigo *e) {
  int8_t x = (int8_t)(e->x + 1), y = (int8_t)(e->y + 2);
  if (y >= MATRIX_H) return false;
  if (celulaTemOutroInimigo(e, x, y)) return false;
  if (y >= 0 && mundo[y][x]) {
    toca_sfx_suave(523, 25);
    return false;
  }
  if (celulaDaForma(NAVE_FORMA, nave.x, nave.y, x, y)) return naveSofreDano();
  for (uint8_t i = 0; i < MAX_TIROS_INIMIGOS; i++) {
    if (tirosInimigos[i].ativo) continue;
    tirosInimigos[i].x = x;
    tirosInimigos[i].y = y;
    tirosInimigos[i].ativo = true;
    toca_sfx_suave(523, 25);
    return false;
  }
  return false;
}

static bool atualizaInimigos(bool *mudou) {
  uint32_t agora = millis();
  bool alguemEntrando = false;
  for (uint8_t k = 0; k < MAX_INIMIGOS; k++) {
    Inimigo *e = &inimigos[k];
    if (!e->ativo) continue;
    if (e->escudo && (int32_t)(agora - e->proximoEscudoMs) >= 0) {
      e->proximoEscudoMs = agora + INV_ESCUDO_PASSO_MS;
      e->escudoFase = (uint8_t)((e->escudoFase + 1) % 14);
      *mudou = true;
    }
    if (e->entrando) {
      alguemEntrando = true;
      if ((int32_t)(agora - e->proximoPassoMs) >= 0) {
        e->proximoPassoMs = agora + INV_ENTRADA_PASSO_MS;
        e->y++;
        *mudou = true;
        if (e->y >= e->yAlvo) {
          e->entrando = false;
          e->proximoTiroMs = agora + CHEFE_TIRO_MS[invNivel] / 2 + k * 300;
          formProximoZigMs = agora + INV_INIMIGO_ZIG_MS;
        }
      }
      continue;
    }
    if ((int32_t)(agora - e->proximoTiroMs) >= 0) {
      e->proximoTiroMs = agora + CHEFE_TIRO_MS[invNivel];
      if (inimigoAtira(e)) return true;
    }
  }

  if (!alguemEntrando && algumInimigoAtivo() && (int32_t)(agora - formProximoZigMs) >= 0) {
    formProximoZigMs = agora + INV_INIMIGO_ZIG_MS;
    if (rand() % 6 == 0) formDx = (int8_t)-formDx;
    int8_t nx = (int8_t)(formX + formDx);
    if (nx < formXMin || nx > formXMax) {
      formDx = (int8_t)-formDx;
      nx = (int8_t)(formX + formDx);
    }
    if (nx < formXMin || nx > formXMax) nx = formX;
    formX = nx;
    for (uint8_t k = 0; k < MAX_INIMIGOS; k++)
      if (inimigos[k].ativo) inimigos[k].x = (int8_t)(formX + inimigos[k].dxForm);
    *mudou = true;
  }
  inimigosLevamTiros();
  Inimigo *trombou = inimigoEncostadoNaNave();
  if (trombou) {
    trombou->ativo = false;
    toca_sfx(659, 80);
    return naveSofreDano();
  }
  return false;
}

static bool atualizaTiros(bool *mudou) {
  uint32_t agora = millis();
  if (agora - invUltimoPassoTiroMs >= INV_TIRO_PASSO_MS) {
    invUltimoPassoTiroMs = agora;
    for (uint8_t i = 0; i < MAX_TIROS; i++) {
      Tiro *t = &tiros[i];
      if (!t->ativo) continue;
      *mudou = true;

      if (t->y >= 0 && mundo[t->y][t->x]) {
        danificaPeca(mundo[t->y][t->x]);
        t->ativo = false;
        continue;
      }
      t->y--;
      if (t->y < 0) {
        t->ativo = false;
        continue;
      }
      if (mundo[t->y][t->x]) {
        danificaPeca(mundo[t->y][t->x]);
        t->ativo = false;
      }
    }
    inimigosLevamTiros();
  }
  if (agora - invUltimoPassoTiroInimigoMs >= INV_TIRO_INIMIGO_PASSO_MS) {
    invUltimoPassoTiroInimigoMs = agora;
    for (uint8_t i = 0; i < MAX_TIROS_INIMIGOS; i++) {
      Tiro *t = &tirosInimigos[i];
      if (!t->ativo) continue;
      *mudou = true;
      t->y++;
      if (t->y >= MATRIX_H) {
        t->ativo = false;
        continue;
      }
      if (t->y >= 0 && mundo[t->y][t->x]) {
        t->ativo = false;
        continue;
      }
      if (celulaDaForma(NAVE_FORMA, nave.x, nave.y, t->x, t->y)) {
        t->ativo = false;
        if (naveSofreDano()) return true;
      }
    }
  }
  return false;
}

static bool atualizaEstilhacos(bool *mudou) {
  uint32_t agora = millis();
  if (agora - invUltimoPassoEstilhacoMs < ESTILHACO_PASSO_MS) return false;
  invUltimoPassoEstilhacoMs = agora;
  for (uint8_t i = 0; i < MAX_ESTILHACOS; i++) {
    Estilhaco *e = &estilhacos[i];
    if (!e->ativo) continue;
    *mudou = true;
    e->x = (int8_t)(e->x + e->dx);
    e->y = (int8_t)(e->y + e->dy);
    if (e->x < 0 || e->x >= MATRIX_W) {
      if (e->quicou) {
        e->ativo = false;
        continue;
      }
      e->quicou = true;
      e->dx = (int8_t)-e->dx;
      e->x = (int8_t)(e->x + e->dx);
    }
    if (e->y < 0 || e->y >= MATRIX_H) {
      e->ativo = false;
      continue;
    }
    if (mundo[e->y][e->x]) {
      e->ativo = false;
      continue;
    }
    if (celulaDaForma(NAVE_FORMA, nave.x, nave.y, e->x, e->y)) {
      e->ativo = false;
      if (naveSofreDano()) return true;
    }
  }
  return false;
}

static void desenhaNaveEm(int8_t x, int8_t y, Cor cor) {
  for (uint8_t r = 0; r < 2; r++)
    for (uint8_t c = 0; c < (uint8_t)NAVE_W; c++)
      if ((NAVE_FORMA[r] >> (NAVE_W - 1 - c)) & 1) ponto((int8_t)(x + c), (int8_t)(y + r), cor);
}

static uint16_t piscaPorProximidade(int8_t distancia) {
  static const int8_t DIST_MAX_PISCA = 10;
  if (distancia > DIST_MAX_PISCA) distancia = DIST_MAX_PISCA;
  if (distancia < DIST_EXPLOSAO) distancia = DIST_EXPLOSAO;
  uint16_t faixa = (uint16_t)(DIST_MAX_PISCA - DIST_EXPLOSAO);
  uint16_t passo = (uint16_t)(distancia - DIST_EXPLOSAO);
  return (uint16_t)(90 + (uint16_t)(500 - 90) * passo / faixa);
}

static void atualiza_status_invader(void) {
  char l1[64], l2[64], l3[64];
  static const char *NOMES_FASE[4] = {"chuva de pecas", "limpando o campo", "ALERTA - chefe chegando", "BATALHA CONTRA O CHEFE"};
  snprintf(l1, sizeof(l1), "nivel %u / %u    (%s)", invNivel, INV_NIVEIS, NOMES_FASE[invFase]);
  char barra[7];
  uint8_t cheios = (naveHpMax == 0) ? 0 : (uint8_t)(6 * naveHp / naveHpMax);
  for (uint8_t i = 0; i < 6; i++) barra[i] = (i < cheios) ? '#' : '-';
  barra[6] = '\0';
  snprintf(l2, sizeof(l2), "nave: [%s] %u/%u", barra, naveHp, naveHpMax);
  snprintf(l3, sizeof(l3), "pecas destruidas: %u   naves: %u", invBlocos, invNaves);
  render_status("TETRIS INVADER", l1, l2, l3, "setas movem | ENTER atira");
}

static void desenhaInvader(void) {
  uint32_t agora = millis();
  limpa_tela_led();

  int8_t distanciaPeca[16];
  for (uint8_t id = 1; id <= 15; id++) distanciaPeca[id] = 127;
  for (uint8_t y = 0; y < MATRIX_H; y++)
    for (uint8_t x = 0; x < MATRIX_W; x++) {
      uint8_t id = mundo[y][x];
      if (!id) continue;
      int8_t d = distanciaAteNave((int8_t)x, (int8_t)y);
      if (d < distanciaPeca[id]) distanciaPeca[id] = d;
    }
  for (uint8_t y = 0; y < MATRIX_H; y++)
    for (uint8_t x = 0; x < MATRIX_W; x++) {
      uint8_t id = mundo[y][x];
      if (!id) continue;
      uint8_t hp = pecaHp[id];
      bool ferida = (hp > 0 && hp < PECA_HP_MAX) && ((agora / PISCA_PECA_MS[hp]) & 1);

      Cor corBase = pecaDx[id] ? COR_GAME_OVER : COR_GRID;
      bool alternada = (agora / piscaPorProximidade(distanciaPeca[id])) & 1;
      Cor corPeca = ferida ? COR_DESTAQUE : (alternada ? COR_GAME_OVER : corBase);
      ponto((int8_t)x, (int8_t)y, corPeca);
    }
  for (uint8_t k = 0; k < MAX_INIMIGOS; k++) {
    const Inimigo *e = &inimigos[k];
    if (!e->ativo) continue;
    bool ferido = e->hp < INIMIGO_HP_MAX && ((agora / PISCA_PECA_MS[e->hp]) & 1);
    Cor corInimigo = ferido ? COR_DESTAQUE : COR_GAME_OVER;
    if (e->entrando) corInimigo = ((agora / 50) & 1) ? COR_DESTAQUE : escala(COR_GAME_OVER, 110);
    for (uint8_t r = 0; r < 2; r++)
      for (uint8_t c = 0; c < (uint8_t)NAVE_W; c++)
        if ((INIMIGO_FORMA[r] >> (NAVE_W - 1 - c)) & 1) ponto((int8_t)(e->x + c), (int8_t)(e->y + r), corInimigo);
    if (e->escudo) {
      int8_t cx, cy;
      for (uint8_t i = 0; i < 2; i++) {
        celulaDoAnel(e, (uint8_t)(e->escudoFase + i * 7), &cx, &cy);
        ponto(cx, cy, COR_GRID);
      }
    }
  }
  if (invFase == FASE_ALERTA && invSireneAlta)
    for (uint8_t x = 0; x < MATRIX_W; x++) ponto((int8_t)x, 0, COR_GAME_OVER);
  for (uint8_t i = 0; i < MAX_TIROS_INIMIGOS; i++)
    if (tirosInimigos[i].ativo) ponto(tirosInimigos[i].x, tirosInimigos[i].y, escala(COR_GAME_OVER, 120));
  for (uint8_t i = 0; i < MAX_TIROS; i++)
    if (tiros[i].ativo) ponto(tiros[i].x, tiros[i].y, COR_DESTAQUE);
  for (uint8_t i = 0; i < MAX_ESTILHACOS; i++)
    if (estilhacos[i].ativo) ponto(estilhacos[i].x, estilhacos[i].y, COR_GAME_OVER);

  Cor corNave = COR_CAINDO;
  if ((int32_t)(agora - naveInvulneravelAteMs) < 0) {
    corNave = ((agora / 70) & 1) ? COR_GAME_OVER : COR_CAINDO;
  } else if (naveHp == 1) {
    corNave = ((agora / 110) & 1) ? COR_GAME_OVER : COR_CAINDO;
  }
  desenhaNaveEm(nave.x, nave.y, corNave);
  atualiza_status_invader();
  mostra();
}

static void iniciaFasePecas(void) {
  invFase = FASE_PECAS;
  invFaseInicioMs = millis();
  invGerando = true;
  for (uint8_t faixa = 0; faixa < N_FAIXAS; faixa++) filaN[faixa] = filaPos[faixa] = atrasoEntrada[faixa] = 0;
  filaNC = filaPosC = 0;
  ondaAtual = ONDA_LATERAL;
  vaoOndaRestante = 3;
  nivel = (uint8_t)(invNivel - 1);
}

void inicia_invader(void) {
  memset(mundo, 0, sizeof(mundo));
  memset(campo, 0, sizeof(campo));
  nave.x = (MATRIX_W - NAVE_W) / 2;
  nave.y = NAVE_Y_MAX;
  for (uint8_t i = 0; i < MAX_TIROS; i++) tiros[i].ativo = false;
  for (uint8_t i = 0; i < MAX_TIROS_INIMIGOS; i++) tirosInimigos[i].ativo = false;
  for (uint8_t i = 0; i < MAX_ESTILHACOS; i++) estilhacos[i].ativo = false;
  invUltimoPassoEstilhacoMs = 0;
  for (uint8_t i = 0; i < MAX_INIMIGOS; i++) inimigos[i].ativo = false;
  for (uint8_t faixa = 0; faixa < N_FAIXAS; faixa++) filaId[faixa] = 0;
  filaIdC = 0;
  pecaMovendoId = 0;
  proximoIdPeca = 1;
  memset(pecaHp, 0, sizeof(pecaHp));
  naveHpMax = NAVE_HP_MAX_BASE;
  naveHp = naveHpMax;
  naveInvulneravelAteMs = 0;
  invBlocos = invNaves = 0;
  invNivel = 1;
  estado = INVADER;

  contagem_regressiva();

  toca_sfx(LA5, 60);
  espera_ms(80);
  toca_sfx(E6, 60);
  espera_ms(80);
  toca_sfx(LA6, 90);
  espera_ms(120);
  inicia_musica();

  uint32_t agora = millis();
  invInicioMs = agora;
  invUltimoScrollMs = agora;
  invUltimoTiroMs = 0;
  invUltimoPassoTiroMs = agora;
  invUltimoPassoTiroInimigoMs = agora;
  repeteMs = agora + DAS_MS;
  iniciaFasePecas();
  desenhaInvader();
}

static void invaderMorte(void) {
  para_musica();

  for (uint8_t i = 0; i < 4; i++) {
    desenhaNaveEm(nave.x, nave.y, (i & 1) ? COR_GAME_OVER : COR_DESTAQUE);
    mostra();
    toca_sfx((uint16_t)(1200 - i * 200), 70);
    espera_ms(110);
  }
  animacao_game_over();
}

static void invaderChefeDerrotado(void) {
  int8_t cx = (int8_t)(nave.x + 1), cy = nave.y;
  uint16_t passo = 130;
  for (uint8_t raio = 0; raio <= 8; raio++) {
    desenhaInvader();
    for (int8_t dy = (int8_t)-raio; dy <= (int8_t)raio; dy++) {
      int8_t dx = (int8_t)(raio - (dy < 0 ? -dy : dy));
      ponto((int8_t)(cx + dx), (int8_t)(cy + dy), COR_DESTAQUE);
      ponto((int8_t)(cx - dx), (int8_t)(cy + dy), COR_DESTAQUE);
    }
    mostra();
    toca_sfx(PENTA[raio], (uint16_t)(passo - 20));
    espera_ms(passo);
    if (passo > 60) passo = (uint16_t)(passo - 8);
  }
  espera_ms(150);
}

static void invaderVitoria(void) {
  para_musica();

  uint16_t passo = 150;
  for (int8_t y = nave.y; y >= -2; y--) {
    limpa_tela_led();
    desenhaNaveEm(nave.x, y, COR_CAINDO);
    ponto((int8_t)(nave.x + 1), (int8_t)(y + 2), (y & 1) ? COR_DESTAQUE : COR_GAME_OVER);
    ponto((int8_t)(nave.x + 1), (int8_t)(y + 3), (y & 1) ? COR_GAME_OVER : COR_DESTAQUE);
    render_status("TETRIS INVADER", "VOCE VENCEU!", "", "", "");
    mostra();
    toca_sfx((uint16_t)(600 + (NAVE_Y_MAX - y) * 80), passo);
    espera_ms(passo);
    if (passo > 40) passo = (uint16_t)(passo - 10);
  }
  para_sfx();
  limpa_tela_led();
  mostra();
  espera_ms(300);

  const Cor *cores[4] = {&COR_CAINDO, &COR_GRID, &COR_GAME_OVER, &COR_DESTAQUE};
  for (uint8_t f = 0; f < 6; f++) {
    int8_t cx = (int8_t)(1 + rand() % 6), cy = (int8_t)(2 + rand() % 12);
    Cor cor = *cores[f % 4];
    toca_sfx(1800, 30);
    for (uint8_t raio = 0; raio <= 3; raio++) {
      esmaece(110);
      for (int8_t dy = (int8_t)-raio; dy <= (int8_t)raio; dy++) {
        int8_t dx = (int8_t)(raio - (dy < 0 ? -dy : dy));
        ponto((int8_t)(cx + dx), (int8_t)(cy + dy), cor);
        ponto((int8_t)(cx - dx), (int8_t)(cy + dy), cor);
      }
      mostra();
      toca_sfx((uint16_t)(1400 - raio * 250), 25);
      espera_ms(70);
    }
    espera_ms(90);
  }
  for (uint8_t i = 0; i < 6; i++) {
    esmaece(110);
    mostra();
    espera_ms(40);
  }

  rajada_glitch(600);
  limpa_tela_led();
  mostra();
  espera_ms(300);
  inicia_idle();
}

void invader(Tecla segurada, Tecla nova) {
  bool mudou = false;
  uint32_t agora = millis();

  Tecla dir = (nova != NADA && nova != SELECT) ? nova : NADA;
  bool repete = false;
  if (dir == NADA && segurada != NADA && segurada != SELECT && agora >= repeteMs) {
    dir = segurada;
    repete = true;
  }
  if (dir != NADA) {
    int8_t dx = (dir == ESQUERDA) ? -1 : (dir == DIREITA) ? 1 : 0;
    int8_t dy = (dir == CIMA) ? -1 : (dir == BAIXO) ? 1 : 0;
    moveNave(dx, dy);
    repeteMs = agora + (repete ? ARR_MS : DAS_MS);
    mudou = true;
    if (naveAtingidaPorTiro()) {
      desenhaInvader();
      invaderMorte();
      return;
    }
  }

  if (nova == SELECT || (segurada == SELECT && agora - invUltimoTiroMs >= INV_CADENCIA_MS)) {
    atira();
    mudou = true;
  }

  if (invFase != FASE_CHEFE && agora - invUltimoScrollMs >= INV_SCROLL_MS[invNivel]) {
    invUltimoScrollMs = agora;
    invaderScroll();
    mudou = true;
    if (naveColideBloco()) {
      for (uint8_t r = 0; r < 2; r++)
        for (uint8_t c = 0; c < (uint8_t)NAVE_W; c++) {
          uint8_t id = mundo[nave.y + r][nave.x + c];
          if (id) removePeca(id);
        }
      if (naveSofreDano()) {
        desenhaInvader();
        invaderMorte();
        return;
      }
    }
  }

  verificaExplosaoPecas(&mudou);
  atualizaDerivaPecas(&mudou);
  if (atualizaTiros(&mudou) || atualizaInimigos(&mudou) || atualizaEstilhacos(&mudou)) {
    desenhaInvader();
    invaderMorte();
    return;
  }

  switch (invFase) {
    case FASE_PECAS:
      if (agora - invFaseInicioMs >= NIVEL_TEMPO_MS) {
        invGerando = false;
        invFase = FASE_LIMPANDO;
        invFaseInicioMs = agora;
      }
      break;

    case FASE_LIMPANDO:
      if (mundoVazio()) {
        if (invNivel >= INV_NIVEIS) {
          invaderVitoria();
          return;
        }
        invNivel++;
        if (CHEFE_QTD[invNivel] > 0) {
          invFase = FASE_ALERTA;
          invFaseInicioMs = agora;
          invSireneMs = agora;
          invSireneAlta = false;
          nivel = 6;
        } else {
          toca_sfx(penta_do_nivel(invNivel), 35);
          iniciaFasePecas();
        }
        mudou = true;
      }
      break;

    case FASE_ALERTA:
      if (agora - invSireneMs >= INV_ALERTA_PISCA_MS) {
        invSireneMs = agora;
        invSireneAlta = !invSireneAlta;
        toca_sfx(invSireneAlta ? 880 : 659, (uint16_t)(INV_ALERTA_PISCA_MS - 20));
        mudou = true;
      }
      if (agora - invFaseInicioMs >= INV_ALERTA_MS) {
        para_sfx();
        invSireneAlta = false;
        invFase = FASE_CHEFE;
        invFaseInicioMs = agora;
        chefesEntram(CHEFE_QTD[invNivel], CHEFE_ESCUDO[invNivel]);
        mudou = true;
      }
      break;

    case FASE_CHEFE:
      if (!algumInimigoAtivo()) {
        if (naveHp >= naveHpMax && naveHpMax < 255) naveHpMax++;
        if (naveHp < naveHpMax) naveHp++;
        invaderChefeDerrotado();
        iniciaFasePecas();
        mudou = true;
      }
      break;
  }

  static uint32_t ultimoQuadroMs = 0;
  if (agora - ultimoQuadroMs >= 60) mudou = true;
  if (mudou) {
    ultimoQuadroMs = agora;
    desenhaInvader();
  }
}
