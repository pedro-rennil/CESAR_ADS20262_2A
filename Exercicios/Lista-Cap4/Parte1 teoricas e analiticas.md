
---

## PARTE I: QUESTÕES TEÓRICAS E ANALÍTICAS

---

### Questão 01. Avaliação de Expressões Condicionais e Atribuição vs. Igualdade

#### a) Efeito de `if (x = 0)` vs. `if (x == 0)`
* **`if (x = 0)` (Atribuição):** O operador `=` atribui o valor `0` à variável `x`. O resultado da expressão de atribuição em C é o próprio valor atribuído (`0`). Em C, `0` é avaliado como **falso**, portanto o bloco do `if` **nunca será executado** (e `x` terá seu valor modificado para `0`).
* **`if (x == 0)` (Comparação):** O operador `==` compara o valor atual de `x` com `0`, sem alterar a variável. Se `x` for igual a `0`, a expressão avalia como verdadeira (`1`) e o bloco do `if` é executado.

#### b) Interpretação de valores numéricos no `if`
Na linguagem C (padrão ANSI C):
* **Falso:** Representado estritamente pelo valor numérico `0` (ou `0.0` para ponto flutuante, ou ponteiro `NULL`).
* **Verdadeiro:** Qualquer valor numérico diferente de zero (seja ele positivo ou negativo, ex: `1`, `-5`, `3.14`).

#### c) Análise da instrução `if (x = -5)`
* A expressão `(x = -5)` atribui o valor `-5` à variável `x`.
* O resultado da expressão de atribuição é `-5`.
* Como `-5` é um valor diferente de zero, ele é avaliado como **verdadeiro**.
* **Conclusão:** O bloco associado ao `if` **será executado**, pois em ANSI C qualquer valor não-nulo representa a condição verdadeira.

---

### Questão 02. Associação do Comando else e Aninhamento de Decisões

Código sob análise:
```c
int x = 15, y = 5;
if (x > 10)
    if (y > 10)
        printf("Opção A\n");
    else
        printf("Opção B\n");
```

#### a) Mensagem impressa no console e justificativa
* **Saída:** `Opção B`
* **Justificativa:** Pela regra sintática da linguagem C, o `else` se associa ao `if` imediatamente anterior mais próximo que ainda não possua um `else`. Logo, o `else` pertence a `if (y > 10)`. Como $x = 15 > 10$ (verdadeiro), o fluxo entra no bloco e avalia $y > 10$ ($5 > 10$, falso), caindo no `else` e imprimindo `"Opção B"`.

#### b) Regra oficial de associação do `else` (Dangling Else)
A cláusula `else` sempre se vincula ao **`if` mais próximo que não esteja emparelhado**, dentro do mesmo nível de escopo (bloco). A indentação é ignorada pelo compilador.

#### c) Reescrita com chaves `{}` para associar o `else` a $x \le 10$
```c
int x = 15, y = 5;

if (x > 10) {
    if (y > 10) {
        printf("Opção A\n");
    }
} else {
    printf("Opção B\n");
}
```

---

### Questão 03. Operador Condicional Ternário vs. Estrutura if-else

Código sob análise:
```c
media = (nota1 + nota2) / 2.0;
situacao = (media >= 7.0) ? 'A' : 'R';
```

#### a) Funcionamento e valor para `media = 6.8`
* O operador ternário avalia a condição `(media >= 7.0)`. Se verdadeira, retorna o valor da primeira expressão (`'A'`); se falsa, retorna o valor da segunda expressão (`'R'`).
* Para `media = 6.8`, a condição $6.8 \ge 7.0$ é **falsa**. Portanto, será retornado e armazenado em `situacao` o caractere `'R'`.

#### b) Reescrita com `if-else` tradicional
```c
media = (nota1 + nota2) / 2.0;
if (media >= 7.0) {
    situacao = 'A';
} else {
    situacao = 'R';
}
```

