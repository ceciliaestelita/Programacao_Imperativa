#include <stdio.h>
int m, n;
char espaco[100][100];

void colocar(int i, int j, char c) {
    if (i < 0 || i >= m || j < 0 || j >= n) return;
    if (espaco[i][j] == 'P') return;
    if (espaco[i][j] == '+' && c == 'x') return;  // + tem prioridade sobre x
    espaco[i][j] = c;
}

void enfeitar(int i, int j) {
    colocar(i - 1, j, '+');
    colocar(i + 1, j, '+');
    colocar(i, j - 1, '+');
    colocar(i, j + 1, '+');
    colocar(i - 1, j - 1, 'x');
    colocar(i - 1, j + 1, 'x');
    colocar(i + 1, j - 1, 'x');
    colocar(i + 1, j + 1, 'x');
}

int main() {
    scanf("%d %d", &m, &n);
    for (int i = 0; i < m; i++)
        scanf("%s", espaco[i]);
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            if (espaco[i][j] == 'P')
                enfeitar(i, j);
    for (int i = 0; i < m; i++)
        printf("%s\n", espaco[i]);
    return 0;
}
