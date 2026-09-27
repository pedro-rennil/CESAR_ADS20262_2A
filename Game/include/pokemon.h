#ifndef POKEMON_H
#define POKEMON_H

// Enum para identificar o tipo do Pokemon
typedef enum { FOGO, AGUA, PLANTA } Tipo;

// UNION: Ocupa o mesmo espaço de memória para qualquer um dos atributos
typedef union {
    int poder_fogo;
    int poder_agua;
    int poder_planta;
} HabilidadeEspecial;

// STRUCT: Representa nosso Pokemon
typedef struct {
    char nome[20];
    int hp_maximo;
    int hp_atual;
    int ataque_base;
    Tipo tipo;
    HabilidadeEspecial especial;
} Pokemon;

// Protótipos de Funções
Pokemon* criarPokemon(const char* nome, int hp, int atk, Tipo tipo, int poder);
void destruirPokemon(Pokemon* p);
void curarEquipeRecursivo(Pokemon** equipe, int tamanho, int indice);
const char* nomeTipo(Tipo tipo);
float multiplicadorTipo(Tipo atacante, Tipo defensor);

#endif