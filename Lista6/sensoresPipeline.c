#include <stdio.h>
#include <stdlib.h>

// filtros
typedef int (*Filtro)(int);

int calibracao(int v){ return v + 5;}
int saturacao(int v){ return v > 80 ? 80 : v;}
int amplificador(int v){ return v * 2;}

// tabela global de filtros indexada por id (1, 2, 3) 
static Filtro tabela_filtros[4] = {NULL, calibracao, saturacao, amplificador};

// alocação e liberação de matriz dinâmica
int **alocar(int N, int M) {
    int **mat = malloc(N * sizeof(int *));
    for (int i = 0; i < N; i++)
        mat[i] = malloc(M * sizeof(int));
    return mat;
}

void liberar(int **mat, int N) {
    for (int i = 0; i < N; i++) free(mat[i]);
    free(mat);
}

// modificar 
// aplica pipeline (vetor de ponteiros para função) de comprimento k a cada elemento da matriz N x M
void modificar(int **mat, int N, int M, Filtro *pipeline, int k) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            for (int f = 0; f < k; f++)
                mat[i][j] = pipeline[f](mat[i][j]);
}

// printar e sensor crítico
void printar(int **mat, int N, int M) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (j > 0) printf(" ");
            printf("%d", mat[i][j]);
        }
        printf("\n");
    }
}

void sensorCritico(int **mat, int N, int M) {
    int maximo = mat[0][0], li = 0, ci = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            if (mat[i][j] > maximo) { maximo = mat[i][j]; li = i; ci = j; }
    printf("\nSensor critico: %d\n", maximo);
    printf("Posicao: (%d,%d)\n", li, ci);
}

// main
int main(void) {
    int N, M;
    scanf("%d %d", &N, &M);

    int **mat = alocar(N, M);
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            scanf("%d", &mat[i][j]);

    int cmd;
    while (scanf("%d", &cmd) == 1 && cmd != 0) {
        Filtro *pipeline = NULL;
        int k = 0;

        if (cmd >= 1 && cmd <= 3) {
            /* Comandos simples: pipeline de 1 filtro */
            k = 1;
            pipeline = malloc(k * sizeof(Filtro));
            pipeline[0] = tabela_filtros[cmd];
        } else if (cmd == 4) {
            scanf("%d", &k);
            pipeline = malloc(k * sizeof(Filtro));
            for (int f = 0; f < k; f++) {
                int id; scanf("%d", &id);
                pipeline[f] = tabela_filtros[id];
            }
        }

        if (pipeline) {
            modificar(mat, N, M, pipeline, k);
            free(pipeline);
        }
    }

    printf("Matriz processada:\n");
    printar(mat, N, M);
    sensorCritico(mat, N, M);

    liberar(mat, N);
    return 0;
}
