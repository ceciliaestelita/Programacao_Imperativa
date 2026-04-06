#include <stdio.h>

int m, n;
char espaco[100][100];

void colocar(int i, int j, char c) {
    if (i < 0 || i >= m || j < 0 || j >= n) return;  // fora da praça
    if (espaco[i][j] == '+' && c == 'x') return;  // + tem prioridade sobre x                  
    espaco[i][j] = c;
}

void enfeitar(int i, int j) {           // as posições imediatamente próximas ao poste
    colocar(i - 1, j, '+');
    colocar(i + 1, j, '+');
    colocar(i, j - 1, '+');
    colocar(i, j + 1, '+');

    colocar(i - 1, j - 1, 'x');         // as diagonais do poste
    colocar(i - 1, j + 1, 'x');
    colocar(i + 1, j - 1, 'x');
    colocar(i + 1, j + 1, 'x');
}

int main() {
    scanf("%d %d", &m, &n);
    for (int i = 0; i < m; i++)         // vai lendo cada caractere de cada coluna da matriz e armazenando
        scanf("%s", espaco[i]);

    for (int i = 0; i < m; i++)         // percorre toda a matriz, verificando onde está o poste
        for (int j = 0; j < n; j++)
            if (espaco[i][j] == 'P')
                enfeitar(i, j);         // quando encontrar o poste, chama a função

    for (int i = 0; i < m; i++)
        printf("%s\n", espaco[i]);

    return 0;
}
