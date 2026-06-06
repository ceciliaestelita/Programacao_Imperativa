#include <stdio.h>
#include <stdlib.h>

// structs das tarefas
typedef struct Tarefa {
    int id;
    int prioridade;
    struct Tarefa *prox;
} Tarefa;

Tarefa *head = NULL;
Tarefa *tail = NULL;

// alocação da memória
void inserir(int id, int prioridade) {
    Tarefa *nova = (Tarefa *)malloc(sizeof(Tarefa));
    if (nova == NULL) {
        printf("Erro: falha ao alocar memória.\n");
        return;
    }
    nova->id = id;
    nova->prioridade = prioridade;
    nova->prox = NULL;

    if (tail == NULL) {
        head = nova;
        tail = nova;
    } else {
        tail->prox = nova;
        tail = nova;
    }
}

// remoção e definição da prioridade
void remover() {
    if (head == NULL) {
        printf("Fila vazia\n");
        return;
    }

    Tarefa *removida = head;
    printf("Removida: id=%d prioridade=%d\n", removida->id, removida->prioridade);

    head = head->prox;
    if (head == NULL) {
        tail = NULL;
    }

    free(removida);
}

// lista os itens
void listar() {
    if (head == NULL) {
        printf("Fila vazia\n");
        return;
    }

    Tarefa *atual = head;
    while (atual != NULL) {
        printf("id=%d prioridade=%d\n", atual->id, atual->prioridade);
        atual = atual->prox;
    }
}

// main
int main() {
    char comando;
    int id, prioridade;

    while (scanf(" %c", &comando) == 1) {
        switch (comando) {
            case 'I':
                if (scanf("%d %d", &id, &prioridade) == 2) {
                    inserir(id, prioridade);
                }
                break;
            case 'R':
                remover();
                break;
            case 'L':
                listar();
                break;
            case 'F':
                // libera memória restante antes de terminar 
                while (head != NULL) {
                    Tarefa *tmp = head;
                    head = head->prox;
                    free(tmp);
                }
                return 0;
            default:
                break;
        }
    }

    return 0;
}
