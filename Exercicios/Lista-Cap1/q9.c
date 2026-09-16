#include <stdio.h> 
#include <stdlib.h> 
 
int main() 
{ 
    printf("%c%c%cPrimeiro programa", '\n', '\t', '\"'); 
    printf("%c", "\""); 
    system("PAUSE"); 
    return 0; 
} 

/*

        "Primeiro programa|Pressione qualquer tecla para continuar. . . 
    
    resposta:O especificador %c espera receber como argumento um valor inteiro representando o correspondente numérico na tabela ASCII de um caractere simples de 1 byte.
Primeiro printf: Os argumentos '\n' (ASCII 10), '\t' (ASCII 9) e '\"' (ASCII 34) são constantes de caractere individuais bem formatadas. 
O compilador converte os especificadores %c em quebra de linha, tabulação e aspas duplas, respectivamente, exibindo "Primeiro programa.
Segundo printf: O argumento passa a string "\"" (delimitada por aspas duplas), que em C representa um ponteiro de caractere (char * de string literal) contendo as aspas.
Passar um ponteiro para %c gera um comportamento indefinido (pois %c tentará ler o endereço da memória como o caractere em si), resultando em um aviso do compilador (type mismatch) e a impressão de lixo de memória na tela. Se o programa usasse '\"' (aspas simples), a saída final exibiria um caractere de aspas adicionais.

*/