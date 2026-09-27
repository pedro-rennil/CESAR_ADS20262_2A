#ifndef RENDER_H
#define RENDER_H
#include <stdint.h>
#include "tipos.h"

// Equivalentes diretos das funcoes de desenho do original (que
// escreviam na matriz de LED via FastLED). Aqui elas escrevem num
// framebuffer interno de MATRIX_W x MATRIX_H "pixels" e mostra()
// imprime esse framebuffer no console usando cores ANSI de 24 bits.
void render_iniciar(void);
void render_encerrar(void);

void ponto(int8_t x, int8_t y, Cor cor);
void limpa_tela_led(void); // equivalente a fill_solid(leds, MATRIX_N, CRGB::Black)
void mostra(void);         // equivalente a FastLED.show() + delay(20)

Cor cor_rgb(uint8_t r, uint8_t g, uint8_t b);
Cor escala(Cor cor, uint8_t percentual255);
Cor blend(Cor a, Cor b, uint8_t quantidade);
void esmaece(uint8_t quantidade); // equivalente a fadeToBlackBy(leds, MATRIX_N, quantidade)

void desenha_glifo_painel(const uint8_t *glifo, uint8_t painel, Cor cor);
void desenha_glifo_painel_borda_letra(const uint8_t *glifo, uint8_t painel, Cor corBorda, Cor corLetra);
void desenha_tela_dupla_cor(const uint8_t *cima, const uint8_t *baixo, Cor cor);
void fade_out_matriz(void);

// Painel de texto ao lado da matriz. Isso nao existia no original
// (o hardware nao tinha tela de texto, so a matriz de LED); e a
// forma natural de trazer pro console as informacoes que antes so
// apareciam no monitor serial (pontos, nivel, vida da nave etc).
void render_status(const char *titulo, const char *l1, const char *l2, const char *l3, const char *l4);

#endif
