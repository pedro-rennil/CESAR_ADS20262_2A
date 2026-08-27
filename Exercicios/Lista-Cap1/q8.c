#include <stdio.h> 
#include <stdlib.h> 
 
int main() 
{ 
    printf("\n\t\"Primeiro programa\""); 
    system("PAUSE"); 
    return 0; 
} 
/*
    saida gerada:
        "Primeiro programa"Pressione qualquer tecla para continuar. . . 

    Resposta:Primeira linha foi pulada devido ao '\n' após isso 
    foi acrescentado uma tabulação horizontal com o \t.
    devido ao 'system("PAUSE");' o sistema aguarda uma ação do usuario para encerrar a execução
*/