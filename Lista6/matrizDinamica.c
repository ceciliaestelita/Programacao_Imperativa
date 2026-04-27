#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// funções de operação
int dobro(int n) {
    return n * 2;
}

int quadrado(int n) {
    return n * n;
}

int absoluto(int n) {
    return abs(n);
}

// aloca a matriz dinamicamente
int **alocarMatriz(int l, int c) {
    int **mat = (int **)malloc(l * sizeof(int *));
    for (int i = 0; i < l; i++) {
        mat[i] = (int *)malloc(c * sizeof(int));
    }
    return mat;
}

//lLê os elementos da matriz
void lerMatriz(int **mat, int l, int c) {
    for (int i = 0; i < l; i++) {
        for (int j = 0; j < c; j++) {
            scanf("%d", &mat[i][j]);
        }
    }
}

// printa a matriz
void imprimirMatriz(int **mat, int l, int c) {
    for (int i = 0; i < l; i++) {
        for (int j = 0; j < c; j++) {
            printf("%d%c", mat[i][j], (j == c - 1) ? '\n' : ' ');
        }
    }
}

// chama a operação usando ponteiro pra função
void aplicarOperacao(int **mat, int l, int c, int (*operacao)(int)) {
    for (int i = 0; i < l; i++) {
        for (int j = 0; j < c; j++) {
            mat[i][j] = operacao(mat[i][j]);
        }
    }
}

// libera a memória alocada
void liberarMatriz(int **mat, int l) {
    for (int i = 0; i < l; i++) {
        free(mat[i]);
    }
    free(mat);
}

int main() {
    int l, c, op;
    if (scanf("%d %d", &l, &c) != 2) return 0;

    int **mat = alocarMatriz(l, c);
    lerMatriz(mat, l, c);
    scanf("%d", &op);

    // define ponteiro para função
    int (*ptrFuncao)(int);

    switch (op) {
        case 1: ptrFuncao = dobro; break;
        case 2: ptrFuncao = quadrado; break;
        case 3: ptrFuncao = absoluto; break;
        default: return 0;
    }

    aplicarOperacao(mat, l, c, ptrFuncao);
    imprimirMatriz(mat, l, c);
    liberarMatriz(mat, l);

    return 0;
}
