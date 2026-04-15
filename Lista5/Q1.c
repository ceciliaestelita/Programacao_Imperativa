#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR 2000

// recebe a matriz de strings e a quantidade n e retorna o tamanho da string mesclada
int total_len(char strings[][MAX_STR], int n) {
    int total = 0;
    for (int i = 0; i < n; i++)     // percorre as strings e soma o tamanho no tamanho total da string mesclada
        total += strlen(strings[i]);
    return total;
}

// retorna um ponteiro
char *mesclar(char strings[][MAX_STR], int n) {
    int total = total_len(strings, n);      // manda pra função de calcular o tamanho da string mesclada

    char *merged = malloc(total + 1);       // aloca no endereço de merged o tamanho da string mesclada + o espaço do \0
    if (!merged) {                          // se não foi possível alocar, msg de erro e retorna ponteiro nulo
        fprintf(stderr, "Erro de alocação\n");
        return NULL;
    }

    int pos = 0;    // próxima posição disponível em merged

    int *indices = calloc(n, sizeof(int));      // zera a memória do endereço de indices e aloca o tamanho de int (total)
    if (!indices) {
        free(merged);       // se não foi possível alocar, libera merged e retorna ponteiro nulo
        fprintf(stderr, "Erro de alocação\n");
        return NULL;
    }

    int restam = n;         // quantas strings ainda têm caracteres
    while (restam > 0) {    // enquanto ainda tiver string com caractere sobrando, percorre as strings e verifica se a string i já acabou 
        for (int i = 0; i < n; i++) {
            if (indices[i] < (int)strlen(strings[i])) {
                merged[pos++] = strings[i][indices[i]++];
                if (indices[i] == (int)strlen(strings[i]))
                    restam--;
            }
        }
    }
    merged[pos] = '\0';

    free(indices);  // libera os indices e retorna a string mesclada
    return merged;
}

// aloca e copia
char *fundir(char *merged) {
    int len = strlen(merged); // define o mesmo tamanho 

    char *tmp = (char*)malloc(len + 1);    // aloca na memória a mesma quantidade de espaço de merged
    if (!tmp) {
        fprintf(stderr, "Erro de alocação\n");
        return NULL;
    }
    strcpy(tmp, merged);    // copia merged em tmp

    int i = 0;
    // Enquanto não chegarmos ao fim da string
    while (i < (int)strlen(tmp) - 1 && strlen(tmp) > 1) {  
        if (tmp[i] == tmp[i + 1]) {
            char novo = (tmp[i] == 'z') ? 'a' : tmp[i] + 1;
            tmp[i] = novo;

            int j = i + 1;
            while (tmp[j] != '\0') {
                tmp[j] = tmp[j + 1];
                j++;
            }

            char *novo_tmp = realloc(tmp, strlen(tmp) + 1);
            if (novo_tmp) tmp = novo_tmp;

            // não muda i — só verifica se o novo char funde com o anterior
            if (i > 0) i--;

        } else {
            i++;
        }
    }

    return tmp;
}

int main() {
    int n;
    scanf("%d", &n);

    // array de arrays (matriz)
    char (*strings)[MAX_STR] = malloc(n * sizeof(*strings));
    if (!strings) {
        fprintf(stderr, "Erro de alocação\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        scanf("%1023s", strings[i]);
    }

    char *merged = mesclar(strings, n);
    if (!merged) {
        free(strings);
        return 1;
    }
    printf("%s\n", merged);

    char *resultado = fundir(merged);
    if (resultado) {
        printf("%s\n", resultado);
        free(resultado);
    }
    
    free(merged);
    free(strings);

    return 0;
}
