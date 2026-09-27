#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pokemon.h"

// Aloca dinamicamente um novo Pokemon
Pokemon* criarPokemon(const char* nome, int hp, int atk, Tipo tipo, int poder) {
    Pokemon* p = (Pokemon*)malloc(sizeof(Pokemon));
    
    strcpy(p->nome, nome);
    p->hp_maximo = hp;
    p->hp_atual = hp;
    p->ataque_base = atk;
    p->tipo = tipo;
    
    // Configura a Union baseada no Enum
    if (tipo == FOGO) p->especial.poder_fogo = poder;
    else if (tipo == AGUA) p->especial.poder_agua = poder;
    else p->especial.poder_planta = poder;
    
    return p;
}

// Libera a memória do Pokemon
void destruirPokemon(Pokemon* p) {
    if (p != NULL) {
        free(p);
    }
}

// Função Recursiva para curar toda a equipe
void curarEquipeRecursivo(Pokemon** equipe, int tamanho, int indice) {
    // Condição de parada: chegamos ao fim do array
    if (indice >= tamanho) {
        return; 
    }
    
    if (equipe[indice] != NULL) {
        equipe[indice]->hp_atual = equipe[indice]->hp_maximo;
    }
    
    // Chamada recursiva para o próximo Pokémon
    curarEquipeRecursivo(equipe, tamanho, indice + 1);
}

const char* nomeTipo(Tipo tipo) {
    switch (tipo) {
        case FOGO: return "Fogo";
        case AGUA: return "Agua";
        case PLANTA: return "Planta";
        default: return "Desconhecido";
    }
}

float multiplicadorTipo(Tipo atacante, Tipo defensor) {
    if ((atacante == FOGO && defensor == PLANTA) ||
        (atacante == PLANTA && defensor == AGUA) ||
        (atacante == AGUA && defensor == FOGO)) {
        return 2.0f;
    }
    if ((atacante == FOGO && defensor == AGUA) ||
        (atacante == PLANTA && defensor == FOGO) ||
        (atacante == AGUA && defensor == PLANTA)) {
        return 0.5f;
    }
    return 1.0f;
}