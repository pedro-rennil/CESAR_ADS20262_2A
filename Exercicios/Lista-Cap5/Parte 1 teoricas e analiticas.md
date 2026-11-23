# Parte I — Questões teóricas e analíticas

## Questão 1

**a)** O protótipo é `float celsius(float);`, escrito antes da `main()`. Ele informa ao compilador o nome da função, seu tipo de retorno e o tipo do parâmetro. A chamada é `c = celsius(f);`, dentro da `main()`, quando a função é executada com o valor de `f`. A definição é o bloco `float celsius(float fahr) { ... }`, que contém os comandos que realizam a conversão e retornam o resultado.

**b)** O protótipo permite que o compilador conheça a assinatura da função antes de encontrar uma chamada. Assim, ele pode verificar o número e os tipos dos argumentos e o tipo do retorno. Se o protótipo fosse omitido e a definição viesse depois da `main()`, a chamada poderia gerar diagnóstico de função não declarada e o compilador não teria a mesma informação para verificar corretamente os parâmetros; em C moderno isso deve ser tratado como erro.

**c)** `celsius()` é uma função do tipo `float`, pois seu valor retornado é `float`. Os parâmetros representam dados de entrada e não determinam o tipo da função. Uma função pode receber parâmetros de tipos variados, mas seu tipo é definido pelo tipo do valor que entrega com `return` — ou por `void` quando não entrega valor.

## Questão 2

**a)** Usando apenas o comando `return`, uma função devolve um único valor. O programador tentou devolver simultaneamente `soma` e `media` com `return soma, media;`. Porém, a vírgula nesse contexto é o operador vírgula: `soma` é avaliada, mas o valor da expressão inteira é o último, isto é, `media`. Portanto, somente a média é retornada.

**b)** O `return;` encerra imediatamente a execução de `imprime_mensagem()` e retorna para o ponto de chamada sem valor. Ele é útil para sair antes do final, como no caso de erro. Não é obrigatório no final de uma função `void`: ao alcançar a chave final, a função termina naturalmente.

**c)**

```c
int calcularMedia(int a, int b, int c) {
    return (a + b + c) / 3;
}

int calcularSoma(int a, int b, int c) {
    return a + b + c;
}
```

São necessárias duas funções porque cada uso do `return` entrega apenas um valor. Outra alternativa seria retornar uma estrutura ou usar parâmetros por endereço, mas isso já seria uma forma diferente de transportar os dois resultados.

## Questão 3

**a)**

- `void exibe_mensagem(char* msg);`: recebe um parâmetro `char*` e não retorna valor.
- `int obter_codigo(void);`: não recebe parâmetros e retorna um `int`. O `void` entre parênteses indica ausência explícita de parâmetros.
- `void limpar_tela(void);`: não recebe parâmetros e não retorna valor.

**b)** Uma função com retorno produz um valor que pode ser atribuído, comparado ou usado em outra expressão, como `codigo = obter_codigo();`. Uma função `void` executa uma ação sem produzir valor, como exibir uma mensagem ou limpar a tela. Deve-se escolher a primeira quando o resultado será usado pelo programa e a segunda quando a responsabilidade é apenas executar um procedimento.

**c)** Não. `limpar_tela()` tem tipo de retorno `void`, portanto não existe valor para atribuir a `x`. A chamada isolada `limpar_tela();` é válida, mas `x = limpar_tela();` não é.

## Questão 4

**a)** O caso base é `n == 0`, que retorna `1`. O passo recursivo é `(long)n * fatorial(n - 1)`, que reduz o problema e chama a própria função. Sem o caso base, as chamadas continuariam indefinidamente até esgotar a pilha de execução, causando falha no programa.

**b)**

```text
Empilhamento:
fatorial(4) = 4 * fatorial(3)
fatorial(3) = 3 * fatorial(2)
fatorial(2) = 2 * fatorial(1)
fatorial(1) = 1 * fatorial(0)
fatorial(0) = 1              <- caso base

Desempilhamento:
fatorial(1) = 1 * 1 = 1
fatorial(2) = 2 * 1 = 2
fatorial(3) = 3 * 2 = 6
fatorial(4) = 4 * 6 = 24
```

**c)** Cada chamada cria um novo registro na pilha, contendo seus parâmetros, variáveis locais e o endereço para onde deve retornar. Esses registros permanecem empilhados enquanto a chamada aguarda o resultado da chamada seguinte. Quando o caso base é alcançado, os registros são removidos na ordem inversa. Sem uma condição que interrompa a recursão, novos registros continuam sendo criados até ocorrer estouro de pilha.

## Questão 5

**a)** O primeiro `printf` imprime `25`, pois `SQR(2+3)` é expandida como `((2+3)*(2+3))`. O segundo imprime `7`, pois `DOBRO(2+3)` é expandida como `2+3*2`; pela precedência, a multiplicação ocorre antes da soma. `SQR` protege tanto o argumento quanto a expressão completa com parênteses, enquanto `DOBRO` não protege o argumento.

**b)** `#define` é uma diretiva de pré-processamento; sua instrução termina no fim da linha, e não é uma instrução C que precise de ponto e vírgula. Identificadores em maiúsculas são uma convenção para destacar macros e constantes de substituições comuns, diferenciando-as de variáveis e funções.

**c)** `#define PRN (n) printf("%d", n)` está incorreto porque `(n)` é interpretado como o nome da macro sem uma lista de parâmetros. A forma correta é:

```c
#define PRN(n) printf("%d", (n))
```

Uma macro é expandida textualmente antes da compilação e pode avaliar um argumento mais de uma vez. Uma função possui parâmetros avaliados na chamada, tem tipo verificado pelo compilador e executa seu corpo uma vez por chamada.

## Questão 6

**a)** `#include <stdio.h>` procura o cabeçalho nas pastas padrão do compilador, sendo a forma usual para bibliotecas do sistema. `#include "areas.h"` procura primeiro no diretório do projeto e depois nas pastas configuradas, sendo apropriado para um cabeçalho criado pelo próprio programador.

**b)** `#undef SOMA` remove a definição da macro `SOMA` a partir daquele ponto do pré-processamento. A forma correta usa somente o identificador: `#undef SOMA`. `#undef SOMA(x,y)` está incorreta porque `#undef` não recebe uma lista de parâmetros, apenas o nome da macro.

**c)** Como `DEBUG` não foi definido, será compilada a alternativa do `#else`, e a execução imprimirá `Modo normal`. A escolha é feita no pré-processamento, antes da compilação. As diretivas controlam quais trechos entram no código-fonte compilado e não são instruções de execução, por isso não aparecem no executável final.
