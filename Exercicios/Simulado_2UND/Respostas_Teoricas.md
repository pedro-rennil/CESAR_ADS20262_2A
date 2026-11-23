# Respostas teoricas - Simulado Cap. 4, 5, 7 e 8

## Questao 01

O `else` fica associado ao `if (b > 5)`. Como `b` vale 3, a condicao e falsa e
o `else` executa `printf("Y\n")`. Portanto, a saida correta e:

```text
Y
Z
```

**Resposta: b) Y e, em seguida, Z.**

## Questao 02

O `switch` entra no `case 2` e, como nao ha `break`, continua no `case 3`. O
`case 3` soma 3 e executa `break`; assim, `t = 2 + 3 = 5`.

**Resposta: c) 5.**

## Questao 05

**Resposta: d) 3 7.**

A funcao recebe copias dos valores. A troca ocorre somente nos parametros locais,
sem alterar `x` e `y` na `main`.

## Questao 06

**Resposta: a) 10.**

```text
f(4) = 4 + f(3)
     = 4 + 3 + f(2)
     = 4 + 3 + 2 + f(1)
     = 4 + 3 + 2 + 1
     = 10
```

## Questao 10

`m[0][2] + m[1][1] + m[2][0] = 3 + 5 + 7 = 15`.

**Resposta: c) 15.**

## Questao 11

**Resposta: b) 9 PROVA2026.**

`strcat` concatena `2026` ao final de `PROVA`, formando uma string com 9
caracteres, sem contar o terminador nulo `'\0'`.

## Questao 16

**Resposta: c) 1 9.**

Estruturas podem ser atribuídas diretamente. `b = a` copia os valores, mas a
alteracao posterior de `b.x` nao altera `a.x`.

## Questao 17

**Resposta: d) 8.**

Uma `union` ocupa o espaco do maior membro. Entre `char[8]`, `int` de 4 bytes e
`double` de 8 bytes, o maior tamanho e 8 bytes.
