#include <stdio.h>

int meuStrlen(char s[]);
void inverte(char s[]);
void removeChar(char s[], int pos);

int meuStrlen(char s[]) {
    int n = 0;
    while (s[n] != '\0') n++;
    return n;
}

void inverte(char s[]) {
    int i = 0, j = meuStrlen(s) - 1;
    while (i < j) { char c = s[i]; s[i++] = s[j]; s[j--] = c; }
}

void removeChar(char s[], int pos) {
    int n = meuStrlen(s);
    if (pos < 0 || pos >= n) return;
    for (int i = pos; i < n; i++) s[i] = s[i + 1];
}

int main(void) {
    char s[100];
    int pos;
    fgets(s, sizeof s, stdin);
    if (s[meuStrlen(s) - 1] == '\n') s[meuStrlen(s) - 1] = '\0';
    printf("Tamanho: %d\n", meuStrlen(s));
    inverte(s); printf("Invertida: %s\n", s);
    scanf("%d", &pos); removeChar(s, pos);
    printf("Sem caractere: %s\n", s);
    return 0;
}

