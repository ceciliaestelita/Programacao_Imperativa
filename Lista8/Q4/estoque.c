#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRODUTOS 1000
#define MAX_MOVIMENTOS 10000
#define MAX_NOME 50
#define MAX_INCONSISTENCIAS 10000

typedef struct {
    int codigo;
    char nome[MAX_NOME];
    int quantidade;
    float preco;
} Produto;

typedef struct {
    int codigo;
    char tipo;
    int quantidade;
} Movimento;

typedef struct {
    int codigo;
    char tipo;
    int quantidade;
    char motivo[30]; // "ESTOQUE_INSUFICIENTE" ou "PRODUTO_INEXISTENTE"
} Inconsistencia;

int encontrar_produto(Produto produtos[], int total, int codigo) {
    for (int i = 0; i < total; i++) {
        if (produtos[i].codigo == codigo)
            return i;
    }
    return -1;
}

int main() {
    FILE *fp_produtos = fopen("produtos.txt", "r");
    FILE *fp_movimentos = fopen("movimentos.txt", "r");

    if (!fp_produtos || !fp_movimentos) {
        printf("Erro ao abrir arquivo.\n");
        if (fp_produtos)  fclose(fp_produtos);
        if (fp_movimentos) fclose(fp_movimentos);
        return 1;
    }

    Produto produtos[MAX_PRODUTOS];
    int total_produtos = 0;

    while (fscanf(fp_produtos, "%d %s %d %f",
                  &produtos[total_produtos].codigo,
                  produtos[total_produtos].nome,
                  &produtos[total_produtos].quantidade,
                  &produtos[total_produtos].preco) == 4) {
        total_produtos++;
    }
    fclose(fp_produtos);

    Movimento movimentos[MAX_MOVIMENTOS];
    int total_movimentos = 0;

    while (fscanf(fp_movimentos, "%d %c %d",
                  &movimentos[total_movimentos].codigo,
                  &movimentos[total_movimentos].tipo,
                  &movimentos[total_movimentos].quantidade) == 3) {
        total_movimentos++;
    }
    fclose(fp_movimentos);

    // Contadores para o relatório
    int movimentos_aplicados = 0;
    int saidas_recusadas = 0;
    int sem_cadastro = 0;

    Inconsistencia inconsistencias[MAX_INCONSISTENCIAS];
    int total_inconsistencias = 0;

    // Processar movimentos
    for (int i = 0; i < total_movimentos; i++) {
        int idx = encontrar_produto(produtos, total_produtos, movimentos[i].codigo);

        if (idx == -1) {
            // Produto não encontrado
            sem_cadastro++;
            inconsistencias[total_inconsistencias].codigo    = movimentos[i].codigo;
            inconsistencias[total_inconsistencias].tipo      = movimentos[i].tipo;
            inconsistencias[total_inconsistencias].quantidade = movimentos[i].quantidade;
            strcpy(inconsistencias[total_inconsistencias].motivo, "PRODUTO_INEXISTENTE");
            total_inconsistencias++;
        } else if (movimentos[i].tipo == 'E') {
            produtos[idx].quantidade += movimentos[i].quantidade;
            movimentos_aplicados++;
        } else if (movimentos[i].tipo == 'S') {
            if (produtos[idx].quantidade >= movimentos[i].quantidade) {
                produtos[idx].quantidade -= movimentos[i].quantidade;
                movimentos_aplicados++;
            } else {
                saidas_recusadas++;
                inconsistencias[total_inconsistencias].codigo    = movimentos[i].codigo;
                inconsistencias[total_inconsistencias].tipo      = movimentos[i].tipo;
                inconsistencias[total_inconsistencias].quantidade = movimentos[i].quantidade;
                strcpy(inconsistencias[total_inconsistencias].motivo, "ESTOQUE_INSUFICIENTE");
                total_inconsistencias++;
            }
        }
    }

    // Gerar estoque_atualizado.txt
    FILE *fp_estoque = fopen("estoque_atualizado.txt", "w");
    if (!fp_estoque) {
        printf("Erro ao abrir arquivo.\n");
        return 1;
    }
    for (int i = 0; i < total_produtos; i++) {
        fprintf(fp_estoque, "%d %s %d %.2f\n",
                produtos[i].codigo,
                produtos[i].nome,
                produtos[i].quantidade,
                produtos[i].preco);
    }
    fclose(fp_estoque);

    // Gerar relatorio.txt
    FILE *fp_relatorio = fopen("relatorio.txt", "w");
    if (!fp_relatorio) {
        printf("Erro ao abrir arquivo.\n");
        return 1;
    }

    fprintf(fp_relatorio, "PRODUTOS PROCESSADOS: %d\n", total_produtos);
    fprintf(fp_relatorio, "MOVIMENTOS APLICADOS: %d\n", movimentos_aplicados);
    fprintf(fp_relatorio, "SAIDAS RECUSADAS: %d\n", saidas_recusadas);
    fprintf(fp_relatorio, "MOVIMENTOS SEM CADASTRO: %d\n", sem_cadastro);

    fprintf(fp_relatorio, "ESTOQUE BAIXO:\n");
    for (int i = 0; i < total_produtos; i++) {
        if (produtos[i].quantidade <= 5) {
            fprintf(fp_relatorio, "%d %s %d\n",
                    produtos[i].codigo,
                    produtos[i].nome,
                    produtos[i].quantidade);
        }
    }

    fprintf(fp_relatorio, "INCONSISTENCIAS:\n");
    for (int i = 0; i < total_inconsistencias; i++) {
        fprintf(fp_relatorio, "%d %c %d %s\n",
                inconsistencias[i].codigo,
                inconsistencias[i].tipo,
                inconsistencias[i].quantidade,
                inconsistencias[i].motivo);
    }

    fclose(fp_relatorio);

    printf("Processamento concluido com sucesso.\n");
    return 0;
}