#### c) Limitações do operador ternário
O operador ternário é uma **expressão** projetada para produzir um único valor de retorno e atribuí-lo ou passá-lo como argumento. Ele **não substitui** qualquer estrutura `if-else` porque:
1. Não suporta naturalmente blocos complexos de múltiplas instruções ou comandos de controle (ex: loops, `return`, `break`), a menos que se use o operador vírgula, o que compromete severamente a legibilidade.
2. Seu uso deve ser restrito a decisões simples de atribuição ou avaliação de expressões pontuais.

---

### Questão 04. Seleção Múltipla com switch-case e Efeito Fall-Through

Código sob análise:
```c
#include <stdio.h>
int main() {
    int codigo = 2;
    switch (codigo) {
        case 1:
            printf("Bronze\n");
        case 2:
            printf("Prata\n");
        case 3:
            printf("Ouro\n");
            printf("Sem Medalha\n");
            break;
        default:
            break;
    }
    return 0;
}
```

#### a) Saída exata no terminal e justificativa
* **Saída:**
  ```text
  Prata
  Ouro
  Sem Medalha
  ```
* **Justificativa:** Como `codigo == 2`, a execução salta para o rótulo `case 2:`. Como não há instrução `break` ao final do `case 2:`, o fluxo continua executando sequencialmente os comandos do `case 3:` até encontrar o primeiro `break`.

#### b) Papel do `break` e nome do fenômeno
* **Papel do `break`:** Interrompe a execução do bloco `switch`, desviando o fluxo para fora do comando.
* **Fenômeno da omissão:** Chama-se **Fall-Through** (queda através).

#### c) Tipos permitidos no argumento do `switch`
* **Permitidos:** Apenas expressões que avaliem para **tipos inteiros** (`int`, `char`, `short`, `long`, `enum` e variações `unsigned`).
* **Não permitidos:** Tipos de ponto flutuante (`float`, `double`) e tipos compostos (estruturas, vetores/ponteiros).
* **Justificativa:** O `switch` foi concebido para saltos diretos baseados em tabelas de dispersão ou saltos indexados (jump tables), demandando igualdade exata e discreta de inteiros, algo inadequado para representação binária aproximada de números reais (IEEE 754).

---

### Questão 05. Avaliação de Curto-Circuito em Operadores Lógicos

Código inicial:
```c
int a = 0, b = 5, c = 10;
if (a != 0 && ++b > 5)
    c += 10;
else
    c -= 2;
printf("a = %d, b = %d, c = %d\n", a, b, c);
```

#### a) Saída exata do `printf`
* **Saída:** `a = 0, b = 5, c = 8`
* **Justificativa:** O operador `&&` realiza avaliação de curto-circuito. Como `a != 0` ($0 \ne 0$) é **falso**, o compilador não avalia o segundo operando (`++b > 5`). Logo, `b` não é incrementado e permanece `5`. O fluxo desvia para o `else`, executando $c = 10 - 2 = 8$.

#### b) Conceito de avaliação de curto-circuito
* **Operador `&&` (E lógico):** Se o primeiro operando for **falso** (`0`), o resultado geral é garantidamente falso; o segundo operando não é avaliado.
* **Operador `||` (OU lógico):** Se o primeiro operando for **verdadeiro** (não-zero), o resultado geral é garantidamente verdadeiro; o segundo operando não é avaliado.

#### c) Valores de `b` e `c` para `if (a == 0 || ++b > 5)`
* Na condição `(a == 0 || ++b > 5)`:
  1. A primeira expressão `a == 0` ($0 == 0$) é **verdadeira**.
  2. Devido ao curto-circuito do `||`, a expressão `++b > 5` **não é avaliada**.
  3. Logo, `b` continua valendo **`5`**.
  4. Como a condição do `if` foi verdadeira, executa-se $c += 10$, resultando em $c = 10 + 10 =$ **`20`**.

---

### Questão 06. Construções else-if e Análise Lógica de Intervalos

