#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// structs   
typedef struct Aluno {
    char mat[12];       // 11 dígitos + '\0' 
    int  pri;
    double cr;
    long long L, R;
    int  score;
} Aluno;

typedef struct No {
    Aluno data;
    struct No *prox;
} No;

typedef struct Fila {
    No *inicio;
    No *fim;
    int tamanho;
} Fila;

// operações de fila
void inicializar(Fila *f) {
    f->inicio = f->fim = NULL;
    f->tamanho = 0;
}

void enqueue(Fila *f, Aluno a) {
    No *novo = (No *)malloc(sizeof(No));
    if (!novo) { fprintf(stderr, "Sem memória\n"); exit(1); }
    novo->data = a;
    novo->prox = NULL;
    if (f->fim) f->fim->prox = novo;
    else        f->inicio    = novo;
    f->fim = novo;
    f->tamanho++;
}

// retorna 1 se removeu, 0 se vazia  
int dequeue(Fila *f, Aluno *out) {
    if (!f->inicio) return 0;
    No *tmp = f->inicio;
    *out = tmp->data;
    f->inicio = tmp->prox;
    if (!f->inicio) f->fim = NULL;
    free(tmp);
    f->tamanho--;
    return 1;
}

void liberar_fila(Fila *f) {
    Aluno a;
    while (dequeue(f, &a));
}

// cálculo do score   
int calcular_score(double cr, int pri) {
    return (int)round(cr * 100) / pri;
}

// main 
int main(void) {
    char cmd[16];
    char nome_disciplina[64];
    int vagas_total = 0, vagas = 0;
    long long relogio = 1;

    Fila fila_req, fila_conf;
    inicializar(&fila_req);
    inicializar(&fila_conf);

    while (scanf("%15s", cmd) == 1) {

        // stard
        if (strcmp(cmd, "START") == 0) {
            scanf("%63s %d", nome_disciplina, &vagas_total);
            vagas   = vagas_total;
            relogio = 1;
            liberar_fila(&fila_req);
            liberar_fila(&fila_conf);
        }

        // add  
        else if (strcmp(cmd, "ADD") == 0) {
            Aluno a;
            scanf("%11s %d %lf %lld %lld",
                  a.mat, &a.pri, &a.cr, &a.L, &a.R);
            a.score = calcular_score(a.cr, a.pri);
            enqueue(&fila_req, a);
        }

        // proc
        else if (strcmp(cmd, "PROC") == 0) {
            int qtd;
            scanf("%d", &qtd);

            int processados = 0;
            while (processados < qtd && fila_req.tamanho > 0) {
                // verifica o próximo sem remover  
                Aluno prox = fila_req.inicio->data;

                // relógio ocioso: avança para L do próximo aluno  
                if (relogio < prox.L) relogio = prox.L;

                // remover da fila  
                Aluno a;
                dequeue(&fila_req, &a);

                // timeout: tempo_atual > R  
                if (relogio > a.R) {
                    printf("[TIMEOUT] mat=%s | Desconectado da fila.\n", a.mat);
                    // relógio não avança  
                } else if (vagas > 0) {
                    printf("[ALOCADO] mat=%s | score=%d | Processado no seg: %lld\n",
                           a.mat, a.score, relogio);
                    enqueue(&fila_conf, a);
                    vagas--;
                    relogio++;
                    processados++;
                } else {
                    printf("[LOTADO] mat=%s | score=%d | Processado no seg: %lld\n",
                           a.mat, a.score, relogio);
                    relogio++;
                    processados++;
                }
            }
        }

        else if (strcmp(cmd, "FIM") == 0) {
            printf("--- LISTA OFICIAL: %s ---\n", nome_disciplina);
            int pos = 1;
            Aluno a;
            while (dequeue(&fila_conf, &a)) {
                printf("%d. Matricula: %s\n", pos++, a.mat);
            }
            liberar_fila(&fila_req);
        }
    }

    return 0;
}
