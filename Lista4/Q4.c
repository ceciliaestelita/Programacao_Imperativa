#include <stdio.h>
#include <string.h>

#define MAX 100

// Mapa e dimensões globais
char mapa[MAX][MAX];
int linhas, colunas;

// Matriz de distâncias: -1 = não visitado
int dist[MAX][MAX];

// Fila para o BFS (armazena posições linha/coluna)
int filaLin[MAX * MAX];
int filaCol[MAX * MAX];

// Posição de origem e destino
int oriLin, oriCol;
int destLin, destCol;

// Lê o mapa e encontra as posições de 'o' e 'd'
void lerMapa() {
    char tam[20];
    scanf("%s", tam);  // lê "LxC"

    // Separa linhas e colunas do formato "LxC"
    int i = 0;
    linhas = 0;
    while (tam[i] != 'x') {
        linhas = linhas * 10 + (tam[i] - '0');
        i++;
    }
    i++;  // pula o 'x'
    colunas = 0;
    while (tam[i] != '\0') {
        colunas = colunas * 10 + (tam[i] - '0');
        i++;
    }

    int l, c;
    for (l = 0; l < linhas; l++) {
        scanf("%s", mapa[l]);
        for (c = 0; c < colunas; c++) {
            if (mapa[l][c] == 'o') { oriLin  = l; oriCol  = c; }
            if (mapa[l][c] == 'd') { destLin = l; destCol = c; }
        }
    }
}

// Inicializa a matriz de distâncias com -1 (não visitado)
void inicializarDist() {
    int l, c;
    for (l = 0; l < linhas; l++)
        for (c = 0; c < colunas; c++)
            dist[l][c] = -1;
}

// Verifica se uma célula é válida para visitar:
// dentro dos limites, não visitada e não é parede
int valida(int l, int c) {
    if (l < 0 || l >= linhas) return 0;
    if (c < 0 || c >= colunas) return 0;
    if (dist[l][c] != -1) return 0;
    if (mapa[l][c] == '#') return 0;
    return 1;
}

// BFS: explora o mapa a partir da origem
// retorna a distância até o destino, ou -1 se não houver caminho
int bfs() {
    // Direções: cima, baixo, esquerda, direita
    int dl[] = {-1, 1,  0, 0};
    int dc[] = { 0, 0, -1, 1};

    int inicio = 0, fim = 0;  // índices da fila

    // Coloca a origem na fila e marca distância 0
    filaLin[fim] = oriLin;
    filaCol[fim] = oriCol;
    fim++;
    dist[oriLin][oriCol] = 0;

    while (inicio < fim) {
        // Retira o próximo da fila
        int l = filaLin[inicio];
        int c = filaCol[inicio];
        inicio++;

        // Chegou no destino: retorna a distância
        if (l == destLin && c == destCol)
            return dist[l][c];

        // Tenta os 4 vizinhos
        int i;
        for (i = 0; i < 4; i++) {
            int nl = l + dl[i];
            int nc = c + dc[i];

            if (valida(nl, nc)) {
                dist[nl][nc] = dist[l][c] + 1;  // distância = pai + 1
                filaLin[fim] = nl;
                filaCol[fim] = nc;
                fim++;
            }
        }
    }

    return -1;  // destino nunca alcançado
}

int main() {
    lerMapa();
    inicializarDist();

    int resultado = bfs();

    if (resultado != -1)
        printf("Apos correr %d metros e quase desistir por causa da distância, Rebeka conseguiu escapar!\n", resultado);
    else
        printf("Poxa... Parece que nao foi dessa vez que Rebeka conseguiu fugir\n");

    return 0;
}