Código fornecido:
```c
int idade = 25;
if (idade >= 60)
    printf("Idoso\n");
if (idade >= 18)
    printf("Adulto\n");
if (idade >= 12)
    printf("Jovem\n");
else
    printf("Criança\n");
```

#### a) Saída para `idade = 65`
* **Saída:**
  ```text
  Idoso
  Adulto
  Jovem
  ```
* **Justificativa:** Tratam-se de comandos `if` independentes em sequência. Para $65$:
  * $65 \ge 60 \rightarrow$ Imprime `"Idoso"`
  * $65 \ge 18 \rightarrow$ Imprime `"Adulto"`
  * $65 \ge 12 \rightarrow$ Imprime `"Jovem"`
  * O `else` está atrelado apenas ao último `if`, portanto não é executado.

#### b) Diferença fundamental: `if`s independentes vs. cadeia `else-if`
* **`if`s independentes:** Todas as condições são testadas independentemente, podendo executar múltiplos blocos se mais de uma for verdadeira.
* **Cadeia `else-if`:** Garante **exclusão mútua**. Assim que a primeira condição verdadeira é encontrada, seu bloco correspondente é executado e toda a cadeia restante é ignorada.

#### c) Reescrita correta com `else-if`
```c
int idade = 25;

if (idade >= 60) {
    printf("Idoso\n");
} else if (idade >= 18) {
    printf("Adulto\n");
} else if (idade >= 12) {
    printf("Jovem\n");
} else {
    printf("Criança\n");
}
```

---

## PARTE II: QUESTÕES PRÁTICAS DE IMPLEMENTAÇÃO (CÓDIGO FONTE EM C)

---

### Questão 07. Raiz Quadrada ou Quadrado de um Número Real
```c
#include <stdio.h>
#include <math.h>

int main() {
    double numero, resultado;

    printf("Digite um número real: ");
    if (scanf("%lf", &numero) != 1) {
        printf("Entrada inválida.\n");
        return 1;
    }

    if (numero >= 0.0) {
        resultado = sqrt(numero);
        printf("Número positivo/nulo. Raiz quadrada: %.4f\n", resultado);
    } else {
        resultado = numero * numero;
        printf("Número negativo. Quadrado: %.4f\n", resultado);
    }

    return 0;
}
```

---

### Questão 08. Verificação de Ano Bissexto
```c
#include <stdio.h>

int main() {
    int ano;

    printf("Digite um ano (inteiro positivo): ");
    if (scanf("%d", &ano) != 1 || ano <= 0) {
        printf("Ano inválido.\n");
        return 1;
    }

    if ((ano % 400 == 0) || (ano % 4 == 0 && ano % 100 != 0)) {
        printf("O ano %d é BISSEXTO.\n", ano);
    } else {
        printf("O ano %d NÃO é bissexto.\n", ano);
    }

    return 0;
}
```

---

### Questão 09. Cálculo de Média Ponderada e Situação Acadêmica
```c
#include <stdio.h>

int main() {
    float lab, semestral, exame, media;

    printf("Digite a nota do Trabalho de Laboratório (peso 2): ");
    scanf("%f", &lab);
    printf("Digite a nota da Avaliação Semestral (peso 3): ");
    scanf("%f", &semestral);
    printf("Digite a nota do Exame Final (peso 5): ");
    scanf("%f", &exame);

    media = (lab * 2.0f + semestral * 3.0f + exame * 5.0f) / 10.0f;

    printf("Média Ponderada: %.2f\n", media);
    if (media >= 5.0f) {
        printf("Situação: Aprovado\n");
    } else if (media >= 3.0f) {
        printf("Situação: Em Recuperação\n");
    } else {
        printf("Situação: Reprovado\n");
    }

    return 0;
}
```

---

