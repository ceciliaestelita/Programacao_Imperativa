#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int valor;
    struct No *esq, *dir;
} No;

No* inserir(No *raiz, int val) {
    if (!raiz) {
        No *novo = malloc(sizeof(No));
        novo->valor = val;
        novo->esq = novo->dir = NULL;
        return novo;
    }
    if (val < raiz->valor)
        raiz->esq = inserir(raiz->esq, val);
    else if (val > raiz->valor)
        raiz->dir = inserir(raiz->dir, val);
    return raiz;
}

void preordem(No *raiz) {
    if (!raiz) return;
    printf("%d ", raiz->valor);
    preordem(raiz->esq);
    preordem(raiz->dir);
}

void emordem(No *raiz) {
    if (!raiz) return;
    emordem(raiz->esq);
    printf("%d ", raiz->valor);
    emordem(raiz->dir);
}

void posordem(No *raiz) {
    if (!raiz) return;
    posordem(raiz->esq);
    posordem(raiz->dir);
    printf("%d ", raiz->valor);
}

int contarNos(No *raiz) {
    if (!raiz) return 0;
    return 1 + contarNos(raiz->esq) + contarNos(raiz->dir);
}

int contarFolhas(No *raiz) {
    if (!raiz) return 0;
    if (!raiz->esq && !raiz->dir) return 1;
    return contarFolhas(raiz->esq) + contarFolhas(raiz->dir);
}

int altura(No *raiz) {
    if (!raiz) return -1;
    int he = altura(raiz->esq);
    int hd = altura(raiz->dir);
    return 1 + (he > hd ? he : hd);
}

int menor(No *raiz) {
    while (raiz->esq) raiz = raiz->esq;
    return raiz->valor;
}

int maior(No *raiz) {
    while (raiz->dir) raiz = raiz->dir;
    return raiz->valor;
}

void liberarArvore(No *raiz) {
    if (!raiz) return;
    liberarArvore(raiz->esq);
    liberarArvore(raiz->dir);
    free(raiz);
}

int main() {
    No *raiz = NULL;
    int val;

    while (scanf("%d", &val) == 1 && val != -1)
        raiz = inserir(raiz, val);

    if (!raiz) {
        printf("ARVORE VAZIA\n");
        return 0;
    }

    printf("PREORDEM: ");
    preordem(raiz);
    printf("\nEMORDEM: ");
    emordem(raiz);
    printf("\nPOSORDEM: ");
    posordem(raiz);
    printf("\nNOS: %d ", contarNos(raiz));
    printf("\nFOLHAS: %d ", contarFolhas(raiz));
    printf("\nALTURA: %d ", altura(raiz));
    printf("\nMENOR: %d ", menor(raiz));
    printf("\nMAIOR: %d\n", maior(raiz));

    liberarArvore(raiz);
    return 0;
}
