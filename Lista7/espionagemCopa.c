#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINHA 256
#define MAX_CIDADELAS 100

typedef struct {
    char nome[50];
    int populacao;
    int periculosidade;
    char func[50];
} cidadela;

// função usada no sorting com base nos critérios de população, periculosidade e ordem alfabética
int cmpCidadelas(const void *a, const void *b) {
    cidadela *c1 = (cidadela *)a;
    cidadela *c2 = (cidadela *)b;

    if (c1->populacao != c2->populacao) {
        return c2->populacao - c1->populacao; // ordem decrescente
    }
    if (c1->periculosidade != c2->periculosidade) {
        return c2->periculosidade - c1->periculosidade; // ordem decrescente
    }
    return strcmp(c1->nome, c2->nome);
}

// padroniza a string pra primeira letra maiúscula e todas as outras minúsculas
void padString(char *str) {
    if (strlen(str) > 0) {
        str[0] = toupper(str[0]);
        for (int i = 1; str[i] != '\0'; i++) {
            str[i] = tolower(str[i]);
        }
    }
}

// main
int main() {
    cidadela cidadelas[MAX_CIDADELAS];
    int num_cidadelas = 0;
    int key = -1;
    int has_key = 0;

    char line[MAX_LINHA];
    while (fgets(line, sizeof(line), stdin)) {
        // tira quebras de linha no final do input
        line[strcspn(line, "\r\n")] = 0;

        if (strlen(line) == 0) {
            continue;
        }

        // verifica se é uma mensagem especial
        int is_special = 0;
        for (int i = 0; line[i] != '\0'; i++) {
            if (line[i] == '!') {
                is_special = 1;
                break;
            }
        }

        if (is_special) {
            int key_val = 0;
            for (int i = 0; line[i] != '\0'; i++) {
                if (isdigit(line[i])) {
                    key_val = key_val * 10 + (line[i] - '0');
                }
            }
            key = key_val;
            has_key = 1;
            continue; // mensagens especiais não são cidadelas
        }

        // processa as características da cidadela
        cidadela c;
        c.populacao = 0;
        c.periculosidade = 0;
        c.nome[0] = '\0';
        c.func[0] = '\0';

        // 1. extração do nome (letras maiúsculas)
        int n_idx = 0;
        for (int i = 0; line[i] != '\0'; i++) {
            if (isupper(line[i])) {
                c.nome[n_idx++] = line[i];
            }
        }
        c.nome[n_idx] = '\0';
        padString(c.nome);

        // 2. extração da quantidade da população
        char pop_str[20];
        int p_idx = 0;
        for (int i = 0; line[i] != '\0'; i++) {
            if (isdigit(line[i])) {
                pop_str[p_idx++] = line[i];
            }
        }
        pop_str[p_idx] = '\0';
        if (p_idx > 0) {
            c.populacao = atoi(pop_str);
        } else {
            c.populacao = 0;
        }

        // 3. extração da periculosidade (número de *)
        int p_count = 0;
        for (int i = 0; line[i] != '\0'; i++) {
            if (line[i] == '*') {
                p_count++;
            }
        }
        c.periculosidade = p_count;

        // 4. extração da função (a partir de espaço duplo)
        int f_idx = 0;
        char func_buff[50];
        for (int i = 0; line[i] != '\0' && line[i+1] != '\0'; i++) {
            if (line[i] == ' ' && line[i+1] == ' ') {
                if (line[i+2] != '\0') {
                    func_buff[f_idx++] = line[i+2];
                }
            }
        }
        func_buff[f_idx] = '\0';
        padString(func_buff);
        strcpy(c.func, func_buff);

        if (num_cidadelas < MAX_CIDADELAS) {
            cidadelas[num_cidadelas++] = c;
        }
    }

    if (!has_key || key < 1 || key > num_cidadelas) {
        printf("Gingrey ainda não foi achada, vamos esperar mais um pouco.\n");
    } else {
        qsort(cidadelas, num_cidadelas, sizeof(cidadela), cmpCidadelas);

        int target_index = key - 1;
        cidadela c = cidadelas[target_index];
        char periculosidade_str[10];
        for (int i = 0; i < c.periculosidade; i++) {
            periculosidade_str[i] = '*';
        }
        periculosidade_str[c.periculosidade] = '\0';

        printf("Gingrey foi encontrada em %s, uma cidadela com %d mil habitantes cuja função é %s e periculosidade %s",
               c.nome, c.populacao, c.func, periculosidade_str);

        int cond1, cond2;
        if (c.populacao >= 1000){
            cond1 = 1;
        } else {
            cond1 = 0;
        }
        if (c.periculosidade > 3){
            cond2 = 1;
        } else {
            cond2 = 0;
        }

        if (cond1 && cond2) {
            printf(". Talvez seja melhor desistir...\n");
        } else if (cond1) {
            printf(". Um lugar denso, vai ser difícil achar ela.\n");
        } else if (cond2) {
            printf(". Vai ser complicado entrar lá.\n");
        } else {
            printf(".\n");
        }
    }

    return 0;
}