### Questão 10. Análise de Paridade e Sinal de Inteiros
```c
#include <stdio.h>

int main() {
    int numero;

    printf("Digite um número inteiro: ");
    scanf("%d", &numero);

    /* Análise de Paridade */
    if (numero % 2 == 0) {
        printf("O número %d é PAR.\n", numero);
    } else {
        printf("O número %d é ÍMPAR.\n", numero);
    }

    /* Análise de Sinal */
    if (numero > 0) {
        printf("Sinal: POSITIVO\n");
    } else if (numero < 0) {
        printf("Sinal: NEGATIVO\n");
    } else {
        printf("Sinal: ZERO (NULO)\n");
    }

    return 0;
}
```

---

### Questão 11. Ordenação Crescente de Três Valores Numéricos
```c
#include <stdio.h>

int main() {
    int a, b, c, temp;

    printf("Digite três números inteiros separados por espaço: ");
    scanf("%d %d %d", &a, &b, &c);

    /* Ordenação por permutações simples sem o uso de vetores */
    if (a > b) {
        temp = a; a = b; b = temp;
    }
    if (a > c) {
        temp = a; a = c; c = temp;
    }
    if (b > c) {
        temp = b; b = c; c = temp;
    }

    printf("Valores em ordem crescente: %d, %d, %d\n", a, b, c);

    return 0;
}
```

---

### Questão 12. Dia da Semana com Comando switch-case
```c
#include <stdio.h>

int main() {
    int dia;

    printf("Digite um número de 1 a 7: ");
    scanf("%d", &dia);

    switch (dia) {
        case 1:
            printf("Domingo\n");
            break;
        case 2:
            printf("Segunda-feira\n");
            break;
        case 3:
            printf("Terça-feira\n");
            break;
        case 4:
            printf("Quarta-feira\n");
            break;
        case 5:
            printf("Quinta-feira\n");
            break;
        case 6:
            printf("Sexta-feira\n");
            break;
        case 7:
            printf("Sábado\n");
            break;
        default:
            printf("Erro: Opção Inválida!\n");
            break;
    }

    return 0;
}
```

---

### Questão 13. Calculadora Aritmética e Científica com Menu switch
```c
#include <stdio.h>
#include <math.h>

int main() {
    char operacao;
    double op1, op2, resultado;

    printf("Selecione a operação (+, -, *, /, ^): ");
    scanf(" %c", &operacao);

    printf("Digite o primeiro operando: ");
    scanf("%lf", &op1);
    printf("Digite o segundo operando: ");
    scanf("%lf", &op2);

    switch (operacao) {
        case '+':
            resultado = op1 + op2;
            printf("Resultado: %.4f\n", resultado);
            break;
        case '-':
            resultado = op1 - op2;
            printf("Resultado: %.4f\n", resultado);
            break;
        case '*':
            resultado = op1 * op2;
            printf("Resultado: %.4f\n", resultado);
            break;
        case '/':
            if (op2 == 0.0) {
                printf("Erro: Divisão por zero não é permitida!\n");
            } else {
                resultado = op1 / op2;
                printf("Resultado: %.4f\n", resultado);
            }
            break;
        case '^':
            resultado = pow(op1, op2);
            printf("Resultado: %.4f\n", resultado);
            break;
        default:
            printf("Erro: Operação inválida!\n");
            break;
    }

    return 0;
}
```

---

### Questão 14. Matriz de Classificação de Conceito por Nota e Faltas
```c
#include <stdio.h>

int main() {
    float nota;
    int faltas;
    char conceito;

    printf("Digite a nota final (0.0 a 10.0): ");
    scanf("%f", &nota);
    printf("Digite a quantidade de faltas: ");
    scanf("%d", &faltas);

    if (nota < 0.0f || nota > 10.0f || faltas < 0) {
        printf("Dados de entrada inválidos.\n");
        return 1;
    }

    if (nota >= 9.0f) {
        conceito = (faltas <= 20) ? 'A' : 'B';
    } else if (nota >= 7.5f) {
        conceito = (faltas <= 20) ? 'B' : 'C';
    } else if (nota >= 5.0f) {
        conceito = (faltas <= 20) ? 'C' : 'D';
    } else if (nota >= 4.0f) {
        conceito = (faltas <= 20) ? 'D' : 'E';
    } else {
        conceito = 'E';
    }

    printf("Conceito atribuído: %c\n", conceito);
    return 0;
}
```

