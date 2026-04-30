#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    FOGO = 0,
    AGUA,
    ELETRICIDADE,
    PLANTA
} TipoElemental;

// struct do pokemon
typedef struct {
    int id;
    char nome[100];
    TipoElemental tipo;
    int xp;
    int ataque;
} Pokemon;

// struct do treinador
typedef struct {
    char nome[100];
    char cpf[50];
    int idade;
    int ordem_cadastro;   // pra desempatar
    Pokemon *pokemons;
    int num_pokemons;
    int nivel;
} Treinador;

// struct das funções
typedef struct {
    void (*cadTreinador)(Treinador **, int *, int *, char *, char *, int);
    void (*cadPokemon)(Treinador *, int, char *, int, char *, int, int, int);
    void (*listarClassificacao)(Treinador *, int);
    void (*removerTreinador)(Treinador **, int *, char *);
    void (*atualizarPokemon)(Treinador *, int, char *, int, char *, int, int, int);
    void (*freeMem)(Treinador **, int *);
} SistemaOps;

// funções auxiliares  
const char *tipoParaString(TipoElemental tipo) {
    switch (tipo) {
        case FOGO:        return "Fogo";
        case AGUA:        return "Agua";
        case ELETRICIDADE: return "Eletricidade";
        case PLANTA:      return "Planta";
        default:          return "Desconhecido";
    }
}

TipoElemental intParaTipo(int t) {
    switch (t) {
        case 0: return FOGO;
        case 1: return AGUA;
        case 2: return ELETRICIDADE;
        case 3: return PLANTA;
        default: return FOGO;
    }
}

int calcularNivel(Treinador *t) {
    int nivel = 0;
    for (int i = 0; i < t->num_pokemons; i++) {
        nivel += (2 * t->pokemons[i].xp) + t->pokemons[i].ataque;
    }
    return nivel;
}

int forcaPokemon(Pokemon *p) {
    return (2 * p->xp) + p->ataque;
}

Treinador *buscarTreinador(Treinador *treinadores, int num_treinadores, char *cpf) {
    for (int i = 0; i < num_treinadores; i++) {
        if (strcmp(treinadores[i].cpf, cpf) == 0) {
            return &treinadores[i];
        }
    }
    return NULL;
}

// implementação das operações
void cadTreinador(Treinador **treinadores, int *num_treinadores,
                        int *contador_ordem, char *nome, char *cpf, int idade) {
    // Verifica duplicata de CPF  
    if (buscarTreinador(*treinadores, *num_treinadores, cpf) != NULL) {
        return;
    }

    *treinadores = realloc(*treinadores, (*num_treinadores + 1) * sizeof(Treinador));
    Treinador *t = &(*treinadores)[*num_treinadores];

    strncpy(t->nome, nome, 99);
    t->nome[99] = '\0';
    strncpy(t->cpf, cpf, 49);
    t->cpf[49] = '\0';
    t->idade = idade;
    t->ordem_cadastro = (*contador_ordem)++;
    t->pokemons = NULL;
    t->num_pokemons = 0;
    t->nivel = 0;

    (*num_treinadores)++;
}

void cadPokemon(Treinador *treinadores, int num_treinadores,
                      char *cpf, int id, char *nome_pokemon,
                      int xp, int ataque, int tipo_int) {
    Treinador *t = buscarTreinador(treinadores, num_treinadores, cpf);
    if (t == NULL) return;

    // Verifica ID duplicado para este treinador  
    for (int i = 0; i < t->num_pokemons; i++) {
        if (t->pokemons[i].id == id) return;
    }

    t->pokemons = realloc(t->pokemons, (t->num_pokemons + 1) * sizeof(Pokemon));
    Pokemon *p = &t->pokemons[t->num_pokemons];

    p->id = id;
    strncpy(p->nome, nome_pokemon, 99);
    p->nome[99] = '\0';
    p->xp = xp;
    p->ataque = ataque;
    p->tipo = intParaTipo(tipo_int);

    t->num_pokemons++;
    t->nivel = calcularNivel(t);
}

// Comparador para ordenação de Pokémons  
int compararPokemon(const void *a, const void *b) {
    const Pokemon *pa = (const Pokemon *)a;
    const Pokemon *pb = (const Pokemon *)b;
    int fa = forcaPokemon((Pokemon *)pa);
    int fb = forcaPokemon((Pokemon *)pb);
    if (fb != fa) return fb - fa; // maior força primeiro  
    return 0; // empate: mantém ordem de inserção (qsort não é estável, mas usamos índice)  
}

// Ordenação estável de pokémons por força (insertion sort para estabilidade)  
void ordenarPokemons(Pokemon *arr, int n) {
    for (int i = 1; i < n; i++) {
        Pokemon chave = arr[i];
        int j = i - 1;
        while (j >= 0 && forcaPokemon(&arr[j]) < forcaPokemon(&chave)) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = chave;
    }
}

