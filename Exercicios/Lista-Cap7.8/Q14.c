#include <stdio.h>
#include <string.h>

int ehPalindromo(char s[]);

int ehPalindromo(char s[]) {
    size_t i = 0, j = strlen(s);
    if (j > 0) j--;
    while (i < j) if (s[i++] != s[j--]) return 0;
    return 1;
}

int main(void) {
    char s[100];
    scanf("%99s", s);
    printf("%s\n", ehPalindromo(s) ? "E palindromo." : "Nao e palindromo.");
    return 0;
}