---

### Questão 15. Verificação de Elegibilidade para Aposentadoria
```c
#include <stdio.h>

int main() {
    int idade, tempo_servico;

    printf("Digite a idade do trabalhador: ");
    scanf("%d", &idade);
    printf("Digite o tempo de serviço (em anos): ");
    scanf("%d", &tempo_servico);

    if (idade >= 65 || tempo_servico >= 30 || (idade >= 60 && tempo_servico >= 25)) {
        printf("Situação: Pode se aposentar.\n");
    } else {
        printf("Situação: Não pode se aposentar.\n");
    }

    return 0;
}
```

---

### Questão 16. Classificação de Eficiência de Consumo de Combustível
```c
#include <stdio.h>

int main() {
    float distancia, litros, consumo;

    printf("Digite a distância percorrida (km): ");
    scanf("%f", &distancia);
    printf("Digite a quantidade de combustível consumida (litros): ");
    scanf("%f", &litros);

    if (litros <= 0.0f) {
        printf("Erro: Quantidade de combustível inválida.\n");
        return 1;
    }

    consumo = distancia / litros;
    printf("Consumo aferido: %.2f km/l\n", consumo);

    if (consumo < 8.0f) {
        printf("Venda o carro!\n");
    } else if (consumo <= 14.0f) {
        printf("Econômico!\n");
    } else {
        printf("Super econômico!\n");
    }

    return 0;
}
```

---

### Questão 17. Cálculo de Pagamento e Comissão de Vendas
```c
#include <stdio.h>

int main() {
    float valor_total, valor_final, comissao;
    int opcao;

    printf("Digite o valor total da compra: R$ ");
    scanf("%f", &valor_total);
    printf("Escolha a opção (1 = À Vista [10%% desc], 2 = 3x Sem Juros): ");
    scanf("%d", &opcao);

    if (opcao == 1) {
        valor_final = valor_total * 0.90f;
        comissao = valor_final * 0.05f;
        printf("Total a pagar (com 10%% de desconto): R$ %.2f\n", valor_final);
        printf("Comissão do vendedor (5%% sobre valor com desconto): R$ %.2f\n", comissao);
    } else if (opcao == 2) {
        float parcela = valor_total / 3.0f;
        comissao = valor_total * 0.05f;
        printf("Valor de cada parcela (3x sem juros): R$ %.2f\n", parcela);
        printf("Total a pagar: R$ %.2f\n", valor_total);
        printf("Comissão do vendedor (5%% sobre total): R$ %.2f\n", comissao);
    } else {
        printf("Erro: Opção de pagamento inválida!\n");
    }

    return 0;
}
```

---

### Questão 18. Conversor Multidirecional de Escalas Termométricas
```c
#include <stdio.h>

int main() {
    int opcao;
    double temp_in, temp_out;

    printf("Menu de Conversão de Temperatura:\n");
    printf("1. Celsius para Fahrenheit\n");
    printf("2. Celsius para Kelvin\n");
    printf("3. Fahrenheit para Celsius\n");
    printf("4. Kelvin para Celsius\n");
    printf("Opção: ");
    scanf("%d", &opcao);

    switch (opcao) {
        case 1:
            printf("Digite a temperatura em Celsius: ");
            scanf("%lf", &temp_in);
            temp_out = temp_in * 1.8 + 32.0;
            printf("Temperatura convertida: %.2f °F\n", temp_out);
            break;
        case 2:
            printf("Digite a temperatura em Celsius: ");
            scanf("%lf", &temp_in);
            temp_out = temp_in + 273.15;
            printf("Temperatura convertida: %.2f K\n", temp_out);
            break;
        case 3:
            printf("Digite a temperatura em Fahrenheit: ");
            scanf("%lf", &temp_in);
            temp_out = (temp_in - 32.0) / 1.8;
            printf("Temperatura convertida: %.2f °C\n", temp_out);
            break;
        case 4:
            printf("Digite a temperatura em Kelvin: ");
            scanf("%lf", &temp_in);
            temp_out = temp_in - 273.15;
            printf("Temperatura convertida: %.2f °C\n", temp_out);
            break;
        default:
            printf("Erro: Opção inválida!\n");
            break;
    }

    return 0;
}
```

