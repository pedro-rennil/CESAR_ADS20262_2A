#ifndef CONFIG_H
#define CONFIG_H
// ===================================================================
// Lightpunk GameDeck - Console Edition
//
// Transcricao para C puro, rodando no console do Windows, do jogo
// original em C++ (github.com/cebola4444/lightpunk-game-deck) feito
// pra ESP32 + matriz de LED WS2812B + keypad analogico + buzzers
// piezo. A logica do jogo (Tetris + o modo hibrido "Tetris Invader")
// foi mantida fiel ao original; so a camada de entrada/saida mudou:
//
//   matriz de LED WS2812B  -> grade de cores ANSI no terminal
//   keypad analogico (ADC) -> teclado real (setas + ENTER/ESPACO)
//   2x buzzer piezo (PWM)  -> Beep() do Windows numa thread separada
//   flash (Preferences)    -> arquivo binario "ajustes.dat"
//
// Este arquivo concentra as constantes que no original dependiam do
// hardware (pinagem, niveis de tensao do keypad etc.); aqui viram so
// o tamanho da "tela" e o mapeamento de teclas.
// ===================================================================

// ---- "MATRIZ" (agora e a grade desenhada no console, 8 de largura
// por 16 de altura - mesmo formato classico de Tetris do original) ----
#define MATRIX_W 8
#define MATRIX_H 16
#define MATRIX_N (MATRIX_W * MATRIX_H)

// ---- TECLADO: 5 teclas logicas, mapeadas pro teclado do notebook ----
// (no original eram 5 botoes fisicos lidos por um keypad analogico
// com escada de resistores; aqui lemos o teclado de verdade)
#define TECLA_ESC VK_ESCAPE

#define KEY_ESTAVEL_MS 12 // mesmo filtro de estabilidade do original

// ---- "BRILHO": no original controlava o PWM dos LEDs (FastLED);
// aqui escala a intensidade RGB antes de imprimir no terminal ----
#define MATRIX_BRIGHTNESS_MIN 40  // 0-255
#define MATRIX_BRIGHTNESS_PADRAO 170 // 0-255
#define MATRIX_BRIGHTNESS_MAX 255 // 0-255

#endif
