#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// aloca e copia a matriz
int **alocarMatriz(int M, int N) {
    int **m = malloc(M * sizeof(int *));
    for (int i = 0; i < M; i++)
        m[i] = calloc(N, sizeof(int));
    return m;
}

void liberarMatriz(int **m, int M) {
    for (int i = 0; i < M; i++) free(m[i]);
    free(m);
}

int **copiarMatriz(int **orig, int M, int N) {
    int **copia = alocarMatriz(M, N);
    for (int i = 0; i < M; i++)
        for (int j = 0; j < N; j++)
            copia[i][j] = orig[i][j];
    return copia;
}

void printarMatriz(int **m, int M, int N) {
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            if (j > 0) printf(" ");
            printf("%d", m[i][j]);
        }
        printf("\n");
    }
}

// calcula as camadas de AoE
// camada[i][j] = 0 (fora), 1 (camada 1), 2 (camada 2)
int **calcularCamadas(int cx, int cy, int M, int N) {
    int **camada = alocarMatriz(M, N);

    // camada 1: centro + ortogonais 
    int dx1[] = {0, -1, 1, 0, 0};
    int dy1[] = {0, 0, 0, -1, 1};
    for (int k = 0; k < 5; k++) {
        int nx = cx + dx1[k];
        int ny = cy + dy1[k];
        if (nx >= 0 && nx < M && ny >= 0 && ny < N)
            camada[nx][ny] = 1;
    }

    // camada 2: 8 vizinhos de cada célula da camada 1, fora as da camada 1 
    int dx8[] = {-1,-1,-1, 0, 0, 1, 1, 1};
    int dy8[] = {-1, 0, 1,-1, 1,-1, 0, 1};
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            if (camada[i][j] == 1) {
                for (int k = 0; k < 8; k++) {
                    int nx = i + dx8[k];
                    int ny = j + dy8[k];
                    if (nx >= 0 && nx < M && ny >= 0 && ny < N && camada[nx][ny] == 0)
                        camada[nx][ny] = 2;
                }
            }
        }
    }

    return camada;
}

// ponteiros de função (tipos de ataque)
typedef int **(*FuncAtaque)(int **mapa, int M, int N, int cx, int cy);

// explosão arcana
int **explosaoArcana(int **mapa, int M, int N, int cx, int cy) {
    int **camada = calcularCamadas(cx, cy, M, N);
    int **novo = copiarMatriz(mapa, M, N);

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            int dano = 0;
            if      (camada[i][j] == 1) dano = 50;
            else if (camada[i][j] == 2) dano = 25;
            if (dano > 0) {
                novo[i][j] = novo[i][j] - dano;
                if (novo[i][j] < 0) novo[i][j] = 0;
            }
        }
    }

    liberarMatriz(camada, M);
    return novo;
}

// nuvem venenosa (retorna vetor de matrizes, quantos turnos foram executados) 
int contarVizinhosVivos(int **mapa, int M, int N, int i, int j) {
    int dx8[] = {-1,-1,-1, 0, 0, 1, 1, 1};
    int dy8[] = {-1, 0, 1,-1, 1,-1, 0, 1};
    int count = 0;
    for (int k = 0; k < 8; k++) {
        int nx = i + dx8[k];
        int ny = j + dy8[k];
        if (nx >= 0 && nx < M && ny >= 0 && ny < N && mapa[nx][ny] > 0)
            count++;
    }
    return count;
}

int **aplicarTurnoVeneno(int **mapa, int M, int N, int **camada) {
    int **novo = copiarMatriz(mapa, M, N);

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            if (camada[i][j] > 0) {
                int vizinhos = contarVizinhosVivos(mapa, M, N, i, j);
                int dano = 5 + 8 * vizinhos;
                novo[i][j] = novo[i][j] - dano;
                if (novo[i][j] < 0) novo[i][j] = 0;
            }
        }
    }
    return novo;
}

// verifica se todas as células da área de efeito estão zeradas 
int todasMortas(int **mapa, int M, int N, int **camada) {
    for (int i = 0; i < M; i++)
        for (int j = 0; j < N; j++)
            if (camada[i][j] > 0 && mapa[i][j] > 0)
                return 0;
    return 1;
}

// main
int main(void) {
    int M, N;
    scanf("%d %d", &M, &N);

    int **mapa = alocarMatriz(M, N);
    for (int i = 0; i < M; i++)
        for (int j = 0; j < N; j++)
            scanf("%d", &mapa[i][j]);

    int cx, cy;
    scanf("%d %d", &cx, &cy);

    char tipo[50];
    scanf("%s", tipo);

    printf("Estado inicial do mapa:\n");
    printarMatriz(mapa, M, N);
    printf("\n");

    if (strcmp(tipo, "EXPLOSAO_ARCANA") == 0) {
        FuncAtaque ataque = explosaoArcana;
        int **resultado = ataque(mapa, M, N, cx, cy);

        printf("Estado do mapa após usar a Explosão Arcana:\n");
        printarMatriz(resultado, M, N);

        liberarMatriz(resultado, M);

    } else if (strcmp(tipo, "NUVEM_VENENOSA") == 0) {
        int **camada = calcularCamadas(cx, cy, M, N);

        printf("Estado do mapa, por turno, após usar a Nuvem Venenosa:\n");

        int **atual = copiarMatriz(mapa, M, N);

        for (int turno = 0; turno < 3; turno++) {
            int **proximo = aplicarTurnoVeneno(atual, M, N, camada);
            liberarMatriz(atual, M);
            atual = proximo;

            printarMatriz(atual, M, N);

            if (todasMortas(atual, M, N, camada)) break;
            printf("\n");
        }

        liberarMatriz(atual, M);
        liberarMatriz(camada, M);
    }

    liberarMatriz(mapa, M);
    return 0;
}