---

### Questão 19. Validação de Condição de Existência e Tipo de Triângulo
```c
#include <stdio.h>

int main() {
    float a, b, c;

    printf("Digite os três lados do triângulo (A B C): ");
    scanf("%f %f %f", &a, &b, &c);

    /* Condição de Existência */
    if (a < b + c && b < a + c && c < a + b) {
        if (a == b && b == c) {
            printf("Triângulo Equilátero\n");
        } else if (a == b || a == c || b == c) {
            printf("Triângulo Isósceles\n");
        } else {
            printf("Triângulo Escaleno\n");
        }
    } else {
        printf("Erro: Os lados fornecidos não formam um triângulo!\n");
    }

    return 0;
}
```

---

### Questão 20. Resolução da Equação do Segundo Grau (Fórmula de Bhaskara)
```c
#include <stdio.h>
#include <math.h>

int main() {
    double a, b, c, delta, x1, x2;

    printf("Digite os coeficientes a, b e c: ");
    scanf("%lf %lf %lf", &a, &b, &c);

    if (a == 0.0) {
        printf("Erro: 'a' não pode ser zero (não é equação de 2º grau).\n");
        return 1;
    }

    delta = (b * b) - (4.0 * a * c);

    if (delta < 0.0) {
        printf("A equação não possui raízes reais.\n");
    } else if (delta == 0.0) {
        x1 = -b / (2.0 * a);
        printf("Raiz única real: x = %.4f\n", x1);
    } else {
        x1 = (-b + sqrt(delta)) / (2.0 * a);
        x2 = (-b - sqrt(delta)) / (2.0 * a);
        printf("Duas raízes reais distintas: x1 = %.4f e x2 = %.4f\n", x1, x2);
    }

    return 0;
}
```

---

### Questão 21. Cálculo de Reajuste Salarial com Base em Categorias
```c
#include <stdio.h>

int main() {
    float salario, aumento, novo_salario;
    int cargo;

    printf("Digite o salário atual: R$ ");
    scanf("%f", &salario);
    printf("Digite o código do cargo (1 = Técnico, 2 = Gerente, 3 = Demais Cargos): ");
    scanf("%d", &cargo);

    switch (cargo) {
        case 1:
            aumento = (salario <= 3000.0f) ? (salario * 0.15f) : (salario * 0.10f);
            break;
        case 2:
            aumento = (salario <= 5000.0f) ? (salario * 0.10f) : (salario * 0.05f);
            break;
        case 3:
            aumento = salario * 0.08f;
            break;
        default:
            printf("Erro: Código de cargo inválido!\n");
            return 1;
    }

    novo_salario = salario + aumento;
    printf("Valor do aumento: R$ %.2f\n", aumento);
    printf("Novo salário reajustado: R$ %.2f\n", novo_salario);

    return 0;
}
```

---