void listarClassificacao(Treinador *treinadores, int num_treinadores) {
    printf("Classificação atual\n");

    // Cria array de índices para ordenar treinadores sem modificar original  
    int *idx = malloc(num_treinadores * sizeof(int));
    for (int i = 0; i < num_treinadores; i++) idx[i] = i;

    // Insertion sort estável por nível (maior primeiro), desempate por ordem de cadastro  
    for (int i = 1; i < num_treinadores; i++) {
        int chave = idx[i];
        int j = i - 1;
        while (j >= 0) {
            Treinador *ta = &treinadores[idx[j]];
            Treinador *tb = &treinadores[chave];
            if (ta->nivel < tb->nivel ||
                (ta->nivel == tb->nivel && ta->ordem_cadastro > tb->ordem_cadastro)) {
                idx[j + 1] = idx[j];
                j--;
            } else {
                break;
            }
        }
        idx[j + 1] = chave;
    }

    for (int i = 0; i < num_treinadores; i++) {
        Treinador *t = &treinadores[idx[i]];
        printf("T: %s, CPF: %s, Nivel: %d\n", t->nome, t->cpf, t->nivel);

        // Cópia dos pokémons para ordenar sem alterar o original  
        Pokemon *pks = malloc(t->num_pokemons * sizeof(Pokemon));
        memcpy(pks, t->pokemons, t->num_pokemons * sizeof(Pokemon));
        ordenarPokemons(pks, t->num_pokemons);

        for (int j = 0; j < t->num_pokemons; j++) {
            printf("  P: %d, %s, %d, %d, %s\n",
                   pks[j].id, pks[j].nome, pks[j].xp, pks[j].ataque,
                   tipoParaString(pks[j].tipo));
        }
        free(pks);
    }

    free(idx);
}

void removerTreinador(Treinador **treinadores, int *num_treinadores, char *cpf) {
    int pos = -1;
    for (int i = 0; i < *num_treinadores; i++) {
        if (strcmp((*treinadores)[i].cpf, cpf) == 0) {
            pos = i;
            break;
        }
    }
    if (pos == -1) return;

    free((*treinadores)[pos].pokemons);

    // Desloca os elementos  
    for (int i = pos; i < *num_treinadores - 1; i++) {
        (*treinadores)[i] = (*treinadores)[i + 1];
    }
    (*num_treinadores)--;

    if (*num_treinadores == 0) {
        free(*treinadores);
        *treinadores = NULL;
    } else {
        *treinadores = realloc(*treinadores, *num_treinadores * sizeof(Treinador));
    }
}

void atualizarPokemon(Treinador *treinadores, int num_treinadores,
                      char *cpf, int id, char *novo_nome,
                      int novo_xp, int novo_ataque, int novo_tipo_int) {
    Treinador *t = buscarTreinador(treinadores, num_treinadores, cpf);
    if (t == NULL) return;

    for (int i = 0; i < t->num_pokemons; i++) {
        if (t->pokemons[i].id == id) {
            strncpy(t->pokemons[i].nome, novo_nome, 99);
            t->pokemons[i].nome[99] = '\0';
            t->pokemons[i].xp = novo_xp;
            t->pokemons[i].ataque = novo_ataque;
            t->pokemons[i].tipo = intParaTipo(novo_tipo_int);
            t->nivel = calcularNivel(t);
            return;
        }
    }
}

void freeMem(Treinador **treinadores, int *num_treinadores) {
    for (int i = 0; i < *num_treinadores; i++) {
        free((*treinadores)[i].pokemons);
    }
    free(*treinadores);
    *treinadores = NULL;
    *num_treinadores = 0;
}

// main
int main(void) {
    Treinador *treinadores = NULL;
    int num_treinadores = 0;
    int contador_ordem = 0;

    // Struct de funções obrigatória  
    SistemaOps ops = {
        cadTreinador,
        cadPokemon,
        listarClassificacao,
        removerTreinador,
        atualizarPokemon,
        freeMem
    };

    int comando;
    while (scanf("%d", &comando) == 1) {
        if (comando == 0) break;

        if (comando == 1) {
            char nome[100], cpf[50];
            int idade;
            scanf("%s %s %d", nome, cpf, &idade);
            ops.cadTreinador(&treinadores, &num_treinadores,
                                   &contador_ordem, nome, cpf, idade);

        } else if (comando == 2) {
            char cpf[50], nome_pokemon[100];
            int id, xp, ataque, tipo;
            scanf("%s %d %s %d %d %d", cpf, &id, nome_pokemon, &xp, &ataque, &tipo);
            ops.cadPokemon(treinadores, num_treinadores,
                                 cpf, id, nome_pokemon, xp, ataque, tipo);

        } else if (comando == 3) {
            ops.listarClassificacao(treinadores, num_treinadores);

        } else if (comando == 4) {
            char cpf[50];
            scanf("%s", cpf);
            ops.removerTreinador(&treinadores, &num_treinadores, cpf);

        } else if (comando == 5) {
            char cpf[50], nome_pokemon[100];
            int id, xp, ataque, tipo;
            scanf("%s %d %s %d %d %d", cpf, &id, nome_pokemon, &xp, &ataque, &tipo);
            ops.atualizarPokemon(treinadores, num_treinadores,
                                 cpf, id, nome_pokemon, xp, ataque, tipo);
        }
    }

    ops.freeMem(&treinadores, &num_treinadores);
    return 0;
}
