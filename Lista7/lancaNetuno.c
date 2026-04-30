#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Mecha Mecha;

typedef struct {
    char nome[30];
    int atrib1;
    int atrib2;
    void (*subrotina)(Mecha *m, int slot, int input, int *output);
} SubSistema;

struct Mecha {
    int id;
    char modelo[50];
    int energia_atual;
    int num_sistemas;
    int valor_wintermute;
    SubSistema sistemas[]; // Flexible Array Member
};

// Funções dos Subsistemas
void defesa_func(Mecha *m, int slot, int input, int *output) {
    int val = input - m->sistemas[slot].atrib1 - (slot * m->sistemas[slot].atrib2);
    if (val < 0) val = 0;
    *output = val;
}

void utilidade_func(Mecha *m, int slot, int input, int *output) {
    int val = m->sistemas[slot].atrib1 + (slot * m->sistemas[slot].atrib2);
    m->energia_atual += val;
    *output = m->energia_atual;
}

void ataque_func(Mecha *m, int slot, int input, int *output) {
    if (m->energia_atual < m->sistemas[slot].atrib2) {
        *output = -1; // Indicador de energia insuficiente
    } else {
        int val = m->sistemas[slot].atrib1 + m->energia_atual + slot - input;
        m->energia_atual -= m->sistemas[slot].atrib2;
        *output = val;
    }
}

int main() {
    int N;
    if (scanf("%d", &N) != 1) return 1;

    Mecha **esquadrao = (Mecha **)malloc(N * sizeof(Mecha *));
    if (!esquadrao) return 1;

    for (int i = 0; i < N; i++) {
        int id, energia_inicial, Q;
        char modelo[50];

        if (scanf("%d %s %d %d", &id, modelo, &energia_inicial, &Q) != 4) {
            for (int k = 0; k < i; k++) {
                free(esquadrao[k]);
            }
            free(esquadrao);
            return 1;
        }

        // Alocação em um único bloco (núcleo + FAM)
        Mecha *m = (Mecha *)malloc(sizeof(Mecha) + Q * sizeof(SubSistema));
        m->id = id;
        strcpy(m->modelo, modelo);
        m->energia_atual = energia_inicial;
        m->num_sistemas = Q;

        for (int j = 0; j < Q; j++) {
            char tipo;
            char nome[30];
            int atrib1, atrib2;

            scanf(" %c %s %d %d", &tipo, nome, &atrib1, &atrib2);

            strcpy(m->sistemas[j].nome, nome);
            m->sistemas[j].atrib1 = atrib1;
            m->sistemas[j].atrib2 = atrib2;

            if (tipo == 'A') {
                m->sistemas[j].subrotina = ataque_func;
            } else if (tipo == 'D') {
                m->sistemas[j].subrotina = defesa_func;
            } else if (tipo == 'U') {
                m->sistemas[j].subrotina = utilidade_func;
            }
        }

        scanf("%d", &m->valor_wintermute);
        esquadrao[i] = m;
    }

    // Ordenação do esquadrão em ordem crescente de IDs
    for (int i = 0; i < N - 1; i++) {
        for (int j = 0; j < N - i - 1; j++) {
            if (esquadrao[j]->id > esquadrao[j + 1]->id) {
                Mecha *temp = esquadrao[j];
                esquadrao[j] = esquadrao[j + 1];
                esquadrao[j + 1] = temp;
            }
        }
    }

    // Saída do relatório
    printf("[RELATORIO DE MISSÃO: OPERAÇÃO LANÇA DE NETUNO]\n");

    for (int i = 0; i < N; i++) {
        Mecha *m = esquadrao[i];

        printf("ID: %d | MECHA: %s | ENERGIA: %d\n", m->id, m->modelo, m->energia_atual);

        // Disparo de subrotinas na ordem estrita de prioridades
        for (int p = 1; p <= 3; p++) {
            void (*ref_func)(Mecha *m, int slot, int input, int *output) = NULL;
            if (p == 1) ref_func = defesa_func;
            if (p == 2) ref_func = utilidade_func;
            if (p == 3) ref_func = ataque_func;

            for (int j = 0; j < m->num_sistemas; j++) {
                if (m->sistemas[j].subrotina == ref_func) {
                    int output = 0;
                    m->sistemas[j].subrotina(m, j, m->valor_wintermute, &output);

                    if (p == 1) {
                        printf("-> [DEFESA] %s | Dano final sofrido: %d\n", m->sistemas[j].nome, output);
                    } else if (p == 2) {
                        printf("-> [UTILIDADE] %s | Energia atual: %d\n", m->sistemas[j].nome, output);
                    } else if (p == 3) {
                        if (output == -1) {
                            printf("-> [ATAQUE] %s | Energia insuficiente!\n", m->sistemas[j].nome);
                        } else {
                            printf("-> [ATAQUE] %s | Dano causado: %d | Energia restante: %d\n", m->sistemas[j].nome, output, m->energia_atual);
                        }
                    }
                }
            }
        }

        printf("ENERGIA FINAL: %d\n", m->energia_atual);
        printf("-----------------------------------------\n");
    }

    printf("Esquadrao pronto para o combate.\n");

    // Limpeza da memória
    for (int i = 0; i < N; i++) {
        free(esquadrao[i]);
    }
    free(esquadrao);

    return 0;
}