### Questão 22. Cálculo de Impostos Estaduais sobre Produtos
```c
#include <stdio.h>

int main() {
    float valor, valor_final;
    int estado;

    printf("Digite o valor do produto: R$ ");
    scanf("%f", &valor);
    printf("Digite o código do estado (1 = MG, 2 = SP, 3 = RJ, 4 = MS): ");
    scanf("%d", &estado);

    switch (estado) {
        case 1: /* MG: 7% */
            valor_final = valor * 1.07f;
            printf("Preço final com imposto (MG - 7%%): R$ %.2f\n", valor_final);
            break;
        case 2: /* SP: 12% */
            valor_final = valor * 1.12f;
            printf("Preço final com imposto (SP - 12%%): R$ %.2f\n", valor_final);
            break;
        case 3: /* RJ: 15% */
            valor_final = valor * 1.15f;
            printf("Preço final com imposto (RJ - 15%%): R$ %.2f\n", valor_final);
            break;
        case 4: /* MS: 8% */
            valor_final = valor * 1.08f;
            printf("Preço final com imposto (MS - 8%%): R$ %.2f\n", valor_final);
            break;
        default:
            printf("Erro: Código de estado inválido!\n");
            break;
    }

    return 0;
}
```

---

### Questão 23. Impressão de Data Por Extenso com switch-case
```c
#include <stdio.h>

int main() {
    int dia, mes, ano;

    printf("Digite a data (Dia Mês Ano, ex: 25 12 2026): ");
    scanf("%d %d %d", &dia, &mes, &ano);

    if (mes < 1 || mes > 12 || dia < 1 || dia > 31) {
        printf("Erro: Data informada é inválida!\n");
        return 1;
    }

    printf("%02d de ", dia);

    switch (mes) {
        case 1:  printf("janeiro"); break;
        case 2:  printf("fevereiro"); break;
        case 3:  printf("março"); break;
        case 4:  printf("abril"); break;
        case 5:  printf("maio"); break;
        case 6:  printf("junho"); break;
        case 7:  printf("julho"); break;
        case 8:  printf("agosto"); break;
        case 9:  printf("setembro"); break;
        case 10: printf("outubro"); break;
        case 11: printf("novembro"); break;
        case 12: printf("dezembro"); break;
    }

    printf(" de %d\n", ano);
    return 0;
}
```

---

### Questão 24. Classificação de Triângulos quanto aos Ângulos Internos
```c
#include <stdio.h>

int main() {
    int ang1, ang2, ang3;

    printf("Digite os três ângulos internos (em graus inteiros): ");
    scanf("%d %d %d", &ang1, &ang2, &ang3);

    if (ang1 <= 0 || ang2 <= 0 || ang3 <= 0 || (ang1 + ang2 + ang3 != 180)) {
        printf("Erro: Os valores não formam um triângulo válido!\n");
        return 1;
    }

    if (ang1 == 90 || ang2 == 90 || ang3 == 90) {
        printf("Classificação: Triângulo Retângulo\n");
    } else if (ang1 > 90 || ang2 > 90 || ang3 > 90) {
        printf("Classificação: Triângulo Obtusângulo\n");
    } else {
        printf("Classificação: Triângulo Acutângulo\n");
    }

    return 0;
}
```

---

### Questão 25. Decomposição de Troco na Menor Quantidade de Cédulas
```c
#include <stdio.h>

int main() {
    int total_pagar, valor_pago, troco;
    int n100, n50, n20, n10, n5, n2;

    printf("Digite o valor total da compra: R$ ");
    scanf("%d", &total_pagar);
    printf("Digite o valor entregue pelo cliente: R$ ");
    scanf("%d", &valor_pago);

    if (valor_pago < total_pagar) {
        printf("Erro: Valor entregue é insuficiente!\n");
        return 1;
    }

    troco = valor_pago - total_pagar;
    printf("Troco devido: R$ %d\n", troco);

    n100 = troco / 100;
    troco %= 100;

    n50 = troco / 50;
    troco %= 50;

    n20 = troco / 20;
    troco %= 20;

    n10 = troco / 10;
    troco %= 10;

    n5 = troco / 5;
    troco %= 5;

    n2 = troco / 2;
    troco %= 2;

    printf("Cédulas distribuídas:\n");
    if (n100 > 0) printf("- %d cédula(s) de R$ 100\n", n100);
    if (n50 > 0)  printf("- %d cédula(s) de R$ 50\n", n50);
    if (n20 > 0)  printf("- %d cédula(s) de R$ 20\n", n20);
    if (n10 > 0)  printf("- %d cédula(s) de R$ 10\n", n10);
    if (n5 > 0)   printf("- %d cédula(s) de R$ 5\n", n5);
    if (n2 > 0)   printf("- %d cédula(s) de R$ 2\n", n2);
    if (troco > 0) printf("- Restante não decomponível em cédulas: R$ %d (moeda de R$ 1)\n", troco);

    return 0;
}
```

