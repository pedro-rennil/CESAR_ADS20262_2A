* #### Questão 1
> A) o While verifica a condição de parada antes de dar inicio ao loop, com um minimo de execuções de '0'; enquando o do-while executa o loop antes de verificar com um minímo de execuções de '1'
> B) 'for': iterações contadas/conhecidas. 'while': repetição baseada em eventos/condições de parada imprevisíveis. 'do-while': menus e validações de entrada onde o bloco precisa rodar ao menos uma vez.


* #### Questão 2
> A) A variável 'soma' foi declarada DENTRO das chaves do laço 'for'. Na Linguagem C, o escopo de bloco faz com que a variável só exista dentro desse bloco. Fora do laço, no 'printf', a variável 'soma' é inacessível, gerando o erro de compilação'error: soma undeclared'.
> B) Se 'soma' fosse inicializada com 'int soma = 0;' dentro do laço, a cada iteração a variável seria destruída e reinicializada em zero, acumulando apenas o quadrado do elemento atual (1, 4, 9, ..., 81) em vez de manter o acumulado acumulativo.
> C)
~~~
#include <stdio.h>
#include <stdlib.h>
int main() {
int i;
int soma = 0; // Declaração no escopo da função main()
for (i = 1; i < 10; i++) {
soma += i * i;
}
printf("Soma final = %d\n", soma); // Imprime 285
system("PAUSE");
return 0;
}
~~~

* #### Questão 3
>A)Saída do Trecho A: 36 18 9 4 2 1
>B) 'ch + 1' avança para o próximo caractere na tabela ASCII (ex: 'A' vira 'B'). Os parênteses são obrigatórios porque o operador de comparação '!=' tem precedência maior que o de atribuição '='.
>C) Usa-se a instrução 'break;' dentro de uma condição 'if' no corpo do laço, ou a função 'exit(0); ' / 'return 0;'.

* #### Questão 4

>A) O 'break' interrompe imediatamente a execução do laço atual e transfere o controle do programa para a primeira instrução após o bloco do laço.
>B) O 'continue' interrompe a iteração atual, salta as instruções restantes do corpo do laço e vai direto para a expressão de INCREMENTO do 'for'.
>C) O 'break' interrompe APENAS o laço mais interno em que está contido diretamente.

* #### Questão 5

~~~
// a) Executa exatamente 5 iterações (i = 0, 1, 2, 3, 4).
// b) Saída exata:
i = 0, j = 10 | soma = 10
i = 1, j = 9 | soma = 10
i = 2, j = 8 | soma = 10
i = 3, j = 7 | soma = 10
i = 4, j = 6 | soma = 10
// c) Reescrita com laço while:
int i = 0, j = 10;
while (i < j) {
    printf("i = %d, j = %d | soma = %d\n", i, j, i + j);
    i++;
    j--;
}
~~~

* #### Questão 6

>A) Valor final de x = 6
>B)1. O incremento pós-fixado 'x++' utiliza o valor atual de 'x' na comparação e incrementa 'x' imediatamente em seguida. 2. Passo a passo do laço: - Teste 1: x=0 (0 < 5 Verdadeiro) -> x vira 1 - Teste 2: x=1 (1 < 5 Verdadeiro) -> x vira 2 - Teste 3: x=2 (2 < 5 Verdadeiro) -> x vira 3 - Teste 4: x=3 (3 < 5 Verdadeiro) -> x vira 4 - Teste 5: x=4 (4 < 5 Verdadeiro) -> x vira 5 - Teste 6: x=5 (5 < 5 FALSO) -> x vira 6! O teste falha e o laço encerra, mas 'x' foi incrementado para 6.

>C) Reescrita explícita equivalente:

~~~
int x = 0;
while (x < 5) {
    x++;
}
x++; // Incremento do teste final que falhou
printf("Valor final de x = %d\n", x);
~~~