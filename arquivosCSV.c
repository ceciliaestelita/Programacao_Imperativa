#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ══════════════════════════════════════════
   ESTRUTURA
══════════════════════════════════════════ */
typedef struct {
    double sepal_length, sepal_width;
    double petal_length, petal_width;
    char   species[64];
} IrisRecord;

/* ══════════════════════════════════════════
   PARTE 1 — GERAÇÃO DOS ARQUIVOS CSV
══════════════════════════════════════════ */

/* Dados fixos usados para preencher os arquivos */
static const char *CSV_LINES[] = {
    "5.1,3.5,1.4,0.2,Iris-setosa",
    "4.9,3.0,1.4,0.2,Iris-setosa",
    "4.7,3.2,1.3,0.2,Iris-setosa",
    "5.4,3.9,1.7,0.4,Iris-setosa",
    "5.0,3.6,1.4,0.3,Iris-setosa",
    "7.0,3.2,4.7,1.4,Iris-versicolor",
    "6.4,3.2,4.5,1.5,Iris-versicolor",
    "6.9,3.1,4.9,1.5,Iris-versicolor",
    "5.5,2.3,4.0,1.3,Iris-versicolor",
    "6.5,2.8,4.6,1.5,Iris-versicolor",
    "6.3,3.3,6.0,2.5,Iris-virginica",
    "5.8,2.7,5.1,1.9,Iris-virginica",
    "7.1,3.0,5.9,2.1,Iris-virginica",
    "6.5,3.0,5.8,2.2,Iris-virginica",
    "7.6,3.0,6.6,2.1,Iris-virginica",
};
static const int TOTAL_LINES = 15;

/*
 * Cada arquivo recebe um subconjunto diferente das linhas acima,
 * usando um offset para variar o conteúdo entre os arquivos.
 */
void gerar_csvs(int n) {
    for (int i = 1; i <= n; i++) {
        char nome[32];
        sprintf(nome, "iris%d.csv", i);         /* monta o nome dinamicamente */

        FILE *fp = fopen(nome, "w");             /* abre para escrita */
        if (!fp) { perror(nome); continue; }

        fprintf(fp, "sepal_length,sepal_width,petal_length,petal_width,species\n");

        /* Cada arquivo terá entre 6 e 10 linhas, com offset variado */
        int qtd    = 6 + (i % 5);
        int offset = (i * 3) % TOTAL_LINES;

        for (int j = 0; j < qtd; j++) {
            int idx = (offset + j) % TOTAL_LINES;
            fprintf(fp, "%s\n", CSV_LINES[idx]);
        }

        fclose(fp);                              /* fecha imediatamente */
        printf("Gerado: %s (%d registros)\n", nome, qtd);
    }
}

/* ══════════════════════════════════════════
   PARTE 2 — LEITURA COM REALLOC
══════════════════════════════════════════ */

int ler_csv(const char *nome, IrisRecord **registros) {
    FILE *fp = fopen(nome, "r");
    if (!fp) { fprintf(stderr, "Nao encontrado: %s\n", nome); return -1; }

    char linha[256];
    int  count     = 0;
    int  capacidade = 0;
    *registros = NULL;

    fgets(linha, sizeof(linha), fp);   /* pula cabeçalho */

    while (fgets(linha, sizeof(linha), fp)) {
        linha[strcspn(linha, "\n")] = '\0';
        if (strlen(linha) == 0) continue;

        /* Dobra a capacidade quando necessário */
        if (count >= capacidade) {
            capacidade = (capacidade == 0) ? 8 : capacidade * 2;
            IrisRecord *tmp = realloc(*registros, capacidade * sizeof(IrisRecord));
            if (!tmp) { fprintf(stderr, "Erro de memoria\n"); break; }
            *registros = tmp;
        }

        /* Parseia os campos separados por vírgula */
        IrisRecord r;
        char *t;
        t = strtok(linha, ","); if (!t) continue; r.sepal_length = atof(t);
        t = strtok(NULL,  ","); if (!t) continue; r.sepal_width  = atof(t);
        t = strtok(NULL,  ","); if (!t) continue; r.petal_length = atof(t);
        t = strtok(NULL,  ","); if (!t) continue; r.petal_width  = atof(t);
        t = strtok(NULL, ",\r\n"); if (!t) continue;
        strncpy(r.species, t, sizeof(r.species) - 1);
        r.species[sizeof(r.species) - 1] = '\0';

        (*registros)[count++] = r;
    }

    fclose(fp);
    return count;
}

/* ══════════════════════════════════════════
   PARTE 3 — ESTATÍSTICAS
══════════════════════════════════════════ */