---

### Questão 26. Quantidade de Dias de um Mês e Validação de Fevereiro Bissexto
```c
#include <stdio.h>

int main() {
    int mes, ano, bissexto;

    printf("Digite o mês (1-12): ");
    scanf("%d", &mes);
    printf("Digite o ano: ");
    scanf("%d", &ano);

    if (mes < 1 || mes > 12) {
        printf("Mês inválido!\n");
        return 1;
    }

    bissexto = ((ano % 400 == 0) || (ano % 4 == 0 && ano % 100 != 0));

    switch (mes) {
        case 1:  printf("Janeiro possui 31 dias.\n"); break;
        case 2:
            if (bissexto) {
                printf("Fevereiro possui 29 dias (Ano Bissexto).\n");
            } else {
                printf("Fevereiro possui 28 dias.\n");
            }
            break;
        case 3:  printf("Março possui 31 dias.\n"); break;
        case 4:  printf("Abril possui 30 dias.\n"); break;
        case 5:  printf("Maio possui 31 dias.\n"); break;
        case 6:  printf("Junho possui 30 dias.\n"); break;
        case 7:  printf("Julho possui 31 dias.\n"); break;
        case 8:  printf("Agosto possui 31 dias.\n"); break;
        case 9:  printf("Setembro possui 30 dias.\n"); break;
        case 10: printf("Outubro possui 31 dias.\n"); break;
        case 11: printf("Novembro possui 30 dias.\n"); break;
        case 12: printf("Dezembro possui 31 dias.\n"); break;
    }

    return 0;
}
```

---

### Questão 27. Tarifador de Estacionamento com Faixas Progressivas
```c
#include <stdio.h>

int main() {
    int horas;
    float total = 0.0f;

    printf("Digite o tempo de permanência (horas inteiras): ");
    scanf("%d", &horas);

    if (horas <= 0) {
        printf("Tempo inválido!\n");
        return 1;
    }

    if (horas <= 2) {
        total = horas * 2.00f;
    } else if (horas <= 4) {
        total = (2 * 2.00f) + ((horas - 2) * 2.50f);
    } else {
        total = (2 * 2.00f) + (2 * 2.50f) + ((horas - 4) * 3.00f);
    }

    printf("Tempo total de permanência: %d hora(s)\n", horas);
    printf("Valor final cobrado: R$ %.2f\n", total);

    return 0;
}
```

---

### Questão 28. Sistema de Atendimento Automático Bancário (SAC)
```c
#include <stdio.h>

int main() {
    int opcao;

    printf("=================================\n");
    printf("    SISTEMA DE ATENDIMENTO SAC   \n");
    printf("=================================\n");
    printf("1 - Consultar Saldo\n");
    printf("2 - Efetuar Extrato\n");
    printf("3 - Fazer Transferência\n");
    printf("4 - Falar com Atendente\n");
    printf("Escolha uma opção: ");
    scanf("%d", &opcao);

    switch (opcao) {
        case 1:
            printf("Direcionando para o menu de Saldo...\n");
            break;
        case 2:
            printf("Direcionando para a emissão de Extrato...\n");
            break;
        case 3:
            printf("Direcionando para a área de Transferências (PIX/TED)...\n");
            break;
        case 4:
            printf("Aguarde na linha, transferindo para um atendente humano...\n");
            break;
        default:
            printf("Opção inválida! Por favor, tente novamente.\n");
            break;
    }

    return 0;
}
```