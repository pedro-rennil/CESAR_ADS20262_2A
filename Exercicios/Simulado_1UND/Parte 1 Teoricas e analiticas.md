* #### Questão 1
> Resposta: C

* #### Questão 2
~~~

#include <stdio.h>
#include <stdlib.h>; //Presença indevida do ';' causa erro
int Main() //Palavra reservada 'Main' deveria estar em minusculo 'main'
{
    int idade = 20;
    printf( A idade do aluno eh: %d anos.. , idade); //Falta de aspas "" para a string ser exibida
    cout << endl; //Sintaxe utilizada em C++, não funciona em C
    system("PAUSE");
    return 0;
}
~~~

* #### Questão 3
>Valores ao final: A = 56, B = 45, C = 13 e D = 10
~~~
a += b + c; // Valor final de a = 11
b *= c = d - 2; // Valores finais de b = 32 e c = 8 
d %= a + 3; // Valor final de d = 10
a += b += c += 5; // Valores finais de a = 56 b = 45 e c = 13
~~~

* #### Questão 4
~~~
a) i < j + 2 => Resultado: 1
b) 2 * i - 5 <= j - 4 => Resultado: 1
c) !k && (x + y >= 7.5) => Resultado: 1
d) !(i == j) || (y / x == 2.0) => Resultado: 1
e) i == 2 && j == 4 || k == 0 => Resultado: 1
~~~

* #### Questão 5

>Resposta: A) A diferença essencial entre o While e o Do While seria que o While realiza a checagem da condição de para antes de iniciar, enquanto o Do While realiza a iteração e somente após o fim da execução verifica a condição de parada.
>B) A estrutura do For permite maior controle e legibilidade das iterações. Sendo adequado para uso em que se tem uma condição de parada pré-determinada.
>C) Não dá erro, o "While(condição);" representa um corpo vazio visando um laço infinito, caso a condição seja verdadeira

* #### Questão 6

>Respostas: A) Como a variavel soma foi declarada dentro do 'For', ela existe apenas no escopo desta estrutura
>B) • i=1: Impar ⇒ soma += 1 (soma local = 1)
• i=2, 4, 6: Pares ⇒ O comando continue ignora o restante do corpo e salta para o próximo incremento.
• i=3: Impar ⇒ soma += 3 (soma local = 3)
• i=5: Impar ⇒ soma += 5 (soma local = 5)
• i=7: O comando break encerra o laço imediatamente.
>C) Declarando soma fora do laço, os valores somados serão os ímpares (1 + 3 + 5). A saída final será: Soma = 9.