void calcular_medias(const IrisRecord *v, int n,
                     double *msl, double *msw,
                     double *mpl, double *mpw) {
    *msl = *msw = *mpl = *mpw = 0.0;
    for (int i = 0; i < n; i++) {
        *msl += v[i].sepal_length;
        *msw += v[i].sepal_width;
        *mpl += v[i].petal_length;
        *mpw += v[i].petal_width;
    }
    *msl /= n; *msw /= n; *mpl /= n; *mpw /= n;
}

/* Moda com desempate lexicográfico (menor nome vence) */
void calcular_moda(const IrisRecord *v, int n, char *moda) {
    char  especies[20][64];
    int   freq[20];
    int   unique = 0;

    for (int i = 0; i < n; i++) {
        int achou = 0;
        for (int j = 0; j < unique; j++) {
            if (strcmp(v[i].species, especies[j]) == 0) { freq[j]++; achou = 1; break; }
        }
        if (!achou && unique < 20) {
            strncpy(especies[unique], v[i].species, 63);
            freq[unique++] = 1;
        }
    }

    int melhor = 0;
    for (int j = 1; j < unique; j++) {
        if (freq[j] > freq[melhor] ||
           (freq[j] == freq[melhor] && strcmp(especies[j], especies[melhor]) < 0))
            melhor = j;
    }
    strncpy(moda, unique > 0 ? especies[melhor] : "", 63);
}

/* ══════════════════════════════════════════
   PARTE 4 — EXIBIÇÃO E APPEND NO ARQUIVO
══════════════════════════════════════════ */

void exibir_e_gravar(const char *nome, const IrisRecord *v, int n,
                     double msl, double msw, double mpl, double mpw,
                     const char *moda) {
    /* Exibe no terminal */
    printf("\n+---------- %s ----------+\n", nome);
    printf("| %-12s %-11s %-12s %-11s %-18s|\n",
           "sepal_len","sepal_wid","petal_len","petal_wid","species");
    printf("|-----------------------------------------------------------|\n");
    for (int i = 0; i < n; i++) {
        printf("| %-12.1f %-11.1f %-12.1f %-11.1f %-18s|\n",
               v[i].sepal_length, v[i].sepal_width,
               v[i].petal_length, v[i].petal_width,
               v[i].species);
    }
    printf("|-----------------------------------------------------------|\n");
    printf("| Registros            : %-34d|\n", n);
    printf("| Media sepal_length   : %-34.4f|\n", msl);
    printf("| Media sepal_width    : %-34.4f|\n", msw);
    printf("| Media petal_length   : %-34.4f|\n", mpl);
    printf("| Media petal_width    : %-34.4f|\n", mpw);
    printf("| Especie predominante : %-34s|\n", moda);
    printf("+-----------------------------------------------------------+\n");

    /* Grava no final do próprio arquivo (append) */
    FILE *fp = fopen(nome, "a");         /* modo "a" = não apaga, escreve no fim */
    if (!fp) { perror(nome); return; }
    fprintf(fp, "\n# --- Resultados ---\n");
    fprintf(fp, "# Registros: %d\n",             n);
    fprintf(fp, "# Media sepal_length: %.4f\n",  msl);
    fprintf(fp, "# Media sepal_width: %.4f\n",   msw);
    fprintf(fp, "# Media petal_length: %.4f\n",  mpl);
    fprintf(fp, "# Media petal_width: %.4f\n",   mpw);
    fprintf(fp, "# Especie predominante: %s\n",  moda);
    fclose(fp);
}

/* ══════════════════════════════════════════
   MAIN
══════════════════════════════════════════ */
int main(void) {
    int n;
    printf("Quantos arquivos CSV processar? ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Entrada invalida.\n");
        return EXIT_FAILURE;
    }

    /* Gera os arquivos antes de analisar */
    printf("\n--- Gerando arquivos ---\n");
    gerar_csvs(n);

    /* Analisa cada arquivo */
    printf("\n--- Analisando arquivos ---\n");
    for (int i = 1; i <= n; i++) {
        char nome[32];
        sprintf(nome, "iris%d.csv", i);

        IrisRecord *registros = NULL;
        int count = ler_csv(nome, &registros);
        if (count <= 0) { free(registros); continue; }

        double msl, msw, mpl, mpw;
        calcular_medias(registros, count, &msl, &msw, &mpl, &mpw);

        char moda[64];
        calcular_moda(registros, count, moda);

        exibir_e_gravar(nome, registros, count, msl, msw, mpl, mpw, moda);

        free(registros);
    }

    printf("\nProcessamento concluido.\n");
    return EXIT_SUCCESS;
}