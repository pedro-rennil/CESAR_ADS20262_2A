#include <stdio.h>
#include <string.h>
#include "sprites.h"

static const char* arteDesconhecida =
    "   /\\_/\\\n"
    "  ( o.o )\n"
    "   > ^ <\n";

static const char* arteCharmander =
    "   _.--.\n"
    " .'  _  `.\n"
    "/   (_)   \\\n"
    "|  .---.  |\n"
    " \\ `---' /\n"
    "  `-----'\n";

static const char* arteBulbasaur =
    "    __\n"
    " .-'  `-.\n"
    "/  .--.  \\\n"
    "| (    ) |\n"
    " \\ '--' /\n"
    "  `----'\n";

void exibirArtePokemon(const char* nome) {
    const char* arte = arteDesconhecida;
    if (strcmp(nome, "Charmander") == 0) arte = arteCharmander;
    else if (strcmp(nome, "Bulbasaur") == 0) arte = arteBulbasaur;
    printf("%s\n", arte);
}